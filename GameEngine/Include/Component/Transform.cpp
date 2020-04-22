#include "Transform.h"
#include "../Resource/ShaderManager.h"
#include "../Device.h"
#include "SceneComponent.h"
#include "../Object/GameObject.h"
#include "../Scene/Scene.h"
#include "../CameraManager.h"
#include "CameraComponent.h"
#include "../Render/RenderManager.h"

CTransform::CTransform()
{
	m_pOwner	= nullptr;
	m_vRelativeScale = Vector3::One;
	m_pParent = nullptr;
	m_iTransformRule = TR_ALL;
	m_vScaleRatio = Vector3::One;

	for (int i = 0; i < AXIS_MAX; ++i)
	{
		m_vRelativeAxis[i] = Vector3::Axis[i];
		m_vWorldAxis[i] = Vector3::Axis[i];
	}
}

CTransform::~CTransform()
{
}

const TransformCBuffer & CTransform::GetCBuffer() const
{
	return m_tCBuffer;
}

void CTransform::SetScene(CScene * pScene)
{
	m_pScene	= pScene;
}

void CTransform::PostUpdate(float fTime)
{
	if (GET_SINGLE(CRenderManager)->GetRenderMode() == RM_2D)
	{
		// m_vRelativePos.z	= 0.f;
		// m_vWorldPos.z = 0.f;
	}
}

void CTransform::SetTransformRule(int iTransformRule)
{
	m_iTransformRule = iTransformRule;
}

void CTransform::ComputeScaleRatio()
{
	if (m_iTransformRule & TR_SCALE && m_pParent)
	{
		Vector3	vScale = m_pParent->GetWorldScale();

		m_vScaleRatio = m_vRelativeScale / vScale;
	}

	size_t	iSize = m_vecChild.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecChild[i]->ComputeScaleRatio();
	}
}

void CTransform::ComputeRotation()
{
	if (m_iTransformRule & TR_ROT && m_pParent)
	{
		m_vWorldRot = m_vRelativeRot + m_pParent->GetWorldRot();

		// 부모가 회전을 했을 경우를 대비해서 자식의 위치를 변경한다.
		// 부모를 기준으로 공전 시킬 수 있도록 해야 한다.
		// 상대적인 위치 * 부모행렬을 해주면 부모에 영향을 받는 위치정보를
		// 만들어낼 수 있다.
		Matrix	matParent;
		matParent.Rotation(m_pParent->GetCurRot());

		m_vCurRot += m_pParent->GetCurRot();

		Vector3	vRelativePos = m_vRelativePos.TransformCoord(matParent);

		m_vCurPos = vRelativePos - m_vRelativePos;

		m_vFramePos += m_vCurPos;

		m_vRelativePos = vRelativePos;

		m_vWorldPos = m_vRelativePos + m_pParent->GetWorldPos();

		m_matTranslation.Translation(m_vWorldPos);
	}

	else
		m_vWorldRot = m_vRelativeRot;

	m_matRot.Rotation(m_vWorldRot);

	// 상대적인 축정보를 만들어낸다.
	Matrix	matRot;
	matRot.Rotation(m_vRelativeRot);

	for (int i = 0; i < AXIS_MAX; ++i)
	{
		m_vRelativeAxis[i] = Vector3::Axis[i].TransformNormal(matRot);
		m_vRelativeAxis[i].Normalize();

		m_vWorldAxis[i] = Vector3::Axis[i].TransformNormal(m_matRot);
		m_vWorldAxis[i].Normalize();
	}

	size_t	iSize = m_vecChild.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecChild[i]->ComputeRotation();
	}
}

void CTransform::ComputePos()
{
	if (m_iTransformRule & TR_POS && m_pParent)
	{
		m_vWorldPos = m_vRelativePos + m_pParent->GetWorldPos();
	}

	else
		m_vWorldPos = m_vRelativePos;

	m_matTranslation.Translation(m_vWorldPos);

	size_t	iSize = m_vecChild.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecChild[i]->ComputePos();
	}
}

void CTransform::Flip(int iFlip)
{
	m_iFlip = iFlip;
}

void CTransform::SetRelativeScale(const Vector3 & vScale)
{
	m_vCurScale = vScale - m_vRelativeScale;

	m_vFrameScale += m_vCurScale;

	m_vRelativeScale = vScale;

	m_vWorldScale = m_vRelativeScale;

	m_matScale.Scaling(m_vWorldScale);

	ComputeScaleRatio();
}

