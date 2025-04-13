#include "vtkGaussianSurfaceMapper.h"


#include "vtkOpenGLRenderWindow.h"
#include "vtkOpenGLShaderCache.h"
#include "vtkShaderProgram.h"
#include "vtkRenderer.h"
#include "vtkCamera.h"
#include "vtkRenderWindow.h"
#include "vtkActor.h"
#include "vtkOpenGLCamera.h"
#include "vtkSmartPointer.h"
#include "vtkNew.h"
#include "vtkObjectFactory.h"
#include "vtkInformation.h"
#include "vtkGaussianSplattionPlyReader.h"
#include "vtkGaussianSplatter.h"
#include "vtk_glew.h"
namespace GS {
std::string vtkGaussianSurface_fs = R"(
/*
 * Copyright (C) 2023, Inria
 * GRAPHDECO research group, https://team.inria.fr/graphdeco
 * All rights reserved.
 *
 * This software is free for non-commercial, research and evaluation use
 * under the terms of the LICENSE.md file.
 *
 * For inquiries contact sibr@inria.fr and/or George.Drettakis@inria.fr
 */
//VTK::System::Dec
//VTK::Output::Dec

uniform mat4 MVP;
uniform float alpha_limit;
uniform int stage;
uniform vec3  rayOrigin;

in vec3 worldPos;
in vec3 ellipsoidCenter;
in vec3 ellipsoidScale;
in mat3 ellipsoidRotation;
in vec3 colorVert;
in float alphaVert;
in flat int boxID;

//layout (location = 0) out vec4 out_color;
//layout (location = 1) out uint out_id;

vec3 closestEllipsoidIntersection(vec3 rayDirection, out vec3 normal) {
  // Convert ray to ellipsoid space
  dvec3 localRayOrigin = (rayOrigin - ellipsoidCenter) * ellipsoidRotation;
  dvec3 localRayDirection = normalize(rayDirection * ellipsoidRotation);

  dvec3 oneover = double(1) / dvec3(ellipsoidScale);

  // Compute coefficients of quadratic equation
  double a = dot(localRayDirection * oneover, localRayDirection * oneover);
  double b = 2.0 * dot(localRayDirection * oneover, localRayOrigin * oneover);
  double c = dot(localRayOrigin * oneover, localRayOrigin * oneover) - 1.0;

  // Compute discriminant
  double discriminant = b * b - 4.0 * a * c;

  // If discriminant is negative, there is no intersection
  if (discriminant < 0.0) {
    return vec3(0.0);
  }

  // Compute two possible solutions for t
  float t1 = float((-b - sqrt(discriminant)) / (2.0 * a));
  float t2 = float((-b + sqrt(discriminant)) / (2.0 * a));

  // Take the smaller positive solution as the closest intersection
  float t = min(t1, t2);

  // Compute intersection point in ellipsoid space
  vec3 localIntersection = vec3(localRayOrigin + t * localRayDirection);

  // Compute normal vector in ellipsoid space
  vec3 localNormal = normalize(localIntersection / ellipsoidScale);

  // Convert normal vector to world space
  normal = normalize(ellipsoidRotation * localNormal);

  // Convert intersection point back to world space
  vec3 intersection = ellipsoidRotation * localIntersection + ellipsoidCenter;

  return intersection;
}

void main(void) {
    vec3 dir = normalize(worldPos - rayOrigin);

    vec3 normal;
    vec3 intersection = closestEllipsoidIntersection(dir, normal);
    float align = max(0.4, dot(-dir, normal));

    out_color = vec4(1, 0, 0, 1);

    if(intersection == vec3(0))
        discard;

    vec4 newPos = MVP * vec4(intersection, 1);
    newPos /= newPos.w;

    gl_FragDepth = newPos.z;

    float a = stage == 0 ? 1.0 : 0.05f;

    gl_FragData[0] = vec4(align * colorVert, a);
    //out_id = boxID;
}

)";

