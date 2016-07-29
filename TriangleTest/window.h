#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "mesh.h"

class QOpenGLShaderProgram;

class Window : public QOpenGLWindow,
               protected QOpenGLFunctions
{
    Q_OBJECT;

    public:
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();

        void setMesh(Mesh* mesh);

    protected slots:
        void teardownGL();

    private:
        QOpenGLBuffer m_vertex;
        QOpenGLVertexArrayObject m_object;
        QOpenGLShaderProgram* m_program;
        Mesh* mesh;


        void printVersionInformation();
};

#endif // WINDOW_H
