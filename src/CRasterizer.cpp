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

CRasterizer::CRasterizer() {
	_lightmap = 0;
	_renderer = 0;
	_mode = FLAT;
	_height = 0;
	_width = 0;
	_envmap = 0;
	
	// lots of initializations
	tw = th = tbitW = tbitH = 0;
	z = dz = z1 = z2 = z3 = z4 = zBase = dzBase = 0.0f;

	 lutID = r = 
	x1 = x2 = x3 = x4 = y1 = y2 = y3 = 
	x = y = k = dx = dy = offset = pos = temp = 
	xL = xR = xBase = xMax = yMax = dxL = dxR =  
	nx1 = nx2 = nx3 = nx4 = ny1 = ny2 = ny3 = ny4 = 
	nxBase = nyBase = 
	dnx4 = dny4 = 
	dnx = dny = nx = ny = 
	dnxBase = dnyBase = 
	tx1 = tx2 = tx3 = tx4 = ty1 = ty2 = ty3 = ty4 = 
	txBase = tyBase = 
	dtx4 = dty4 = 
	dtx = dty = tx = ty = 
	dtxBase = dtyBase = 0;
}

CRasterizer::CRasterizer(CRenderer* rend) {
	_renderer = rend;
	_lightmap = 0;
	//RebuildReferences();

	// lots of initializations
	tw = th = tbitW = tbitH = 0;
	lutID  = 
	x1 = x2 = x3 = x4 = y1 = y2 = y3 = 
	x = y =  k = dx = dy = offset = pos = temp = 
	xL = xR = xBase =  xMax = yMax = dxL = dxR = 
	nx1 = nx2 = nx3 = nx4 = ny1 = ny2 = ny3 = ny4 = 
	nxBase = nyBase = 
	dnx4 = dny4 = 
	dnx = dny = nx = ny = 
	dnxBase = dnyBase = 
	tx1 = tx2 = tx3 = tx4 = ty1 = ty2 = ty3 = ty4 = 
	txBase = tyBase = 
	dtx4 = dty4 = 
	dtx = dty = tx = ty = 
	dtxBase = dtyBase = 0;
}

void CRasterizer::RebuildReferences() {
	assert(_renderer!=0);

	_height = _renderer->GetScene()->GetHeight();
	_width = _renderer->GetScene()->GetWidth();
	_zbuffer = &(_renderer->_zbuffer);
}

CRasterizer::~CRasterizer() {
	_height = 0;
	_width = 0;
	_zbuffer = 0;
	lutID =
	x1 = x2 = x3 = x4 = y1 = y2 = y3 = 
	x = y =  k = dx = dy =  offset = pos = temp = 
	xL = xR = xBase =  xMax = yMax = dxL = dxR = 
	nx1 = nx2 = nx3 = nx4 = ny1 = ny2 = ny3 = ny4 = 
	nxBase = nyBase = 
	dnx4 = dny4 = 
	dnx = dny = nx = ny = 
	dnxBase = dnyBase = 
	tx1 = tx2 = tx3 = tx4 = ty1 = ty2 = ty3 = ty4 = 
	txBase = tyBase = 
	dtx4 = dty4 = 
	dtx = dty = tx = ty = 
	dtxBase = dtyBase = 0;
}

