#include "window.h"
#include <QDebug>
#include <QString>
#include <QOpenGLShaderProgram>
#include "mesh.h"
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

float Window::interatorX = 0.0f;
float Window::interatorY = 0.0f;

Window::Window()
	: mesh(NULL), interator(NULL), collisionDetector(NULL, NULL)
{
	//intentionally blank
}

void Window::initializeGL()
{
    initializeOpenGLFunctions();
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
    printVersionInformation();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Loading, compiling and linking shaders.
	m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ".\\simple.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ".\\simple.frag");
    m_program->link();
    m_program->bind();

	//Creating the VBO
    m_vertex.create();
    m_vertex.bind();
    m_vertex.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_vertex.allocate(mesh->getVertices(), mesh->getNumberOfBytes());

	//Creating the VAO
    m_object.create();
    m_object.bind();

	//Enabling attribute arrays for vertex and color data.
    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

    m_object.release();
    m_vertex.release();
    m_program->release();

	//Setting up model, view and projection matrices.
	mvpSetup();

	//Creating interator ray
	interator = new Ray(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));

	//Setting up the collision detector
	collisionDetector.setMesh(mesh);
	collisionDetector.setRay(interator);
}

void Window::resizeGL(int width, int height)
{
    (void) width;
    (void) height;
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
	collisionDetector.testCollision();
    m_program->bind();
    m_object.bind();
	m_program->setUniformValue("mvp", QMatrix4x4(glm::value_ptr(mvp)));
    glDrawArrays(GL_TRIANGLES, 0, mesh->getNumberOfVertices());
    m_object.release();
    m_program->release();
}

void Window::teardownGL()
{
    m_object.destroy();
    m_vertex.destroy();
    delete m_program;
	delete interator;
}

void Window::setMesh(Mesh* mesh)
{
    this->mesh = mesh;
}

void printMatrix(mat4& m)
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cout << m[j][i] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void Window::mvpSetup()
{
	//Setting up MVP matrix
	mat4 model = mat4(1.0f);
	model = glm::scale(model, vec3(0.1, 0.1f, 1.0f));
	model = glm::translate(model, vec3(-1.0f, -1.0f, 0.0f));

	mat4 view;
	vec3 cameraPos(0.0f, 0.0f, 1.0f);
	vec3 cameraTarget(0.0f, 0.0f, 0.0f);
	vec3 up(0.0f, 1.0f, 0.0f);
	view = glm::lookAt(cameraPos, cameraTarget, up);

	mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	//mat4 projection = glm::perspective(45.0f, 1.0f, 0.1f, 10.0f);

	mvp = projection * view * model;
}

void Window::keyPressEvent(QKeyEvent* keyEvent)
{
	switch (keyEvent->key()) {
		case Qt::Key_Up:
			Window::interatorY += 0.1f;
			break;
		case Qt::Key_Down:
			Window::interatorY -= 0.1f;
			break;
		case Qt::Key_Left:
			Window::interatorX -= 0.1f;
			break;
		case Qt::Key_Right:
			Window::interatorX += 0.1f;
			break;
		default:
			break;
	}
	vec3 origin(interatorX, interatorY, 0.0);
	interator->setOrigin(origin);
	collisionDetector.getRay()->printRayInfo();
	cout << Window::interatorX << "\t" << Window::interatorY << endl;
	paintGL();
}

void Window::printVersionInformation()
{
    QString glType, glVersion, glProfile;

    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    switch(format().profile()){
        case QSurfaceFormat::NoProfile:
            glProfile = "No Profile";
            break;
        case QSurfaceFormat::CoreProfile:
            glProfile = "Core Profile";
            break;
        case QSurfaceFormat::CompatibilityProfile:
            glProfile = "Compatibility Profile";
            break;
    }

    qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