void CTransform::SetRelativeScale(float x, float y, float z)
{
	m_vCurScale = Vector3(x, y, z) - m_vRelativeScale;

	m_vFrameScale += m_vCurScale;

	m_vRelativeScale = Vector3(x, y, z);

	m_vWorldScale = m_vRelativeScale;

	m_matScale.Scaling(m_vWorldScale);

	ComputeScaleRatio();
}

void CTransform::SetRelativeRotation(const Vector3 & vRot)
{
	m_vCurRot = vRot - m_vRelativeRot;

	m_vFrameRot += m_vCurRot;

	m_vRelativeRot = vRot;

	ComputeRotation();
}

void CTransform::SetRelativeRotation(float x, float y, float z)
{
	m_vCurRot = Vector3(x, y, z) - m_vRelativeRot;

	m_vFrameRot += m_vCurRot;

	m_vRelativeRot = Vector3(x, y, z);

	ComputeRotation();
}

void CTransform::SetRelativeRotationX(float x)
{
	m_vCurRot = Vector3::Zero;
	m_vCurRot.x = x - m_vRelativeRot.x;

	m_vFrameRot.x += (x - m_vRelativeRot.x);

	m_vRelativeRot.x = x;

	ComputeRotation();
}

void CTransform::SetRelativeRotationY(float y)
{
	m_vCurRot = Vector3::Zero;
	m_vCurRot.y = y - m_vRelativeRot.y;

	m_vFrameRot.y += (y - m_vRelativeRot.y);

	m_vRelativeRot.y = y;

	ComputeRotation();
}

void CTransform::SetRelativeRotationZ(float z)
{
	m_vCurRot = Vector3::Zero;
	m_vCurRot.z = z - m_vRelativeRot.z;

	m_vFrameRot.z += (z - m_vRelativeRot.z);

	m_vRelativeRot.z = z;

	ComputeRotation();
}

void CTransform::SetRelativePos(const Vector3 & vPos)
{
	m_vCurPos = vPos - m_vRelativePos;

	m_vFramePos += m_vCurPos;

	m_vRelativePos = vPos;

	ComputePos();
}

void CTransform::SetRelativePos(float x, float y, float z)
{
	m_vCurPos = Vector3(x, y, z) - m_vRelativePos;

	m_vFramePos += m_vCurPos;

	m_vRelativePos = Vector3(x, y, z);

	ComputePos();
}

void CTransform::AddRelativeScale(const Vector3 & vScale)
{
	m_vCurScale = vScale;

	m_vFrameScale += vScale;

	m_vRelativeScale += vScale;

	m_vWorldScale += vScale;

	m_matScale.Scaling(m_vWorldScale);

	ComputeScaleRatio();
}

void CTransform::AddRelativeScale(float x, float y, float z)
{
	m_vCurScale = Vector3(x, y, z);

	m_vFrameScale += Vector3(x, y, z);

	m_vRelativeScale += Vector3(x, y, z);

	m_vWorldScale += Vector3(x, y, z);

	m_matScale.Scaling(m_vWorldScale);

	ComputeScaleRatio();
}

void CTransform::AddRelativePos(const Vector3 & vPos)
{
	m_vCurPos = vPos;

	m_vFramePos += vPos;

	m_vRelativePos += vPos;

	ComputePos();
}

void CTransform::AddRelativePos(float x, float y, float z)
{
	m_vCurPos = Vector3(x, y, z);

	m_vFramePos += Vector3(x, y, z);

	m_vRelativePos += Vector3(x, y, z);

	ComputePos();
}

void CTransform::AddRelativeRotation(const Vector3 & vRot)
{
	m_vCurRot = vRot;

	m_vFrameRot += vRot;

	m_vRelativeRot += vRot;

	ComputeRotation();
}

void CTransform::AddRelativeRotation(float x, float y, float z)
{
	m_vCurRot = Vector3(x, y, z);

	m_vFrameRot += Vector3(x, y, z);

	m_vRelativeRot += Vector3(x, y, z);

	ComputeRotation();
}

void CTransform::AddRelativeRotationX(float x)
{
	m_vCurRot = Vector3::Zero;
	m_vCurRot.x = x;

	m_vFrameRot.x += x;

	m_vRelativeRot.x += x;

	ComputeRotation();
}

