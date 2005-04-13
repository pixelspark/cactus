/* ---------------------------------------------------------------------------------------------------------------------------------------------------
Copyright (C) 2003 Tommy van der Vorst

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

#ifndef __CCACTUS_POSTEFFECT_H
#define __CCACTUS_POSTEFFECT_H

class CACTUS_API CPostEffect {
	public:
		CPostEffect() {
			_next = 0;
		}
	
		virtual ~CPostEffect(){
			_next = 0;
		}

		/// Subclass this class and implement this method to perform an effect
		virtual void ProcessImage (int *buffer, int width, int height)=0;

		void Call(int* buffer,int width,int height) {
			ProcessImage(buffer,width,height);
			Next(buffer,width,height);
		}
		
		void Link(CPostEffect* l) {
			_next = l;
		}

		CPostEffect* GetNext() {
			return _next;
		}
	protected:
		void Next(int* buffer,int width,int height) {
			if(_next!=0) {
				_next->ProcessImage(buffer,width,height);
			}
		}
	

	private:
		CPostEffect* _next;
};

class CACTUS_API CPreEffect: public CPostEffect {
};

#endif 