void CRasterizer::Render(CTriangle* tri) {
	//RebuildReferences();
	_currentTriangle = tri;

	CVertex* p1=tri->_a;
	CVertex* p2=tri->_b;
	CVertex* p3=tri->_c;
	CVertex* tempVertex;
		
	if (p1->_y>p2->_y) {
		tempVertex=p1;
		p1=p2;
		p2=tempVertex;
	}

	if (p2->_y>p3->_y) {
		tempVertex=p2;
		p2=p3;
		p3=tempVertex; 
	}
	if (p1->_y>p2->_y) {
		tempVertex=p1;
		p1=p2;
		p2=tempVertex;
	}
	
	if (p1->_y>=_height) {
		return;
	}
	if (p3->_y<0) {
		return;
	}
	if (p1->_y==p3->_y) {
		return;
	}
	
	if ((_mode&(~WIREFRAME))==FLAT) {
		lutID = (int) (tri->n2._x*127+127)+((int)(tri->n2._y*127+127)<<8); // +127

		c = CColor::Multiply(color,_lightmap->diffuse[lutID]);
		
		s = CColor::Scale(_lightmap->specular[lutID],reflectivity);
		currentColor = CColor::Add(c,s);
	}

	
	x1=p1->_x<<8;
	x2=p2->_x<<8;
	x3=p3->_x<<8;
	y1=p1->_y;
	y2=p2->_y;
	y3=p3->_y;
	
	x4=x1+(x3-x1)*(y2-y1)/(y3-y1);
	x1<<=8; x2<<=8; x3<<=8; x4<<=8;

	z1 = p1->_z;
	z2 = p2->_z;
	z3 = p3->_z;
	nx1=p1->nx<<16;
	nx2=p2->nx<<16;
	nx3=p3->nx<<16;
	ny1=p1->ny<<16;
	ny2=p2->ny<<16;
	ny3=p3->ny<<16;

	tx1=p1->tx<<16;
	tx2=p2->tx<<16;
	tx3=p3->tx<<16;
	ty1=p1->ty<<16;
	ty2=p2->ty<<16;
	ty3=p3->ty<<16;
	
	dx=(x4-x2)>>16;
	if (dx==0) return;
	
	temp=256*(y2-y1)/(y3-y1);
	
	z4=z1+((z3-z1)/(float)pow(2,8))*temp; // 	z4=z1+((z3-z1)>>8)*temp;
	nx4=nx1+((nx3-nx1)>>8)*temp;
	ny4=ny1+((ny3-ny1)>>8)*temp;
	tx4=tx1+((tx3-tx1)>>8)*temp;
	ty4=ty1+((ty3-ty1)>>8)*temp;

	dz=(z4-z2)/dx;
	dnx=(nx4-nx2)/dx;
	dny=(ny4-ny2)/dx;
	dtx=(tx4-tx2)/dx;
	dty=(ty4-ty2)/dx;


	if (dx<0)
	{ 
		temp=x2; x2=x4; x4=temp; 
		z2=z4;
		tx2=tx4;
		ty2=ty4;
		nx2=nx4;
		ny2=ny4;
	}
	if (y2>=0)
	{
		dy=y2-y1;
		if (dy!=0)
		{
			dxL=(x2-x1)/dy;
			dxR=(x4-x1)/dy;
			dzBase=(z2-z1)/dy;
			dnxBase=(nx2-nx1)/dy;
			dnyBase=(ny2-ny1)/dy;
			dtxBase=(tx2-tx1)/dy;
			dtyBase=(ty2-ty1)/dy;
		}
					
		xBase=x1;
		xMax=x1;
		zBase=z1;
		nxBase=nx1;
		nyBase=ny1;
		txBase=tx1;
		tyBase=ty1;
		
		if (y1<0)
		{
			xBase-=y1*dxL;
			xMax-=y1*dxR;
			zBase-=y1*dzBase;
			nxBase-=y1*dnxBase;
			nyBase-=y1*dnyBase;
			txBase-=y1*dtxBase;
			tyBase-=y1*dtyBase;
			y1=0;
		}
		
		y2=(y2<_height)?y2:_height;
		offset=y1*_width;
		for (y=y1;y<y2;y++) RenderLine();
	}
	
	if (y2<_height)
	{
		dy=y3-y2;
		if (dy!=0)
		{
			dxL=(x3-x2)/dy;
			dxR=(x3-x4)/dy;
			dzBase=(z3-z2)/dy;
			dnxBase=(nx3-nx2)/dy;
			dnyBase=(ny3-ny2)/dy;
			dtxBase=(tx3-tx2)/dy;
			dtyBase=(ty3-ty2)/dy;	
		}
						
		xBase=x2;
		xMax=x4;
		zBase=z2;
		nxBase=nx2;
		nyBase=ny2;
		txBase=tx2;
		tyBase=ty2;
		
		if (y2<0)
		{
			xBase-=y2*dxL;
			xMax-=y2*dxR;
			zBase-=y2*dzBase;
			nxBase-=y2*dnxBase;
			nyBase-=y2*dnyBase;
			txBase-=y2*dtxBase;
			tyBase-=y2*dtyBase;
			y2=0;
		}
		
		y3=(y3<_height)?y3:_height;
		offset=y2*_width;
		

		for (y=y2;y<y3;y++) RenderLine();
	}

	// Draw a wireframe
	if ((_mode&WIREFRAME)!=0) {
		DrawWireframe(tri);
	}
	if((_mode&VERTICES)!=0) {
		DrawDot((int)tri->_a->_x, (int)tri->_a->_y, tri->_a->_z, color);
		DrawDot((int)tri->_b->_x, (int)tri->_b->_y, tri->_b->_z, color);
		DrawDot((int)tri->_c->_x, (int)tri->_c->_y, tri->_c->_z, color);
	}
}


