#ifndef VTKGAUSSIANSPLATTIONPLYREADER_H
#define VTKGAUSSIANSPLATTIONPLYREADER_H

#include <iostream>
#include <vector>
#include <fstream>
#include "Eigen/Dense"

typedef	Eigen::Matrix<float, 3,			1,Eigen::DontAlign>			Vector3f;
typedef Eigen::Matrix<int, 3,1,Eigen::DontAlign> Vector3i;
typedef Vector3f Pos;
template<int D>
struct SHs
{
    float shs[(D+1)*(D+1)*3];
};
struct Scale
{
    float scale[3];
};
struct Rot
{
    float rot[4];
};
template<int D>
struct RichPoint
{
    Pos pos;
    float n[3];
    SHs<D> shs;
    float opacity;
    Scale scale;
    Rot rot;
};

//float sigmoid(const float m1)
//{
//    return 1.0f / (1.0f + exp(-m1));
//}

//float inverse_sigmoid(const float m1)
//{
//    return log(m1 / (1.0f - m1));
//}

// Load the Gaussians from the given file.
template<int D>
int loadPly(const char* filename,
    std::vector<Pos>& pos,
    std::vector<SHs<3>>& shs,
    std::vector<float>& opacities,
    std::vector<Scale>& scales,
    std::vector<Rot>& rot,
    Vector3f& minn,
    Vector3f& maxx)
{
    std::ifstream infile(filename, std::ios_base::binary);

    if (!infile.good())
        std::cout << "Unable to find model's PLY file, attempted:\n" << filename << std::endl;

    // "Parse" header (it has to be a specific format anyway)
    std::string buff;
    std::getline(infile, buff);
    std::getline(infile, buff);

    std::string dummy;
    std::getline(infile, buff);
    std::stringstream ss(buff);
    int count;
    ss >> dummy >> dummy >> count;

    // Output number of Gaussians contained
    std::cout << "Loading " << count << " Gaussian splats" << std::endl;

    while (std::getline(infile, buff))
        if (buff.compare("end_header") == 0)
            break;

    // Read all Gaussians at once (AoS)
    std::vector<RichPoint<D>> points(count);
    infile.read((char*)points.data(), count * sizeof(RichPoint<D>));

    // Resize our SoA data
    pos.resize(count);
    shs.resize(count);
    scales.resize(count);
    rot.resize(count);
    opacities.resize(count);

    // Gaussians are done training, they won't move anymore. Arrange
    // them according to 3D Morton order. This means better cache
    // behavior for reading Gaussians that end up in the same tile
    // (close in 3D --> close in 2D).
    minn = Vector3f(FLT_MAX, FLT_MAX, FLT_MAX);
    maxx = -minn;
    for (int i = 0; i < count; i++)
    {
        maxx = maxx.cwiseMax(points[i].pos);
        minn = minn.cwiseMin(points[i].pos);
    }
    std::vector<std::pair<uint64_t, int>> mapp(count);
    for (int i = 0; i < count; i++)
    {
        Vector3f rel = (points[i].pos - minn).array() / (maxx - minn).array();
        Vector3f scaled = ((float((1 << 21) - 1)) * rel);
        Vector3i xyz = scaled.cast<int>();

        uint64_t code = 0;
        for (int i = 0; i < 21; i++) {
            code |= ((uint64_t(xyz.x() & (1 << i))) << (2 * i + 0));
            code |= ((uint64_t(xyz.y() & (1 << i))) << (2 * i + 1));
            code |= ((uint64_t(xyz.z() & (1 << i))) << (2 * i + 2));
        }

        mapp[i].first = code;
        mapp[i].second = i;
    }
    auto sorter = [](const std::pair < uint64_t, int>& a, const std::pair < uint64_t, int>& b) {
        return a.first < b.first;
    };
    std::sort(mapp.begin(), mapp.end(), sorter);

    // Move data from AoS to SoA
    int SH_N = (D + 1) * (D + 1);
    for (int k = 0; k < count; k++)
    {
        int i = mapp[k].second;
        pos[k] = points[i].pos;

        // Normalize quaternion
        float length2 = 0;
        for (int j = 0; j < 4; j++)
            length2 += points[i].rot.rot[j] * points[i].rot.rot[j];
        float length = sqrt(length2);
        for (int j = 0; j < 4; j++)
            rot[k].rot[j] = points[i].rot.rot[j] / length;

        // Exponentiate scale
        for(int j = 0; j < 3; j++)
            scales[k].scale[j] = exp(points[i].scale.scale[j]);

        // Activate alpha1.0f / (1.0f + exp(-m1));
        opacities[k] = 1.0f / (1.0f + exp(-points[i].opacity));

        shs[k].shs[0] = points[i].shs.shs[0];
        shs[k].shs[1] = points[i].shs.shs[1];
        shs[k].shs[2] = points[i].shs.shs[2];
        for (int j = 1; j < SH_N; j++)
        {
            // 球谐函数参数
            shs[k].shs[j * 3 + 0] = points[i].shs.shs[(j - 1) + 3];
            shs[k].shs[j * 3 + 1] = points[i].shs.shs[(j - 1) + SH_N + 2];
            shs[k].shs[j * 3 + 2] = points[i].shs.shs[(j - 1) + 2 * SH_N + 1];
        }
    }
    return count;
}



#endif // VTKGAUSSIANSPLATTIONPLYREADER_H
