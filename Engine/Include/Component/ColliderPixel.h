#pragma once

#include "ColliderBase.h"

class ENGINE_DLL CColliderPixel :
	public CColliderBase
{
	friend class CGameObject;
	friend class CCollision;

protected:
	CColliderPixel();
	CColliderPixel(const CColliderPixel& com);
	virtual ~CColliderPixel();

protected:
	unsigned char*	m_pPixel;
	int		m_iWidth;
	int		m_iHeight;
	int		m_iPixelSize;
	unsigned char	m_IgnoreColor[4];

public:
	unsigned char* GetPixel();
	int GetPixelSize()	const;
	int GetPixelCountX()	const;
	int GetPixelCountY()	const;
	unsigned char* GetIgnoreColor();

public:
	bool LoadTexture(const TCHAR* pFileName, const string& strPathName = TEXTURE_PATH);
	void SetIgnoreColor(unsigned char r, unsigned char g, unsigned char b);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
	virtual void RenderInstancing(float fTime, PInstancingBuffer pBuffer);

public:
	virtual bool Collision(CColliderBase* pDest);
	virtual bool Collision(const Vector2& vMousePos);
};

