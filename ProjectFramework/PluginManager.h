#pragma once

#include <vector>
#include <atlbase.h>
#include "ProjectFramework_h.h"

// Define Plugin Component Category GUID
// {3A2F1B5C-6D8E-4F9A-B2C3-E5F7A8D9C0B1}
static const CATID CATID_ProjectFrameworkPlugin = 
{ 0x3A2F1B5C, 0x6D8E, 0x4F9A, { 0xB2, 0xC3, 0xE5, 0xF7, 0xA8, 0xD9, 0xC0, 0xB1 } };

class CPluginManager
{
public:
	CPluginManager();
	~CPluginManager();

	// Load all plugins registered in the component category
	BOOL LoadPlugins();
	
	// Get number of loaded plugins
	int GetPluginCount() const { return (int)m_plugins.size(); }
	
	// Get plugin by index
	CComPtr<IPlugin> GetPlugin(int index);
	
	// Get all available objects from all plugins
	void GetAvailableObjects(CStringArray& objectNames);
	
	// Create object by name
	CComPtr<I3DObject> CreateObjectByName(LPCTSTR pszObjectName);
	
	// Unload all plugins
	void UnloadAllPlugins();

private:
	struct PluginInfo
	{
		CComPtr<IPlugin> pPlugin;
		HMODULE hModule;
		CString strPath;
	};

	std::vector<PluginInfo> m_plugins;
	
	// Load single plugin by CLSID
	BOOL LoadPluginByCLSID(REFCLSID clsid);
};
