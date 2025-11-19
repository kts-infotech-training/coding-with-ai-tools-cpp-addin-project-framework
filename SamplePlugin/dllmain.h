// dllmain.h : Declaration of module class.

class CSamplePluginModule : public ATL::CAtlDllModuleT< CSamplePluginModule >
{
public :
	DECLARE_LIBID(LIBID_SamplePluginLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SAMPLEPLUGIN, "{701436F8-7DFF-4B49-A231-70CDCFC50202}")
};

extern class CSamplePluginModule _AtlModule;
