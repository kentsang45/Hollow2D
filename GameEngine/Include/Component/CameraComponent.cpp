#include "CameraComponent.h"
#include "../Device.h"
#include "Transform.h"

CCameraComponent::CCameraComponent()
{
	SetTypeID<CCameraComponent>();
	m_eCameraType = CT_PERSPECTIVE;

	ComputeMatrix();
}

CCameraComponent::CCameraComponent(const CCameraComponent & com)	:
	CSceneComponent(com)
{
	m_eCameraType = com.m_eCameraType;
}

CCameraComponent::~CCameraComponent()
{
}

CAMERA_TYPE CCameraComponent::GetCameraType() const
{
	return m_eCameraType;
}

void CCameraComponent::SetCameraType(CAMERA_TYPE eType)
{
	m_eCameraType = eType;

	ComputeMatrix();
}

Matrix CCameraComponent::GetViewMatrix() const
{
	return m_matView;
}

Matrix CCameraComponent::GetProjMatrix() const
{
	return m_matProj;
}

void CCameraComponent::ComputeMatrix()
{
	switch (m_eCameraType)
	{
	case CT_PERSPECTIVE:
		//m_matProj	= XMMatrixPerspectiveFovLH()
		break;
	case CT_ORTHOGONAL:
		m_matProj = XMMatrixOrthographicOffCenterLH(0.f,
			_RESOLUTION.iWidth, 0.f, _RESOLUTION.iHeight, 0.f, 1000.f);
		break;
	}
}

bool CCameraComponent::Init()
{
	if (!CSceneComponent::Init())
		return false;

	return true;
}

void CCameraComponent::Begin()
{
	CSceneComponent::Begin();

	ComputeMatrix();
}

void CCameraComponent::Update(float fTime)
{
	CSceneComponent::Update(fTime);
	
	/*
	Xx Xy Xz   00 01 02    1 0 0
	Yx Yy Yz * 10 11 12 = 0 1 0
	Zx Zy Zz   20 21 22    0 0 1

	1 0 0 0
	0 1 0 0
	0 0 1 0
	-X -Y -Z 1

	Xx Yx Zx 0
	Xy Yy Zy 0
	Xz Yz Zz 0
	-P.X -P.Y -P.Z  1
	*/
	m_matView.Identity();

	for (int i = 0; i < AXIS_MAX; ++i)
	{
		memcpy(&m_matView[i][0], &m_pTransform->GetWorldAxis((AXIS)i), sizeof(Vector3));
	}

	m_matView.Transpose();

	for (int i = 0; i < AXIS_MAX; ++i)
	{
		m_matView[3][i] = m_pTransform->GetWorldPos().Dot(m_pTransform->GetWorldAxis((AXIS)i)) * -1.f;
	}
}

void CCameraComponent::Render(float fTime)
{
	CSceneComponent::Render(fTime);
}
