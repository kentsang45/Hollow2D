#pragma once

#include "GameEngine.h"

class ENGINE_DLL CSectionManager
{
	friend class CCollisionManager;

private:
	CSectionManager();
	~CSectionManager();

private:
	Vector3		m_vMin;
	Vector3		m_vMax;
	Vector3		m_vSize;
	Vector3		m_vSectionSize;
	Vector3		m_vDefaultSectionSize;
	class CSection**	m_ppSectionArray;
	unsigned int		m_iSectionCountX;
	unsigned int		m_iSectionCountY;
	unsigned int		m_iSectionCountZ;
	unsigned int		m_iSectionCount;
	bool m_bUI;

public:
	bool CreateSection(const Vector3& vMin, const Vector3& vMax, bool bUI = false);
	void AddCollider(class CColliderBase* pCollider);
	void Clear();
	void Collision(float fTime);
	bool CollisionMouse(const Vector2& vMousePos, float fTime);
	void Sort();
};

