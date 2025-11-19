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

// ProjectFrameworkView.cpp : implementation of the CProjectFrameworkView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ProjectFramework.h"
#endif

#include "ProjectFrameworkDoc.h"
#include "ProjectFrameworkView.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProjectFrameworkView

IMPLEMENT_DYNCREATE(CProjectFrameworkView, CView)

BEGIN_MESSAGE_MAP(CProjectFrameworkView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CProjectFrameworkView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_USER + 100, &CProjectFrameworkView::OnChangeObject)
END_MESSAGE_MAP()

// CProjectFrameworkView construction/destruction

CProjectFrameworkView::CProjectFrameworkView()
	: m_angleX(0.5)
	, m_angleY(0.5)
	, m_bRotating(FALSE)
	, m_currentObject(OBJECT_CUBE)
{
	EnableActiveAccessibility();
	// Initialize the cube vertices
	InitializeCube();
	
	// Load plugins
	LoadPlugins();
}

CProjectFrameworkView::~CProjectFrameworkView()
{
}

BOOL CProjectFrameworkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProjectFrameworkView drawing

void CProjectFrameworkView::OnDraw(CDC* pDC)
{
	CProjectFrameworkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);

	// Create a memory DC for double buffering
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	// Fill background
	memDC.FillSolidRect(&rect, RGB(240, 240, 255));

	// Draw based on selected object type
	if (m_pPluginObject)
	{
		DrawPluginObject(&memDC, rect);
	}
	else
	{
		switch (m_currentObject)
		{
		case OBJECT_CUBE:
			DrawCube(&memDC, rect);
			break;
		case OBJECT_FOOTBALL_GOAL:
			DrawFootballGoal(&memDC, rect);
			break;
		case OBJECT_CAR:
			DrawCar(&memDC, rect);
			break;
		}
	}

	// Display instructions
	memDC.SetBkMode(TRANSPARENT);
	memDC.SetTextColor(RGB(0, 0, 0));
	memDC.TextOut(10, 10, _T("Click and drag to rotate"));
	memDC.TextOut(10, 30, _T("Use Arrow Keys: Up/Down/Left/Right to rotate"));

	// Copy to screen
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// Cleanup
	memDC.SelectObject(pOldBitmap);
}


// CProjectFrameworkView printing


void CProjectFrameworkView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CProjectFrameworkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProjectFrameworkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProjectFrameworkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CProjectFrameworkView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CProjectFrameworkView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CProjectFrameworkView diagnostics

#ifdef _DEBUG
void CProjectFrameworkView::AssertValid() const
{
	CView::AssertValid();
}

void CProjectFrameworkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProjectFrameworkDoc* CProjectFrameworkView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProjectFrameworkDoc)));
	return (CProjectFrameworkDoc*)m_pDocument;
}
#endif //_DEBUG


// CProjectFrameworkView message handlers

void CProjectFrameworkView::InitializeCube()
{
	// Define cube vertices (centered at origin)
	double size = 100.0;
	m_cubeVertices[0] = Point3D(-size, -size, -size);
	m_cubeVertices[1] = Point3D( size, -size, -size);
	m_cubeVertices[2] = Point3D( size,  size, -size);
	m_cubeVertices[3] = Point3D(-size,  size, -size);
	m_cubeVertices[4] = Point3D(-size, -size,  size);
	m_cubeVertices[5] = Point3D( size, -size,  size);
	m_cubeVertices[6] = Point3D( size,  size,  size);
	m_cubeVertices[7] = Point3D(-size,  size,  size);
}

void CProjectFrameworkView::RotatePoint(const Point3D& input, Point3D& output, double angleX, double angleY)
{
	// Rotation around X axis
	double cosX = cos(angleX);
	double sinX = sin(angleX);
	double y1 = input.y * cosX - input.z * sinX;
	double z1 = input.y * sinX + input.z * cosX;
	
	// Rotation around Y axis
	double cosY = cos(angleY);
	double sinY = sin(angleY);
	output.x = input.x * cosY + z1 * sinY;
	output.y = y1;
	output.z = -input.x * sinY + z1 * cosY;
}

