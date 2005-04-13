/** Uncompilable, depends on Triangle-class. Class methods are implemented 
the same way as the source, except for the java.util.Vector class, it is replaced with std::vector. **/

#ifndef __DDENGINE_VERTEX_H
#define __DDENGINE_VERTEX_H

class Object;
class Triangle;

#include "Matrix.h"
#include "Camera.h"

class Vertex {
	public:
		Vertex();
		Vertex(float xpos,float ypos,float zpos);
		Vertex(float xpos,float ypos,float zpos,float u,float v);
		Vertex(Vector ppos);
		Vertex(Vector ppos,float u,float v);

		virtual ~Vertex();
		Object* parent;
		Vector pos;
		Vector pos2;
		Vector n;
		Vector n2;

		// data members
		int x,y,z;
		float u,v;
		int nx,ny,tx,ty;
		bool visible;
		int clipcode;
		int id;
		float fact;
		std::vector<Triangle*> neighbor;

		// methods
		void Project(Matrix vertexProjection,Matrix normalProjection,Camera camera);
		void SetUV(float u,float v);
		void clipFrustrum(int w,int h);
		void RegisterNeighbor(Triangle triangle);
		void resetNeighbors();
		void RegenerateNormal();
		void ScaleTextureCoordinates(float fx,float fy);
		Vertex GetClone();
		bool equals(Vertex v);
		bool equals(Vertex v,float tolerance);
};
#endif
