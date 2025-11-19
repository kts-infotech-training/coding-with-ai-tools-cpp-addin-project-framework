#include "stdafx.h"
#include "VehiclePlugin.h"
#include "BusObject.h"
#include "JCBObject.h"
#include "TruckObject.h"
#include "..\ProjectFramework\ProjectFramework_i.c"

// CVehiclePlugin

STDMETHODIMP CVehiclePlugin::GetPluginName(BSTR* pName)
{
	if (!pName)
		return E_POINTER;
	
	*pName = SysAllocString(L"Vehicle Plugin");
	return S_OK;
}

STDMETHODIMP CVehiclePlugin::GetPluginVersion(BSTR* pVersion)
{
	if (!pVersion)
		return E_POINTER;
	
	*pVersion = SysAllocString(L"1.0");
	return S_OK;
}

STDMETHODIMP CVehiclePlugin::GetObjectCount(long* pCount)
{
	if (!pCount)
		return E_POINTER;
	
	*pCount = 3; // Bus, JCB, Truck
	return S_OK;
}

STDMETHODIMP CVehiclePlugin::GetObjectName(long index, BSTR* pName)
{
	if (!pName)
		return E_POINTER;
	
	switch (index)
	{
	case 0:
		*pName = SysAllocString(L"Bus");
		break;
	case 1:
		*pName = SysAllocString(L"JCB");
		break;
	case 2:
		*pName = SysAllocString(L"Truck");
		break;
	default:
		return E_INVALIDARG;
	}
	
	return S_OK;
}

STDMETHODIMP CVehiclePlugin::CreateObject(long index, IDispatch** ppObject)
{
	if (!ppObject)
		return E_POINTER;
	
	*ppObject = NULL;
	HRESULT hr = E_INVALIDARG;
	
	switch (index)
	{
	case 0: // Bus
		{
			CComObject<CBusObject>* pBus = NULL;
			hr = CComObject<CBusObject>::CreateInstance(&pBus);
			if (SUCCEEDED(hr))
			{
				pBus->AddRef();
				hr = pBus->QueryInterface(IID_IDispatch, (void**)ppObject);
				pBus->Release();
			}
		}
		break;
		
	case 1: // JCB
		{
			CComObject<CJCBObject>* pJCB = NULL;
			hr = CComObject<CJCBObject>::CreateInstance(&pJCB);
			if (SUCCEEDED(hr))
			{
				pJCB->AddRef();
				hr = pJCB->QueryInterface(IID_IDispatch, (void**)ppObject);
				pJCB->Release();
			}
		}
		break;
		
	case 2: // Truck
		{
			CComObject<CTruckObject>* pTruck = NULL;
			hr = CComObject<CTruckObject>::CreateInstance(&pTruck);
			if (SUCCEEDED(hr))
			{
				pTruck->AddRef();
				hr = pTruck->QueryInterface(IID_IDispatch, (void**)ppObject);
				pTruck->Release();
			}
		}
		break;
	}
	
	return hr;
}

STDMETHODIMP CVehiclePlugin::Initialize(IDispatch* pHost)
{
	// No initialization needed
	return S_OK;
}

STDMETHODIMP CVehiclePlugin::Shutdown()
{
	// No cleanup needed
	return S_OK;
}
