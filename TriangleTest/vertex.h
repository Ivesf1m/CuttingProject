#ifndef VERTEX_H
#define VERTEX_H

#include <glm.hpp>
#include <iostream>

using glm::vec3;

class Vertex
{
    public:
        Vertex();
        explicit Vertex(const vec3& position);
        Vertex(const vec3& position, const vec3& color);

        const vec3& position() const;
        const vec3& color() const;
        void setPosition(const vec3& position);
        void setColor(const vec3& color);

        void printInfo();

        static const int PositionTupleSize = 3;
        static const int ColorTupleSize = 3;
        static int positionOffset();
        static int colorOffset();
        static int stride();

    private:
        vec3 m_position;
        vec3 m_color;
};

//Inline implementation

inline Vertex::Vertex() {}
inline Vertex::Vertex(const vec3& position) : m_position(position) {}
inline Vertex::Vertex(const vec3& position, const vec3& color) : m_position(position), m_color(color) {}

inline const vec3& Vertex::position() const { return m_position; }
inline const vec3& Vertex::color() const { return m_color; }
void inline Vertex::setPosition(const vec3& position) { m_position = position; }
void inline Vertex::setColor(const vec3& color) { m_color = color; }

inline int Vertex::positionOffset() { return offsetof(Vertex, m_position); }
inline int Vertex::colorOffset() { return offsetof(Vertex, m_color); }
inline int Vertex::stride() { return sizeof(Vertex); }


#endif // VERTEX_H
