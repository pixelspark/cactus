#include "Vertex.h"

Vertex::Vertex() {
	pos = Vector(0,0,0);
}

Vertex::Vertex(float xpos,float ypos,float zpos) {
	pos = Vector(xpos,ypos,zpos);
}

Vertex::Vertex(float xpos,float ypos,float zpos,float u,float v) {
	pos = Vector(xpos,ypos,zpos);
	this->u = u;
	this->v = v;
}

Vertex::Vertex(Vector ppos) {
	pos = ppos.Clone();
}

Vertex::Vertex(Vector ppos,float u,float v) {
	pos = ppos.Clone();
	this->u = u;
	this->v = v;
}

Vertex::~Vertex() {
}

void Vertex::Project(Matrix vertexProjection,Matrix normalProjection,Camera camera) {
	pos2 = pos.Transform(vertexProjection);
	n2 = n.Transform(normalProjection);

	fact = (float)(camera.screenscale/camera.fovfact/((pos2.z>0.1?pos2.z:0.1)));
	x = (int)(pos2.x*fact+(camera.screenwidth>>1));
	y = (int)(-pos2.x*fact+(camera.screenheight>>1));
	z = (int)(65536*pos2.z);

	nx = (int)(n2.x*127+127);
	ny = (int)(n2.y*127+127);
	if(parent.material==NULL) {
		return;
	}

	if(parent.material.texture==NULL) {
		return;
	}

	tx = (int)((float)(parent.material.texture.width*u));
	ty = (int)((float)(parent.material.texture.height*v));
}

void Vertex::SetUV(float u,float v) {
	this->u = u;
	this->v = v;
}

void Vertex::clipFrustrum(int w,int h) {
	clipcode = 0;
	if(x<0) clipcode |= 1;
	if(x>=w) clipcode |= 2;
	if(y<0) clipcode |= 4;
	if(y>=h) clipcode |= 8;
	if(pos2.z<0) clipcode |= 16;
	visible = (clipcode==0);
}

void Vertex::RegisterNeighbor(Triangle triangle) {
	for(int a=0;a<neighbor.size();a++) {
		if(neighbor.at(a)==triangle) {
			return;
		}
	}

	neigbor.push_back(triangle);
}

void Vertex::resetNeighbors() {
	neighbor.clear();
}

void Vertex::RegenerateNormal() {
	float nx = 0;
	float ny = 0;
	float nz = 0;
	Triangle tri;
	Vector wn;


	for(int a=0;a<neighbor.size();a++) {
		tri = neighbor.at(a);
		wn = tri.GetWeightedNormal();
		nx += wn.x;
		ny += wn.y;
		nz += wn.z;
	}

	n = Vector(nx,ny,nz).Normalize();
}

void Vertex::ScaleTextureCoordinates(float fx,float fy) {
	u *= fx;
	v *= fy;
}

Vertex Vertex::GetClone() {
	Vertex newvertex;
	newvertex.pos = pos.Clone();
	newvertex.n = n.Clone();
	newvertex.u = u;
	newvertex.v = v;
	return newvertex;
}

bool Vertex::equals(Vertex v) {
	return ((pos.x==v.pos.x)&&(pos.y==v.pos.y)&&(pos.z==v.pos.z));
}

bool Vertex::equals(Vertex v,float tolerance) {
	return abs(Vector::sub(pos,v.pos).Length())<tolerance;
}


