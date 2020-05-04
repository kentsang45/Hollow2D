#include "Section.h"
#include "Component/ColliderBase.h"
#include "CollisionManager.h"

CSection::CSection()	:
	m_iIndex(0)
	, m_bUI(false)
{
	m_iColliderCount = 0;

	m_vecCollider.resize(1000);
}

CSection::~CSection()
{
}

bool CSection::Init(const Vector3 & vMin, const Vector3 & vMax, int iIndex)
{
	m_iIndex = iIndex;

	m_vMin = vMin;
	m_vMax = vMax;
	m_vSize = m_vMax - m_vMin;

	return true;
}

void CSection::AddCollider(CColliderBase * pCollider)
{
	if (m_iColliderCount == m_vecCollider.capacity())
		m_vecCollider.resize(m_vecCollider.capacity() * 2);

	m_vecCollider[m_iColliderCount] = pCollider;
	++m_iColliderCount;
}

void CSection::Clear()
{
	m_iColliderCount = 0;
}

void CSection::Collision(float fTime)
{
	if (m_iColliderCount < 2)
		return;

	for (unsigned int i = 0; i < m_iColliderCount - 1; ++i)
	{
		CColliderBase*	pSrc = m_vecCollider[i];

		for (unsigned int j = i + 1; j < m_iColliderCount; ++j)
		{
			CColliderBase*	pDest = m_vecCollider[j];

			if (pSrc->GetOwner() == pDest->GetOwner())
				continue;

			PCollisionProfile	pSrcProfile = pSrc->GetCollisionProfile();
			PCollisionProfile	pDestProfile = pDest->GetCollisionProfile();

			COLLISION_TYPE	eSrcType = FindCollisionType(pSrcProfile, pDestProfile->strChannelName);
			COLLISION_TYPE	eDestType = FindCollisionType(pDestProfile, pSrcProfile->strChannelName);

			if (eSrcType != CT_NONE && eDestType != CT_NONE &&
				!pSrc->IsCurrentFrameCollision(pDest))
			{
				if (eSrcType != CT_IGNORE || eDestType != CT_IGNORE)
				{
					///////////////////////////////////////////////////////////
					///////////////////////////////////////////////////////////
					///////////////////////////////////////////////////////////
					// MK::PLAYER_VERSION

					if (true == pSrc->IsPlayer() || true == pSrc->IsSencer())
					{
						if (pSrc->Collision(pDest))
						{
							// 있으면 다시 넣지 않는다.
							// 없으면 넣음
							if (false == pSrc->IsCollisionList(pDest))
							{
								pSrc->AddCollisionList(pDest);
								pDest->AddCollisionList(pSrc);
							}

							
							// 항상 콜백 호출
							pSrc->CallBlock(pDest, fTime);
							pDest->CallBlock(pSrc, fTime);


							pSrc->IsColliding(true);
							
		

							if (pSrc->IsOverlap())
								pSrc->CallBeginOverlap(pDest, fTime);

							if (pDest->IsOverlap())
								pDest->CallBeginOverlap(pSrc, fTime);
						}
						// 충돌 중이 아니다.
						else
						{
							// 충돌되다가 지금 떨어질 경우
							if (pSrc->IsCollisionList(pDest))
							{
								pSrc->DeleteCollisionList(pDest);
								pDest->DeleteCollisionList(pSrc);

								if (true == pDest->IsPlayer() || true == pSrc->IsPlayer())
								{
									int a = 0;
								}

								if (pSrc->IsOverlap())
								{
									pSrc->CallEndOverlap(pDest, fTime);
									pSrc->IsColliding(false);
								}

								if (pDest->IsOverlap())
								{
									pDest->CallEndOverlap(pSrc, fTime);
								}
							}
						}
					}
					else
					{
						////////////////////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////////////////////
					//////////////////////////////////////////////////////////////////////////////// 보통 충돌

					// 충돌 되었다면
						if (pSrc->Collision(pDest))
						{
							// 처음 충돌되는지 계속 충될되고 있었는지를 판단한다.
							// 리스트에 들어있지 않으면 처음 충돌
							if (!pSrc->IsCollisionList(pDest))
							{
								if (true == pSrc->IsOn() && true == pDest->IsOn())
								{

									pSrc->AddCollisionList(pDest);
									pDest->AddCollisionList(pSrc);

									pSrc->CallBlock(pDest, fTime);
									pDest->CallBlock(pSrc, fTime);

									if (pSrc->IsOverlap())
										pSrc->CallBeginOverlap(pDest, fTime);

									if (pDest->IsOverlap())
										pDest->CallBeginOverlap(pSrc, fTime);
								}
							}

							pSrc->AddCurrentFrameCollision(pDest);
							pDest->AddCurrentFrameCollision(pSrc);
						}

						else
						{
							// 충돌되다가 지금 떨어질 경우
							if (pSrc->IsCollisionList(pDest))
							{
								pSrc->DeleteCollisionList(pDest);
								pDest->DeleteCollisionList(pSrc);

								if (true == pDest->IsPlayer() || true == pSrc->IsPlayer())
								{
									int a = 0;
								}

								if (pSrc->IsOverlap())
								{

									pSrc->CallEndOverlap(pDest, fTime);
								}

								if (pDest->IsOverlap())
								{
									pDest->CallEndOverlap(pSrc, fTime);
								}
							}
					}

					
					}
				}
			}
		}
	}
}

