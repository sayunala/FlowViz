#ifndef VTKGAUSSIANSURFACEMAPPER_H
#define VTKGAUSSIANSURFACEMAPPER_H

#include <memory>
#include "vtkMapper.h"
#include "vtkShader.h"


class vtkActor;
class vtkDataSet;
class vtkImageData;
class vtkRenderer;
class vtkShaderProgram;
class vtkOpenGLShaderCache;
namespace GS {

class vtkGaussianData
{
public:
    typedef std::shared_ptr<vtkGaussianData>	Ptr;

public:

    /// Constructor.
    vtkGaussianData(int num_gaussians, float* mean_data, float* rot_data, float* scale_data, float* alpha_data, float* color_data);

    void render(int G) const;

private:

    int _num_gaussians;
    unsigned int meanBuffer;
    unsigned int rotBuffer;
    unsigned int scaleBuffer;
    unsigned int alphaBuffer;
    unsigned int colorBuffer;
};


class vtkGaussianSurfaceMapper : public vtkMapper
{
public:
    static vtkGaussianSurfaceMapper* New();
    vtkTypeMacro(vtkGaussianSurfaceMapper, vtkMapper);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    void Render(vtkRenderer* ren, vtkActor* vol) override;

    void ReleaseGraphicsResources(vtkWindow *) override;

    int FillInputPortInformation(int vtkNotUsed(port), vtkInformation* info) override;

protected:

    vtkGaussianSurfaceMapper();
    ~vtkGaussianSurfaceMapper() override;
    void DrawGaussian(vtkRenderer* ren, vtkActor* actor);

    int process(int G, const vtkGaussianData &mesh, vtkRenderer* ren, vtkActor* actor, float limit);

    void makeFBO(int w, int h);

    bool prepareBuffer(vtkRenderer* ren, vtkActor* actor);


    unsigned int idTexture;
    unsigned int colorTexture;
    unsigned int depthBuffer;
    unsigned int fbo;
    int resX, resY;
    vtkOpenGLShaderCache* ShaderCache;
    vtkShaderProgram* Program;
    unsigned int clearProg;
    unsigned int clearShader;

    vtkGaussianData* gData;
    int count;
    class Private;
    Private* Internal;

    friend class Private;

};

}
#endif // VTKGAUSSIANSURFACEMAPPER_H
