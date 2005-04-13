class MeshImporter {
	public:
		MeshImporter(const char* szFilename) {
			_file = ifstream(szFilename);

			if(_file.fail()) {
				throw "Failed.";
			}

		}
		~MeshImporter() {
		}

		int LoadFromFile(CScene* scene) {
			_scene = scene;
			
			ReadJunkHeader();
			if(_currentJunkID!=0x4D4D) {
				return FILE_INVALID;
			}

			endOfStream = false;
			while(!endOfStream) ReadNextJunk();
			return OK;
		}

	protected:
		unsigned char ReadChar() {
			unsigned char p;
			_file >> p;

			return p;
		}

		short ReadShort() {
			unsigned char loByte = ReadChar();
			unsigned char hiByte = ReadChar();
			return loByte | (hiByte<<8);
		}

		int ReadInt() {
			unsigned char first = ReadChar();
			unsigned char second = ReadChar();
			unsigned char third = ReadChar();
			unsigned char fourth = ReadChar();
			return first|(second<<8)|(third<<16)|(fourth<<24);
		}

		float ReadFloat() {
			int bits = ReadInt();
			float fl = *(float*)(&bits);
			return fl;

		/*	In all other cases, let s, e, and m be three values that can be computed from the argument: 

 int s = ((bits >> 31) == 0) ? 1 : -1;
 int e = ((bits >> 23) & 0xff);
 int m = (e == 0) ?
                 (bits & 0x7fffff) << 1 :
                 (bits & 0x7fffff) | 0x800000;
 Then the floating-point result equals the value of the mathematical expression s·m·2e-150. 

			int s = ((bits>>31)==0)?1:-1;
			int e = ((bits>>23) & 0xFF);
			int m = (e==0)?(bits & 0x7fffff) << 1:(bits & 0x7fffff) | 0x800000;

			float f = pow(s*m*2,e-150);

			return f;*/
		}

		void ReadString() {
			while(ReadChar()!=0) {
			}
		}

		void ReadJunkHeader() {
			_currentJunkID = ReadShort();
			_nextJunkOffset = ReadInt();

			endOfStream = _currentJunkID<0;
		}

		void ReadVertexList() {
			float x,y,z;
			int vertices = ReadShort();
			for (int i=0; i<vertices; i++) {
				x = ReadFloat();
				y = ReadFloat();
				z = ReadFloat();
				_currentObject->AddVertex(new CVertex(x,-y,z));
			}
		}

		void ReadPointList() {
			int v1,v2,v3;
			int triangles = ReadShort();
			for (int i=0; i<triangles; i++) {
				v1 = ReadShort();
				v2 = ReadShort();
				v3 = ReadShort();
				ReadShort();
				_currentObject->AddTriangle(v1,v2,v3);
			}
		}

		void ReadMappingCoordinates() {
			int vertices = ReadShort();
			for (int i=0; i<vertices; i++) {
				_currentObject->VertexAt(i)->_u = ReadFloat();
				_currentObject->VertexAt(i)->_v = ReadFloat();
			}
		}

		void ReadNextJunk() {
			ReadJunkHeader();
			
			switch(_currentJunkID) {
				case 0x3D3D:
					return; // mesh block
				case 0x4000:
					ReadString();
					return;
				case 0x4100:
					_currentObject = new CObject();
					_currentObject->_material.SetMode(PHONG);
					_currentObject->_material.SetColor(CColor(0,0,100));
					_scene->AddObject(_currentObject);
					return;
				case 0x4110:
					ReadVertexList();
					return;
				case 0x4120:
					ReadPointList();
					return;
				case 0x4140:
					ReadMappingCoordinates();
					return;
			}

			SkipJunk();
		}

		void SkipJunk() {			
			for (int i=0; (i<_nextJunkOffset-6)&&(!endOfStream);i++) {
				endOfStream=ReadChar()<0;
			}
		}

		OFSTRUCT _openFileStruct;
		short _currentJunkID;
		int _nextJunkOffset;
		CObject* _currentObject;
		CScene* _scene;
		bool endOfStream;
		ifstream _file;
};