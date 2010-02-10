/*
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
*/
#ifdef _WIN32
	#pragma warning(disable:4251)
#endif


#ifdef _WIN32
	#ifdef MQDLL_EXPORTS
		#define DLL_API __declspec(dllexport)
	#elif defined MQDLL_IMPORTS
		#define DLL_API __declspec(dllimport)
	#else
		#define DLL_API
	#endif
#else
#define DLL_API
#endif
/*
// This class is exported from the dll.dll
class DLL_API CDll {
public:
	CDll(void);
	// TODO: add your methods here.
};
 
extern DLL_API int nDll;
 
DLL_API int fnDll(void);
*/
