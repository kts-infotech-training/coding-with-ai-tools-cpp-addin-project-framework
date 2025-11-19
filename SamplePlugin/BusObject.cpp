#include "stdafx.h"
#include "BusObject.h"
#include <vector>
#include <math.h>

// CBusObject

STDMETHODIMP CBusObject::GetObjectName(BSTR* pName)
{
	if (!pName)
		return E_POINTER;
	
	*pName = SysAllocString(L"Bus");
	return S_OK;
}

void CBusObject::RotatePoint(const Point3D& input, Point3D& output, double angleX, double angleY)
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

POINT CBusObject::ProjectTo2D(const Point3D& point3D, long centerX, long centerY)
{
	double distance = 500.0;
	double scale = distance / (distance + point3D.z);
	
	POINT pt;
	pt.x = (long)(point3D.x * scale) + centerX;
	pt.y = (long)(point3D.y * scale) + centerY;
	return pt;
}

STDMETHODIMP CBusObject::Draw(long hDC, long rectLeft, long rectTop, long rectRight, long rectBottom, double angleX, double angleY)
{
	HDC dc = (HDC)hDC;
	long centerX = (rectLeft + rectRight) / 2;
	long centerY = (rectTop + rectBottom) / 2;
	
	// Bus dimensions
	double length = 180.0;
	double width = 70.0;
	double height = 80.0;
	
	// Define bus vertices
	std::vector<Point3D> vertices;
	
	// Main body (box)
	vertices.push_back({-length/2, -width/2, -height/2});  // 0
	vertices.push_back({length/2, -width/2, -height/2});   // 1
	vertices.push_back({length/2, width/2, -height/2});    // 2
	vertices.push_back({-length/2, width/2, -height/2});   // 3
	vertices.push_back({-length/2, -width/2, height/2});   // 4
	vertices.push_back({length/2, -width/2, height/2});    // 5
	vertices.push_back({length/2, width/2, height/2});     // 6
	vertices.push_back({-length/2, width/2, height/2});    // 7
	
	// Rotate and project all vertices
	std::vector<POINT> points2D;
	for (size_t i = 0; i < vertices.size(); i++)
	{
		Point3D rotated;
		RotatePoint(vertices[i], rotated, angleX, angleY);
		points2D.push_back(ProjectTo2D(rotated, centerX, centerY));
	}
	
	// Draw bus body
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 180, 0));
	HPEN oldPen = (HPEN)SelectObject(dc, pen);
	
	// Bottom face
	MoveToEx(dc, points2D[0].x, points2D[0].y, NULL);
	LineTo(dc, points2D[1].x, points2D[1].y);
	LineTo(dc, points2D[2].x, points2D[2].y);
	LineTo(dc, points2D[3].x, points2D[3].y);
	LineTo(dc, points2D[0].x, points2D[0].y);
	
	// Top face
	MoveToEx(dc, points2D[4].x, points2D[4].y, NULL);
	LineTo(dc, points2D[5].x, points2D[5].y);
	LineTo(dc, points2D[6].x, points2D[6].y);
	LineTo(dc, points2D[7].x, points2D[7].y);
	LineTo(dc, points2D[4].x, points2D[4].y);
	
	// Vertical edges
	MoveToEx(dc, points2D[0].x, points2D[0].y, NULL); LineTo(dc, points2D[4].x, points2D[4].y);
	MoveToEx(dc, points2D[1].x, points2D[1].y, NULL); LineTo(dc, points2D[5].x, points2D[5].y);
	MoveToEx(dc, points2D[2].x, points2D[2].y, NULL); LineTo(dc, points2D[6].x, points2D[6].y);
	MoveToEx(dc, points2D[3].x, points2D[3].y, NULL); LineTo(dc, points2D[7].x, points2D[7].y);
	
	// Draw windows (simplified as rectangles on the side)
	HPEN windowPen = CreatePen(PS_SOLID, 2, RGB(100, 150, 255));
	SelectObject(dc, windowPen);
	
	for (int i = 0; i < 5; i++)
	{
		Point3D win1 = {-length/2 + 30 + i * 30, -width/2 - 2, height/2 - 20};
		Point3D win2 = {-length/2 + 50 + i * 30, -width/2 - 2, height/2 - 40};
		Point3D r1, r2;
		RotatePoint(win1, r1, angleX, angleY);
		RotatePoint(win2, r2, angleX, angleY);
		POINT p1 = ProjectTo2D(r1, centerX, centerY);
		POINT p2 = ProjectTo2D(r2, centerX, centerY);
		Rectangle(dc, p1.x, p1.y, p2.x, p2.y);
	}
	
	// Draw wheels
	HBRUSH wheelBrush = CreateSolidBrush(RGB(40, 40, 40));
	HBRUSH oldBrush = (HBRUSH)SelectObject(dc, wheelBrush);
	SelectObject(dc, pen);
	
	// Front wheels
	Point3D wheel1 = {-length/3, -width/2 - 10, -height/2 + 15};
	Point3D wheel2 = {-length/3, width/2 + 10, -height/2 + 15};
	// Rear wheels
	Point3D wheel3 = {length/3, -width/2 - 10, -height/2 + 15};
	Point3D wheel4 = {length/3, width/2 + 10, -height/2 + 15};
	
	Point3D wheels[] = {wheel1, wheel2, wheel3, wheel4};
	for (int i = 0; i < 4; i++)
	{
		Point3D rot;
		RotatePoint(wheels[i], rot, angleX, angleY);
		POINT p = ProjectTo2D(rot, centerX, centerY);
		Ellipse(dc, p.x - 12, p.y - 12, p.x + 12, p.y + 12);
	}
	
	// Cleanup
	SelectObject(dc, oldBrush);
	DeleteObject(wheelBrush);
	SelectObject(dc, oldPen);
	DeleteObject(windowPen);
	DeleteObject(pen);
	
	return S_OK;
}
