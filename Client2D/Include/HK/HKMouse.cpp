#include "HKMouse.h"

#include "Component/ColliderPoint.h"
#include "Input.h"

HKMouse::HKMouse()
{
}

HKMouse::~HKMouse()
{
	SAFE_RELEASE(m_pBody);
}

bool HKMouse::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pBody = CreateComponent<CColliderPoint>("MouseBody");

	m_pBody->CollisionMouse(true);

	SetRoot(m_pBody);

	m_pBody->AddBeginOverlapCallback<HKMouse>(this, &HKMouse::OnBlock);

	return true;
}

void HKMouse::Begin()
{
	CGameObject::Begin();
}

void HKMouse::Update(float fTime)
{
	CGameObject::Update(fTime);

	Vector2 mouse = GET_SINGLE(CInput)->GetMousePos();

	m_pBody->SetPoint( Vector3(mouse.x , mouse.y, 0.f) );

}

void HKMouse::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void HKMouse::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	int a = 0;
}