std::string vtkGaussianSurface_vs = R"(
/*
 * Copyright (C) 2023, Inria
 * GRAPHDECO research group, https://team.inria.fr/graphdeco
 * All rights reserved.
 *
 * This software is free for non-commercial, research and evaluation use
 * under the terms of the LICENSE.md file.
 *
 * For inquiries contact sibr@inria.fr and/or George.Drettakis@inria.fr
 */

//VTK::System::Dec
//VTK::Output::Dec

uniform mat4 MVP;
uniform float alpha_limit;
uniform int stage;

layout (std430, binding = 0) buffer BoxCenters {
    float centers[];
};
layout (std430, binding = 1) buffer Rotations {
    vec4 rots[];
};
layout (std430, binding = 2) buffer Scales {
    float scales[];
};
layout (std430, binding = 3) buffer Alphas {
    float alphas[];
};
layout (std430, binding = 4) buffer Colors {
    float colors[];
};

mat3 quatToMat3(vec4 q) {
  float qx = q.y;
  float qy = q.z;
  float qz = q.w;
  float qw = q.x;

  float qxx = qx * qx;
  float qyy = qy * qy;
  float qzz = qz * qz;
  float qxz = qx * qz;
  float qxy = qx * qy;
  float qyw = qy * qw;
  float qzw = qz * qw;
  float qyz = qy * qz;
  float qxw = qx * qw;

  return mat3(
    vec3(1.0 - 2.0 * (qyy + qzz), 2.0 * (qxy - qzw), 2.0 * (qxz + qyw)),
    vec3(2.0 * (qxy + qzw), 1.0 - 2.0 * (qxx + qzz), 2.0 * (qyz - qxw)),
    vec3(2.0 * (qxz - qyw), 2.0 * (qyz + qxw), 1.0 - 2.0 * (qxx + qyy))
  );
}

const vec3 boxVertices[8] = vec3[8](
    vec3(-1, -1, -1),
    vec3(-1, -1,  1),
    vec3(-1,  1, -1),
    vec3(-1,  1,  1),
    vec3( 1, -1, -1),
    vec3( 1, -1,  1),
    vec3( 1,  1, -1),
    vec3( 1,  1,  1)
);

const int boxIndices[36] = int[36](
    0, 1, 2, 1, 3, 2,
    4, 6, 5, 5, 6, 7,
    0, 2, 4, 4, 2, 6,
    1, 5, 3, 5, 7, 3,
    0, 4, 1, 4, 5, 1,
    2, 3, 6, 3, 7, 6
);

out vec3 worldPos;
out vec3 ellipsoidCenter;
out vec3 ellipsoidScale;
out mat3 ellipsoidRotation;
out vec3 colorVert;
out float alphaVert;
out flat int boxID;

void main() {
    boxID = gl_InstanceID;
    ellipsoidCenter = vec3(centers[3 * boxID + 0], centers[3 * boxID + 1], centers[3 * boxID + 2]);
    float a = alphas[boxID];
    alphaVert = a;
    ellipsoidScale = vec3(scales[3 * boxID + 0], scales[3 * boxID + 1], scales[3 * boxID + 2]);
    ellipsoidScale = 2 * ellipsoidScale;

    vec4 q = rots[boxID];
    ellipsoidRotation = transpose(quatToMat3(q));

    int vertexIndex = boxIndices[gl_VertexID];
    worldPos = ellipsoidRotation * (ellipsoidScale * boxVertices[vertexIndex]);
    worldPos += ellipsoidCenter;

    float r = colors[boxID * 48 + 0] * 0.2 + 0.5;
    float g = colors[boxID * 48 + 1] * 0.2 + 0.5;
    float b = colors[boxID * 48 + 2] * 0.2 + 0.5;

    colorVert = vec3(r, g, b);

    if((stage == 0 && a < alpha_limit) || (stage == 1 && a >= alpha_limit))
        gl_Position = vec4(0,0,0,0);
    else
        gl_Position = MVP * vec4(worldPos, 1);
}
)";

