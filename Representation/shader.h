#ifndef SHADER_H
#define SHADER_H
#include <string>

std::string vtkStreamLines_fs = R"(
// clang-format off
//VTK::System::Dec
//VTK::Output::Dec
// clang-format on

uniform vec3 color;
uniform int scalarVisibility;

varying vec3 vertexColorVSOutput;

void main(void)
{
  if (scalarVisibility != 0)
    gl_FragData[0] = vec4(vertexColorVSOutput, 1.);
  else
    gl_FragData[0] = vec4(color, 1.);
}

)";
std::string vtkStreamLines_gs = R"(
// clang-format off
//VTK::System::Dec
//VTK::Output::Dec
// clang-format on

in vec3 vertexColorVSOutput[];

out vec3 vertexColorGSOutput;

uniform vec2 lineWidthNVC;

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

void main()
{
  // compute the lines direction
  vec2 normal = normalize(gl_in[1].gl_Position.xy / gl_in[1].gl_Position.w -
    gl_in[0].gl_Position.xy / gl_in[0].gl_Position.w);

  // rotate 90 degrees
  normal = vec2(-1.0 * normal.y, normal.x);

  for (int j = 0; j < 4; j++)
  {
    int i = j / 2;

    vertexColorGSOut‘put = vertexColorVSOutput[i];

    gl_Position = vec4(gl_in[i].gl_Position.xy +
        (lineWidthNVC * normal) * ((j + 1) % 2 - 0.5) * gl_in[i].gl_Position.w,
      gl_in[i].gl_Position.z, gl_in[i].gl_Position.w);

    EmitVertex();
  }
  EndPrimitive();
}

)";
std::string vtkStreamLines_vs = R"(
//VTK::System::Dec
//VTK::Output::Dec

attribute vec4 vertexMC;
attribute vec3 scalarColor;

uniform mat4 MCDCMatrix;

varying vec3 vertexColorVSOutput;

void main(void)
{
  vertexColorVSOutput = scalarColor.rgb;
  gl_Position = MCDCMatrix * vertexMC;
}

)";
std::string vtkStreamLinesBlending_fs = R"(
//VTK::System::Dec
//VTK::Output::Dec

varying vec2 tcoordVC;

uniform sampler2D prev;
uniform sampler2D current;
uniform float alpha;

void main(void)
{
  vec4 pc = texture2D(prev, tcoordVC);
  vec4 cc = texture2D(current, tcoordVC);
  gl_FragData[0] = pc * alpha + cc;
}
)";
std::string vtkStreamLinesCopy_fs = R"(
//VTK::System::Dec
//VTK::Output::Dec

varying vec2 tcoordVC;

uniform sampler2D source;

void main(void)
{
  gl_FragData[0] = texture2D(source, tcoordVC);
}
)";


#endif // SHADER_H
