#include "stdafx.h"
#include "TruckObject.h"
#include <vector>
#include <math.h>

// CTruckObject

STDMETHODIMP CTruckObject::GetObjectName(BSTR* pName)
{
	if (!pName)
		return E_POINTER;
	
	*pName = SysAllocString(L"Truck");
	return S_OK;
}

void CTruckObject::RotatePoint(const Point3D& input, Point3D& output, double angleX, double angleY)
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

POINT CTruckObject::ProjectTo2D(const Point3D& point3D, long centerX, long centerY)
{
	double distance = 500.0;
	double scale = distance / (distance + point3D.z);
	
	POINT pt;
	pt.x = (long)(point3D.x * scale) + centerX;
	pt.y = (long)(point3D.y * scale) + centerY;
	return pt;
}

STDMETHODIMP CTruckObject::Draw(long hDC, long rectLeft, long rectTop, long rectRight, long rectBottom, double angleX, double angleY)
{
	HDC dc = (HDC)hDC;
	long centerX = (rectLeft + rectRight) / 2;
	long centerY = (rectTop + rectBottom) / 2;
	
	std::vector<Point3D> vertices;
	
	// Cabin dimensions
	double cabL = 60, cabW = 70, cabH = 70;
	// Cargo dimensions
	double cargoL = 120, cargoW = 70, cargoH = 80;
	
	// Cabin vertices (front)
	vertices.push_back({-cargoL/2 - cabL, -cabW/2, -cabH});      // 0
	vertices.push_back({-cargoL/2, -cabW/2, -cabH});             // 1
	vertices.push_back({-cargoL/2, cabW/2, -cabH});              // 2
	vertices.push_back({-cargoL/2 - cabL, cabW/2, -cabH});       // 3
	vertices.push_back({-cargoL/2 - cabL, -cabW/2, 0});          // 4
	vertices.push_back({-cargoL/2, -cabW/2, 0});                 // 5
	vertices.push_back({-cargoL/2, cabW/2, 0});                  // 6
	vertices.push_back({-cargoL/2 - cabL, cabW/2, 0});           // 7
	
	// Cargo box vertices (rear)
	vertices.push_back({-cargoL/2, -cargoW/2, -cargoH});         // 8
	vertices.push_back({cargoL/2, -cargoW/2, -cargoH});          // 9
	vertices.push_back({cargoL/2, cargoW/2, -cargoH});           // 10
	vertices.push_back({-cargoL/2, cargoW/2, -cargoH});          // 11
	vertices.push_back({-cargoL/2, -cargoW/2, 0});               // 12
	vertices.push_back({cargoL/2, -cargoW/2, 0});                // 13
	vertices.push_back({cargoL/2, cargoW/2, 0});                 // 14
	vertices.push_back({-cargoL/2, cargoW/2, 0});                // 15
	
	// Rotate and project all vertices
	std::vector<POINT> points2D;
	for (size_t i = 0; i < vertices.size(); i++)
	{
		Point3D rotated;
		RotatePoint(vertices[i], rotated, angleX, angleY);
		points2D.push_back(ProjectTo2D(rotated, centerX, centerY));
	}
	
	// Draw cabin
	HPEN cabPen = CreatePen(PS_SOLID, 3, RGB(0, 150, 255));
	HPEN oldPen = (HPEN)SelectObject(dc, cabPen);
	
	// Cabin bottom
	MoveToEx(dc, points2D[0].x, points2D[0].y, NULL);
	LineTo(dc, points2D[1].x, points2D[1].y);
	LineTo(dc, points2D[2].x, points2D[2].y);
	LineTo(dc, points2D[3].x, points2D[3].y);
	LineTo(dc, points2D[0].x, points2D[0].y);
	
	// Cabin top
	MoveToEx(dc, points2D[4].x, points2D[4].y, NULL);
	LineTo(dc, points2D[5].x, points2D[5].y);
	LineTo(dc, points2D[6].x, points2D[6].y);
	LineTo(dc, points2D[7].x, points2D[7].y);
	LineTo(dc, points2D[4].x, points2D[4].y);
	
	// Cabin sides
	MoveToEx(dc, points2D[0].x, points2D[0].y, NULL); LineTo(dc, points2D[4].x, points2D[4].y);
	MoveToEx(dc, points2D[1].x, points2D[1].y, NULL); LineTo(dc, points2D[5].x, points2D[5].y);
	MoveToEx(dc, points2D[2].x, points2D[2].y, NULL); LineTo(dc, points2D[6].x, points2D[6].y);
	MoveToEx(dc, points2D[3].x, points2D[3].y, NULL); LineTo(dc, points2D[7].x, points2D[7].y);
	
	// Draw cargo box
	HPEN cargoPen = CreatePen(PS_SOLID, 3, RGB(200, 50, 50));
	SelectObject(dc, cargoPen);
	
	// Cargo bottom
	MoveToEx(dc, points2D[8].x, points2D[8].y, NULL);
	LineTo(dc, points2D[9].x, points2D[9].y);
	LineTo(dc, points2D[10].x, points2D[10].y);
	LineTo(dc, points2D[11].x, points2D[11].y);
	LineTo(dc, points2D[8].x, points2D[8].y);
	
	// Cargo top
	MoveToEx(dc, points2D[12].x, points2D[12].y, NULL);
	LineTo(dc, points2D[13].x, points2D[13].y);
	LineTo(dc, points2D[14].x, points2D[14].y);
	LineTo(dc, points2D[15].x, points2D[15].y);
	LineTo(dc, points2D[12].x, points2D[12].y);
	
	// Cargo sides
	MoveToEx(dc, points2D[8].x, points2D[8].y, NULL); LineTo(dc, points2D[12].x, points2D[12].y);
	MoveToEx(dc, points2D[9].x, points2D[9].y, NULL); LineTo(dc, points2D[13].x, points2D[13].y);
	MoveToEx(dc, points2D[10].x, points2D[10].y, NULL); LineTo(dc, points2D[14].x, points2D[14].y);
	MoveToEx(dc, points2D[11].x, points2D[11].y, NULL); LineTo(dc, points2D[15].x, points2D[15].y);
	
	// Draw wheels
	HBRUSH wheelBrush = CreateSolidBrush(RGB(40, 40, 40));
	HBRUSH oldBrush = (HBRUSH)SelectObject(dc, wheelBrush);
	HPEN wheelPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(dc, wheelPen);
	
	// Define wheel positions
	Point3D wheels[] = {
		{-cargoL/2 - cabL + 20, -cabW/2 - 10, -cabH + 15},  // Front left
		{-cargoL/2 - cabL + 20, cabW/2 + 10, -cabH + 15},   // Front right
		{cargoL/2 - 30, -cargoW/2 - 10, -cargoH + 15},      // Rear left
		{cargoL/2 - 30, cargoW/2 + 10, -cargoH + 15}        // Rear right
	};
	
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
	DeleteObject(wheelPen);
	DeleteObject(cargoPen);
	DeleteObject(cabPen);
	
	return S_OK;
}
