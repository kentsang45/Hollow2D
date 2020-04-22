
#include "ColliderPixel.h"
#include "Transform.h"
#include "Collision.h"
#include "ColliderRect.h"
#include "ColliderSphere2D.h"
#include "ColliderPoint.h"
#include "../Resource/DirectXTex.h"
#include "../PathManager.h"

CColliderPixel::CColliderPixel()
{
	m_bTickUpdate = true;
	m_pPixel = nullptr;
	m_iWidth = 0;
	m_iHeight = 0;
	m_iPixelSize = 0;

	SetTypeID<CColliderPixel>();

	m_vSectionMin = Vector3(-30.f, -30.f, 0.f);
	m_vSectionMax = Vector3(30.f, 30.f, 0.f);

	m_eColliderType = COLLIDER_PIXEL;

	m_IgnoreColor[0] = 255;
	m_IgnoreColor[1] = 0;
	m_IgnoreColor[2] = 255;
	m_IgnoreColor[3] = 0;
}

CColliderPixel::CColliderPixel(const CColliderPixel & com) :
	CColliderBase(com)
{
	m_pPixel = nullptr;
	m_iWidth = 0;
	m_iHeight = 0;
	m_iPixelSize = 0;

	m_IgnoreColor[0] = 255;
	m_IgnoreColor[1] = 0;
	m_IgnoreColor[2] = 255;
	m_IgnoreColor[3] = 0;
}

CColliderPixel::~CColliderPixel()
{
	SAFE_DELETE_ARRAY(m_pPixel);
}

unsigned char * CColliderPixel::GetPixel()
{
	return m_pPixel;
}

int CColliderPixel::GetPixelSize() const
{
	return m_iPixelSize;
}

int CColliderPixel::GetPixelCountX() const
{
	return m_iWidth;
}

int CColliderPixel::GetPixelCountY() const
{
	return m_iHeight;
}

unsigned char * CColliderPixel::GetIgnoreColor()
{
	return m_IgnoreColor;
}

bool CColliderPixel::LoadTexture(const TCHAR* pFileName, const string& strPathName)
{
	ScratchImage	tImage = {};

	const TCHAR* pPath = GET_SINGLE(CPathManager)->FindPath(strPathName);

	TCHAR	strFullPath[MAX_PATH] = {};

	if (pPath)
		lstrcpy(strFullPath, pPath);

	lstrcat(strFullPath, pFileName);

	// 경로에서 확장자를 얻어온다.
	TCHAR	strExt[_MAX_EXT] = {};

	_wsplitpath_s(strFullPath, nullptr, 0, nullptr, 0, nullptr, 0, strExt, _MAX_EXT);

	char	_strExt[_MAX_EXT] = {};

	WideCharToMultiByte(CP_ACP, 0, strExt, -1, _strExt,
		lstrlen(strExt), nullptr, nullptr);

	_strupr_s(_strExt);

	if (strcmp(_strExt, ".DDS") == 0)
	{
		if (FAILED(LoadFromDDSFile(strFullPath, DDS_FLAGS_NONE, nullptr, tImage)))
			return false;
	}

	else if (strcmp(_strExt, ".TGA") == 0)
	{
		if (FAILED(LoadFromTGAFile(strFullPath, nullptr, tImage)))
			return false;
	}

	else
	{
		if (FAILED(LoadFromWICFile(strFullPath, WIC_FLAGS_NONE, nullptr, tImage)))
			return false;
	}

	m_iWidth = tImage.GetImages()[0].width;
	m_iHeight = tImage.GetImages()[0].height;
	m_iPixelSize = tImage.GetPixelsSize() / (m_iWidth * m_iHeight);

	m_pPixel = new unsigned char[tImage.GetPixelsSize()];

	memcpy(m_pPixel, tImage.GetPixels(), tImage.GetPixelsSize());

	unsigned char*	pLine = new unsigned char[m_iWidth * m_iPixelSize + 1];

	for (int i = 0; i < m_iHeight / 2; ++i)
	{
		memcpy(pLine, &m_pPixel[i * m_iWidth * m_iPixelSize], m_iWidth * m_iPixelSize);
		memcpy(&m_pPixel[i * m_iWidth * m_iPixelSize], &m_pPixel[(m_iHeight - 1 - i) * m_iWidth * m_iPixelSize], m_iWidth * m_iPixelSize);
		memcpy(&m_pPixel[(m_iHeight - 1 - i) * m_iWidth * m_iPixelSize], pLine, m_iWidth * m_iPixelSize);
	}

	SAFE_DELETE_ARRAY(pLine);

	return true;
}

void CColliderPixel::SetIgnoreColor(unsigned char r, unsigned char g, unsigned char b)
{
	m_IgnoreColor[0] = r;
	m_IgnoreColor[1] = g;
	m_IgnoreColor[2] = b;
}

bool CColliderPixel::Init()
{
	if (!CColliderBase::Init())
		return false;

	SetDebugMesh("ColliderRect");

	return true;
}

void CColliderPixel::Begin()
{
	CColliderBase::Begin();
}

void CColliderPixel::Update(float fTime)
{
	CColliderBase::Update(fTime);

	m_vSectionMin = m_pTransform->GetWorldPos() - m_pTransform->GetPivot() * Vector3(m_iWidth, m_iHeight, 0.f);
	m_vSectionMax = m_vSectionMin + Vector3(m_iWidth, m_iHeight, 0.f);
	SetRelativeScale(m_iWidth, m_iHeight, 1.f);
}

void CColliderPixel::Render(float fTime)
{
	CColliderBase::Render(fTime);
}

void CColliderPixel::RenderInstancing(float fTime, PInstancingBuffer pBuffer)
{
	CColliderBase::RenderInstancing(fTime, pBuffer);
}

bool CColliderPixel::Collision(CColliderBase * pDest)
{
	switch (pDest->GetColliderType())
	{
	case COLLIDER_RECT:
		return CCollision::CollisionRectToPixel((CColliderRect*)pDest, this);
	case COLLIDER_SPHERE2D:
		//return CCollision::CollisionSphere2DToSphere2D(this, (CColliderPixel*)pDest);
		break;
	case COLLIDER_OBB2D:
		//return CCollision::CollisionOBB2DToOBB2D(this, (CColliderPixel*)pDest);
		break;
	case COLLIDER_PIXEL:
		break;
	case COLLIDER_POINT:
		break;
	}

	return false;
}

bool CColliderPixel::Collision(const Vector2 & vMousePos)
{
	return CCollision::CollisionPixelToMouse(this, vMousePos);
}
