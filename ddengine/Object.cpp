/** All right, this is a pretty long and important clas, so let's do it! 

NOTES: 

- what to do with vertices that get created here and need to be pointed to? place them in a separate std:vector?

**/
#include "Object.h"

Object::Object() {	
}

Object::~Object() {
}

Vertex* Object::vertex(int id) {
	return vertexData.at(id);
}

Triangle* Object::triangle(int id) {
	return triangleData.at(id);
}

void Object::AddVertex(Vertex* newVertex) {
	newVertex->parent = this;
	vertexData.push_back(newVertex);
	dirty = true;
}

void Object::AddTriangle(Triangle* newTriangle) {
	newTriangle->parent = this;
	triangleData.push_back(newTriangle);
	dirty = true;
}

void Object::AddTriangle(int v1,int v2,int v3) {
	AddTriangle(vertex(v1),vertex(v2),vertex(v3));
}

void Object::RemoveVertex(Vertex* v) {
	std::vector<Vertex*> temp = vertexData;
	vertexData.clear();

	for(int a=0;a<temp.size();a++) {
		if(temp.at(a)==v) {
			continue;
		}		

		vertexData.push_back(temp.at(a));
	}
} 

void Object::RemoveTriangle(Triangle* v) {
	std::vector<Triangle*> temp = triangleData;
	triangleData.clear();

	for(int a=0;a<temp.size();a++) {
		if(temp.at(a)==v) {
			continue;
		}		

		triangleData.push_back(temp.at(a));
	}
}

void Object::RemoveVertexAt(int pos) {
	std::vector<Vertex*> temp = vertexData;
	vertexData.clear();
	
	for(int a=0;a<temp.size();a++) {
		if(a==pos) {
			continue;
		}

		vertexData.push_back(temp.at(a));
	}
}

void Object::RemoveTriangleAt(int pos) {
	std::vector<Triangle*> temp = triangleData;
	triangleData.clear();
	
	for(int a=0;a<temp.size();a++) {
		if(a==pos) {
			continue;
		}

		triangleData.push_back(temp.at(a));
	}
}

void Object::SetMaterial(Material m) {
	material = m;
}

void Object::Rebuild() {
	if(!dirty) {
		return;
	}

	dirty = false;

	// snelle arrays opbouwen voor vertices niet geport, zie onder
	vertices = vertexData.size();
	// snelle arrays opbouwen voor triangles niet geport;  gebruikt gewoon de std::vector
	triangles = triangleData.size();



	for(int i=vertices-1;i>=0;i--) {
		vertexData[i]->id = i;
		vertexData[i]->resetNeighbors();
	}

	
	Triangle* tri;
	for(int x=triangles-1;x>=0;x--) {
		tri = triangleData[x];
		tri->p1->registerNeighbor(tri);
		tri->p2->registerNeighbor(tri);
		tri->p3->registerNeighbor(tri);
	}

	Regenerate();
}

void Object::AddVertex(float x,float y,float z) {
	AddVertex(Vertex(x,y,z));
}

void Object::AddVertex(float x,float y,float z,float u,float v) {
	Vertex* vert = new Vertex(x,y,z);
	vert.SetUV(u,v);
	AddVertex(vert);
}

void Object::AddTriangle(Vertex* a,Vertex* b,Vertex* c) {
	AddTriangle(new Triangle(a,b,c));
}

void Object::ScaleTextureCoordinates(float fu,float fv) {
	Rebuild();
	for(int i=0;i<vertices;i++) {
		vertexData.at(i)->ScaleTextureCoordinates(fu,fv);
	}
}

void Object::Tilt(float fact) {
	Rebuild();
	for(int i=0;i<vertices;i++) {
		vertexData.at(i)->pos = Vector::add(vertexData.at(i)->pos,Vector::random(fact));
	}
}

Vector Object::min() {
	if(vertices==0) {
		return Vector(0,0,0);
	}

	float minX = vertexData.at(0)->pos.x;
	float minY = vertexData.at(0)->pos.y;
	float minZ = vertexData.at(0)->pos.z;

	for(int i=0;i<vertices;i++) {
		if(vertexData.at(i)->pos.y<minY) {
			minY = vertexData.at(i)->pos.y;
		}
		if(vertexData.at(i)->pos.x<minX) {
			minX = vertexData.at(i)->pos.x;
		}
		if(vertexData.at(i)->pos.z<minZ) {
			minZ = vertexData.at(i)->pos.z;
		}
	}

	return Vector(minX,minY,minZ);
}

Vector Object::max() {
	if(vertices==0) {
		return Vector(0,0,0);
	}

	float minX = vertexData.at(0)->pos.x;
	float minY = vertexData.at(0)->pos.y;
	float minZ = vertexData.at(0)->pos.z;

	for(int i=0;i<vertices;i++) {
		if(vertexData.at(i)->pos.y>minY) {
			minY = vertexData.at(i)->pos.y;
		}
		if(vertexData.at(i)->pos.x>minX) {
			minX = vertexData.at(i)->pos.x;
		}
		if(vertexData.at(i)->pos.z>minZ) {
			minZ = vertexData.at(i)->pos.z;
		}
	}

	return Vector(minX,minY,minZ);
}

