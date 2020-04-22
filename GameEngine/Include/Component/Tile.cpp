
#include "Tile.h"
#include "../Resource/StaticMesh.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/ShaderManager.h"
#include "../Resource/Shader.h"
#include "../Resource/BlendState.h"
#include "../Resource/Material.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../CameraManager.h"
#include "CameraComponent.h"
#include "../Device.h"

CTile::CTile()
{
	m_pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pLayout = GET_SINGLE(CShaderManager)->FindInputLayout(TILEMAP_INSTANCING_LAYOUT);
	m_pAlphaBlend = nullptr;
	m_pMaterial = nullptr;
	m_eType = TT_NONE;
	m_eOption = TO_NONE;
	ClearNav();
}

CTile::~CTile()
{
	SAFE_RELEASE(m_pMaterial);
	SAFE_RELEASE(m_pAlphaBlend);
	SAFE_RELEASE(m_pMesh);
}

float CTile::GetG() const
{
	return m_fG;
}

float CTile::GetTotal() const
{
	return m_fTotal;
}

NAV_INSERT_TYPE CTile::GetNavType() const
{
	return m_eNavType;
}

int CTile::GetIndexX() const
{
	return m_iIndexX;
}

int CTile::GetIndexY() const
{
	return m_iIndexY;
}

int CTile::GetIndex() const
{
	return m_iIndex;
}

TILE_OPTION CTile::GetTileOption() const
{
	return m_eOption;
}

Vector3 CTile::GetTilePos() const
{
	return m_vPos;
}

CTile * CTile::GetParent() const
{
	return m_pParent;
}

CMaterial * CTile::GetMaterial() const
{
	return m_pMaterial;
}

Vector3 CTile::GetTileSize() const
{
	return m_vSize;
}

Vector3 CTile::GetCenter() const
{
	return m_vCenter;
}

void CTile::SetTileOption(TILE_OPTION eOption)
{
	m_eOption = eOption;
}

void CTile::SetCost(float fG, float fH)
{
	m_fG = fG;
	m_fH = fH;
	m_fTotal = fG + fH;
}

void CTile::ClearNav()
{
	m_eNavType = NIT_NONE;
	m_fG = 0.f;
	m_fH = 0.f;
	m_fTotal = 0.f;
	m_pParent = nullptr;
}

void CTile::SetNavInsertType(NAV_INSERT_TYPE eType)
{
	m_eNavType = eType;
}

void CTile::SetParent(CTile * pParent)
{
	m_pParent = pParent;
}

void CTile::SetMesh(const string & strName)
{
	SAFE_RELEASE(m_pMesh);
	m_pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh(strName);
}

void CTile::SetInputLayout(const string & strName)
{
	m_pLayout = GET_SINGLE(CShaderManager)->FindInputLayout(strName);
}

void CTile::SetMaterial(const string & strName)
{
	CMaterial*	pMtrl = GET_SINGLE(CResourceManager)->FindMaterial(strName);

	if (pMtrl)
	{
		if (!m_pMaterial)
		{
			m_pMaterial = new CMaterial;

			m_pMaterial->Init();
		}
		m_pMaterial->CopyMaterial(pMtrl);

		m_pMaterial->SetMaterialShaderStyle(MSS_ENVIRONMENT);

		SAFE_RELEASE(pMtrl);
	}
}

void CTile::SetAlphaBlend()
{
	if (m_pAlphaBlend)
		return;

	m_pAlphaBlend = GET_SINGLE(CResourceManager)->FindRenderState(RENDERSTATE_ALPHABLEND);
}

void CTile::SetFrame(const ImageFrame & tFrame)
{
	m_tImgFrame = tFrame;
}

void CTile::SetInstancingData(PTileMapInstancingData pData)
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();

	CCameraComponent*	pCamera = pScene->GetCameraManager()->GetMainCamera();

	pData->matWVP = m_matWorld * pCamera->GetViewMatrix() * pCamera->GetProjMatrix();
	pData->matWVP.Transpose();

	pData->vStart = m_tImgFrame.vStart;
	pData->vEnd = m_tImgFrame.vEnd;
	pData->vImageSize = m_tImgFrame.vImageSize;
	pData->iFrame = m_tImgFrame.iFrame;
	pData->iImageType = m_tImgFrame.iImageType;
	pData->iTileOption = m_eOption;
	pData->iTileType = m_eType;
}

void CTile::PostUpdate(float fTime)
{
	Matrix	matScale, matPos;

	matScale.Scaling(m_vSize);
	matPos.Translation(m_vPos);

	m_matWorld = matScale * matPos;
}

