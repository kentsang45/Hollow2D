
#include "../stdafx.h"
#include "FreeCamera.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/CameraComponent.h"
#include "Device.h"
#include "Input.h"

CFreeCamera::CFreeCamera()
{
}

CFreeCamera::~CFreeCamera()
{
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pCamera);
}

bool CFreeCamera::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pCamera = CGameObject::CreateComponent<CCameraComponent>("Camera");

	m_pCamera->SetCameraType(CT_ORTHOGONAL);

	m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f, _RESOLUTION.iHeight / -2.f, -20.f);

	SetRoot(m_pCamera);

	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pCamera);

	GET_SINGLE(CInput)->AddAxisKey("MoveUpDown", DIK_W, 1.f);
	GET_SINGLE(CInput)->AddAxisKey("MoveUpDown", DIK_S, -1.f);
	GET_SINGLE(CInput)->BindAxis<CFreeCamera>("MoveUpDown", this, &CFreeCamera::MoveUp);

	GET_SINGLE(CInput)->AddAxisKey("MoveSide", DIK_D, 1.f);
	GET_SINGLE(CInput)->AddAxisKey("MoveSide", DIK_A, -1.f);
	GET_SINGLE(CInput)->BindAxis<CFreeCamera>("MoveSide", this, &CFreeCamera::MoveSide);

	return true;
}

void CFreeCamera::Begin()
{
	CGameObject::Begin();
}

void CFreeCamera::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CFreeCamera::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CFreeCamera::MoveUp(float fScale, float fTime)
{
	m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * fScale);
}

void CFreeCamera::MoveSide(float fScale, float fTime)
{
	m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * fScale);
}