void CTransform::AddRelativeRotationY(float y)
{
	m_vCurRot = Vector3::Zero;
	m_vCurRot.y = y;

	m_vFrameRot.y += y;

	m_vRelativeRot.y += y;

	ComputeRotation();
}

void CTransform::AddRelativeRotationZ(float z)
{
	m_vCurRot = Vector3::Zero;
	m_vCurRot.z = z;

	m_vFrameRot.z += z;

	m_vRelativeRot.z += z;

	ComputeRotation();
}

Vector3 CTransform::GetRelativeScale() const
{
	return m_vRelativeScale;
}

Vector3 CTransform::GetRelativeRot() const
{
	return m_vRelativeRot;
}

Vector3 CTransform::GetRelativePos() const
{
	return m_vRelativePos;
}

Vector3 CTransform::GetRelativeAxis(AXIS eAxis) const
{
	return m_vRelativeAxis[eAxis];
}

// =================== World ===================
void CTransform::SetWorldScale(const Vector3 & vScale)
{
	m_vCurScale = vScale - m_vWorldScale;

	m_vFrameScale += m_vCurScale;

	m_vWorldScale = vScale;

	m_matScale.Scaling(m_vWorldScale);

	ComputeScaleRatio();
}

void CTransform::SetWorldScale(float x, float y, float z)
{
	m_vCurScale = Vector3(x, y, z) - m_vWorldScale;

	m_vFrameScale += m_vCurScale;

	m_vWorldScale = Vector3(x, y, z);

	m_matScale.Scaling(m_vWorldScale);

	ComputeScaleRatio();
}

void CTransform::SetWorldRotation(const Vector3 & vRot)
{
	m_vCurRot = vRot - m_vWorldRot;

	m_vFrameRot += m_vCurRot;

	m_vRelativeRot += (vRot - m_vWorldRot);

	m_vWorldRot = vRot;

	ComputeRotation();
}

void CTransform::SetWorldRotation(float x, float y, float z)
{
	m_vCurRot = Vector3(x, y, z) - m_vWorldRot;

	m_vFrameRot += m_vCurRot;

	m_vRelativeRot += (Vector3(x, y, z) - m_vWorldRot);

	m_vWorldRot = Vector3(x, y, z);

	ComputeRotation();
}

void CTransform::SetWorldRotationX(float x)
{
	m_vCurRot = Vector3::Zero;
	m_vCurRot.x = x - m_vWorldRot.x;

	m_vFrameRot.x += m_vCurRot.x;

	m_vRelativeRot.x += (x - m_vWorldRot.x);

	m_vWorldRot.x = x;

	ComputeRotation();
}

void CTransform::SetWorldRotationY(float y)
{
	m_vCurRot = Vector3::Zero;
	m_vCurRot.y = y - m_vWorldRot.y;

	m_vFrameRot.y += m_vCurRot.y;

	m_vRelativeRot.y += (y - m_vWorldRot.y);

	m_vWorldRot.y = y;

	ComputeRotation();
}

void CTransform::SetWorldRotationZ(float z)
{
	m_vCurRot = Vector3::Zero;
	m_vCurRot.z = z - m_vWorldRot.z;

	m_vFrameRot.z += m_vCurRot.z;

	m_vRelativeRot.z += (z - m_vWorldRot.z);

	m_vWorldRot.z = z;

	ComputeRotation();
}

void CTransform::SetWorldPos(const Vector3 & vPos)
{
	m_vCurPos = vPos - m_vWorldPos;

	m_vFramePos += m_vCurPos;

	m_vRelativePos += (vPos - m_vWorldPos);

	m_vWorldPos = vPos;

	ComputePos();
}

void CTransform::SetWorldPos(float x, float y, float z)
{
	m_vCurPos = Vector3(x, y, z) - m_vWorldPos;

	m_vFramePos += m_vCurPos;

	m_vRelativePos += (Vector3(x, y, z) - m_vWorldPos);

	m_vWorldPos = Vector3(x, y, z);

	ComputePos();
}

void CTransform::AddWorldScale(const Vector3 & vScale)
{
	m_vCurScale = vScale;

	m_vFrameScale += vScale;

	m_vWorldScale += vScale;

	m_matScale.Scaling(m_vWorldScale);

	ComputeScaleRatio();
}

