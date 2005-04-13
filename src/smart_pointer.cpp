// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Method definitions for our smart-pointer class.
//
// TODO:
// - Operator = and == don't compile right, disabled right now.
// - Throw errors on invalid arguments
// ---------------------------------------------------------------------------------------------------------------------------------------------------
#include "../include/smart_pointer.h"

namespace smartpointer {

template<class T> void Ptr<T>::Delete() {
	Ptr* a;
	if(_pointer) {
		if(_size>1) {
			delete[] _pointer;
		}
		else {
			delete _pointer;
		}

		a = this;
		while(a) {
			a->_pointer = 0;
			a = a->_prev;
		}

		a = _next;
		while(a) {
			a->_pointer = 0;
			a = a->_next;
		}
	}

	_size = 0;
}

template<class T> void Ptr<T>::Remove() {
	if(_prev) {
		_prev->_next = _next;
	}

	if(_next) {
		_next->_prev = _prev;
	}

	if(!_prev&&!_next) {
		Delete();
	}

	_pointer = 0;
	_prev = 0;
	_next = 0;
	_size = 0;
}

template<class T> void Ptr<T>::Assign(Ptr& a) {
	Remove();

	_prev = &a;
	_next = a._next;

	if(a._next) {
		a._next->_prev = this;
	}

	a._next = this;
	_pointer = a._pointer;
	_size = a._size;
}

template<class T> void Ptr<T>::New(long count) {
	Remove();
	if(count==1) {
		_pointer = new T;
	}
	else {
		_pointer = new T[count];
	}

	_size = count;
}

template<class T> void Ptr<T>::Copy(int extra) {
	if(!_pointer) {
		return;
	}

	if(!_next && !_prev) {
		return;
	}

	T* p;
	p = _pointer;

	New(_size+extra);
	memcpy(_pointer,p,sizeof(T)*_size);
}

template<class T> int Ptr<T>::ArraySize() {
	return _size;
}

template<class T> void Ptr<T>::CopyElements(Ptr<T>& a,unsigned int sb,unsigned int se, unsigned int db) {
	if(!_pointer) {
		return;
	}

	if(!a._pointer) {
		return;
	}

	if(db>=_size) {
		return;
	}

	if(sb>=a._size) {
		return;
	}

	if(se>=a._size) {
		se = a._size-1;
	}

	if(db+(se-sb) >= a._size) {
		se = _size-1-(db-sb);
	}

	memcpy(_pointer+db,a._pointer+sb, se-sb+1);
}

template<class T> Ptr<T>::~Ptr() {
	Remove();
}

template<class T> T& Ptr<T>::operator *() {
	if(!_pointer) {
		// throw an error here?
	}

	return *_pointer;
}

template<class T> T* Ptr<T>::operator ->() {
	if(!_pointer) {
		// throw something :-)
	}

	return _pointer;
}

template<class T> T* Ptr<T>::operator +(long index) {
	if(!_pointer) {
		// throoooow!
	}

	if(index<0) {
		// throooowww!
	}

	if(index>_size) {
		// throooooww!
	}

	return _pointer+index;
}

template<class T> T& Ptr<T>::operator [](long index) {
	if(!_pointer) {
		// throoooow!
	}

	if(index<0) {
		// throooowww!
	}

	if(index>_size) {
		// throooooww!
	}

	return _pointer[index];
}

/*
template<class T> bool Ptr<T>::operator==(Ptr compare) {
	return (_pointer==compare._pointer);
}*/

template<class T> Ptr<T>::operator bool() {
	if(_pointer) {
		return true;
	}
	return false;
}

/*
template<class T>
Ptr<T>& Ptr<T>::operator=(Ptr& a) {
	Assign(a);
	return a;
}
*/

template<class T> T* Ptr<T>::Address() {
	return _pointer;
}

}