void CRasterizer::DrawWireframe(CTriangle* tri) {
	DrawLine(tri->_a,tri->_b,CColor(color));
	DrawLine(tri->_b,tri->_c,CColor(color));
	DrawLine(tri->_c,tri->_a,CColor(color));
}

void CRasterizer::DrawLine(int x1, int y1, int z1,int x2, int y2, int z2, CColor &c) {
	int x3,y3,z3;
	dx = (int)(abs((int)x1-(int)x2));
	dy = (int)(abs((int)y1-(int)y2));
	dz=0;

	if (dx>dy) {
		if (x1>x2) {
			x3 = x1;
			y3 = y1;
			z3 = z1;
			
			x1 = x2;
			y1 = y2;
			z1 = z2;

			x2 = x3;
			y2 = y3;
			z2 = z3;
		}
				
		if (dx>0) {
			dz = (float)((z2-z1)/dx);
			dy = (((int)(y2-y1)<<16)/dx);
		}
		
		z = (float)z1;
		y = y1<<16;
		for(x=x1;x<=x2;x++) {
			y2=y>>16;
			if (Inrange(x,0,_width-1)&&Inrange(y2,0,_height-1)) {
				offset=y2*_width;
				float gz = _zbuffer->Get(x,y2);

				_canvas->DrawTexel(x,y2,c);
					
			} 
			z+=dz;
			y+=dy;	
		}
	}
	else {
		if (y1>y2){ 
			//temp=a;
			x3 = x1;
			y3 = y1;
			z3 = z1;
			
			x1 = x2;
			y1 = y2;
			z1 = z2;

			x2 = x3;
			y2 = y3;
			z2 = z3;
		}
		if (dy>0) {
			dz = (float)((z2-z1)/dy);
			dx = ((int)(x2-x1)<<16)/dy;
		}
		z = (float)z1;
		x= (int)(x1)<<16;

		for(y=(int)y1;y<=y2;y++) {
			x2=x>>16;
			if (Inrange(x2,0,_width-1)&&Inrange(y,0,_height-1)) {
				offset=y*_width;
				if (z<_zbuffer->Get(x2,y)) {
					_canvas->DrawTexel(x2,y,c);
					_zbuffer->Put(x2,y,z);
				}
			}
			z+=dz;
			x+=dx; 
		}
	}
}

