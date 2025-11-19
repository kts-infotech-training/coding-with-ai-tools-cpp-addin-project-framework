// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ProjectFrameworkDoc.cpp : implementation of the CProjectFrameworkDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ProjectFramework.h"
#endif

#include "ProjectFrameworkDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CProjectFrameworkDoc

IMPLEMENT_DYNCREATE(CProjectFrameworkDoc, CDocument)

BEGIN_MESSAGE_MAP(CProjectFrameworkDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProjectFrameworkDoc, CDocument)
END_DISPATCH_MAP()

// Note: we add support for IID_IProjectFramework to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {68DA994E-AF0D-4ECB-8110-00B1FBED4F1C}
static const IID IID_IProjectFramework =
{ 0x68DA994E, 0xAF0D, 0x4ECB, { 0x81, 0x10, 0x0, 0xB1, 0xFB, 0xED, 0x4F, 0x1C } };

BEGIN_INTERFACE_MAP(CProjectFrameworkDoc, CDocument)
	INTERFACE_PART(CProjectFrameworkDoc, IID_IProjectFramework, Dispatch)
END_INTERFACE_MAP()


// CProjectFrameworkDoc construction/destruction

CProjectFrameworkDoc::CProjectFrameworkDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CProjectFrameworkDoc::~CProjectFrameworkDoc()
{
	AfxOleUnlockApp();
}

BOOL CProjectFrameworkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CProjectFrameworkDoc serialization

void CProjectFrameworkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CProjectFrameworkDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CProjectFrameworkDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CProjectFrameworkDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CProjectFrameworkDoc diagnostics

#ifdef _DEBUG
void CProjectFrameworkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProjectFrameworkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CProjectFrameworkDoc commands
