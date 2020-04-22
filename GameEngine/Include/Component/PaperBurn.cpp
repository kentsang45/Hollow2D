#include "PaperBurn.h"
#include "SceneComponent.h"
#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Material.h"

CPaperBurn::CPaperBurn() :
	m_fTime(0.f),
	m_fBurnTime(2.f),
	m_pUpdateComponent(nullptr),
	m_bInverse(false),
	m_pBurnTexture(nullptr),
	m_pMaterial(nullptr),
	m_bComplete(false)
{
	SetTypeID<CPaperBurn>();

	m_tCBuffer.vColorOut = Vector3(1.f, 0.f, 0.f);
	m_tCBuffer.vColorCenter = Vector3(1.f, 1.f, 0.f);
	m_tCBuffer.vColorIn = Vector3(1.f, 1.f, 1.f);
}

CPaperBurn::CPaperBurn(const CPaperBurn & com) :
	CObjectComponent(com)
{
	m_fBurnTime = com.m_fBurnTime;

	m_fTime = 0.f;
	m_pUpdateComponent = nullptr;
	m_bComplete = false;
	m_bInverse = com.m_bInverse;

	m_pBurnTexture = com.m_pBurnTexture;

	if (m_pBurnTexture)
		m_pBurnTexture->AddRef();

	m_tCBuffer = com.m_tCBuffer;

	m_pMaterial = nullptr;
}

CPaperBurn::~CPaperBurn()
{
	SAFE_RELEASE(m_pMaterial);
	SAFE_RELEASE(m_pBurnTexture);
	SAFE_RELEASE(m_pUpdateComponent);
}

bool CPaperBurn::IsInverse() const
{
	return m_bInverse;
}

void CPaperBurn::SetUpdateComponent(CSceneComponent * pComponent)
{
	SAFE_RELEASE(m_pUpdateComponent);
	m_pUpdateComponent = pComponent;

	if (m_pUpdateComponent)
	{
		m_pUpdateComponent->AddRef();

		m_pMaterial = m_pUpdateComponent->GetMaterial();

		if (m_pMaterial)
		{
			m_pMaterial->EnablePaperBurn(true);
			m_pMaterial->CreateCBufferNode(PAPERBURN_CBUFFER, 6, sizeof(PaperBurnCBuffer));

			if (m_pBurnTexture && m_pMaterial)
				m_pMaterial->SetTexture(6, m_pBurnTexture);
		}
	}
}

void CPaperBurn::SetBurnTime(float fTime)
{
	m_fBurnTime = fTime;
}

void CPaperBurn::Clear()
{
	m_fTime = 0.f;
	m_bComplete = false;
}

void CPaperBurn::SetBurnTexture(const string & strName, const TCHAR * pFileName, const string & strPathName)
{
	SAFE_RELEASE(m_pBurnTexture);
	GET_SINGLE(CResourceManager)->LoadTexture(strName, pFileName, strPathName);
	m_pBurnTexture = GET_SINGLE(CResourceManager)->FindTexture(strName);

	if (m_pMaterial)
		m_pMaterial->SetTexture(6, m_pBurnTexture);
}

void CPaperBurn::Inverse()
{
	m_bInverse = !m_bInverse;

	if (!m_pUpdateComponent)
		return;
}

void CPaperBurn::SetColorOutLine(const Vector3 & vColor)
{
	m_tCBuffer.vColorOut = vColor;
}

void CPaperBurn::SetColorOutLine(float r, float g, float b)
{
	m_tCBuffer.vColorOut = Vector3(r, g, b);
}

void CPaperBurn::SetColorCenter(const Vector3 & vColor)
{
	m_tCBuffer.vColorCenter = vColor;
}

void CPaperBurn::SetColorCenter(float r, float g, float b)
{
	m_tCBuffer.vColorCenter = Vector3(r, g, b);
}

void CPaperBurn::SetColorInLine(const Vector3 & vColor)
{
	m_tCBuffer.vColorIn = vColor;
}

void CPaperBurn::SetColorInLine(float r, float g, float b)
{
	m_tCBuffer.vColorIn = Vector3(r, g, b);
}

bool CPaperBurn::Init()
{
	SetBurnTexture("DefaultBurn", TEXT("DefaultPaperBurn.png"));

	return true;
}

void CPaperBurn::Begin()
{
}

void CPaperBurn::Update(float fTime)
{
	m_fTime += fTime;

	m_tCBuffer.fFilter = m_fTime / m_fBurnTime;

	m_tCBuffer.fFilter = m_tCBuffer.fFilter > 1.f ? 1.f : m_tCBuffer.fFilter;

	if (m_fTime >= m_fBurnTime)
	{
		m_bComplete = true;

		if (m_CompleteFunction)
			m_CompleteFunction();
	}

	m_tCBuffer.bInverse = m_bInverse;

	m_pMaterial->UpdateCBufferNode(PAPERBURN_CBUFFER, &m_tCBuffer);
}

void CPaperBurn::PostUpdate(float fTime)
{
}

void CPaperBurn::SetCompleteFunction(void(*pFunc)())
{
	m_CompleteFunction = bind(pFunc);
}