void CRasterizer::DrawLine(CVertex* a, CVertex* b, CColor &c) {
	CVertex* temp;
	if((a->clipcode&b->clipcode)!=0) {
		return;
	}

	dx = (int)(abs((int)a->_x-(int)b->_x));
	dy = (int)(abs((int)a->_y-(int)b->_y));
	dz=0;

	if (dx>dy) {
		if (a->_x>b->_x) {
			temp=a; 
			a=b;
			b=temp;
		}
				
		if (dx>0) {
			dz = ((b->_z-a->_z)/dx);
			dy=(((int)(b->_y-a->_y)<<16)/dx);
		}
		
		z = a->_z;
		y=(int)a->_y<<16;
		for(x=(int)a->_x;x<=b->_x;x++) {
			y2=y>>16;
			if (Inrange(x,0,_width-1)&&Inrange(y2,0,_height-1)) {
				offset=y2*_width;
				float gz = _zbuffer->Get(x,y2);

				if (z<gz||gz<0) {
					_canvas->DrawTexel(x,y2,c);
					_zbuffer->Put(x,y2,z);	
				}
			} 
			z+=dz;
			y+=dy;	
		}
	}
	else {
		if (a->_y>b->_y){ 
			temp=a;
			a=b;
			b=temp;
		}
		if (dy>0) {
			dz=((b->_z-a->_z)/dy);
			dx=((int)(b->_x-a->_x)<<16)/dy;
		}
		z=a->_z;
		x= (int)(a->_x)<<16;
		for(y=(int)a->_y;y<=b->_y;y++) {
			x2=x>>16;
			if (Inrange(x2,0,_width-1)&&Inrange(y,0,_height-1)) {
				offset=y*_width;
				if (z<_zbuffer->Get(x2,y)) {
					_canvas->DrawTexel(x2,y,c);
					_zbuffer->Put(x2,y,z);
				}
			}
			z+=dz;
			x+=dx; 
		}
	}
}

void CRasterizer::RenderLine() {
	yXwidth = y*_width;
	xL=xBase>>16;
	xR=xMax>>16;
	z=zBase;
	nx=nxBase;
	ny=nyBase;
	tx=txBase;
	ty=tyBase;
	

	if (xL<0) {
		z-=xL*dz;
		nx-=xL*dnx;
		ny-=xL*dny;
		tx-=xL*dtx;
		ty-=xL*dty;
		xL=0;
	}

	xR = (xR<_width)?xR:_width;

	int m = _mode&(~WIREFRAME)&(~VERTICES);
	if(m==(PHONG|ENVMAP)) RenderLinePE();
	else if (m==FLAT) RenderLineF();
	else if (m==TEXTURED) RenderLineT();
	else if (m==PHONG) RenderLineP();
	else if (m==(PHONG|TEXTURED)) RenderLinePT();
	else if (m==(PHONG|ENVMAP|TEXTURED)) RenderLinePET();	
	
	offset+=_width;
	xBase+=dxL;
	xMax+=dxR;
	zBase+=dzBase;
	nxBase+=dnxBase;
	nyBase+=dnyBase;
	txBase+=dtxBase;
	tyBase+=dtyBase;	
}

void CRasterizer::RenderLineF() {
	float gz;

	for(x=xL;x<xR;x++) {
		pos = x+offset;

		gz = _zbuffer->Get(x,y);


		if(z<gz||gz<0) {
			_canvas->At(x,y,bkgrd);
			c = CColor::Transparency(bkgrd,currentColor,transparency);
				
			_canvas->_buffer[yXwidth+x] = c;
			_zbuffer->_array[yXwidth+x] = z;
			if(_renderer->_populateIDBuffer) _renderer->_IDBuffer[yXwidth+x] = _currentTriangle;
		}
		
		z += dz;
	}
}

void CRasterizer::RenderLineT() {
	float gz = 0;

	for(x=xL;x<xR;x++) {
		pos = x+offset;
		gz = _zbuffer->Get(x,y);

		if(z<gz||gz<0) {
			_canvas->At(x,y,bkgrd);
			
			int index = ((tx>>16)&tw) + (((ty>>16)&th) << tbitW);
			c = texture->_pixel[index]; // change!

			c = CColor::Transparency(bkgrd,c,transparency);
			_canvas->_buffer[y*_width+x] = c;
			_zbuffer->_array[yXwidth+x] = z;
			if(_renderer->_populateIDBuffer) _renderer->_IDBuffer[yXwidth+x] = _currentTriangle;
		}

		z += dz;
		tx += dtx;
		ty += dty;
	}
}

