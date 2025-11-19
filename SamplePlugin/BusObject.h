#pragma once
#include "resource.h"
#include "SamplePlugin_i.h"
#include "..\ProjectFramework\ProjectFramework_h.h"

using namespace ATL;

// CBusObject

class ATL_NO_VTABLE CBusObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBusObject, &CLSID_BusObject>,
	public IDispatchImpl<I3DObject, &IID_I3DObject, &LIBID_ProjectFramework, 1, 0>
{
public:
	CBusObject()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_BUSOBJECT)

	BEGIN_COM_MAP(CBusObject)
		COM_INTERFACE_ENTRY(I3DObject)
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
	// I3DObject Methods
	STDMETHOD(GetObjectName)(BSTR* pName);
	STDMETHOD(Draw)(long hDC, long rectLeft, long rectTop, long rectRight, long rectBottom, double angleX, double angleY);

private:
	struct Point3D { double x, y, z; };
	void RotatePoint(const Point3D& input, Point3D& output, double angleX, double angleY);
	POINT ProjectTo2D(const Point3D& point3D, long centerX, long centerY);
};

OBJECT_ENTRY_AUTO(__uuidof(BusObject), CBusObject)
