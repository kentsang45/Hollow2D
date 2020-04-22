#pragma once

#include "HKTileMap.h"

#include "EngineGlobals.h"
#include "Scene/Scene.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Component/ColliderRect.h"
#include "Component/ColliderBase.h"

HKTileMap::HKTileMap()
{
	m_pTileArray = nullptr;
	m_iTileCountX = 0;
	m_iTileCountY = 0;
	m_iTileTotalCount = 0;
}

HKTileMap::~HKTileMap()
{
	if (m_iTileTotalCount != 0)
	{
		for (unsigned int i = 0; i < m_iTileCountY; ++i)
		{
			for (unsigned int j = 0; j < m_iTileCountX; ++j)
			{
				if (nullptr != m_pTileArray[i * m_iTileCountX + j])
				{
					SAFE_RELEASE(m_pTileArray[i * m_iTileCountX + j]);
				}
				
			}
		}

		SAFE_DELETE_ARRAY(m_pTileArray);
	}

	SAFE_RELEASE(m_pMesh);
}

bool HKTileMap::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");
	SetRoot(m_pMesh);


	return true;
}

void HKTileMap::Begin()
{
	CGameObject::Begin();
}

void HKTileMap::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void HKTileMap::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void HKTileMap::CreateMap(TILE_MOVE eMove, int totalX, int totalY, int ilevel, float fTileSizeX, float fTileSizeY, const Vector3 & vPos)
{
	if (m_iTileTotalCount != 0)
	{
		for (unsigned int i = 0; i < m_iTileCountY; ++i)
		{
			for (unsigned int j = 0; j < m_iTileCountX; ++j)
			{
				SAFE_RELEASE(m_pTileArray[i * m_iTileCountX + j]);
			}
		}

		SAFE_DELETE_ARRAY(m_pTileArray);
	}

	m_iTileCountX = totalX;
	m_iTileCountY = totalY;
	m_iTileTotalCount = totalX * totalY;

	for (unsigned int i = 0; i < m_iTileCountY; ++i)
	{
		for (unsigned int j = 0; j < m_iTileCountX; ++j)
		{
			int	iIndex = i * m_iTileCountX + j;

			m_pTileArray[iIndex] = CGameObject::CreateComponent<CColliderRect>("TileBody");
			m_pTileArray[iIndex]->SetWorldPos(vPos + Vector3(j * fTileSizeX, i * fTileSizeY, 0.f));
		}
	}



}

void HKTileMap::SetTileMove(int countX, int countY, TILE_MOVE eMove)
{
}

void HKTileMap::SetInit(int countX, int countY)
{
	m_iTileCountX = countX;
	m_iTileCountY = countY;
	m_iTileTotalCount = countX * countY;

	m_pTileArray = new CColliderRect*[m_iTileTotalCount];

	for (unsigned int i = 0; i < m_iTileCountY; ++i)
	{
		for (unsigned int j = 0; j < m_iTileCountX; ++j)
		{
			m_pTileArray[i * m_iTileCountX + j] = nullptr;
		}
	}
}

void HKTileMap::CreateOneTile(int indexX, int indexY, float fTileSizeX, float fTileSizeY, int currentIndex, const Vector3 & vPos)
{
	m_pTileArray[currentIndex] = CGameObject::CreateComponent<CColliderRect>("TileBody");
	m_pTileArray[currentIndex]->SetWorldPos(vPos + Vector3(indexX * fTileSizeX, indexY * fTileSizeY, 0.f));

	m_pTileArray[currentIndex]->SetRelativeScale(fTileSizeX, fTileSizeY, 0);
	m_pTileArray[currentIndex]->SetStage(true);

	m_pMesh->AddChild(m_pTileArray[currentIndex], TR_POS);

	m_pTileArray[currentIndex]->SetExtent(fTileSizeX, fTileSizeY);
	m_pTileArray[currentIndex]->SetPivot(0.5f, 0.5f, 0.f);
	m_pTileArray[currentIndex]->SetCollisionProfile("Stage");



}
