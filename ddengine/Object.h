/** PORT STATUS: waiting for Scene, Material and Triangle to complete. Many methods still need to be implemented 
	KNOWN BUGS: possible memory leaking when creating a vertex from here
	THINGS NEED TO BE KNOWN: Are Triangle.p1, p2 and p3 pointers to vertices or just vertices?
**/



#ifndef __DDENGINE_OBJECT_H
#define __DDENGINE_OBJECT_H


// standaard includes
#include <string>
#include <vector>
#include <math.h>
using namespace std;

// en nu het gezeur met includes
#include "CoreObject.h"
#include "Vector.h"
#include "Matrix.h"
#include "Material.h"
#include "Edge.h"

// gcc gaat zeuren over macro's
#undef min
#undef max

#include "Vertex.h"
#include "Triangle.h"

class Scene;

class Object:public CoreObject {
	public:
		// constructors
		Object();
		virtual ~Object();
		std::string user;
		std::vector<Vertex*> vertexData;
		std::vector<Triangle*> triangleData;
		int id;
		std::string name;
		bool visible;
		Scene* parent;
		bool dirty;
		int vertices;
		int triangles;

		// methods
		Vertex* vertex(int id);
		Triangle* triangle(int id);
		void AddVertex(Vertex* newVertex);
		void AddTriangle(Triangle* newTriangle);
		void AddTriangle(int v1,int v2,int v3);
		void RemoveVertex(Vertex* v);
		void RemoveTriangle(Triangle* v);
		void RemoveVertexAt(int pos);
		void RemoveTriangleAt(int pos);
		void SetMaterial(Material m);
		void Rebuild();
		void AddVertex(float x,float y,float z);
		void AddVertex(float x,float y,float z,float u,float v);
		void AddTriangle(Vertex* a,Vertex* b,Vertex* c);
		void Regenerate();
		void ScaleTextureCoordinates(float fu,float fv);
		void Tilt(float fact);
		Vector min();
		Vector max();
		void Detach();
		Vector GetCenter();
		Vector GetDimension();
		void MatrixMeltdown();
		Object GetClone();
		void RemoveDuplicateVertices();
		void RemoveDegeneratedVertices();
		void MeshSmooth();
		void EdgeCollapse(Edge edge);
};
#endif
