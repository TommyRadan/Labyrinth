#include <RenderingEngine/Mesh/TerrainGenerator.hpp>

namespace RenderingEngine
{
    std::vector<Vertex> GenerateTerrain()
    {
        std::vector<Vertex> terrain;

        for (int i = -200; i < 200; i++)
        {
            for (int j = -200; j < 200; j++)
            {
                Vertex v1;
                v1.Pos.x = i;
                v1.Pos.y = j;
                v1.Pos.z = 0.0;

                Vertex v2;
                v2.Pos.x = i+1;
                v2.Pos.y = j;
                v2.Pos.z = 0.0;

                Vertex v3;
                v3.Pos.x = i;
                v3.Pos.y = j+1;
                v3.Pos.z = 0.0;

                Vertex v4;
                v4.Pos.x = i+1;
                v4.Pos.y = j+1;
                v4.Pos.z = 0.0;

                terrain.push_back(v2);
                terrain.push_back(v1);
                terrain.push_back(v3);

                terrain.push_back(v4);
                terrain.push_back(v2);
                terrain.push_back(v3);
            }
        }

        return terrain;
    }
}
