
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the AUTONK_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// AUTONK_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef AUTONK_EXPORTS
#define AUTONK_API __declspec(dllexport)
#else
#define AUTONK_API __declspec(dllimport)
#endif

// This class is exported from the autonk.dll
class AUTONK_API CAutonk {
public:
	CAutonk(void);
	// TODO: add your methods here.
};

extern AUTONK_API int nAutonk;

AUTONK_API int fnAutonk(void);

