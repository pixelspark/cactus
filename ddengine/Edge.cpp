#include "Edge.h"

Edge::Edge() {

}

Edge::Edge(Vertex* v1,Vertex* v2) {
	a = v1;
	b = v2;
}

Edge::~Edge() {
}

Vertex* Edge::start() {
	return a;
}

Vertex* Edge::end() {
	return b;
}
