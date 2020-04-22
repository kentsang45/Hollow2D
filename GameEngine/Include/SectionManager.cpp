#include "SectionManager.h"
#include "Section.h"
#include "Component/ColliderBase.h"

CSectionManager::CSectionManager() :
	m_vDefaultSectionSize(100000.f, 100000.f, 100000.f),
	m_iSectionCountX(0),
	m_iSectionCountY(0),
	m_iSectionCountZ(0),
	m_iSectionCount(0),
	m_ppSectionArray(nullptr),
	m_bUI(false)
{
}

CSectionManager::~CSectionManager()
{
	for (int i = 0; i < m_iSectionCount; ++i)
	{
		SAFE_DELETE(m_ppSectionArray[i]);
	}

	SAFE_DELETE_ARRAY(m_ppSectionArray);
}

bool CSectionManager::CreateSection(const Vector3 & vMin, const Vector3 & vMax, bool bUI)
{
	m_bUI = bUI;

	m_vMin = vMin;
	m_vMax = vMax;
	m_vSize = m_vMax - m_vMin;

	float	fX = m_vSize.x / m_vDefaultSectionSize.x;
	m_iSectionCountX = (int)fX;

	fX -= (int)fX;

	if (fX > 0.f)
		++m_iSectionCountX;

	float	fY = m_vSize.y / m_vDefaultSectionSize.y;
	m_iSectionCountY = (int)fY;

	fY -= (int)fY;

	if (fY > 0.f)
		++m_iSectionCountY;

	float	fZ = m_vSize.z / m_vDefaultSectionSize.z;
	m_iSectionCountZ = (int)fZ;

	fZ -= (int)fZ;

	if (fZ > 0.f)
	{
		++m_iSectionCountZ;
	}
	

	m_iSectionCount = m_iSectionCountX * m_iSectionCountY * m_iSectionCountZ;

	m_vSectionSize = m_vSize / Vector3(m_iSectionCountX, m_iSectionCountY, m_iSectionCountZ);

	SAFE_DELETE_ARRAY(m_ppSectionArray);

	m_ppSectionArray = new CSection*[m_iSectionCount];

	for (int z = 0; z < m_iSectionCountZ; ++z)
	{
		for (int y = 0; y < m_iSectionCountY; ++y)
		{
			for (int x = 0; x < m_iSectionCountX; ++x)
			{
				int	idx = z * (m_iSectionCountX * m_iSectionCountY) + y * m_iSectionCountX + x;
				
				m_ppSectionArray[idx] = new CSection;

				if (true == bUI)
				{
					m_ppSectionArray[idx]->UIEnable();
				}

				m_ppSectionArray[idx]->Init(Vector3(x, y, z) * m_vSectionSize,
					Vector3(x + 1, y + 1, z + 1) * m_vSectionSize, idx);
			}
		}
	}

	return true;
}

void CSectionManager::AddCollider(CColliderBase * pCollider)
{
	// 충돌체가 소속될 영역의 인덱스를 구한다.
	Vector3	vMin = pCollider->GetColliderSectionMin() - m_vMin;
	Vector3 vMax = pCollider->GetColliderSectionMax() - m_vMin;

	int	iStartX = (int)vMin.x / (int)m_vSectionSize.x;
	int	iStartY = (int)vMin.y / (int)m_vSectionSize.y;
	int	iStartZ = (int)vMin.z / (int)m_vSectionSize.z;

	int	iEndX = (int)vMax.x / (int)m_vSectionSize.x;
	int	iEndY = (int)vMax.y / (int)m_vSectionSize.y;
	int	iEndZ = (int)vMax.z / (int)m_vSectionSize.z;

	if (iStartX >= m_iSectionCountX || iEndX < 0 ||
		iStartY >= m_iSectionCountY || iEndY < 0 ||
		iStartZ >= m_iSectionCountZ || iEndZ < 0)
		return;

	iStartX = iStartX < 0 ? 0 : iStartX;
	iStartY = iStartY < 0 ? 0 : iStartY;
	iStartZ = iStartZ < 0 ? 0 : iStartZ;

	iEndX = iEndX >= m_iSectionCountX ? m_iSectionCountX - 1 : iEndX;
	iEndY = iEndY >= m_iSectionCountY ? m_iSectionCountY - 1 : iEndY;
	iEndZ = iEndZ >= m_iSectionCountZ ? m_iSectionCountZ - 1 : iEndZ;

	for (int z = iStartZ; z <= iEndZ; ++z)
	{
		for (int y = iStartY; y <= iEndY; ++y)
		{
			for (int x = iStartX; x <= iEndX; ++x)
			{
				int	iIndex = z * m_iSectionCountX * m_iSectionCountY + y * m_iSectionCountX + x;

				pCollider->AddSectionIndex(iIndex);
				m_ppSectionArray[iIndex]->AddCollider(pCollider);
			}
		}
	}
}

void CSectionManager::Clear()
{
	for (int i = 0; i < m_iSectionCount; ++i)
	{
		m_ppSectionArray[i]->Clear();
	}
}

void CSectionManager::Collision(float fTime)
{
	for (int i = 0; i < m_iSectionCount; ++i)
	{
		m_ppSectionArray[i]->Collision(fTime);
	}
}

bool CSectionManager::CollisionMouse(const Vector2 & vMousePos, float fTime)
{
	// 충돌체가 소속될 영역의 인덱스를 구한다.
	Vector2	vMin = vMousePos - Vector2(m_vMin.x, m_vMin.y);

	int	iStartX = (int)vMin.x / (int)m_vSectionSize.x;
	int	iStartY = (int)vMin.y / (int)m_vSectionSize.y;

	if (iStartX >= m_iSectionCountX || iStartY >= m_iSectionCountY ||
		iStartX < 0 || iStartY < 0)
		return false;

	int	iIndex = iStartY * m_iSectionCountX + iStartX;

	return m_ppSectionArray[iIndex]->Collision(vMousePos, fTime);
}

void CSectionManager::Sort()
{
	for (int i = 0; i < m_iSectionCount; ++i)
	{
		m_ppSectionArray[i]->Sort();
	}
}
