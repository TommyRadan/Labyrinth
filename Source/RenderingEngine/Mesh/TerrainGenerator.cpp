#include <RenderingEngine/Mesh/TerrainGenerator.hpp>

namespace RenderingEngine
{
    std::vector<Vertex> GenerateTerrain()
    {
        std::vector<Vertex> terrain;

        Vertex v1;
        v1.Pos.x = -200;
        v1.Pos.y = -200;
        v1.Pos.z = 0.0;

        Vertex v2;
        v2.Pos.x = 200;
        v2.Pos.y = -200;
        v2.Pos.z = 0.0;

        Vertex v3;
        v3.Pos.x = -200;
        v3.Pos.y = 200;
        v3.Pos.z = 0.0;

        Vertex v4;
        v4.Pos.x = 200;
        v4.Pos.y = 200;
        v4.Pos.z = 0.0;

        terrain.push_back(v2);
        terrain.push_back(v1);
        terrain.push_back(v3);

        terrain.push_back(v4);
        terrain.push_back(v2);
        terrain.push_back(v3);

        return terrain;
    }
}
