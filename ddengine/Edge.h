/** PORT STATUS: DONE! **/


#ifndef __DDENGINE_EDGE_H
#define __DDENGINE_EDGE_H

class Vertex;

class Edge {
	public:
		Edge();
		Edge(Vertex* v1,Vertex* v2);
		virtual ~Edge();
		Vertex *a,*b;
		Vertex* start();
		Vertex* end();
};

#endif
