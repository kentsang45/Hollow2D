#include "ChildObj.h"
#include "EngineGlobals.h"
#include "Input.h"
#include "Scene/Scene.h"

CChildObj::CChildObj()	:
	m_pMesh(nullptr)
{
}


CChildObj::~CChildObj()
{
	SAFE_RELEASE(m_pMesh);
}

bool CChildObj::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("ColorTri");

	m_pMesh->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);

	SetRoot(m_pMesh);

	m_pMesh->SetRelativePos(0.f, 100.f, 0.f);
	m_pMesh->SetRelativeScale(80.f, 80.f, 1.f);

	return true;
}

void CChildObj::Begin()
{
	CGameObject::Begin();
}

void CChildObj::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CChildObj::Render(float fTime)
{
	CGameObject::Render(fTime);
}
