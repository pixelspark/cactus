/* ---------------------------------------------------------------------------------------------------------------------------------------------------
Copyright (C) 2003-2004 Tommy van der Vorst

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
--------------------------------------------------------------------------------------------------------------------------------------------------- */
#include "../include/cactus.h"
using namespace cactus;

CObject* CObjectFactory::Sphere(float radius, int segments) {
	CVector* path = new CVector[segments];
	
	float x,y,angle;
	
	path[0] = CVector(0,radius,0);
	path[segments-1] = CVector(0,-radius,0);
	
	for(int i=1;i<segments-1;i++) {
		angle = -(((float)i/(float)(segments-2))-0.5f)*3.14159265f;
		x = (float)math.cos(angle)*radius;
		y = (float)math.sin(angle)*radius;
		path[i] = CVector(x,y,0);
	}
	
	CObject* n = RotationObject(path,segments,segments);
	delete[] path;
	return n;
}

CObject* CObjectFactory::Spiral(float h, float r_out, float r_in, float r_tube, float w, float f, int segments, int steps) {
	float x,y,z,r,t,theta;
	
	CVector* path = new CVector[segments+1];
	for (int i=0;i<segments+1;i++) {
		t=(float)i/(float)segments;
		r=r_out+r_in*sin(2*3.14159265f*f*t);
		z=(h/2)+h*t;
		theta=2*3.14159265f*w*t;
		x=r*math.cos(theta);
		y=r*math.sin(theta);
		path[i] = CVector(x,y,z);
	}
	CObject* n = Tube(path,segments, r_tube, steps, false);
	delete[] path;
	return n;
}

CObject* CObjectFactory::Cube(float xsize, float ysize, float zsize) {
	float x = (float)abs((int)xsize/2);
	float y = (float)abs((int)ysize/2);
	float z = (float)abs((int)zsize/2);

	float xx, yy, zz;

	CObject* n = new CObject();
	int* xflag = new int[6];
	int* yflag = new int[6];
	int* zflag = new int[6];

	xflag[0]=10;	yflag[0]=3;		zflag[0]=0;
	xflag[1]=10;	yflag[1]=15;	zflag[1]=3;
	xflag[2]=15;	yflag[2]=3;		zflag[2]=10;
	xflag[3]=10;	yflag[3]=0;		zflag[3]=12;
	xflag[4]=0;		 yflag[4]=3;	zflag[4]=5;
	xflag[5]=5;		 yflag[5]=3;	zflag[5]=15;

	
	for(int side=0;side<6;side++) {
		for(int i=0;i<4;i++) {
			xx=((xflag[side]&(1<<i))>0)?x:-x;
			yy=((yflag[side]&(1<<i))>0)?y:-y;
			zz=((zflag[side]&(1<<i))>0)?z:-z;	
			n->AddVertex(new CVertex(xx,yy,zz));
		}

		int t = side <<2;
		//CTriangle t1(verts[t],verts[t+2],verts[t+3]);
		//CTriangle t2(verts[t],verts[t+3],verts[t+1]);

		n->AddTriangle(t,t+2,t+3);
		n->AddTriangle(t,t+3,t+1);
	}
	
	delete[] xflag;
	delete[] yflag;
	delete[] zflag;

	return n;
}

CObject* CObjectFactory::RotationObject(CVector* path,int nodes, int sides) {
	int steps = sides+1;
	CObject* n = new CObject();
	float alpha = (float)(2.0f*PI/((float)steps-1));
	float qx, qz;

	float u,v;

	for(int j=0;j<steps;j++) {
		u = (float)(steps-j-1)/(float)(steps-1);
		for(int i=0;i<nodes;i++) {
			CVector c = path[i];
			v = (float)i/(float)(steps-1);
			qx = c._x*cos(j*alpha)+c._z*sin(j*alpha);
			qz = c._z*cos(j*alpha)-c._x*math.sin(j*alpha);

			CVertex* vx = new CVertex(qx,c._y,qz);
			vx->SetUV(u,v);

			n->AddVertex(vx);
		}
	}

	for(int b=0;b<steps-1;b++) {
		for(int c=0;c<nodes-1;c++) {
			//n.AddTriangle(CTriangle(vertices.Atn(c+nodes*b),vertices.Atn(c+nodes*(b+1)),vertices.Atn(c+1+nodes*b)));
			//n.AddTriangle(CTriangle(vertices.Atn(c+nodes*(b+1)),vertices.Atn(c+1+nodes*(b+1)),vertices.Atn(c+1+nodes*b)));
			n->AddTriangle(c+nodes*b, c+nodes*(b+1), c+1+nodes*b);
			n->AddTriangle(c+nodes*(b+1), c+1+nodes*(b+1), c+1+nodes*b);
		}
	}

	for (int d=0;d<nodes-1;d++) {
		//n.AddTriangle(CTriangle(*vertices.At(d+nodes*(steps-1)),*vertices.At(d),*vertices.At(d+1+nodes*(steps-1))));
		n->AddTriangle(d+nodes*(steps-1),d,d+1+nodes*(steps-1));
		//n.AddTriangle(CTriangle(*vertices.At(d),*vertices.At(d+1),*vertices.At(d+1+nodes*(steps-1))));
		n->AddTriangle(d,d+1,d+1+nodes*(steps-1));
	}
	return n;
}