bool CSection::Collision(const Vector2 & vMousePos, float fTime)
{
	for (unsigned int i = 0; i < m_iColliderCount; ++i)
	{
		CColliderBase*	pSrc = m_vecCollider[i];

		PCollisionProfile	pSrcProfile = pSrc->GetCollisionProfile();

		COLLISION_TYPE	eSrcType = FindCollisionType(pSrcProfile, "Mouse");

		if (eSrcType != CT_NONE)
		{
			if (eSrcType != CT_IGNORE)
			{
				if (pSrc->Collision(vMousePos))
				{
					if(!pSrc->IsMouseCollision())
					{
						pSrc->CollisionMouse(true);
						pSrc->CallBlock(nullptr, fTime);
						pSrc->CallBeginOverlap(nullptr, fTime);
					}

					GET_SINGLE(CCollisionManager)->SetCurrentMouseCollision(pSrc);
					
					return true;
				}

				else if (pSrc->IsMouseCollision())
				{
					GET_SINGLE(CCollisionManager)->SetPrevMouseCollision(nullptr);
					pSrc->CallEndOverlap(nullptr, fTime);
					pSrc->CollisionMouse(false);
				}
			}
		}
	}

	return false;
}

void CSection::UIEnable()
{
	m_bUI = true;
}

void CSection::Sort()
{
	if (m_iColliderCount < 2)
		return;

	if (m_bUI)
		sort(m_vecCollider.begin(), m_vecCollider.begin() + m_iColliderCount, CSection::SortZOrder);

	else
		sort(m_vecCollider.begin(), m_vecCollider.begin() + m_iColliderCount, CSection::SortY);
}



COLLISION_TYPE CSection::FindCollisionType(PCollisionProfile pProfile, const string& strChannelName)
{
	auto	iter = pProfile->ChannelList.begin();
	auto	iterEnd = pProfile->ChannelList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter).strName == strChannelName)
			return (*iter).eType;
	}

	return CT_NONE;
}

bool CSection::SortY(CColliderBase * pSrc, CColliderBase * pDest)
{
	float	fSrcY = pSrc->GetWorldPos().y - pSrc->GetPivot().y * pSrc->GetWorldScale().y;
	float	fDestY = pDest->GetWorldPos().y - pDest->GetPivot().y * pDest->GetWorldScale().y;

	return fSrcY < fDestY;
}

bool CSection::SortZOrder(CColliderBase * pSrc, CColliderBase * pDest)
{
	return pSrc->GetZOrder() > pDest->GetZOrder();
}