void Object::Detach() {
	Vector center = GetCenter();

	for(int i=0;i<vertices;i++) {
		vertexData.at(i)->pos.x = center.x;
		vertexData.at(i)->pos.y = center.y;
		vertexData.at(i)->pos.z = center.z;
	}

	Shift(center);
}

Vector Object::GetCenter() {
	Vector max = max();
	Vector min = min();
	return Vector((max.x+min.x)/2,(max.y+min.y)/2,(max.z-min.z)/2);
}

Vector Object::GetDimension() {
	Vector max = max();
	Vector min = min();

	return Vector(max.x-min.x,max.y-min.y,max.z-min.z);
}

void Object::MatrixMeltdown() {
	Rebuild();

	for(int i=vertices;i>=0;i--) {
		vertexData.at(i)->pos = vertexData.at(i)->pos.transform(matrix);	
	}

	Regenerate();
	matrix.Reset();
	normalmatrix.Reset();
}

Object Object::GetClone() {
	Object obj;
	Rebuild();
	for(int i=0;i<vertices;i++) {
		obj.AddVertex(vertexData.at(i).GetClone());
	}
	for(int i=0;i<triangles;i++) {
		obj.AddVertex(triangleData.at(i).GetClone());
	}

	obj.material = materual;
	obj.matrix = matrix.GetClone();
	obj.normalmatrix = normalmatrix.GetClone();
	obj.Rebuild();

	return obj;
}

void Object::RemoveDuplicateVertices() {
	this->Rebuild();

	for(int i=0;i<triangles;i++) {
		if(triangleData[i].degenerated()) {
			RemoveTriangleAt(i);
		}
	}

	dirty = true;
	this->Rebuild();
}

void Object::MeshSmooth() {
	Rebuild();
	Triangle* tri;
	float u,v;
	Vertex* a,b,c,d,e,f,temp;
	Vector ab,bc,ca,nab,nba,nca,center;
	float sab,sbc,sca,rab,rbc,rca;
	float sqrt3 = (float)sqrt(3);

	for(int i=0;i<triangles;i++) {
		tri = triangleData[i];
		a = tri->p1;
		b = tri->p2;
		c = tri->p3;
		ab = Vector::scale(0.5,Vector::add(b.pos,a.pos));
		bc = Vector::scale(0.5,Vector::add(c.pos,b.pos));
		ca = Vector::scale(0.5,Vector::add(a.pos,c.pos));

		rab = Vector::sub(ab,a.pos).length();
		rbc = Vector::sub(bc,b.pos).length();
		rca = Vector::sub(ca,c.pos).length();

		nab = Vector::scale(0.5,Vector::add(a.n,b.n));
		nbc = Vector::scale(0.5,Vector::add(b.n,c.n));
		nca = Vector::scale(0.5,Vector::add(c.n,a.n));

		uab = 0.5*(a.u+b.u);
		vab = 0.5*(a.v+b.v);
		ubc = 0.5*(b.u+c.u);
		vbc = 0.5*(b.v+c.v);
		uca = 0.5*(c.u+a.u);
		vca = 0.5*(c.v+a.v);

		sab = 1 - nab.Length();
		sbc = 1 - nbc.Length();
		sca = 1 - nca.Length();

		nab.Normalize();
		nbc.Normalize();
		nca.Normalize();

		d = new Vertex(Vector::sub(ab,Vector::scale(rab*sab,nab)),uab,vab);
		e = new Vertex(Vector::sub(bc,Vector::scale(rbc*sbc,nbc)),ubc,vbc);
		f = new Vertex(Vector::sub(ca,Vector::scale(rca*sca,nca)),uca,vca);

		AddVertex(d);
		AddVertex(e);
		AddVertex(f);

		tri.p2 = d;
		tri.p3 = f;

		AddTriangle(b,e,d);
		AddTriangle(c,f,e);
		AddTriangle(d,e,f);
	}

	RemoveDuplicateVertices();
}

void Object::EdgeCollapse(Edge edge) {
	Vertex u = edge.start;
	Vertex v = edge.end;
	bool contains = false;

	for(int i=0;i<vertices;i++) {
		if(vertexData[i]->equals(u)) {
			contains = true;
		}
	}

	if(!contains) {
		return;
	}

	contains = false;
	for(int i=0;i<vertices;i++) {
		if(vertexData[i]->equals(v)) {
			contains = true;
		}
	}

	if(!contains) {
		return;
	}

	Triangle tri;

	for(int i=0;i<triangles;i++) {
		tri = triangleData[i];
		if(tri.p1==v) {
			tri.p1 = u;
		}

		if(tri.p2==v) {
			tri.p2 = u;
		}

		if(tri.p3==v) {
			tri.p3 = u;
		}
	}
}

void Object::Regenerate() {
	for(int i=0;i<triangles;i++) {
		triangleData[i]->RegenerateNormal();
	}

	for(int i=0;i<vertices;i++) {
		vertexData[i]->RegenerateNormal();
	}
}