void CTransform::AddWorldScale(float x, float y, float z)
{
	m_vCurScale = Vector3(x, y, z);

	m_vFrameScale += Vector3(x, y, z);

	m_vWorldScale += Vector3(x, y, z);

	m_matScale.Scaling(m_vWorldScale);

	ComputeScaleRatio();
}

void CTransform::AddWorldPos(const Vector3 & vPos)
{
	m_vCurPos = vPos;

	m_vFramePos += vPos;

	Vector3	vPrevWorld = m_vWorldPos;

	m_vWorldPos += vPos;

	m_vRelativePos += (m_vWorldPos - vPrevWorld);

	ComputePos();
}

void CTransform::AddWorldPos(float x, float y, float z)
{
	m_vCurPos = Vector3(x, y, z);

	m_vFramePos += Vector3(x, y, z);

	Vector3	vPrevWorld = m_vWorldPos;

	m_vWorldPos += Vector3(x, y, z);

	m_vRelativePos += (m_vWorldPos - vPrevWorld);

	ComputePos();
}

void CTransform::AddWorldRotation(const Vector3 & vRot)
{
	m_vCurRot = vRot;

	m_vFrameRot += vRot;

	m_vRelativeRot += vRot;

	m_vWorldRot += vRot;

	ComputeRotation();
}

void CTransform::AddWorldRotation(float x, float y, float z)
{
	m_vCurRot = Vector3(x, y, z);

	m_vFrameRot += Vector3(x, y, z);

	m_vRelativeRot += Vector3(x, y, z);

	m_vWorldRot += Vector3(x, y, z);

	ComputeRotation();
}

void CTransform::AddWorldRotationX(float x)
{
	m_vCurRot = Vector3::Zero;
	m_vCurRot.x = x;

	m_vFrameRot.x += x;

	m_vRelativeRot.x += x;

	m_vWorldRot.x += x;

	ComputeRotation();
}

void CTransform::AddWorldRotationY(float y)
{
	m_vCurRot = Vector3::Zero;
	m_vCurRot.y = y;

	m_vFrameRot.y += y;

	m_vRelativeRot.y += y;

	m_vWorldRot.y += y;

	ComputeRotation();
}

void CTransform::AddWorldRotationZ(float z)
{
	m_vCurRot = Vector3::Zero;
	m_vCurRot.z = z;

	m_vFrameRot.z += z;

	m_vRelativeRot.z += z;

	m_vWorldRot.z += z;

	ComputeRotation();
}

void CTransform::SetPivot(const Vector3 & vPivot)
{
	m_vPivot = vPivot;
}

void CTransform::SetPivot(float x, float y, float z)
{
	m_vPivot = Vector3(x, y, z);
}

void CTransform::SetMeshSize(const Vector3 & vSize)
{
	m_vMeshSize = vSize;
}

Vector3 CTransform::GetWorldScale() const
{
	return m_vWorldScale;
}

Vector3 CTransform::GetWorldRot() const
{
	return m_vWorldRot;
}

Vector3 CTransform::GetWorldPos() const
{
	return m_vWorldPos;
}

Vector3 CTransform::GetWorldAxis(AXIS eAxis) const
{
	return m_vWorldAxis[eAxis];
}

Vector3 CTransform::GetPivot() const
{
	return m_vPivot;
}

Matrix CTransform::GetScaleMatrix() const
{
	return m_matScale;
}

Matrix CTransform::GetRotMatrix() const
{
	return m_matRot;
}

Matrix CTransform::GetTranslationMatrix() const
{
	return m_matTranslation;
}

Matrix CTransform::GetWorldMatrix() const
{
	return m_matWorld;
}

Vector3 CTransform::GetFrameScale() const
{
	return m_vFrameScale;
}

Vector3 CTransform::GetFrameRot() const
{
	return m_vFrameRot;
}

Vector3 CTransform::GetFramePos() const
{
	return m_vFramePos;
}

Vector3 CTransform::GetCurScale() const
{
	return m_vCurScale;
}

Vector3 CTransform::GetCurRot() const
{
	return m_vCurRot;
}

Vector3 CTransform::GetCurPos() const
{
	return m_vCurPos;
}

