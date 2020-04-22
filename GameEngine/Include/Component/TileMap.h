#pragma once

#include "SceneComponent.h"

class ENGINE_DLL CTileMap :
	public CSceneComponent
{
	friend class CGameObject;

protected:
	CTileMap();
	CTileMap(const CTileMap& com);
	virtual ~CTileMap();

protected:
	class CStaticMesh*	m_pMesh;
	ID3D11InputLayout*	m_pLayout;
	class CMaterial*	m_pMaterial;
	class CRenderState*		m_pAlphaBlend;
	class CTile**			m_pTileArray;
	unsigned int			m_iTileCountX;
	unsigned int			m_iTileCountY;
	unsigned int			m_iTileCount;
	Vector3					m_vSize;
	Vector3					m_vTileSize;
	TILE_TYPE				m_eTileType;
	int						m_iStartX;
	int						m_iStartY;
	int						m_iEndX;
	int						m_iEndY;
	bool					m_bTileRender;
	vector<ImageFrame>		m_vecFrame;
	PInstancingBuffer		m_pInstancingBuffer;
	PTileMapInstancingData	m_pInstancingData;
	int						m_iRenderCount;

public:
	int GetTileCountX()	const;
	int	GetTileCountY()	const;
	int	GetTileCount()	const;
	Vector3 GetTileSize()	const;
	TILE_TYPE GetTileType() const;

public:
	void SetMesh(const string& strName);
	void SetInputLayout(const string& strName);
	void SetMaterial(const string& strName);
	void SetAlphaBlend();
	void SetTileMesh(const string& strName);
	void SetTileInputLayout(const string& strName);
	void SetTileMaterial(const string& strName);
	void SetTileAlphaBlend();
	void CreateTile(TILE_TYPE eType, unsigned int iCountX, unsigned int iCountY,
		const Vector3& vTileSize, const Vector3& vPos = Vector3::Zero);
	void AddFrame(const Vector2& vStart, const Vector2& vEnd, const Vector2& vImgSize,
		IMAGE_TYPE eType);
	class CTile* GetTile(const Vector3& vPos);
	class CTile* GetTile(float x, float y);
	class CTile* GetTileFromIndex(int x, int y);
	int GetTileIndex(const Vector3& vPos);
	int GetTileIndex(float x, float y);
	int GetTileIndexX(const Vector3& vPos);
	int GetTileIndexY(const Vector3& vPos);


public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Render(float fTime);


	void Save(const char* pFullPath);
	void Load(const char* pFullPath);
	void LoadPath(const char* pFileName, const string& strPathName = RESOURCE_PATH);

private:
	void CreateTileRect(const Vector3& vPos = Vector3::Zero);
	void CreateTileIsometric(const Vector3& vPos = Vector3::Zero);

};

