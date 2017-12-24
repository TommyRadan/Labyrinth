#include "Utility/LabyrinthGenerator.hpp"

enum Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

LabyrinthGenerator::LabyrinthGenerator(const int32_t width, const int32_t height) :
    m_Height { height },
    m_Width { width }
{
    if (m_Width % 2 == 0)
    {
        m_Width++;
    }

    if (m_Height % 2 == 0)
    {
        m_Height++;
    }

    m_Grid = std::unique_ptr<unsigned char[]>(new unsigned char[m_Width * m_Height]);

    ResetGrid();
    Visit(1, 1);
    SpawnStartAndEndLocation();
}

bool LabyrinthGenerator::IsWalled(const int32_t x, const int32_t y) const
{
    return m_Grid[XYToIndex(x, y)] == '#';
}

void LabyrinthGenerator::ResetGrid() const
{
    for (auto i = 0; i < m_Width * m_Height; i++)
    {
        m_Grid[i] = '#';
    }
}

void LabyrinthGenerator::SpawnStartAndEndLocation()
{
    int32_t quadrant[] = { 1, 2, 3, 4 };

    m_Random.ShuffleArray(quadrant);

    const auto startIndex = GetRandomIndexInQuadrant(quadrant[0]);
    const auto endIndex = GetRandomIndexInQuadrant(quadrant[1]);

    m_Grid[startIndex] = 'S';
    m_Grid[endIndex] = 'E';
}

void LabyrinthGenerator::Visit(const int32_t x, const int32_t y)
{
    int32_t directions[] = { NORTH, EAST, SOUTH, WEST };
    m_Random.ShuffleArray(directions);

    m_Grid[XYToIndex(x, y)] = ' ';

    for (const auto& i : directions)
    {
        auto dx = 0;
        auto dy = 0;

        switch (i)
        {
        case NORTH:
            dy = -1;
            break;
        case SOUTH:
            dy = 1;
            break;
        case EAST:
            dx = 1;
            break;
        case WEST:
            dx = -1;
            break;
        default:
            break;
        }

        const auto x2 = x + dx * 2;
        const auto y2 = y + dy * 2;

        if (IsInBounds(x2, y2) && m_Grid[XYToIndex(x2, y2)] == '#')
        {
            m_Grid[XYToIndex(x2 - dx, y2 - dy)] = ' ';
            Visit(x2, y2);
        }
    }
}

int32_t LabyrinthGenerator::GetRandomIndexInQuadrant(const int32_t quadrant) const
{
    auto minX = 0;
    auto maxX = m_Width;

    auto minY = 0;
    auto maxY = m_Height;

    switch (quadrant)
    {
    case 1:
        maxX = m_Width / 2;
        maxY = m_Height / 2;
        break;
    case 2:
        minX = m_Width / 2;
        maxY = m_Height / 2;
        break;
    case 3:
        maxX = m_Width / 2;
        minY = m_Height / 2;
        break;
    case 4:
        minX = m_Width / 2;
        minY = m_Height / 2;
        break;
    default:
        break;
    }

    while (true)
    {
        const auto x = m_Random.Next(minX, maxX);
        const auto y = m_Random.Next(minY, maxY);

        if (m_Grid[XYToIndex(x, y)] == ' ')
        {
            return XYToIndex(x, y);
        }
    }
}

bool LabyrinthGenerator::IsInBounds(const int32_t x, const int32_t y) const
{
    if (x < 0 || x >= m_Width)
    {
        return false;
    }

    return y >= 0 || y < m_Height;
}

int32_t LabyrinthGenerator::XYToIndex(const int32_t x, const int32_t y) const
{
    return y * m_Width + x;
}
