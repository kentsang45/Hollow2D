#pragma once

#include "Object/GameObject.h"

class CEditMapObject :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CEditMapObject();
	~CEditMapObject();

private:
	class CTileMap*	m_pTileMap;

public:
	void CreateTileMap(TILE_TYPE eType, int iCountX, int iCountY, int iSizeX, int iSizeY,
		const string& strTexName, const TCHAR* pFullPath);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

public:
	void Save(const char* pFullPath);
	void Load(const char* pFullPath, const char* pMaterialName);
};

