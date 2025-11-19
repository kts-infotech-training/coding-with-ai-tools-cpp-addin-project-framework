#include "stdafx.h"
#include "JCBObject.h"
#include <vector>
#include <math.h>

// CJCBObject

STDMETHODIMP CJCBObject::GetObjectName(BSTR* pName)
{
	if (!pName)
		return E_POINTER;
	
	*pName = SysAllocString(L"JCB");
	return S_OK;
}

void CJCBObject::RotatePoint(const Point3D& input, Point3D& output, double angleX, double angleY)
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

POINT CJCBObject::ProjectTo2D(const Point3D& point3D, long centerX, long centerY)
{
	double distance = 500.0;
	double scale = distance / (distance + point3D.z);
	
	POINT pt;
	pt.x = (long)(point3D.x * scale) + centerX;
	pt.y = (long)(point3D.y * scale) + centerY;
	return pt;
}

STDMETHODIMP CJCBObject::Draw(long hDC, long rectLeft, long rectTop, long rectRight, long rectBottom, double angleX, double angleY)
{
	HDC dc = (HDC)hDC;
	long centerX = (rectLeft + rectRight) / 2;
	long centerY = (rectTop + rectBottom) / 2;
	
	std::vector<Point3D> vertices;
	std::vector<POINT> points2D;
	
	// Base/Chassis (tracks)
	double baseW = 80, baseH = 30, baseD = 120;
	vertices.push_back({-baseD/2, -baseW/2, -baseH});  // 0
	vertices.push_back({baseD/2, -baseW/2, -baseH});   // 1
	vertices.push_back({baseD/2, baseW/2, -baseH});    // 2
	vertices.push_back({-baseD/2, baseW/2, -baseH});   // 3
	vertices.push_back({-baseD/2, -baseW/2, 0});       // 4
	vertices.push_back({baseD/2, -baseW/2, 0});        // 5
	vertices.push_back({baseD/2, baseW/2, 0});         // 6
	vertices.push_back({-baseD/2, baseW/2, 0});        // 7
	
	// Cabin
	double cabW = 60, cabH = 60, cabD = 70;
	vertices.push_back({-cabD/2, -cabW/2, 0});         // 8
	vertices.push_back({cabD/2, -cabW/2, 0});          // 9
	vertices.push_back({cabD/2, cabW/2, 0});           // 10
	vertices.push_back({-cabW/2, cabW/2, 0});          // 11
	vertices.push_back({-cabD/2 + 10, -cabW/2 + 10, cabH});  // 12
	vertices.push_back({cabD/2 - 10, -cabW/2 + 10, cabH});   // 13
	vertices.push_back({cabD/2 - 10, cabW/2 - 10, cabH});    // 14
	vertices.push_back({-cabD/2 + 10, cabW/2 - 10, cabH});   // 15
	
	// Excavator arm segments
	vertices.push_back({baseD/2 - 20, 0, 10});         // 16: Arm base
	vertices.push_back({baseD/2 + 40, 0, 40});         // 17: Arm joint
	vertices.push_back({baseD/2 + 80, 0, 20});         // 18: Arm end
	vertices.push_back({baseD/2 + 100, 0, 0});         // 19: Bucket
	
	// Rotate and project all vertices
	for (size_t i = 0; i < vertices.size(); i++)
	{
		Point3D rotated;
		RotatePoint(vertices[i], rotated, angleX, angleY);
		points2D.push_back(ProjectTo2D(rotated, centerX, centerY));
	}
	
	// Draw base/tracks
	HPEN trackPen = CreatePen(PS_SOLID, 4, RGB(255, 200, 0));
	HPEN oldPen = (HPEN)SelectObject(dc, trackPen);
	
	// Base bottom
	MoveToEx(dc, points2D[0].x, points2D[0].y, NULL);
	LineTo(dc, points2D[1].x, points2D[1].y);
	LineTo(dc, points2D[2].x, points2D[2].y);
	LineTo(dc, points2D[3].x, points2D[3].y);
	LineTo(dc, points2D[0].x, points2D[0].y);
	
	// Base top
	MoveToEx(dc, points2D[4].x, points2D[4].y, NULL);
	LineTo(dc, points2D[5].x, points2D[5].y);
	LineTo(dc, points2D[6].x, points2D[6].y);
	LineTo(dc, points2D[7].x, points2D[7].y);
	LineTo(dc, points2D[4].x, points2D[4].y);
	
	// Base sides
	MoveToEx(dc, points2D[0].x, points2D[0].y, NULL); LineTo(dc, points2D[4].x, points2D[4].y);
	MoveToEx(dc, points2D[1].x, points2D[1].y, NULL); LineTo(dc, points2D[5].x, points2D[5].y);
	MoveToEx(dc, points2D[2].x, points2D[2].y, NULL); LineTo(dc, points2D[6].x, points2D[6].y);
	MoveToEx(dc, points2D[3].x, points2D[3].y, NULL); LineTo(dc, points2D[7].x, points2D[7].y);
	
	// Draw cabin
	HPEN cabinPen = CreatePen(PS_SOLID, 3, RGB(255, 150, 0));
	SelectObject(dc, cabinPen);
	
	// Cabin bottom
	MoveToEx(dc, points2D[8].x, points2D[8].y, NULL);
	LineTo(dc, points2D[9].x, points2D[9].y);
	LineTo(dc, points2D[10].x, points2D[10].y);
	LineTo(dc, points2D[11].x, points2D[11].y);
	LineTo(dc, points2D[8].x, points2D[8].y);
	
	// Cabin top
	MoveToEx(dc, points2D[12].x, points2D[12].y, NULL);
	LineTo(dc, points2D[13].x, points2D[13].y);
	LineTo(dc, points2D[14].x, points2D[14].y);
	LineTo(dc, points2D[15].x, points2D[15].y);
	LineTo(dc, points2D[12].x, points2D[12].y);
	
	// Cabin edges
	MoveToEx(dc, points2D[8].x, points2D[8].y, NULL); LineTo(dc, points2D[12].x, points2D[12].y);
	MoveToEx(dc, points2D[9].x, points2D[9].y, NULL); LineTo(dc, points2D[13].x, points2D[13].y);
	MoveToEx(dc, points2D[10].x, points2D[10].y, NULL); LineTo(dc, points2D[14].x, points2D[14].y);
	MoveToEx(dc, points2D[11].x, points2D[11].y, NULL); LineTo(dc, points2D[15].x, points2D[15].y);
	
	// Draw excavator arm
	HPEN armPen = CreatePen(PS_SOLID, 5, RGB(100, 100, 100));
	SelectObject(dc, armPen);
	
	MoveToEx(dc, points2D[16].x, points2D[16].y, NULL);
	LineTo(dc, points2D[17].x, points2D[17].y);
	LineTo(dc, points2D[18].x, points2D[18].y);
	LineTo(dc, points2D[19].x, points2D[19].y);
	
	// Draw bucket
	HBRUSH bucketBrush = CreateSolidBrush(RGB(150, 150, 150));
	HBRUSH oldBrush = (HBRUSH)SelectObject(dc, bucketBrush);
	Ellipse(dc, points2D[19].x - 15, points2D[19].y - 15, points2D[19].x + 15, points2D[19].y + 15);
	
	// Cleanup
	SelectObject(dc, oldBrush);
	DeleteObject(bucketBrush);
	SelectObject(dc, oldPen);
	DeleteObject(armPen);
	DeleteObject(cabinPen);
	DeleteObject(trackPen);
	
	return S_OK;
}
