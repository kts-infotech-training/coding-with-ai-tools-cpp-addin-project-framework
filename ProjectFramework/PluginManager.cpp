#include "stdafx.h"
#include "PluginManager.h"
#include "ProjectFramework_h.h"
#include <comcat.h>

// Include the generated IID definitions
#include "ProjectFramework_i.c"

CPluginManager::CPluginManager()
{
}

CPluginManager::~CPluginManager()
{
	UnloadAllPlugins();
}

BOOL CPluginManager::LoadPlugins()
{
	// Get the component category manager
	CComPtr<ICatInformation> pCatInfo;
	HRESULT hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL,
		CLSCTX_INPROC_SERVER, IID_ICatInformation, (void**)&pCatInfo);
	if (FAILED(hr))
		return FALSE;

	// Enumerate all classes in our plugin category
	CComPtr<IEnumGUID> pEnumCLSID;
	CATID catid = CATID_ProjectFrameworkPlugin;
	hr = pCatInfo->EnumClassesOfCategories(1, &catid, 0, NULL, &pEnumCLSID);
	if (FAILED(hr))
		return FALSE;

	// Load each plugin
	CLSID clsid;
	while (pEnumCLSID->Next(1, &clsid, NULL) == S_OK)
	{
		LoadPluginByCLSID(clsid);
	}

	return TRUE;
}

BOOL CPluginManager::LoadPluginByCLSID(REFCLSID clsid)
{
	// Create instance of the plugin
	CComPtr<IPlugin> pPlugin;
	HRESULT hr = pPlugin.CoCreateInstance(clsid);
	if (FAILED(hr))
		return FALSE;

	// Initialize plugin
	hr = pPlugin->Initialize(NULL);
	if (SUCCEEDED(hr))
	{
		PluginInfo info;
		info.pPlugin = pPlugin;
		info.hModule = NULL; // Not needed with COM
		info.strPath = _T(""); // Not needed with COM
		m_plugins.push_back(info);
		return TRUE;
	}

	return FALSE;
}

CComPtr<IPlugin> CPluginManager::GetPlugin(int index)
{
	if (index >= 0 && index < (int)m_plugins.size())
		return m_plugins[index].pPlugin;
	return NULL;
}

void CPluginManager::GetAvailableObjects(CStringArray& objectNames)
{
	objectNames.RemoveAll();

	for (size_t i = 0; i < m_plugins.size(); i++)
	{
		CComPtr<IPlugin> pPlugin = m_plugins[i].pPlugin;
		if (pPlugin)
		{
			long count = 0;
			if (SUCCEEDED(pPlugin->GetObjectCount(&count)))
			{
				for (long j = 0; j < count; j++)
				{
					CComBSTR bstrName;
					if (SUCCEEDED(pPlugin->GetObjectName(j, &bstrName)))
					{
						objectNames.Add(CString(bstrName));
					}
				}
			}
		}
	}
}

CComPtr<I3DObject> CPluginManager::CreateObjectByName(LPCTSTR pszObjectName)
{
	for (size_t i = 0; i < m_plugins.size(); i++)
	{
		CComPtr<IPlugin> pPlugin = m_plugins[i].pPlugin;
		if (pPlugin)
		{
			long count = 0;
			if (SUCCEEDED(pPlugin->GetObjectCount(&count)))
			{
				for (long j = 0; j < count; j++)
				{
					CComBSTR bstrName;
					if (SUCCEEDED(pPlugin->GetObjectName(j, &bstrName)))
					{
						if (CString(bstrName) == pszObjectName)
						{
							CComPtr<IDispatch> pDisp;
							if (SUCCEEDED(pPlugin->CreateObject(j, &pDisp)))
							{
								CComPtr<I3DObject> pObject;
								pDisp->QueryInterface(IID_I3DObject, (void**)&pObject);
								return pObject;
							}
						}
					}
				}
			}
		}
	}
	return NULL;
}

void CPluginManager::UnloadAllPlugins()
{
	for (size_t i = 0; i < m_plugins.size(); i++)
	{
		if (m_plugins[i].pPlugin)
		{
			m_plugins[i].pPlugin->Shutdown();
			m_plugins[i].pPlugin.Release();
		}
		// No need to FreeLibrary with COM
	}
	m_plugins.clear();
}
