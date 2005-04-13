// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Package of classes for smart pointers. Smart pointers are used to avoid many poroblems that may show up while using pointers,
// such as accessing NULL-memory. Read more on:
// http://www.flipcode.com/cgi-bin/msg.cgi?showThread=COTD-SmartPointersGM&forum=cotd&id=-1 .
//
// ---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _SMARTPOINTER_CLASS
#define _SMARTPOINTER_CLASS

namespace smartpointer {

template<class T> class Ptr {
	public:
		void Delete(); // Deletes the object/array being pointed to. Resets all other smart-pointers pointing to this object to NULL.
		void Remove(); // Stops pointing to the current address, points to NULL instead.
		void New(long count=1); // Creates a new object or array on the heap.
		void Copy(int extra=0); // Creates a copy of the object/array pointed to and starts pointing there. Adds extra elements if neccessary.
		int ArraySize(); // Returns the size of the array being pointed to. If pointing to a single object, this returns 1.
		void CopyElements(Ptr& a,unsigned int sb,unsigned int se,unsigned int db);
		Ptr() {
			_next = 0;
			_pointer = 0;
			_prev = 0;
			_size = 0;
		}
		Ptr(Ptr& a) {
			_next = 0;
			_pointer = 0;
			_prev = 0;
			_size = 0;

			Assign(a);
		}
		virtual ~Ptr(); // calls Remove();
		inline T& operator*();
		inline T* operator ->();
		inline T* operator +(long index);
		inline T& operator[](long index);
		inline T& operator==(Ptr compare); // compare pointers
		inline operator bool();
		inline Ptr& operator = (Ptr a);
		inline T* Address(); // 1337 p01nt3r h4x0rz only
		void Assign(Ptr& a);

	protected:
		T* _pointer;
		Ptr* _prev;
		Ptr* _next;
		int _size;

};
}
#endif