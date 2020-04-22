
#include "TestPixelCollision.h"
#include "EngineGlobals.h"
#include "Input.h"
#include "Scene/Scene.h"
//#include "Component/ColliderPixel.h"

CTestPixelCollision::CTestPixelCollision() :
	m_pMesh(nullptr),
	m_pBody(nullptr)
{
}


CTestPixelCollision::~CTestPixelCollision()
{
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pMesh);
}

bool CTestPixelCollision::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pBody = CreateComponent<CColliderPixel>("PixelBody");

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);

	m_pMesh->AddChild((CSceneComponent*)m_pBody, TR_POS);

	SetRoot(m_pMesh);

	m_pMesh->SetRelativePos(700.f, 300.f, 0.f);
	m_pMesh->SetRelativeScale(200.f, 200.f, 1.f);

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("TestPixelMtrl");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	m_pBody->LoadTexture(TEXT("PixelCollision.png"));

	return true;
}

void CTestPixelCollision::Begin()
{
	CGameObject::Begin();
}

void CTestPixelCollision::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CTestPixelCollision::Render(float fTime)
{
	CGameObject::Render(fTime);
}
