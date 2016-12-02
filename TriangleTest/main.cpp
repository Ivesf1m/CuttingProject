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
	Grid grid(2);
	/*CollisionPath testPath;
	vec3 p1(0.3f, 0.2f, 0.0f);
	vec3 p2(1.3f, 0.2f, 0.0f);
	testPath.addPoint(p1);
	testPath.addIndex(0);
	vec3 dir = glm::normalize(p2 - p1);
	for (int i = 1; i < 100; ++i) {
		vec3 point = p1 + (i / 100.0f) * dir;
		testPath.addPoint(point);
		if (point.x <= 0.8f)
			testPath.addIndex(0);
		else if (point.x > 1.0f)
			testPath.addIndex(12);
		else
			testPath.addIndex(3);
	}
	testPath.addPoint(p2);	
	testPath.addIndex(12);
	grid.cut(testPath);*/

	//Loading mesh from file
	Mesh mesh;
	mesh.loadFromObjFile(string("esfera.obj"));

	Mesh interatorMesh;
	interatorMesh.loadFromObjFile(string("pointy.obj"));

	/*QApplication app(argc, argv);
	StartScreen sscreen;
	sscreen.show();*/

    Window window(true);
    window.setMesh(&grid);
	window.setInterator(&interatorMesh);
    window.setFormat(format);
    window.resize(QSize(800, 600));
    window.show();
	return app.exec();
}
