#include "vertex.h"

void Vertex::printInfo()
{
    std::cout << "Position: " << m_position.x << "\t" << m_position.y << "\t" << m_position.z << std::endl;
	std::cout << "Normal: " << m_normal.x << "\t" << m_normal.y << "\t" << m_normal.z << std::endl;
    std::cout << "Color: " << m_color.r << "\t" << m_color.g << "\t" << m_color.b << std::endl;
}