void CTile::Render(float fTime)
{
	if (m_pMaterial)
	{
		TransformCBuffer	tBuffer = {};

		CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();

		CCameraComponent*	pCamera = pScene->GetCameraManager()->GetMainCamera();

		tBuffer.matWorld = m_matWorld;
		tBuffer.matView = pCamera->GetViewMatrix();
		// XMMatrixPerspectiveFovLH : 원근투영 행렬을 만들어주는 함수.
		// XMMatrixOrthographicOffCenterLH : 직교투영 행렬을 만들어주는 함수.
		tBuffer.matProj = pCamera->GetProjMatrix();
		tBuffer.matWV = tBuffer.matWorld * tBuffer.matView;
		tBuffer.matWVP = tBuffer.matWV * tBuffer.matProj;
		tBuffer.vPivot = Vector3::Zero;
		tBuffer.vMeshSize = m_pMesh->GetMax() - m_pMesh->GetMin();

		tBuffer.matWorld.Transpose();
		tBuffer.matView.Transpose();
		tBuffer.matProj.Transpose();
		tBuffer.matWV.Transpose();
		tBuffer.matWVP.Transpose();

		GET_SINGLE(CShaderManager)->UpdateCBuffer(TRANSFORM_CBUFFER,
			&tBuffer);

		GET_SINGLE(CShaderManager)->UpdateCBuffer(TILEMAP_CBUFFER,
			&m_tImgFrame);

		if (m_pAlphaBlend)
			m_pAlphaBlend->SetState();

		size_t	iContainer = m_pMesh->GetContainerCount();

		for (size_t i = 0; i < iContainer; ++i)
		{
			size_t	iSubset = m_pMesh->GetSubsetCount(i);

			for (size_t j = 0; j < iSubset; ++j)
			{
				m_pMaterial->SetMaterial(i, j);
				m_pMesh->Render(i, j);

				m_pMaterial->ResetState();
			}
		}

		if (m_pAlphaBlend)
			m_pAlphaBlend->ResetState();
	}
}

void CTile::RenderInstancing(float fTime, PInstancingBuffer pBuffer)
{
	if (m_pMaterial)
	{
		TransformCBuffer	tBuffer = {};

		CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();

		CCameraComponent*	pCamera = pScene->GetCameraManager()->GetMainCamera();

		tBuffer.matWorld = m_matWorld;
		tBuffer.matView = pCamera->GetViewMatrix();
		// XMMatrixPerspectiveFovLH : 원근투영 행렬을 만들어주는 함수.
		// XMMatrixOrthographicOffCenterLH : 직교투영 행렬을 만들어주는 함수.
		tBuffer.matProj = pCamera->GetProjMatrix();
		tBuffer.matWV = tBuffer.matWorld * tBuffer.matView;
		tBuffer.matWVP = tBuffer.matWV * tBuffer.matProj;
		tBuffer.vPivot = Vector3::Zero;
		tBuffer.vMeshSize = m_pMesh->GetMax() - m_pMesh->GetMin();

		tBuffer.matWorld.Transpose();
		tBuffer.matView.Transpose();
		tBuffer.matProj.Transpose();
		tBuffer.matWV.Transpose();
		tBuffer.matWVP.Transpose();

		GET_SINGLE(CShaderManager)->UpdateCBuffer(TRANSFORM_CBUFFER,
			&tBuffer);

		GET_SINGLE(CShaderManager)->UpdateCBuffer(TILEMAP_CBUFFER,
			&m_tImgFrame);

		if (m_pAlphaBlend)
			m_pAlphaBlend->SetState();

		CONTEXT->IASetInputLayout(m_pLayout);

		size_t	iContainer = m_pMesh->GetContainerCount();

		for (size_t i = 0; i < iContainer; ++i)
		{
			size_t	iSubset = m_pMesh->GetSubsetCount(i);

			for (size_t j = 0; j < iSubset; ++j)
			{
				m_pMaterial->SetMaterial(i, j);
				m_pMesh->RenderInstancing(i, j, pBuffer);

				m_pMaterial->ResetState();
			}
		}

		if (m_pAlphaBlend)
			m_pAlphaBlend->ResetState();
	}
}

void CTile::Save(FILE * pFile)
{
	fwrite(&m_eType, sizeof(TILE_TYPE), 1, pFile);
	fwrite(&m_eOption, sizeof(TILE_OPTION), 1, pFile);
	fwrite(&m_vPos, sizeof(Vector3), 1, pFile);
	fwrite(&m_vSize, sizeof(Vector3), 1, pFile);
	fwrite(&m_vImgStart, sizeof(Vector2), 1, pFile);
	fwrite(&m_vImgEnd, sizeof(Vector2), 1, pFile);
	fwrite(&m_tImgFrame, sizeof(ImageFrame), 1, pFile);
	fwrite(&m_iIndexX, sizeof(int), 1, pFile);
	fwrite(&m_iIndexY, sizeof(int), 1, pFile);
	fwrite(&m_iIndex, sizeof(int), 1, pFile);
}

void CTile::Load(FILE * pFile)
{
	fread(&m_eType, sizeof(TILE_TYPE), 1, pFile);
	fread(&m_eOption, sizeof(TILE_OPTION), 1, pFile);
	fread(&m_vPos, sizeof(Vector3), 1, pFile);
	fread(&m_vSize, sizeof(Vector3), 1, pFile);
	fread(&m_vImgStart, sizeof(Vector2), 1, pFile);
	fread(&m_vImgEnd, sizeof(Vector2), 1, pFile);
	fread(&m_tImgFrame, sizeof(ImageFrame), 1, pFile);
	fread(&m_iIndexX, sizeof(int), 1, pFile);
	fread(&m_iIndexY, sizeof(int), 1, pFile);
	fread(&m_iIndex, sizeof(int), 1, pFile);

	m_vCenter = (m_vPos + m_vPos + m_vSize) / 2.f;
}
