#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QKeyEvent>
#include "mesh.h"
#include "CollisionDetector.h"
#include "CollisionPath.h"
#include "HapticInterface.h"

using glm::mat4;

class QOpenGLShaderProgram;

class Window : public QOpenGLWindow,
               protected QOpenGLFunctions
{
    Q_OBJECT;

    public:
		Window(bool enableHaptics = false);
		
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
        QOpenGLBuffer vertexBuffer;
		QOpenGLBuffer indexBuffer;
        QOpenGLVertexArrayObject vertexArrayObject;
        QOpenGLShaderProgram* shaderProgram;
        Mesh* mesh;
		Ray* interator;
		CollisionDetector collisionDetector;
		CollisionPath path;
		mat4 mvp;
		HapticInterface haptic;
		HDSchedulerHandle handle;
		bool hapticsEnabled;

		//Private functions

		//Setup for the model-view-projection matrix.
		void mvpSetup();
        void printVersionInformation();
		void keyPressEvent(QKeyEvent* keyEvent);
};

#endif // WINDOW_H