vtkGaussianData::vtkGaussianData(int num_gaussians, float* mean_data, float* rot_data, float* scale_data, float* alpha_data, float* color_data)
{
    meanBuffer = 0;
    _num_gaussians = num_gaussians;
    glCreateBuffers(1, &meanBuffer);
    glCreateBuffers(1, &rotBuffer);
    glCreateBuffers(1, &scaleBuffer);
    glCreateBuffers(1, &alphaBuffer);
    glCreateBuffers(1, &colorBuffer);
    glNamedBufferStorage(meanBuffer, num_gaussians * 3 * sizeof(float), mean_data, 0);
    glNamedBufferStorage(rotBuffer, num_gaussians * 4 * sizeof(float), rot_data, 0);
    glNamedBufferStorage(scaleBuffer, num_gaussians * 3 * sizeof(float), scale_data, 0);
    glNamedBufferStorage(alphaBuffer, num_gaussians * sizeof(float), alpha_data, 0);
    glNamedBufferStorage(colorBuffer, num_gaussians * sizeof(float) * 48, color_data, 0);
}

void vtkGaussianData::render(int G) const
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, meanBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, rotBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, scaleBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, alphaBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, colorBuffer);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, G);
}


class vtkGaussianSurfaceMapper::Private : public vtkObject{

public:
    static Private* New();
    void ReleaseGraphicsResources(vtkWindow* renWind)
    {

    }

    void SetMapper(vtkGaussianSurfaceMapper* mapper) {}

    void setData(vtkDataSet*, vtkDataArray*, vtkDataArray*);

    void Process(vtkRenderer*, vtkActor*, bool);

protected:
    Private();
    ~Private();

   bool PrepareGLBuffer(vtkRenderer* ren, vtkActor*);

   vtkOpenGLBufferObject* IndexBufferObject;
   vtkOpenGLFramebufferObject* CurrentBuffer;
   vtkOpenGLBufferObject* FrameBuffer;
   vtkOpenGLShaderCache* ShaderCache;

};

void vtkGaussianSurfaceMapper::PrintSelf(std::ostream &os, vtkIndent indent)
{

}

