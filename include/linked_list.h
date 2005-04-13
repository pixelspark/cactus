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


// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Header file for the CLinkedList class.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _CLINKEDLIST_CLASS
#define _CLINKEDLIST_CLASS

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Class for usage with our linked list. A linked list tends to be very fast, however it is very slow on random access.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
template<class T> class CLinkedListEntry {	
	public:
		CLinkedListEntry(T entry,CLinkedListEntry* next) {
			_data = entry;
			_next = next;
		}

		virtual ~CLinkedListEntry() {
		}

		CLinkedListEntry(T& entry) {
			_data = T(entry);
			_next = 0;
		}

		CLinkedListEntry* GetNext() {
			return _next;
		}

		void SetNext(CLinkedListEntry* next) {
			_next = next;
		}

		inline T GetEntry() {
			return _data;
		}

		inline T* GetEntryPointer() {
			return &_data;
		}

		void SetEntry(T entry) {
			_data = entry;
		}
	protected:
		T _data;
		CLinkedListEntry* _next;
};




// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Linked-List class. A linked list is a very fast list as explained above. It is based on the principal that each element holds a pointer
// to the next element. A linked list does not consume very much memory and looping through it is quite easy.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
#pragma warning(disable: 4251)
template<class T> class CLinkedList {
	public:
		CLinkedList() {
			_first = 0;
			_last = 0;
			_count = 0;
			_current = 0;
		}

		int GetCount() {
			return _count;
		}
		
		T* operator [](int index) {
			return At(index);
		}

		virtual ~CLinkedList() {
			// delete entries here
			//Empty(); 
		}

		void Empty() {
			CLinkedListEntry<T>* current = _first;
			CLinkedListEntry<T>* c = _first;

			while(current!=0) {
				current = c->GetNext();
				delete c;
				c = current;
			}

			_first = 0;
			_count = 0;
		}

		void Assign(int index,T w) {
			assert(index>=0);

			CLinkedListEntry<T>* cur;
			if(index==0) {
				cur = _first;
			}
			else {
				cur = _first;
				
				if(cur!=0) {
					for(int a=0;a<index;a++) {
						cur = cur->GetNext();
					}
				}
				else {
					return; // index bestaat niet
				}
			}

			if(cur!=0) {
				cur->SetEntry(w);
			}
		}

		T* At(int index) {
			assert(index>=0);
			if(index==0) {
				return _first->GetEntryPointer();
			}
			if(index==_count-1) {
				return _last->GetEntryPointer();
			}

			CLinkedListEntry<T>* cur = _first;
			for(int a=0;a<index-1;a++) {
				cur = cur->GetNext();
			}

			//_current = cur;
			return cur->GetEntryPointer();
		}

		T Atn(int index) {
			assert(index>=0);
			if(index==0) {
				return _first->GetEntry();
			}
			if(index==_count-1) {
				return _last->GetEntry();
			}

			CLinkedListEntry<T>* cur = _first;
			for(int a=0;a<index-1;a++) {
				cur = cur->GetNext();
			}

			//_current = cur;
			return cur->GetEntry();
		}

		inline T* Add(T item) {
			CLinkedListEntry<T>* en = new CLinkedListEntry<T>(item);

			if(_last!=0) {
				_last->SetNext(en);
				_last = en;
			}
			else {
				_last = en;
			}

			if(_first==0) {
				_first = en;
			}

			_count++;
			return en->GetEntryPointer();
		}

		inline T* Next() {
			if(_current==0) {
				_current = _first;
				return _current->GetEntryPointer();
			}
			else {
				_current = _current->GetNext();
				return _current->GetEntryPointer();
			}
		}

		inline T NextStack() {
			if(_current==0) {
				_current = _first;
				return _current->GetEntry();
			}
			else {
				_current = _current->GetNext();
				return _current->GetEntry();
			}
		}

		inline bool HasNext() {
			if(_first==0) {
				return false;
			}

			if(_current==0&&_first!=0) {
				return true;
			}
			
			if(_current->GetNext()==0) {
				return false;
			}
			else {
				return true;
			}	
		}

		inline void Restart() {
			_current = 0;
		}
	private:
		CLinkedListEntry<T>* _first;
		CLinkedListEntry<T>* _last;
		CLinkedListEntry<T>* _current;
		int _count;
};

#endif