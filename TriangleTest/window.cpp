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

Window::Window(bool enableHaptics)
	: mesh(NULL), interator(NULL), collisionDetector(NULL, NULL),
	  hapticsEnabled(enableHaptics), interatorMesh(NULL)
{

}

void Window::initializeGL()
{
    initializeOpenGLFunctions();
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
    printVersionInformation();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Loading, compiling and linking shaders.
	shaderProgram = new QOpenGLShaderProgram();
	shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ".\\simple.vert");
	shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ".\\simple.frag");
	shaderProgram->link();
	shaderProgram->bind();

	//Creating the VAO
	vertexArrayObject.create();
	vertexArrayObject.bind();

	//We now need to combine the data of out mesh and our interator mesh
	vector<Vertex> combinedVertexBuffer;
	combinedVertexBuffer.reserve(mesh->getVertexVector().size() +
		interatorMesh->getVertexVector().size());
	combinedVertexBuffer.insert(combinedVertexBuffer.end(), mesh->
		getVertexVector().begin(), mesh->getVertexVector().end());
	combinedVertexBuffer.insert(combinedVertexBuffer.end(), interatorMesh->
		getVertexVector().begin(), interatorMesh->getVertexVector().end());


	//Index buffer
	vector<unsigned int> combinedIndexBuffer;
	combinedIndexBuffer.reserve(mesh->getIndexVector().size() + interatorMesh->
		getIndexVector().size());
	combinedIndexBuffer.insert(combinedIndexBuffer.end(), mesh->
		getIndexVector().begin(), mesh->getIndexVector().end());

	unsigned int vertexVectorSize = static_cast<unsigned int>(mesh->
		getVertexVector().size());
	for (auto index : interatorMesh->getIndexVector()) {
		combinedIndexBuffer.push_back(index + vertexVectorSize);
	}

	//Creating the VBO for the mesh
    vertexBuffer.create();
	vertexBuffer.bind();
	vertexBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
	vertexBuffer.allocate(combinedVertexBuffer.data(), 
		static_cast<int>(combinedVertexBuffer.size() * sizeof(Vertex)));

	//Creating IBO for the mesh
	indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	indexBuffer.create();
	indexBuffer.bind();
	indexBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
	indexBuffer.allocate(combinedIndexBuffer.data(),
		static_cast<int>(combinedIndexBuffer.size() * sizeof(unsigned int)));

	//Enabling attribute arrays for vertex, normal and color data.
	shaderProgram->enableAttributeArray(0);
	shaderProgram->enableAttributeArray(1);
	shaderProgram->enableAttributeArray(2);
	shaderProgram->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
	shaderProgram->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());
	shaderProgram->setAttributeBuffer(2, GL_FLOAT, Vertex::normalOffset(), Vertex::NormalTupleSize, Vertex::stride());

	vertexArrayObject.release();
	vertexBuffer.release();
	indexBuffer.release();
	shaderProgram->release();

	//Setting up model, view and projection matrices.
	mvpSetup();

	//Creating interator ray
	interator = new Ray(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));

	//Setting up the collision detector
	collisionDetector.setMesh(mesh);
	collisionDetector.setRay(interator);

	//Initializaing haptic device
	if (hapticsEnabled) {
		haptic.initializeHL();
		haptic.updateHapticWorkspace();
		haptic.setInterator(interator);
		haptic.setCollisionDetector(&collisionDetector);
		haptic.setCollisionPath(&path);
		handle = hdScheduleAsynchronous(HapticInterface::mainHapticCallback,
			&haptic, HD_MAX_SCHEDULER_PRIORITY);
		hdStartScheduler();
	}
}

void Window::resizeGL(int width, int height)
{
    (void) width;
    (void) height;
}

void Window::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderProgram->bind();    

	//Drawing the mesh
	vertexArrayObject.bind();
	shaderProgram->setUniformValue("translateFactor", 0.0f, 0.0f, 0.0f);
	shaderProgram->setUniformValue("mvp", QMatrix4x4(glm::value_ptr(mvp)));
	glDrawElements(GL_TRIANGLES, mesh->getNumberOfIndices(), GL_UNSIGNED_INT, 
		0);
	

	//Drawing the interator
	unsigned int indexOffset = mesh->getNumberOfIndices() * sizeof(unsigned int);
	shaderProgram->setUniformValue("translateFactor", 1.0f, 1.0f, 0.0f);
	shaderProgram->setUniformValue("mvp", QMatrix4x4(glm::value_ptr(mvp)));
	glDrawElements(GL_TRIANGLES, interatorMesh->getNumberOfIndices(), 
		GL_UNSIGNED_INT, reinterpret_cast<void*>(indexOffset));

	vertexArrayObject.release();
	shaderProgram->release();
}

void Window::teardownGL()
{
	vertexArrayObject.destroy();
    vertexBuffer.destroy();
	indexBuffer.destroy();

	if (hapticsEnabled) {
		haptic.terminateHL();
		hdUnschedule(handle);
	}

    delete shaderProgram;
	delete interator;
}

void Window::setMesh(Mesh* mesh)
{
    this->mesh = mesh;
}

void Window::setInterator(Mesh* interator)
{
	this->interatorMesh = interator;
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
	model = glm::scale(model, vec3(0.5, 0.5f, 0.5f));
	//model = glm::translate(model, vec3(-1.0f, -1.0f, 0.0f));

	mat4 view;
	vec3 cameraPos(0.0f, 0.0f, 1.0f);
	vec3 cameraTarget(0.0f, 0.0f, 0.0f);
	vec3 up(0.0f, 1.0f, 0.0f);
	view = glm::lookAt(cameraPos, cameraTarget, up);

	mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	//mat4 projection = glm::perspective(45.0f, 1.0f, 0.1f, 10.0f);

	mvp = projection * view * model;

	if (hapticsEnabled) {
		haptic.setModelviewMatrix(view * model);
		haptic.setProjectionMatrix(projection);
	}
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
	/*vec3 origin(interatorX, interatorY, 0.0);
	interator->setOrigin(origin);
	collisionDetector.testCollision();
	if (collisionDetector.hasCollided())
		path.addPoint(collisionDetector.getCollisionPoint());
	else
		mesh->cut(path);*/
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
