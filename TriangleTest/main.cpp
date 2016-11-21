#include <QGuiApplication>
#include "window.h"
#include "trianglecutter.h"
#include "Grid.h"
#include "CollisionDetector.h"
#include "startscreen.hpp"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);
	format.setDepthBufferSize(24);

    //Initializing mesh
	/*Mesh mesh;
    mesh.addVertex(Vertex(vec3(-0.50f,  0.5f, 1.0f), vec3(1.0f, 0.0f, 0.0f)));
    mesh.addVertex(Vertex(vec3(-1.00f, -0.5f, 1.0f), vec3(0.0f, 1.0f, 0.0f)));
    mesh.addVertex(Vertex(vec3( 0.00f, -0.5f, 1.0f), vec3(0.0f, 0.0f, 1.0f)));

	mesh.addTriangularFace(0, 1, 2);*/

	//Grid for test
	//Grid grid(1);
	/*CollisionPath testPath;
	vec3 p1(0.3f, 0.1f, 1.0f);
	vec3 p2(0.8f, 0.9f, 1.0f);
	testPath.addPoint(p1);
	testPath.addPoint(p2);
	testPath.addIndex(0);
	testPath.addIndex(3);
	grid.cut(testPath);*/

	//Loading mesh from file
	Mesh mesh;
	mesh.loadFromObjFile(string("esfera.obj"));

	Mesh interatorMesh;
	interatorMesh.loadFromObjFile(string("pointy.obj"));

	/*QApplication app(argc, argv);
	StartScreen sscreen;
	sscreen.show();*/

    Window window(false);
    window.setMesh(&mesh);
	window.setInterator(&interatorMesh);
    window.setFormat(format);
    window.resize(QSize(800, 600));
    window.show();
	return app.exec();
}
