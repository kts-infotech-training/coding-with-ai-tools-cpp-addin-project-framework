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

// ProjectFrameworkView.h : interface of the CProjectFrameworkView class
//

#pragma once

#include <math.h>
#include "PluginManager.h"
#include "ProjectFramework_h.h"

// 3D Point structure
struct Point3D
{
	double x, y, z;
	Point3D(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {}
};

// Object type enumeration
enum ObjectType
{
	OBJECT_CUBE = 0,
	OBJECT_FOOTBALL_GOAL = 1,
	OBJECT_CAR = 2
};


class CProjectFrameworkView : public CView
{
protected: // create from serialization only
	CProjectFrameworkView();
	DECLARE_DYNCREATE(CProjectFrameworkView)

// Attributes
public:
	CProjectFrameworkDoc* GetDocument() const;

private:
	// Cube rotation angles
	double m_angleX;
	double m_angleY;
	
	// Mouse tracking
	CPoint m_lastMousePos;
	BOOL m_bRotating;
	
	// Current object type
	ObjectType m_currentObject;
	
	// Plugin object
	CComPtr<I3DObject> m_pPluginObject;
	CString m_strCurrentObjectName;
	
	// Cube vertices (8 corners)
	Point3D m_cubeVertices[8];
	Point3D m_rotatedVertices[8];
	
	// Helper methods for 3D transformations
	void InitializeCube();
	void RotatePoint(const Point3D& input, Point3D& output, double angleX, double angleY);
	CPoint ProjectTo2D(const Point3D& point3D, const CRect& rect);
	
	// Drawing methods for different objects
	void DrawCube(CDC* pDC, const CRect& rect);
	void DrawFootballGoal(CDC* pDC, const CRect& rect);
	void DrawCar(CDC* pDC, const CRect& rect);
	void DrawPluginObject(CDC* pDC, const CRect& rect);

// Operations
public:
	void LoadPlugins();
	void SetObjectByName(LPCTSTR pszObjectName);
	CPluginManager m_pluginManager; // Public to allow MainFrm access

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CProjectFrameworkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnChangeObject(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ProjectFrameworkView.cpp
inline CProjectFrameworkDoc* CProjectFrameworkView::GetDocument() const
   { return reinterpret_cast<CProjectFrameworkDoc*>(m_pDocument); }
#endif

