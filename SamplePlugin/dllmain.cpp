// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "SamplePlugin_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CSamplePluginModule _AtlModule;

class CSamplePluginApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CSamplePluginApp, CWinApp)
END_MESSAGE_MAP()

CSamplePluginApp theApp;

BOOL CSamplePluginApp::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, NULL))
		return FALSE;
#endif
	return CWinApp::InitInstance();
}

int CSamplePluginApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
