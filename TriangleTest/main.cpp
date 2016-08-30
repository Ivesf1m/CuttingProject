#include <QGuiApplication>
#include "window.h"
#include "trianglecutter.h"
#include "Grid.h"
#include "CollisionDetector.h"

Mesh mesh;

void updateMesh(TriangleCutter& tc)
{
    static vec3 red(1.0f, 0.0f, 0.0f);
    static vec3 green(0.0f, 1.0f, 0.0f);
    static vec3 blue(0.0f, 0.0f, 1.0f);
    static vec3 yellow(1.0f, 1.0f, 0.0f);
    static vec3 cyan(0.0f, 1.0f, 1.0f);
    static vec3 magenta(1.0f, 0.0f, 1.0f);
    static vec3 colors[] = {red, green, blue, yellow, cyan, magenta};
    mesh.removeAllVertices();

    cout << "Numero de novos triangulos " << tc.getNewTriangles().size() << endl;

    for(unsigned int i = 0; i < tc.getNewTriangles().size(); ++i){
        vec3 pos1 = tc.getNewTriangles().at(i).getVertex(0);
        vec3 pos2 = tc.getNewTriangles().at(i).getVertex(1);
        vec3 pos3 = tc.getNewTriangles().at(i).getVertex(2);

        Vertex v1(pos1, colors[i]);
        v1.printInfo();
        Vertex v2(pos2, colors[i]);
        v2.printInfo();
        Vertex v3(pos3, colors[i]);
        v3.printInfo();

        mesh.addVertex(v1);
        mesh.addVertex(v2);
        mesh.addVertex(v3);
    }
}

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);

    //Initializing mesh
    mesh.addVertex(Vertex(vec3(-0.50f,  0.5f, 1.0f), vec3(1.0f, 0.0f, 0.0f)));
    mesh.addVertex(Vertex(vec3(-1.00f, -0.5f, 1.0f), vec3(0.0f, 1.0f, 0.0f)));
    mesh.addVertex(Vertex(vec3( 0.00f, -0.5f, 1.0f), vec3(0.0f, 0.0f, 1.0f)));

	mesh.addTriangularFace(0, 1, 2);

	//Grid for test
	Grid grid(5);
	CollisionPath testPath;
	vec3 p1(0.3f, 0.1f, 1.0f);
	vec3 p2(0.8f, 0.9f, 1.0f);
	testPath.addPoint(p1);
	testPath.addPoint(p2);
	testPath.addIndex(0);
	testPath.addIndex(3);
	grid.cut(testPath);

    Window window;
    window.setMesh(&grid);
    window.setFormat(format);
    window.resize(QSize(800, 600));
    window.show();

    /*Triangle t(&mesh, 0, 1, 2);
    t.printTriangleInfo();


    vec3 entrance(-0.2f, -0.5f, 1.0f);
    vec3 exit(-0.30,  0.1f, 1.0f);
    vec3 internal(-0.5f, 0.0f, 1.0f);
    TriangleCutter tc(0, t, entrance, internal, exit);
    tc.cut();
    updateMesh(tc);*/

    return app.exec();
}