void CRasterizer::RenderLinePT() {
	float gz = 0;

	for (x=xL;x<xR;x++) {
		pos=x+offset;
		gz = _zbuffer->Get(x,y);

		if(z<gz||gz<0) {
			lutID=((nx>>16)&255)+(((ny>>16)&255)<<8);
			
			 _canvas->At(x,y,bkgrd);
			int index = ((tx>>16)&tw) + (((ty>>16)&th) << tbitW);
			c = texture->_pixel[index]; // change!
			c = CColor::Multiply(c,_lightmap->diffuse[lutID]);
			s = _lightmap->specular[lutID];
			s = CColor::Scale(s,reflectivity);
			c = CColor::Transparency(bkgrd,c,transparency);
			c = CColor::Add(c,s);
								
			_canvas->_buffer[yXwidth+x] = c;
			_zbuffer->_array[yXwidth+x] = z;
			if(_renderer->_populateIDBuffer) _renderer->_IDBuffer[yXwidth+x] = _currentTriangle;
		}
		z+=dz;
		nx+=dnx;
		ny+=dny;
		tx+=dtx;
		ty+=dty;
	}
}


void CRasterizer::LoadMaterial(CMaterial* material) {
	texture = &material->texture;
	color = material->color.ToInt();
	transparency = material->transparency;
	reflectivity = material->reflectivity;
	
	tw=texture->_width-1;
	th=texture->_height-1;
	tbitW=texture->_bitWidth;
	tbitH=texture->_bitHeight;

	_mode = material->mode;
	_envmap = material->envmap._pixel;
	_bumpmap = &material->bumpmap;
}

void CRasterizer::LoadLightmap(CLightmap* lightmap) {
	_lightmap = lightmap;
}

void CRasterizer::RenderLineP() {
	assert(_lightmap!=0);
	float gz;

	for(x=xL;x<xR;x++) {
		pos = x+offset;
		
		gz = _zbuffer->Get(x,y);

		_canvas->At(x,y,bkgrd);
		if(z<gz||gz<0) {
			lutID=((nx>>16)&255)+(((ny>>16)&255)<<8);
			c = CColor::Multiply(color,_lightmap->diffuse[lutID]);
			s = _lightmap->specular[lutID];
			s = CColor::Scale(s,reflectivity);
			c = CColor::Add(c,s);
			c = CColor::Transparency(bkgrd,c,transparency);
										
			_canvas->_buffer[yXwidth+x] = c;
			_zbuffer->_array[yXwidth+x] = z;
			if(_renderer->_populateIDBuffer) _renderer->_IDBuffer[yXwidth+x] = _currentTriangle;
		}
		z+=dz;
		nx+=dnx;
		ny+=dny;
	}	
}

void CRasterizer::DrawDot(int x, int y, float z, int color) {
	if(x<0) return;
	if(y<0) return;
	if(x>_width) return;
	if(y>_height) return;
	
	float gz = _zbuffer->Get(x,y);
	if (!(z<gz||gz<0)) {
		return;
	}

	_canvas->_buffer[y*(this->_width)+x] = color;

	if(x-1>0) {
		_canvas->_buffer[y*(this->_width)+x-1] = color;
	}
	if(x+1<_width) {
		_canvas->_buffer[y*(this->_width)+x+1] = color;
	}
	if(y-1>0) {
		_canvas->_buffer[(y-1)*(this->_width)+x] = color;
	}
	if(y+1<_height) {
		_canvas->_buffer[(y+1)*(this->_width)+x] = color;
	}
}

