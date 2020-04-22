#pragma once

#include "../Client.h"

#include "Object/GameObject.h"

class HKTileMap : public CGameObject
{
public:
	HKTileMap();
	~HKTileMap();

	virtual bool Init();
	virtual void Begin();
	virtual void Render(float fTime);
	virtual void Update(float fTime);

	void CreateMap(TILE_MOVE eMove, int totalX, int totalY, int ilevel, float fTileSizeX, float fTileSizeY, const Vector3& vPos = Vector3::Zero);
	void SetTileMove(int countX, int countY, TILE_MOVE eMove);

	void SetInit(int countX, int countY);
	void CreateOneTile(int indexX, int indexY, float fTileSizeX, float fTileSizeY, int currentIndex, const Vector3& vPos = Vector3::Zero);

private:
	class CStaticMeshComponent* m_pMesh;
	class CColliderRect**			m_pTileArray;
	unsigned int			m_iTileCountX;
	unsigned int			m_iTileCountY;
	unsigned int			m_iTileTotalCount;


};