#ifndef __PLUGIN_TEST__
#define __PLUGIN_TEST__

#include <windows.h>
#define dlopen(P,G) (void*)LoadLibrary(P)
#define dlsym(D,F) (void*)GetProcAddress((HMODULE)D,F)
#define dlclose(D) FreeLibrary((HMODULE)D)

class Test{
	
public:
	virtual const char *version() = 0;
	virtual ~Test(){};
};

#endif