void CRasterizer::RenderLinePE() {
	assert(_lightmap!=0);
	float gz;

	for(x=xL;x<xR;x++) {
		pos = x+offset;
		gz = _zbuffer->_array[yXwidth+x];
		
		if(z<gz||gz<0) {
			lutID=((nx>>16)&255)+(((ny>>16)&255)<<8);
			_canvas->At(x,y,bkgrd);
			c = CColor::Multiply(color,_lightmap->diffuse[lutID]);
			s = CColor::Add(_lightmap->specular[lutID], _envmap[lutID]);
			s = CColor::Scale(s,reflectivity);
			c = CColor::Add(c,s);
			c = CColor::Transparency(bkgrd,c,transparency);

			_canvas->_buffer[yXwidth+x] = c;
			_zbuffer->_array[yXwidth+x] = z;
			if(_renderer->_populateIDBuffer) _renderer->_IDBuffer[yXwidth+x] = _currentTriangle;
		}

		z+=dz;
		nx+=dnx;
		ny+=dny;
	}	
}

void CRasterizer::RenderLinePET() {
	assert(_lightmap!=0);
	float gz;

	for(x=xL;x<xR;x++) {
		pos = x+offset;
		gz = _zbuffer->_array[yXwidth+x];
		
		if(z<gz||gz<0) {
			lutID=((nx>>16)&255)+(((ny>>16)&255)<<8);
			_canvas->At(x,y,bkgrd);
			c = texture->_pixel[((tx>>16)&tw)+(((ty>>16)&th)<<tbitW)];
			c = CColor::Multiply(c,_lightmap->diffuse[lutID]);
			s = CColor::Add(_lightmap->specular[lutID], _envmap[lutID]);
			s = CColor::Scale(s,reflectivity);
			c = CColor::Add(c,s);
			c = CColor::Transparency(bkgrd,c,transparency);

			_canvas->_buffer[yXwidth+x] = c;
			_zbuffer->_array[yXwidth+x] = z;
			if(_renderer->_populateIDBuffer) _renderer->_IDBuffer[yXwidth+x] = _currentTriangle;
		}

		z+=dz;
		nx+=dnx;
		ny+=dny;
		tx+=dtx;
		ty+=dty;
	}	
}

void CRasterizer::RenderLinePEB() {
	assert(_lightmap!=0);
	float gz;
	int slopeHorizontal, slopeVertical, bumpHeight;
	int nnx, nny;

	for(x=xL;x<xR;x++) {
		pos = x+offset;
		gz = _zbuffer->_array[yXwidth+x];
		
		if(z<gz||gz<0) {
			bumpHeight = _bumpmap->_pixel[((tx>>16)&tw)+(((ty>>16)&th)<<tbitW)];
			int bumpHeightRight = _bumpmap->_pixel[(((tx+dtx)>>16)&tw)+((((ty+dty)>>16)&th)<<tbitW)];
			int bumpHeightLeft = _bumpmap->_pixel[(((tx-dtx)>>16)&tw)+((((ty-dty)>>16)&th)<<tbitW)];
			slopeHorizontal = bumpHeightRight - bumpHeightLeft;
			slopeVertical = 0;

			// do bumpmap things
			nnx = slopeHorizontal;
			nny = slopeVertical;
			// lighting
			lutID=((nnx>>16)&255)+(((nny>>16)&255)<<8);

			_canvas->At(x,y,bkgrd);
			c = CColor::Multiply(color,_lightmap->diffuse[lutID]);
			s = CColor::Add(_lightmap->specular[lutID], _envmap[lutID]);
			s = CColor::Scale(s,reflectivity);
			c = CColor::Add(c,s);
			c = CColor::Transparency(bkgrd,c,transparency);
			if(_renderer->_populateIDBuffer) _renderer->_IDBuffer[yXwidth+x] = _currentTriangle;

			_canvas->_buffer[yXwidth+x] = c;
			_zbuffer->_array[yXwidth+x] = z;
		}

		z+=dz;
		nx+=dnx;
		ny+=dny;
		tx+=dtx;
		ty+=dty;
	}	
}

