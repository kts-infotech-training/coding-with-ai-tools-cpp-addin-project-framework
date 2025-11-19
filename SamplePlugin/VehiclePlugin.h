#pragma once
#include "resource.h"
#include "SamplePlugin_i.h"
#include "..\ProjectFramework\ProjectFramework_h.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform"
#endif

using namespace ATL;

// CVehiclePlugin

class ATL_NO_VTABLE CVehiclePlugin :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVehiclePlugin, &CLSID_VehiclePlugin>,
	public IDispatchImpl<IPlugin, &IID_IPlugin, &LIBID_ProjectFramework, 1, 0>
{
public:
	CVehiclePlugin()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_VEHICLEPLUGIN)

	BEGIN_COM_MAP(CVehiclePlugin)
		COM_INTERFACE_ENTRY(IPlugin)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	// IPlugin Methods
	STDMETHOD(GetPluginName)(BSTR* pName);
	STDMETHOD(GetPluginVersion)(BSTR* pVersion);
	STDMETHOD(GetObjectCount)(long* pCount);
	STDMETHOD(GetObjectName)(long index, BSTR* pName);
	STDMETHOD(CreateObject)(long index, IDispatch** ppObject);
	STDMETHOD(Initialize)(IDispatch* pHost);
	STDMETHOD(Shutdown)();
};

OBJECT_ENTRY_AUTO(__uuidof(VehiclePlugin), CVehiclePlugin)
