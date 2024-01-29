#include <gtest/gtest.h>

#include <algorithm>

#include "../src/vein/vein_generator.hpp"
#include "../src/defines.hpp"

using namespace vein;

static constexpr float radiusTop = 50;
static constexpr float radius = 50;
static constexpr int vLayers = 300;

float radiusLeft = 50;
float radiusRight = 50;

TEST(VeinGeneratorTests, CylinderSkewDoesNotChangeLength)
{
    VeinMesh mesh = VeinGenerator::createCylinder(radiusTop, radius, vLayers, 0.5f, 0.5f);
    EXPECT_EQ(mesh.positions.size() == vLayers * cyl::hLayers, true);
}

TEST(VeinGeneratorTests, LengthCorrespondsToVertexCount)
{
    static constexpr int n = 10;
    VeinMesh mesh1 = VeinGenerator::createCylinder(radiusTop, radius, vLayers, 0, 0);
    VeinMesh mesh2 = VeinGenerator::createCylinder(radiusTop, radius, vLayers + n, 0, 0);
    EXPECT_EQ(mesh1.positions.size() + n * cyl::hLayers == mesh2.positions.size(), true);
}

TEST(VeinGeneratorTests, DifferentArgumentsDoNotChangeIndices)
{
    VeinMesh mesh1 = VeinGenerator::createCylinder(radiusTop, radius, vLayers, 0, 0);
    VeinMesh mesh2 = VeinGenerator::createCylinder(radiusTop + 10, radius - 10, vLayers, 0.2, 0.8);
    EXPECT_EQ(mesh1.indices == mesh2.indices, true);
}

TEST(VeinGeneratorTests, BifurcationRotationDoesNotChangeSize)
{
    VeinMesh mesh = VeinGenerator::createBifurcation(radiusTop, radiusLeft, radiusRight, -0.4, -1.2, 0.9, 0.3);
    EXPECT_EQ(mesh.positions.size() == bif::vLayers * 3 * bif::hLayers, true);
}

auto vecComparator = [](auto& v1, auto& v2)
    {
        if (v1.x == v2.x)
        {
            if (v1.y == v2.y)
            {
                return v1.z < v2.z;
            }
            else
                return v1.y < v2.y;
        }
        else
            return v1.x < v2.x;

    };

auto vecEpsComparator = [](auto& v1, auto& v2)
    {
        static constexpr float eps = 0.00001f;
        return (v1.x - v2.x < eps && v1.x - v2.x > -eps) &&
            (v1.y - v2.y < eps && v1.y - v2.y > -eps) &&
            (v1.z - v2.z < eps && v1.z - v2.z > -eps);

    };

TEST(VeinGeneratorTests, BasicBifurcationVerticesAreOverlapping)
{
    VeinMesh mesh = VeinGenerator::createBifurcation(radiusTop, radiusLeft, radiusRight, 0, 0, 0, 0);
    std::sort(mesh.positions.begin(), mesh.positions.end(), vecComparator);
    bool hasDuplicates = std::adjacent_find(mesh.positions.begin(), mesh.positions.end(), vecEpsComparator) != mesh.positions.end();
    EXPECT_EQ(hasDuplicates, true);
}

TEST(VeinGeneratorTests, BentBifurcationVerticesAreOverlapping)
{
    
    VeinMesh mesh = VeinGenerator::createBifurcation(radiusTop, radiusLeft, radiusRight, -0.5, -0.3, 0.6, 0.1);
    std::sort(mesh.positions.begin(), mesh.positions.end(), vecComparator);
    bool hasDuplicates = std::adjacent_find(mesh.positions.begin(), mesh.positions.end(), vecEpsComparator) != mesh.positions.end();
    EXPECT_EQ(hasDuplicates, true);
}