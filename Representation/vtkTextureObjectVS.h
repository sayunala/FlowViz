#ifndef vtkTextureObjectVS_h
#define vtkTextureObjectVS_h

std::string vtkTextureObjectVS = R"(
//VTK::System::Dec
in vec4 vertexMC;
in vec2 tcoordMC;
out vec2 tcoordVC;

void main()
{
    tcoordVC = tcoordMC;
    gl_Position = vertexMC;
}
)";

#endif
