#pragma once

#include "../GameEngine.h"

class ENGINE_DLL CCollision
{
public:
	static bool CollisionRectToRect(class CColliderRect* pSrc, class CColliderRect* pDest);
	static bool CollisionSphere2DToSphere2D(class CColliderSphere2D* pSrc, class CColliderSphere2D* pDest);
	static bool CollisionOBB2DToOBB2D(class CColliderOBB2D* pSrc, class CColliderOBB2D* pDest);
	static bool CollisionRectToPixel(class CColliderRect* pSrc, class CColliderPixel* pDest);
	static bool CollisionRectToMouse(class CColliderRect* pSrc, const Vector2& vMousePos);
	static bool CollisionSphere2DToMouse(class CColliderSphere2D* pSrc, const Vector2& vMousePos);
	static bool CollisionOBB2DToMouse(class CColliderOBB2D* pSrc, const Vector2& vMousePos);
	static bool CollisionPixelToMouse(class CColliderPixel* pSrc, const Vector2& vMousePos);

private:
	static bool CollisionRectToRect(Vector3& vIntersect, const Vector3& vSrcMin, const Vector3& vSrcMax,
		const Vector3& vDestMin, const Vector3& vDestMax);
	static bool CollisionSphere2DToSphere2D(Vector3& vIntersect, const Vector3& vSrcCenter,
		float fSrcRadius, const Vector3& vDestCenter, float fDestRadius);
	static bool CollisionOBB2DToOBB2D(Vector3& vIntersect, const Vector3& vSrcCenter,
		Vector3 vSrcAxis[2], float fSrcLength[2], const Vector3& vDestCenter,
		Vector3 vDestAxis[2], float fDestLength[2]);
	static bool CollisionRectToPixel(Vector3& vIntersect, const Vector3& vSrcMin, const Vector3& vSrcMax,
		const Vector3& vDestMin, const Vector3& vDestMax, unsigned char* pPixel,
		int iPixelSize, int iPixelCountX, int iPixelCountY, unsigned char* pIgnoreColor);
};

