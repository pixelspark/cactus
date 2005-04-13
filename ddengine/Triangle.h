#ifndef __DDENGINE_TRIANGLE_H
#define __DDENGINE_TRIANGLE_H

#include "Vector.h"
#include "Vertex.h"

class Object;
class Matrix;


class Triangle {
	public:
		Triangle();
		Triangle(Vertex a,Vertex b,Vertex c);

		void clipFrustrum(int w,int h);
		void project(Matrix normalProjection);
		void RegenerateNormal();
		Vector GetWeightedNormal();
		Vertex GetMedium();
		Vector GetCenter();
		float GetDist();
		bool Degenerated();
		Triangle GetClone();


		Object* parent;
		bool visible;
		bool outOfFrustrum;
		Vertex p1;
		Vertex p2;
		Vertex p3;
		Vector n;
		Vector n2;
		int minx,maxx,miny,maxy;
		Vector triangleCenter;
		float dist;
		int id;
		virtual ~Triangle();

};

#endif
