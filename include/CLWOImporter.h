#ifndef __CACTUS_CLWOIMPORTER_H
#define __CACTUS_CLWOIMPORTER_H

/** Use this class to import LWO (Lightwave) object data from a file into cactus. Does not work 100% (yet). **/
class CACTUS_API CLWOImporter {
	public:
		CLWOImporter() {
		}
		~CLWOImporter() {
		}

		CObject* FromLWO(const char* filename);

	private:
		unsigned short SwapEndian (unsigned short num);
		unsigned long SwapEndian (unsigned long num);
		float SwapEndian (float num);
		bool read_pnts (unsigned short size, FILE *file, CObject *pObject);
		bool read_polys (unsigned short size, FILE *file, CObject *pObject);
		bool read_srfs (unsigned short size, FILE *file, CObject *pObject);

};

#endif