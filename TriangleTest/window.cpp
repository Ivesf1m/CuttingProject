#include "window.h"
#include <QDebug>
#include <QString>
#include <QOpenGLShaderProgram>
#include "mesh.h"

void Window::initializeGL()
{
    initializeOpenGLFunctions();
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
    printVersionInformation();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ".\\simple.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ".\\simple.frag");
    m_program->link();
    m_program->bind();

    m_vertex.create();
    m_vertex.bind();
    m_vertex.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_vertex.allocate(mesh->getVertices(), mesh->getNumberOfBytes());

    m_object.create();
    m_object.bind();
    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

    m_object.release();
    m_vertex.release();
    m_program->release();
}

void Window::resizeGL(int width, int height)
{
    (void) width;
    (void) height;
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    m_program->bind();
    m_object.bind();
    glDrawArrays(GL_TRIANGLES, 0, mesh->getNumberOfVertices());
    m_object.release();
    m_program->release();
}

void Window::teardownGL()
{
    m_object.destroy();
    m_vertex.destroy();
    delete m_program;
}

void Window::setMesh(Mesh* mesh)
{
    this->mesh = mesh;
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