vtkStandardNewMacro(vtkGaussianSurfaceMapper)
vtkGaussianSurfaceMapper::vtkGaussianSurfaceMapper()
{
    this->Program = nullptr;
    this->ShaderCache = nullptr;


    std::vector<Pos> pos;
    std::vector<Rot> rot;
    std::vector<Scale> scale;
    std::vector<float> opacity;
    std::vector<SHs<3>> shs;
    Vector3f _scenemin, _scenemax;
    count = loadPly<3>("2D_Data/point_cloud.ply", pos, shs, opacity, scale, rot, _scenemin, _scenemax);
    int P = count;
    gData = new vtkGaussianData(P,
    (float*)pos.data(),
    (float*)rot.data(),
    (float*)scale.data(),
    opacity.data(),
    (float*)shs.data());
    // 后期尝试转换为vtkOpengl格式，
    glCreateTextures(GL_TEXTURE_2D, 1, &idTexture);
    glTextureParameteri(idTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(idTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glCreateTextures(GL_TEXTURE_2D, 1, &colorTexture);
    glTextureParameteri(colorTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(colorTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glCreateFramebuffers(1, &fbo);
    glCreateRenderbuffers(1, &depthBuffer);

    makeFBO(800, 800);

    this->clearProg = glCreateProgram();
    const char* clearShaderSrc = R"(
    #version 430

    layout(local_size_x = 256, local_size_y = 1, local_size_z = 1) in;

    layout(std430, binding = 0) buffer IntArray {
        int arr[];
    };

    layout(location = 0) uniform int size;

    void main() {
        uint index = gl_GlobalInvocationID.x;
        if (index < size) {
            arr[index] = 0;
        }
    }
    )";
    clearShader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(clearShader, 1, &clearShaderSrc, nullptr);
    glAttachShader(clearProg, clearShader);
    glLinkProgram(clearProg);

}

vtkGaussianSurfaceMapper::~vtkGaussianSurfaceMapper()
{

}

void vtkGaussianSurfaceMapper::Render(vtkRenderer *ren, vtkActor *vol)
{
    if(!this->prepareBuffer(ren, vol))
    {
        return ;
    }
    this->process(count, *gData, ren, vol, 0.2f);
}
//----------------------------------------------------------------------------
int vtkGaussianSurfaceMapper::FillInputPortInformation(int vtkNotUsed(port), vtkInformation* info)
{
  info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkDataSet");
  return 1;
}
void vtkGaussianSurfaceMapper::ReleaseGraphicsResources(vtkWindow *)
{

}


void DrawGaussian(vtkRenderer* ren, vtkActor* actor)
{

}
int vtkGaussianSurfaceMapper::process(int G, const vtkGaussianData &mesh, vtkRenderer* ren, vtkActor* actor, float limit)
{

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    vtkOpenGLCamera* eye = vtkOpenGLCamera::SafeDownCast(ren->GetActiveCamera());

    vtkOpenGLRenderWindow* renWin = vtkOpenGLRenderWindow::SafeDownCast(ren->GetRenderWindow());
    const int* size = renWin->GetSize();
    unsigned int width = static_cast<unsigned int>(size[0]);
    unsigned int height = static_cast<unsigned int>(size[1]);
    if (width != resX || width != resY)
    {
        makeFBO(width,height);
    }

    // Solid pass
    GLuint drawBuffers[2];
    drawBuffers[0] = GL_COLOR_ATTACHMENT0;
    drawBuffers[1] = GL_COLOR_ATTACHMENT1;
    glDrawBuffers(2, drawBuffers);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    this->ShaderCache->ReadyShaderProgram(this->Program); //_shader.begin();
    vtkMatrix4x4* wcdc;
    vtkMatrix4x4* wcvc;
    vtkMatrix3x3* norms;
    vtkMatrix4x4* vcdc;
    eye->GetKeyMatrices(ren, wcvc, norms, vcdc, wcdc);
    this->Program->SetUniformMatrix("MVP",wcdc); // _paramMVP.set(eye.viewproj());
    this->Program->SetUniform3f("rayOrigin", eye->GetPosition()); //_paramCamPos.set(eye.position());
    this->Program->SetUniformf("alpha_limit", limit);//_paramLimit.set(limit);
    this->Program->SetUniformi("stage", 0); //_paramStage.set(0);


    mesh.render(G);

    // Simple additive blendnig (no order)
    glDrawBuffers(1, drawBuffers);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    this->Program->SetUniformi("stage", 1); //_paramStage.set(1);

    mesh.render(G);

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    //_shader.end();

    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glBlitNamedFramebuffer(
        fbo, 0,
        0, 0, resX, resY,
        0, 0, resX, resY,
        GL_COLOR_BUFFER_BIT, GL_NEAREST);

    return 0;
}

void vtkGaussianSurfaceMapper::makeFBO(int w, int h)
{
    resX = w;
    resY = h;

    glBindTexture(GL_TEXTURE_2D, idTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, resX, resY, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resX, resY, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glNamedRenderbufferStorage(depthBuffer, GL_DEPTH_COMPONENT, resX, resY);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, idTexture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
}

bool vtkGaussianSurfaceMapper::prepareBuffer(vtkRenderer *ren, vtkActor *actor)
{
    vtkOpenGLRenderWindow* renWin = vtkOpenGLRenderWindow::SafeDownCast(ren->GetRenderWindow());
    const int* size = renWin->GetSize();
    unsigned int width = static_cast<unsigned int>(size[0]);
    unsigned int height = static_cast<unsigned int>(size[1]);

    if (!this->ShaderCache)
    {
        this->ShaderCache = renWin->GetShaderCache();

    }

    if (!this->Program)
    {
        this->ShaderCache->ReleaseCurrentShader();
        this->Program = this->ShaderCache->ReadyShaderProgram(
        vtkGaussianSurface_vs.c_str(), vtkGaussianSurface_fs.c_str(), "");
        this->Program->Register(this);
    }


    return this->Program && this->ShaderCache;
}

}