CObject* CObjectFactory::Cone(float height, float radius, int segments) {
	CVector* path = new CVector[5];
	float h = height/2;

	path[0] = CVector(0,h,0);
	path[1] = CVector(radius, -h, 0);
	path[2] = CVector(radius,-h, 0);
	path[3] = CVector(0,-h,0);

	CObject* ret =  RotationObject(path,4, segments);

	delete[] path;
	return ret;
}



CObject* CObjectFactory::Tube(CVector* path, int segments, float r, int steps, bool closed) {
		CVector* circle = new CVector[steps+1];

		float angle;
		for (int i=0; i<steps; i++) {
			angle=2*3.14159265f*(float)i/(float)steps;
			circle[i] = CVector(r*cos(angle),r*sin(angle),0.0f);
		}
		
		CObject* newObject = new CObject();
		CVector forward,up,right;
		CMatrix frenetmatrix;
		CVertex* tempvertex=0;
		float relx,rely;
		int a,b,c,d;
		
		for (int i=0; i<segments; i++) {
			// Calculate frenet frame matrix
			if (i!=segments-1) {
				forward = CVector::Subtract(path[i+1],path[i]);
			}
			else {
				if (!closed) {
					forward = CVector::Subtract(path[i],path[i-1]);
				}
				else {
					forward = CVector::Subtract(path[1],path[0]);
				}
			}
					
			forward.Normalize();
			up = CVector(0.0f,0.0f,1.0f);
			right = CVector::GetNormal(forward,up);
			up = CVector::GetNormal(forward,right);

			frenetmatrix= CMatrix(right,up,forward);
			frenetmatrix.Shift(path[i]._x,path[i]._y,path[i]._z);
		
			// Add nodes
			relx=(float)i/(float)(segments-1);
			for (int k=0; k<steps; k++) {
				rely=(float)k/(float)steps;
				
				tempvertex = new CVertex(circle[k].Transform(frenetmatrix));
				tempvertex->_u = relx;
				tempvertex->_v = rely;
				newObject->AddVertex(tempvertex);
			}
		}
		
		for (int i=0;i<segments-1;i++) {
			for (int k=0; k<steps-1; k++) {
				a=i*steps+k;
				b=a+1;
				c=a+steps;
				d=b+steps;
				newObject->AddTriangle(a,c,b);
				newObject->AddTriangle(b,c,d);
			}
			a=(i+1)*steps-1;
			b=a+1-steps;
			c=a+steps;
			d=b+steps;

			newObject->AddTriangle(a,c,b);
			//assert(vertices[d]._color._red<256&&vertices[d]._color._red>-1);
			newObject->AddTriangle(b,c,d);
		}
		
		delete[] circle;

		return newObject;
}


CObject* CObjectFactory::TorusKnot(float p, float q, float r_tube, float r_out, float r_in, float h, int segments, int steps) {
	float x,y,z,r,t,theta;
	
	CVector* path = new CVector[segments+1];
	for (int i=0;i<segments+1;i++) {
		t=2*3.14159265f*i/(float)segments;
		r=r_out+r_in*(float)cos(p*t);
		z=h*(float)math.sin(p*t);
		theta=q*t;
		x=r*(float)math.cos(theta);
		y=r*(float)math.sin(theta);
		path[i]=CVector(x,y,z);
	}
	
	CObject* to = Tube(path,segments+1,r_tube,steps, true);

	delete[] path;
	return to;
}


