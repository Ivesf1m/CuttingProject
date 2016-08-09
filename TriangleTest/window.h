#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QKeyEvent>
#include "mesh.h"
#include "CollisionDetector.h"

using glm::mat4;

class QOpenGLShaderProgram;

class Window : public QOpenGLWindow,
               protected QOpenGLFunctions
{
    Q_OBJECT;

    public:
		Window();
		
		void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();

        void setMesh(Mesh* mesh);

		//Static variables
		//Interator translations
		static float interatorX;
		static float interatorY;

    protected slots:
        void teardownGL();

    private:
        QOpenGLBuffer m_vertex;
        QOpenGLVertexArrayObject m_object;
        QOpenGLShaderProgram* m_program;
        Mesh* mesh;
		Ray* interator;
		CollisionDetector collisionDetector;
		mat4 mvp;

		//Private functions

		//Setup for the model-view-projection matrix.
		void mvpSetup();
        void printVersionInformation();
		void keyPressEvent(QKeyEvent* keyEvent);
};

#endif // WINDOW_H
