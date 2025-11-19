#include "stdafx.h"
#include "ProjectFramework.h"
#include "SettingsDlg.h"

// CSettingsDlg dialog

IMPLEMENT_DYNAMIC(CSettingsDlg, CDialogEx)

CSettingsDlg::CSettingsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTINGS_DIALOG, pParent)
	, m_bLaunchOnStartup(FALSE)
{
	EnableActiveAccessibility();
}

CSettingsDlg::~CSettingsDlg()
{
}

void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_LAUNCH_STARTUP_CHECK, m_bLaunchOnStartup);
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSettingsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSettingsDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSettingsDlg message handlers

BOOL CSettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Load the saved setting from registry
	m_bLaunchOnStartup = theApp.GetInt(_T("LaunchOnStartup"), FALSE);
	UpdateData(FALSE);

	return TRUE;
}

void CSettingsDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	
	// Save the setting to registry
	theApp.WriteInt(_T("LaunchOnStartup"), m_bLaunchOnStartup);
	
	CDialogEx::OnOK();
}

void CSettingsDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