CObject* CObjectFactory::HeightField(float* data,int xmax,int ymax, float height, bool doublesided) {
	CObject* newObject = new CObject();
	CVertex* vertex;
	float xtemp,ytemp,ztemp;
	int q1,q2,q3,q4;
	float u,v;

	float xscale=2/(float)(xmax-1);
	float yscale=2/(float)(ymax-1);
	int doubleSideOffset = xmax*ymax;

	for (int i=0; i<xmax; i++) {
		u = (float)i/(float)(xmax-1);
		for (int j=0; j<ymax; j++) {
			v = (float)j/(float)(ymax-1);
			xtemp = -1+xscale*(float)i;
			ytemp = -1+yscale*(float)j;
			ztemp = data[i*xmax+j]*height;
			vertex = new CVertex(xtemp,ytemp,ztemp);
			vertex->_u = u;
			vertex->_v = v;
			newObject->AddVertex(vertex);
		}
	}

	if (doublesided) {	
		for(int i=0; i<xmax; i++) {
			u = (float)(xmax-i)/(float)xmax;
			for(int j=0; j<ymax; j++) {
				v = (float)j/(float)(ymax-1);
				xtemp = -1+xscale*(float)i;
				ytemp = -1+yscale*(float)j;
				ztemp = data[i*xmax+j]*height;
				vertex = new CVertex(xtemp,ytemp,ztemp);
				vertex->_u = u;
				vertex->_v = v;
				newObject->AddVertex(vertex);
			}
		}
	}

	for (int i=0; i<(xmax-1); i++) {
		for (int j=0; j<(ymax-1); j++) {
			q1=j+xmax*i;
			q2=j+1+xmax*i;
			q3=j+xmax*(i+1);
			q4=j+1+xmax*(i+1);

			newObject->AddTriangle(q1,q2,q3);
			newObject->AddTriangle(q2,q4,q3);
			if (doublesided) {
				newObject->AddTriangle(doubleSideOffset+q1,doubleSideOffset+q3,doubleSideOffset+q2);
				newObject->AddTriangle(doubleSideOffset+q2,doubleSideOffset+q3,doubleSideOffset+q4);
			}
		}
	}		
	return newObject;
}


CObject* CObjectFactory::Field3D(int resolution, float height) {
	float x,y;
	float* map = new float[resolution*resolution];
	
	for (int i=0;i<resolution;i++) {
		for (int j=0;j<resolution;j++) {
			x = (float)i/(float)resolution*2-1;
			y = (float)j/(float)resolution*2-1;
			map[i*resolution+j]=x*x*x*y-y*y*y*x+(float)(math.sin(x*y*10)/4-0.2);
		}
	}
	CObject* ret = HeightField(map, resolution, resolution, height, true);

	delete[] map;

	return ret;
}

/*
CObject CObjectFactory::Tube(CVector* path, int segments, float r, int steps, bool closed) {
	CVector* circle = new CVector[steps];
	CVertex* vertices = new CVertex[steps*segments];
	float angle;
	for(int i=0; i<steps; i++) {
		angle = 2*PI*(float)i/(float)steps;
		circle[i] = CVector(r*cos(angle),r*sin(angle),0.0f);
	}
	
	CObject newObject;
	CVector forward, up, right;
	CMatrix frenetmatrix;
	CVertex tempVertex;
	float relx, rely;
	int a,b,c,d;


	for(int i=0; i<segments; i++) {
		// calculate frenet frame matrix
		if(i!=segments-1) {
			forward = CVector::Subtract(path[i+1], path[i]);
		}
		else {
			if(!closed) {
				forward = CVector::Subtract(path[i], path[i-1]);
			}
			else {
				forward = CVector::Subtract(path[1], path[0]);
			}
		}

		forward.Normalize();
		up = CVector(0.0f, 0.0f, 1.0f);
		right = CVector::GetNormal(forward, up);
		up = CVector::GetNormal(forward, right);

		frenetmatrix = CMatrix(right, up, forward);
		frenetmatrix.Shift(path[i]._x, path[i]._y, path[i]._z);

		// add nodes
		relx = (float)i/(float)(segments-1);
		for(int k=0; k<steps; k++) {
			rely = (float)k/(float)steps;
			tempvertex = CVertex(circle[k].Transform(frenetmatrix));
			tempvertex._u = relx;
			tempvertex._v = rely;
			
			vertices[i*steps+k] = tempvertex;
		}
	}

	for(i=0; i<segments-1; i++) {
		for(k=0; k<steps-1; k++) {
			a = i*steps+k; 
			b = a+1;
			c = a+steps;
			d = b+steps;
			newObject.AddTriangle(CTriangle(vertices[a], vertices[c], vertices[b]));
			newObject.AddTriangle(CTriangle(vertices[b], vertices[c], vertices[d]));
		}

		a = (i+1)*steps-1;
		b = a+1-steps;
		c = a+steps;
		d = b+steps;

		newObject.AddTriangle(CTriangle(vertices[a], vertices[c], vertices[b]));
		newObject.AddTriangle(CTriangle(vertices[b], vertices[c], vertices[d]));
	}

	delete[] circle;
	delete[] vertices;
	delete[] path;

	return newObject;
}

CObject CObjectFactory::TorusKnot(float p, float q, float r_tube, float r_out, float r_in, float h, int segments, int steps) {
	float x, y, z, r, t, theta, temp;

	CVector* path = new CVector[segments+1];
	for(int i=0;i<segments+1;i++) {
		t = 2*PI*i/(float)segments;
		r = r_out+r_in*cos(p*t);
		z = h*sin(p*t);

		theta = q*t;
		x = r*cos(theta);
		y = r*sin(theta);
		path[i] = CVector(x,y,z);
	}

	return Tube(path, segments+1, r_tube, steps, true);
}*/