void CTransform::ClearFrameInfo()
{
	m_vFrameScale = Vector3::Zero;
	m_vFrameRot = Vector3::Zero;
	m_vFramePos = Vector3::Zero;
}

void CTransform::LookAt(CSceneComponent * pCom)
{
	LookAt(pCom->GetWorldPos());
}

void CTransform::LookAt(CTransform * pTransform)
{
	LookAt(pTransform->GetWorldPos());
}

void CTransform::LookAt(CGameObject * pObj)
{
	LookAt(pObj->GetWorldPos());
}

void CTransform::LookAt(const Vector3 & vLookAt)
{
	Vector3	vOriginAxis = Vector3::Axis[AXIS_Y];
	Vector3	vDir = vLookAt - m_vWorldPos;

	if (vDir.x == 0.f && vDir.y == 0.f && vDir.z == 0.f)
		return;

	vDir.Normalize();

	float	fDot = vOriginAxis.Dot(vDir);

	if (fDot >= 0.9999f || fDot <= -0.9999f)
		return;

	Vector3	vRotAxis = vOriginAxis.Cross(vDir);
	vRotAxis.Normalize();

	float	fAngle = vOriginAxis.Angle(vDir);

	m_matRot.RotationAxis(vRotAxis, fAngle);

	m_vRelativeRot = GetRotationAngle(m_matRot);

	ComputeRotation();

	for (int i = 0; i < AXIS_MAX; ++i)
	{
		m_vRelativeAxis[i] = Vector3::Axis[i].TransformNormal(m_matRot);
		m_vRelativeAxis[i].Normalize();

		m_vWorldAxis[i] = Vector3::Axis[i].TransformNormal(m_matRot);
		m_vWorldAxis[i].Normalize();
	}
}

void CTransform::ComputeTransform()
{
	CCameraComponent*	pCamera = m_pScene->GetCameraManager()->GetMainCamera();

	if (m_pOwner)
	{
		if (m_pOwner->IsUI())
			pCamera = m_pScene->GetCameraManager()->GetUICamera();
	}

	else
	{
		pCamera = m_pScene->GetCameraManager()->GetUICamera();
	}

	m_tCBuffer.matWorld = m_matScale * m_matRot * m_matTranslation;
	m_tCBuffer.matView = pCamera->GetViewMatrix();
	// XMMatrixPerspectiveFovLH : 원근투영 행렬을 만들어주는 함수.
	// XMMatrixOrthographicOffCenterLH : 직교투영 행렬을 만들어주는 함수.
	m_tCBuffer.matProj = pCamera->GetProjMatrix();
	m_tCBuffer.matWV = m_tCBuffer.matWorld * m_tCBuffer.matView;
	m_tCBuffer.matWVP = m_tCBuffer.matWV * m_tCBuffer.matProj;
	m_tCBuffer.vPivot = m_vPivot;
	m_tCBuffer.vMeshSize = m_vMeshSize;

	m_tCBuffer.matWorld.Transpose();
	m_tCBuffer.matView.Transpose();
	m_tCBuffer.matProj.Transpose();
	m_tCBuffer.matWV.Transpose();
	m_tCBuffer.matWVP.Transpose();

	if (-1 == m_iFlip)
	{
		m_tCBuffer.iEmpty = -1;
	}
	else if (1 == m_iFlip)
	{
		m_tCBuffer.iEmpty = 1;
	}

}

void CTransform::SetTransform()
{
	ComputeTransform();

	GET_SINGLE(CShaderManager)->UpdateCBuffer(TRANSFORM_CBUFFER,
		&m_tCBuffer);

	m_vFrameScale = Vector3::Zero;
	m_vFrameRot = Vector3::Zero;
	m_vFramePos = Vector3::Zero;
	m_vCurScale = Vector3::Zero;
	m_vCurRot = Vector3::Zero;
	m_vCurPos = Vector3::Zero;
}

Vector3 CTransform::GetRotationAngle(Matrix & matRot)
{
	Vector3	vAngle = {};

	vAngle.z = atan2(matRot[0][0], matRot[1][0]) * 180.f / PI - 90.f;
	vAngle.y = atan2(-matRot[2][0], sqrtf(matRot[0][0] * matRot[0][0] + matRot[1][0] * matRot[1][0])) * 180.f / PI;
	vAngle.x = atan2(matRot[2][1], matRot[2][2]) * 180.f / PI;

	return vAngle;
}
