#include "JustBug.h"

#include "EngineGlobals.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Component/ColliderRect.h"
#include "Component/ColliderOBB2D.h"

#include "Sencer.h"

JustBug::JustBug()
{
}


JustBug::~JustBug()
{
}

bool JustBug::Init()
{
	if (false == Bug::Init())
	{
		BOOM
		return false;
	}

	Bug::SetAnimation("BUG");
	m_pMesh->SetPivot(0.5f, 0.585f, 0.f);

	m_pBody->AddBlockCallback<JustBug>(this, &JustBug::OnBlock);

	return true;
}

void JustBug::Begin()
{
	Bug::Begin();
}

void JustBug::Update(float fTime)
{
	Bug::Update(fTime);
}

void JustBug::Render(float fTime)
{
	Bug::Render(fTime);
}

void JustBug::MoveX(float fTime)
{
	Bug::MoveX(fTime);
}

void JustBug::Reverse()
{
}

void JustBug::CheckFront()
{
	Bug::CheckFront();
}

void JustBug::MoveBack(float fTime)
{
	Bug::MoveBack(fTime);
}

void JustBug::JumpBack(float fTime)
{
	Bug::JumpBack(fTime);
}

void JustBug::JumpEnd(float fTime)
{
	Bug::JumpEnd(fTime);
}

void JustBug::SetCurrentState(BUG_STATE eState)
{
	Bug::SetCurrentState(eState);
}

void JustBug::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	Bug::OnBlock(pSrc, pDest, fTime);
}