CPoint CProjectFrameworkView::ProjectTo2D(const Point3D& point3D, const CRect& rect)
{
	// Simple perspective projection
	double distance = 500.0; // Distance from viewer
	double scale = distance / (distance + point3D.z);
	
	int x = (int)(point3D.x * scale) + rect.Width() / 2;
	int y = (int)(point3D.y * scale) + rect.Height() / 2;
	
	return CPoint(x, y);
}

void CProjectFrameworkView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bRotating = TRUE;
	m_lastMousePos = point;
	SetCapture();
	
	CView::OnLButtonDown(nFlags, point);
}

void CProjectFrameworkView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bRotating = FALSE;
	ReleaseCapture();
	
	CView::OnLButtonUp(nFlags, point);
}

void CProjectFrameworkView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bRotating)
	{
		// Calculate rotation delta based on mouse movement
		int deltaX = point.x - m_lastMousePos.x;
		int deltaY = point.y - m_lastMousePos.y;
		
		// Update rotation angles
		m_angleY += deltaX * 0.01; // Horizontal mouse movement rotates around Y axis
		m_angleX += deltaY * 0.01; // Vertical mouse movement rotates around X axis
		
		// Update last position
		m_lastMousePos = point;
		
		// Redraw
		Invalidate();
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CProjectFrameworkView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	double rotationStep = 0.1; // Rotation step size
	
	switch (nChar)
	{
	case VK_UP:
		// Rotate up (decrease X angle)
		m_angleX -= rotationStep;
		Invalidate();
		break;
		
	case VK_DOWN:
		// Rotate down (increase X angle)
		m_angleX += rotationStep;
		Invalidate();
		break;
		
	case VK_LEFT:
		// Rotate left (decrease Y angle)
		m_angleY -= rotationStep;
		Invalidate();
		break;
		
	case VK_RIGHT:
		// Rotate right (increase Y angle)
		m_angleY += rotationStep;
		Invalidate();
		break;
	}
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

LRESULT CProjectFrameworkView::OnChangeObject(WPARAM wParam, LPARAM lParam)
{
	// wParam contains the object name as a string pointer
	LPCTSTR pszObjectName = (LPCTSTR)wParam;
	if (pszObjectName)
	{
		SetObjectByName(pszObjectName);
	}
	return 0;
}

void CProjectFrameworkView::DrawCube(CDC* pDC, const CRect& rect)
{
	// Rotate all vertices
	for (int i = 0; i < 8; i++)
	{
		RotatePoint(m_cubeVertices[i], m_rotatedVertices[i], m_angleX, m_angleY);
	}

	// Project to 2D and draw
	CPoint points2D[8];
	for (int i = 0; i < 8; i++)
	{
		points2D[i] = ProjectTo2D(m_rotatedVertices[i], rect);
	}

	// Create pen for drawing
	CPen pen(PS_SOLID, 2, RGB(0, 0, 200));
	CPen* pOldPen = pDC->SelectObject(&pen);

	// Draw the 12 edges of the cube
	// Bottom face (0-1-2-3)
	pDC->MoveTo(points2D[0]);
	pDC->LineTo(points2D[1]);
	pDC->LineTo(points2D[2]);
	pDC->LineTo(points2D[3]);
	pDC->LineTo(points2D[0]);

	// Top face (4-5-6-7)
	pDC->MoveTo(points2D[4]);
	pDC->LineTo(points2D[5]);
	pDC->LineTo(points2D[6]);
	pDC->LineTo(points2D[7]);
	pDC->LineTo(points2D[4]);

	// Vertical edges
	pDC->MoveTo(points2D[0]);
	pDC->LineTo(points2D[4]);
	pDC->MoveTo(points2D[1]);
	pDC->LineTo(points2D[5]);
	pDC->MoveTo(points2D[2]);
	pDC->LineTo(points2D[6]);
	pDC->MoveTo(points2D[3]);
	pDC->LineTo(points2D[7]);

	// Draw vertices as small circles
	CBrush brush(RGB(200, 0, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	for (int i = 0; i < 8; i++)
	{
		pDC->Ellipse(points2D[i].x - 4, points2D[i].y - 4,
			points2D[i].x + 4, points2D[i].y + 4);
	}

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void CProjectFrameworkView::DrawFootballGoal(CDC* pDC, const CRect& rect)
{
	// Football goal post with goalkeeper
	std::vector<Point3D> goalVertices;
	double w = 150.0; // Width
	double h = 100.0; // Height
	double d = 50.0;  // Depth

	// Goal posts (frame)
	goalVertices.push_back(Point3D(-w, -h, 0));  // 0: Bottom left front
	goalVertices.push_back(Point3D(w, -h, 0));   // 1: Bottom right front
	goalVertices.push_back(Point3D(w, h, 0));    // 2: Top right front
	goalVertices.push_back(Point3D(-w, h, 0));   // 3: Top left front
	goalVertices.push_back(Point3D(-w, -h, d));  // 4: Bottom left back
	goalVertices.push_back(Point3D(w, -h, d));   // 5: Bottom right back
	goalVertices.push_back(Point3D(w, h, d));    // 6: Top right back
	goalVertices.push_back(Point3D(-w, h, d));   // 7: Top left back

	// Goalkeeper (simple stick figure)
	goalVertices.push_back(Point3D(0, -h + 30, 10));     // 8: Head
	goalVertices.push_back(Point3D(0, -h + 60, 10));     // 9: Body top
	goalVertices.push_back(Point3D(0, -h + 90, 10));     // 10: Body bottom
	goalVertices.push_back(Point3D(-30, -h + 50, 10));   // 11: Left hand
	goalVertices.push_back(Point3D(30, -h + 50, 10));    // 12: Right hand

	// Rotate and project all vertices
	std::vector<CPoint> points2D;
	for (size_t i = 0; i < goalVertices.size(); i++)
	{
		Point3D rotated;
		RotatePoint(goalVertices[i], rotated, m_angleX, m_angleY);
		points2D.push_back(ProjectTo2D(rotated, rect));
	}

	// Draw goal post
	CPen goalPen(PS_SOLID, 3, RGB(200, 200, 200));
	CPen* pOldPen = pDC->SelectObject(&goalPen);

	// Front frame
	pDC->MoveTo(points2D[0]);
	pDC->LineTo(points2D[3]);
	pDC->LineTo(points2D[2]);
	pDC->LineTo(points2D[1]);
	pDC->LineTo(points2D[0]);

	// Back frame
	pDC->MoveTo(points2D[4]);
	pDC->LineTo(points2D[7]);
	pDC->LineTo(points2D[6]);
	pDC->LineTo(points2D[5]);
	pDC->LineTo(points2D[4]);

	// Connecting edges
	pDC->MoveTo(points2D[0]); pDC->LineTo(points2D[4]);
	pDC->MoveTo(points2D[1]); pDC->LineTo(points2D[5]);
	pDC->MoveTo(points2D[2]); pDC->LineTo(points2D[6]);
	pDC->MoveTo(points2D[3]); pDC->LineTo(points2D[7]);

	// Draw net pattern
	CPen netPen(PS_SOLID, 1, RGB(100, 100, 100));
	pDC->SelectObject(&netPen);
	for (int i = 1; i < 5; i++)
	{
		Point3D p1(-w + i * w / 2.5, -h, 0);
		Point3D p2(-w + i * w / 2.5, h, 0);
		Point3D r1, r2;
		RotatePoint(p1, r1, m_angleX, m_angleY);
		RotatePoint(p2, r2, m_angleX, m_angleY);
		pDC->MoveTo(ProjectTo2D(r1, rect));
		pDC->LineTo(ProjectTo2D(r2, rect));
	}

	// Draw goalkeeper
	CPen playerPen(PS_SOLID, 3, RGB(255, 100, 0));
	pDC->SelectObject(&playerPen);

	// Head
	CBrush headBrush(RGB(255, 200, 150));
	CBrush* pOldBrush = pDC->SelectObject(&headBrush);
	pDC->Ellipse(points2D[8].x - 10, points2D[8].y - 10,
		points2D[8].x + 10, points2D[8].y + 10);

	// Body
	pDC->SelectObject(pOldBrush);
	pDC->MoveTo(points2D[9]);
	pDC->LineTo(points2D[10]);

	// Arms
	pDC->MoveTo(points2D[9]);
	pDC->LineTo(points2D[11]);
	pDC->MoveTo(points2D[9]);
	pDC->LineTo(points2D[12]);

	pDC->SelectObject(pOldPen);
}

void CProjectFrameworkView::DrawCar(CDC* pDC, const CRect& rect)
{
	// Simple 3D car
	std::vector<Point3D> carVertices;
	double length = 120.0;
	double width = 60.0;
	double height = 40.0;
	double cabHeight = 30.0;

	// Car body (box)
	carVertices.push_back(Point3D(-length / 2, -width / 2, -height));  // 0: Bottom front left
	carVertices.push_back(Point3D(length / 2, -width / 2, -height));   // 1: Bottom front right
	carVertices.push_back(Point3D(length / 2, width / 2, -height));    // 2: Bottom back right
	carVertices.push_back(Point3D(-length / 2, width / 2, -height));   // 3: Bottom back left
	carVertices.push_back(Point3D(-length / 2, -width / 2, 0));        // 4: Top front left
	carVertices.push_back(Point3D(length / 2, -width / 2, 0));         // 5: Top front right
	carVertices.push_back(Point3D(length / 2, width / 2, 0));          // 6: Top back right
	carVertices.push_back(Point3D(-length / 2, width / 2, 0));         // 7: Top back left

	// Cabin
	carVertices.push_back(Point3D(-length / 4, -width / 2 + 5, 0));       // 8
	carVertices.push_back(Point3D(length / 4, -width / 2 + 5, 0));        // 9
	carVertices.push_back(Point3D(length / 4, width / 2 - 5, 0));         // 10
	carVertices.push_back(Point3D(-length / 4, width / 2 - 5, 0));        // 11
	carVertices.push_back(Point3D(-length / 4 + 10, -width / 2 + 5, cabHeight));  // 12
	carVertices.push_back(Point3D(length / 4 - 10, -width / 2 + 5, cabHeight));   // 13
	carVertices.push_back(Point3D(length / 4 - 10, width / 2 - 5, cabHeight));    // 14
	carVertices.push_back(Point3D(-length / 4 + 10, width / 2 - 5, cabHeight));   // 15

	// Wheels
	carVertices.push_back(Point3D(-length / 3, -width / 2 - 5, -height + 10));  // 16: Front left wheel
	carVertices.push_back(Point3D(-length / 3, width / 2 + 5, -height + 10));   // 17: Front right wheel
	carVertices.push_back(Point3D(length / 3, -width / 2 - 5, -height + 10));   // 18: Rear left wheel
	carVertices.push_back(Point3D(length / 3, width / 2 + 5, -height + 10));    // 19: Rear right wheel

	// Rotate and project all vertices
	std::vector<CPoint> points2D;
	for (size_t i = 0; i < carVertices.size(); i++)
	{
		Point3D rotated;
		RotatePoint(carVertices[i], rotated, m_angleX, m_angleY);
		points2D.push_back(ProjectTo2D(rotated, rect));
	}

	// Draw car body
	CPen carPen(PS_SOLID, 2, RGB(200, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&carPen);

	// Bottom face
	pDC->MoveTo(points2D[0]);
	pDC->LineTo(points2D[1]);
	pDC->LineTo(points2D[2]);
	pDC->LineTo(points2D[3]);
	pDC->LineTo(points2D[0]);

	// Top face
	pDC->MoveTo(points2D[4]);
	pDC->LineTo(points2D[5]);
	pDC->LineTo(points2D[6]);
	pDC->LineTo(points2D[7]);
	pDC->LineTo(points2D[4]);

	// Vertical edges
	pDC->MoveTo(points2D[0]); pDC->LineTo(points2D[4]);
	pDC->MoveTo(points2D[1]); pDC->LineTo(points2D[5]);
	pDC->MoveTo(points2D[2]); pDC->LineTo(points2D[6]);
	pDC->MoveTo(points2D[3]); pDC->LineTo(points2D[7]);

	// Draw cabin
	CPen cabinPen(PS_SOLID, 2, RGB(100, 100, 255));
	pDC->SelectObject(&cabinPen);

	// Cabin bottom
	pDC->MoveTo(points2D[8]);
	pDC->LineTo(points2D[9]);
	pDC->LineTo(points2D[10]);
	pDC->LineTo(points2D[11]);
	pDC->LineTo(points2D[8]);

	// Cabin top
	pDC->MoveTo(points2D[12]);
	pDC->LineTo(points2D[13]);
	pDC->LineTo(points2D[14]);
	pDC->LineTo(points2D[15]);
	pDC->LineTo(points2D[12]);

	// Cabin edges
	pDC->MoveTo(points2D[8]); pDC->LineTo(points2D[12]);
	pDC->MoveTo(points2D[9]); pDC->LineTo(points2D[13]);
	pDC->MoveTo(points2D[10]); pDC->LineTo(points2D[14]);
	pDC->MoveTo(points2D[11]); pDC->LineTo(points2D[15]);

	// Draw wheels
	CBrush wheelBrush(RGB(50, 50, 50));
	CBrush* pOldBrush = pDC->SelectObject(&wheelBrush);
	CPen wheelPen(PS_SOLID, 2, RGB(0, 0, 0));
	pDC->SelectObject(&wheelPen);

	for (int i = 16; i < 20; i++)
	{
		pDC->Ellipse(points2D[i].x - 8, points2D[i].y - 8,
			points2D[i].x + 8, points2D[i].y + 8);
	}

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void CProjectFrameworkView::LoadPlugins()
{
	// Load all plugins registered in the component category
	m_pluginManager.LoadPlugins();
}

void CProjectFrameworkView::SetObjectByName(LPCTSTR pszObjectName)
{
	m_strCurrentObjectName = pszObjectName;
	
	// Check if it's a built-in object
	if (m_strCurrentObjectName == _T("Cube"))
	{
		m_currentObject = OBJECT_CUBE;
		m_pPluginObject.Release();
	}
	else if (m_strCurrentObjectName == _T("Football Goal Post"))
	{
		m_currentObject = OBJECT_FOOTBALL_GOAL;
		m_pPluginObject.Release();
	}
	else if (m_strCurrentObjectName == _T("Car"))
	{
		m_currentObject = OBJECT_CAR;
		m_pPluginObject.Release();
	}
	else
	{
		// Try to load from plugin
		m_pPluginObject = m_pluginManager.CreateObjectByName(pszObjectName);
	}
	
	Invalidate();
}

void CProjectFrameworkView::DrawPluginObject(CDC* pDC, const CRect& rect)
{
	if (m_pPluginObject)
	{
		// Call the plugin's Draw method
		m_pPluginObject->Draw((long)pDC->m_hDC, rect.left, rect.top, rect.right, rect.bottom, m_angleX, m_angleY);
	}
}
