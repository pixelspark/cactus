#include "../include/Sandstorm.h"

CLogger::CLogger() {
	if(!AllocConsole()) {
		//throw "Could not allocate console!";
	}

	_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if(_handle==0) {
		throw "Could not get handle for standard output";
	}
}

void CLogger::Write(const char* str) {
	WriteConsole(_handle,str,(DWORD)strlen(str),NULL,NULL);		
	WriteConsole(_handle,"\r\n",(DWORD)strlen("\r\n"),NULL,NULL);
}

void CLogger::WriteError(const char* str) {
	SetConsoleTextAttribute(_handle,FOREGROUND_RED|FOREGROUND_INTENSITY);
	Write(str);
	SetConsoleTextAttribute(_handle,0);
}

CLogger::~CLogger() {
	FreeConsole();
}


void CLogger::operator <<(const char* str) {
	Write(str);
}

void CLogger::WriteF(const char* fmt,...) {
	va_list args;
	char* buffer = new char[strlen(fmt)*2];

	va_start( args, fmt );
	vsprintf(buffer,fmt,args);
	va_end(args);

	Write(buffer);

	delete[] buffer;
}
