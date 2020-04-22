#include "Input.h"
#include "Engine.h"
#include "Device.h"
#include "Resource/StaticMesh.h"
#include "Resource/Shader.h"
#include "Resource/ShaderManager.h"
#include "Resource/ResourceManager.h"
#include "Resource/Texture.h"
#include "Component/Animation2D.h"
#include "Component/Transform.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "CameraManager.h"
#include "Component/CameraComponent.h"
#include "Resource/RenderState.h"

DEFINITION_SINGLE(CInput)

CInput::CInput()	:
	m_pInput(nullptr),
	m_pKeyboard(nullptr),
	m_pMouse(nullptr),
	m_pMouseTr(nullptr),
	m_pMouseMesh(nullptr),
	m_pMouseShader(nullptr),
	m_pMouseAnim(nullptr),
	m_pMouseTexture(nullptr),
	m_pAlphaBlend(nullptr),
	m_bShowCursor(true),
	m_fDoubleKeyTime(0.5f)
{
}

CInput::~CInput()
{
	SAFE_RELEASE(m_pAlphaBlend);
	SAFE_DELETE(m_pMouseTexture);
	SAFE_DELETE(m_pMouseTr);
	SAFE_RELEASE(m_pMouseMesh);
	SAFE_RELEASE(m_pMouseShader);
	SAFE_RELEASE(m_pMouseAnim);

	SAFE_DELETE_NORMAL_MAP(m_mapAxis);
	SAFE_DELETE_NORMAL_MAP(m_mapAction);

	if (m_pKeyboard)
		m_pKeyboard->Unacquire();

	if (m_pMouse)
		m_pMouse->Unacquire();

	SAFE_RELEASE(m_pKeyboard);
	SAFE_RELEASE(m_pMouse);
	SAFE_RELEASE(m_pInput);
}

Vector2 CInput::GetMousePos() const
{
	return m_vMousePos;
}

Vector2 CInput::GetMouseWorldPos() const
{
	return m_vMouseWorldPos;
}

Vector2 CInput::GetMouseMove() const
{
	return m_vMouseMove;
}

bool CInput::LButtonDown() const
{
	return m_tMouseInfo[MT_LBUTTON].bOnEvent[KS_PRESS];
}

bool CInput::RButtonDown() const
{
	return m_tMouseInfo[MT_RBUTTON].bOnEvent[KS_PRESS];
}

bool CInput::LButtonPush() const
{
	return m_tMouseInfo[MT_LBUTTON].bOnEvent[KS_PUSH];
}

bool CInput::RButtonPush() const
{
	return m_tMouseInfo[MT_RBUTTON].bOnEvent[KS_PUSH];
}

bool CInput::LButtonRelease() const
{
	return m_tMouseInfo[MT_LBUTTON].bOnEvent[KS_RELEASE];
}

bool CInput::RButtonRelease() const
{
	return m_tMouseInfo[MT_RBUTTON].bOnEvent[KS_RELEASE];
}

void CInput::SetDoubleKeyTime(float fTime)
{
	m_fDoubleKeyTime = fTime;
}

void CInput::CreateAnim2D()
{
	if (m_pMouseAnim)
		return;

	if (m_bShowCursor)
		ShowCursor(false);

	m_bShowCursor = false;

	m_pMouseAnim = CAnimation2D::CreateAnimation2D<CAnimation2D>();

	SAFE_RELEASE(m_pMouseShader);
	m_pMouseShader	= GET_SINGLE(CShaderManager)->FindShader(UI_ANIM2D_SHADER);
}

void CInput::AddAnim2DSequence(const string & strName)
{
	m_pMouseAnim->AddAnimation2DSequence(strName);
}

void CInput::ChangeAnimation(const string & strName)
{
	m_pMouseAnim->ChangeAnimation(strName);
}

void CInput::SetReturnSequenceName(const string & strName, const string & strReturnName)
{
	m_pMouseAnim->SetReturnSequenceName(strName, strReturnName);
}

void CInput::SetMouseTexture(const string & strName, const TCHAR* pFileName,
	const string& strPathName)
{
	if(pFileName)
		GET_SINGLE(CResourceManager)->LoadTexture(strName, pFileName, strPathName);

	SAFE_RELEASE(m_pMouseTexture);
	m_pMouseTexture = GET_SINGLE(CResourceManager)->FindTexture(strName);

	if (m_bShowCursor)
		ShowCursor(false);

	m_bShowCursor = false;
}

void CInput::MouseSize(const Vector2 & vSize)
{
	m_pMouseTr->SetRelativeScale(vSize.x, vSize.y, 1.f);
}

void CInput::AlphaBlendEnable()
{
	if(m_pAlphaBlend)
		return;

	m_pAlphaBlend	= GET_SINGLE(CResourceManager)->FindRenderState(RENDERSTATE_ALPHABLEND);
}

bool CInput::InitDX()
{
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, nullptr)))
		return false;

	if (FAILED(m_pKeyboard->SetDataFormat(&c_dfDIKeyboard)))
		return false;

	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr)))
		return false;

	if (FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
		return false;

	return true;
}

bool CInput::InitWindow()
{
	return true;
}

bool CInput::Init()
{
	m_eInputType = IT_DX;

	HRESULT	hr = DirectInput8Create(WINDOWINSTANCE, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&m_pInput, nullptr);

	if (FAILED(hr))
	{
		m_eInputType = IT_WINDOW;
	}

	switch (m_eInputType)
	{
	case IT_DX:
		if (!InitDX())
			return false;
		break;
	case IT_WINDOW:
		if (!InitWindow())
			return false;
		break;
	}

	m_pMouseTr	= new CTransform;

	m_pMouseTr->SetPivot(0.f, 1.f, 0.f);

	m_pMouseMesh	= GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMouseShader	= GET_SINGLE(CShaderManager)->FindShader(UI_SHADER);

	m_pMouseTr->SetMeshSize(m_pMouseMesh->GetMax() - m_pMouseMesh->GetMin());

	return true;
}

void CInput::Update(float fTime)
{
	if (m_eInputType == IT_DX)
	{
		ReadKeyboard();
		ReadMouse();
	}

	// 마우스 위치를 구해둔다.
	UpdateMouse(fTime);

	UpdateKeyInfo(fTime);
	UpdateAxis(fTime);
	UpdateAction(fTime);
}

void CInput::Render(float fTime)
{
	if (!m_pMouseTexture && !m_pMouseAnim)
		return;

	m_pMouseTr->SetScene(GET_SINGLE(CSceneManager)->GetScene());
	m_pMouseTr->SetTransform();

	m_pMouseTexture->SetTexture(0, CST_PIXEL);

	MaterialCBuffer	tCBuffer = {};
	tCBuffer.vDif = Vector4::White;

	GET_SINGLE(CShaderManager)->UpdateCBuffer(MATERIAL_CBUFFER, &tCBuffer);

	m_pMouseAnim->SetShader();

	if(m_pAlphaBlend)
		m_pAlphaBlend->SetState();

	size_t	iContainer = m_pMouseMesh->GetContainerCount();

	m_pMouseShader->SetShader();

	for (size_t i = 0; i < iContainer; ++i)
	{
		size_t	iSubset = m_pMouseMesh->GetSubsetCount(i);

		for (size_t j = 0; j < iSubset; ++j)
		{
			m_pMouseMesh->Render(i, j);
		}
	}

	if(m_pAlphaBlend)
		m_pAlphaBlend->ResetState();
}

void CInput::UpdateMouse(float fTime)
{
	POINT	ptMouse;

	GetCursorPos(&ptMouse);
	ScreenToClient(WINDOWHANDLE, &ptMouse);

	Vector2	vMousePos = Vector2(ptMouse.x, ptMouse.y);

	m_vMouseMove = vMousePos - m_vMousePos;

	m_vMousePos	= vMousePos * GET_SINGLE(CDevice)->GetDeviceToWindowRatio();
	m_vMousePos.y = _RESOLUTION.iHeight - m_vMousePos.y;

	Vector3 vCameraPos = GET_SINGLE(CSceneManager)->GetScene()->GetCameraManager()->GetMainCamera()->GetWorldPos();

	m_vMouseWorldPos = m_vMousePos + Vector2(vCameraPos.x, vCameraPos.y);

	m_pMouseTr->SetRelativePos(m_vMousePos.x, m_vMousePos.y, 0.f);

	if(m_pMouseAnim)
	{
		m_pMouseAnim->Update(fTime);

		SAFE_RELEASE(m_pMouseTexture);
		m_pMouseTexture	= m_pMouseAnim->GetAnimTexture();

		Animation2DFrameInfo	tInfo = m_pMouseAnim->GetAnimFrame();

		Vector3	vScale;
		vScale.x = tInfo.vEnd.x - tInfo.vStart.x;
		vScale.y = tInfo.vEnd.y - tInfo.vStart.y;
		vScale.z = 1.f;

		m_pMouseTr->SetRelativeScale(vScale);
	}

	m_pMouseTr->PostUpdate(fTime);
}

void CInput::UpdateKeyInfo(float fTime)
{
	switch (m_eInputType)
	{
	case IT_DX:
		UpdateKeyInfoDX(fTime);
		break;
	case IT_WINDOW:
		UpdateKeyInfoWindow(fTime);
		break;
	}

	// 마우스 처리
	int	iKey[MT_END]	= {VK_LBUTTON, VK_RBUTTON};
	for(int i = 0; i < MT_END; ++i)
	{
		if (GetAsyncKeyState(iKey[i]) & 0x8000)
		{
			// 처음 눌렀을 경우
			if (!m_tMouseInfo[i].bOnEvent[KS_PRESS] && !m_tMouseInfo[i].bOnEvent[KS_PUSH])
			{
				m_tMouseInfo[i].bOnEvent[KS_PRESS] = true;
				m_tMouseInfo[i].bOnEvent[KS_PUSH] = true;
			}

			// 이전프레임에 눌렀을 경우
			else if (m_tMouseInfo[i].bOnEvent[KS_PRESS])
				m_tMouseInfo[i].bOnEvent[KS_PRESS] = false;
		}

		// 이전프레임에 키를 누르다 지금 키를 안누를 경우
		else if (m_tMouseInfo[i].bOnEvent[KS_PRESS] || m_tMouseInfo[i].bOnEvent[KS_PUSH])
		{
			m_tMouseInfo[i].bOnEvent[KS_PRESS] = false;
			m_tMouseInfo[i].bOnEvent[KS_PUSH] = false;
			m_tMouseInfo[i].bOnEvent[KS_RELEASE] = true;
		}

		else if (m_tMouseInfo[i].bOnEvent[KS_RELEASE])
		{
			m_tMouseInfo[i].bOnEvent[KS_RELEASE] = false;
		}
	}
}

void CInput::UpdateKeyInfoDX(float fTime)
{
	auto	iter = m_UseKeyList.begin();
	auto	iterEnd = m_UseKeyList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (m_KeyState[*iter] & 0x80)
		{
			// 처음 눌렀을 경우
			if (!m_tKeyInfo[*iter].bOnEvent[KS_PRESS] && !m_tKeyInfo[*iter].bOnEvent[KS_PUSH])
			{
				m_tKeyInfo[*iter].bOnEvent[KS_PRESS] = true;
				m_tKeyInfo[*iter].bOnEvent[KS_PUSH] = true;
			}

			// 이전프레임에 눌렀을 경우
			else if (m_tKeyInfo[*iter].bOnEvent[KS_PRESS])
				m_tKeyInfo[*iter].bOnEvent[KS_PRESS] = false;
		}

		// 이전프레임에 키를 누르다 지금 키를 안누를 경우
		else if (m_tKeyInfo[*iter].bOnEvent[KS_PRESS] || m_tKeyInfo[*iter].bOnEvent[KS_PUSH])
		{
			m_tKeyInfo[*iter].bOnEvent[KS_PRESS] = false;
			m_tKeyInfo[*iter].bOnEvent[KS_PUSH] = false;
			m_tKeyInfo[*iter].bOnEvent[KS_RELEASE] = true;
		}

		else if (m_tKeyInfo[*iter].bOnEvent[KS_RELEASE])
		{
			m_tKeyInfo[*iter].bOnEvent[KS_RELEASE] = false;
		}
	}

	// Ctrl, Alt, Shift 키 체크
	unsigned char	cSKey[KU_END] = { DIK_LCONTROL, DIK_LALT, DIK_LSHIFT };

	for (int i = 0; i < KU_END; ++i)
	{
		if (m_KeyState[cSKey[i]] & 0x80)
		{
			// 처음 눌렀을 경우
			if (!m_tKeyInfo[cSKey[i]].bOnEvent[KS_PRESS] && !m_tKeyInfo[cSKey[i]].bOnEvent[KS_PUSH])
			{
				m_tKeyInfo[cSKey[i]].bOnEvent[KS_PRESS] = true;
				m_tKeyInfo[cSKey[i]].bOnEvent[KS_PUSH] = true;
			}

			// 이전프레임에 눌렀을 경우
			else if (m_tKeyInfo[cSKey[i]].bOnEvent[KS_PRESS])
				m_tKeyInfo[cSKey[i]].bOnEvent[KS_PRESS] = false;
		}

		// 이전프레임에 키를 누르다 지금 키를 안누를 경우
		else if (m_tKeyInfo[cSKey[i]].bOnEvent[KS_PRESS] || m_tKeyInfo[cSKey[i]].bOnEvent[KS_PUSH])
		{
			m_tKeyInfo[cSKey[i]].bOnEvent[KS_PRESS] = false;
			m_tKeyInfo[cSKey[i]].bOnEvent[KS_PUSH] = false;
			m_tKeyInfo[cSKey[i]].bOnEvent[KS_RELEASE] = true;
		}

		else if (m_tKeyInfo[cSKey[i]].bOnEvent[KS_RELEASE])
		{
			m_tKeyInfo[cSKey[i]].bOnEvent[KS_RELEASE] = false;
		}
	}
}

void CInput::UpdateKeyInfoWindow(float fTime)
{
	auto	iter = m_UseKeyList.begin();
	auto	iterEnd = m_UseKeyList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (GetAsyncKeyState(*iter) & 0x8000)
		{
			// 처음 눌렀을 경우
			if (!m_tKeyInfo[*iter].bOnEvent[KS_PRESS] && !m_tKeyInfo[*iter].bOnEvent[KS_PUSH])
			{
				m_tKeyInfo[*iter].bOnEvent[KS_PRESS] = true;
				m_tKeyInfo[*iter].bOnEvent[KS_PUSH] = true;
			}

			// 이전프레임에 눌렀을 경우
			else if (m_tKeyInfo[*iter].bOnEvent[KS_PRESS])
				m_tKeyInfo[*iter].bOnEvent[KS_PRESS] = false;
		}

		// 이전프레임에 키를 누르다 지금 키를 안누를 경우
		else if (m_tKeyInfo[*iter].bOnEvent[KS_PRESS] || m_tKeyInfo[*iter].bOnEvent[KS_PUSH])
		{
			m_tKeyInfo[*iter].bOnEvent[KS_PRESS] = false;
			m_tKeyInfo[*iter].bOnEvent[KS_PUSH] = false;
			m_tKeyInfo[*iter].bOnEvent[KS_RELEASE] = true;
		}

		else if (m_tKeyInfo[*iter].bOnEvent[KS_RELEASE])
		{
			m_tKeyInfo[*iter].bOnEvent[KS_RELEASE] = false;
		}
	}

	// Ctrl, Alt, Shift 키 체크
	unsigned char	cSKey[KU_END] = { VK_CONTROL, VK_MENU, VK_SHIFT };

	for (int i = 0; i < KU_END; ++i)
	{
		//if (m_KeyState[cSKey[i]] & 0x80)
		if (GetAsyncKeyState(cSKey[i]) & 0x8000)
		{
			// 처음 눌렀을 경우
			if (!m_tKeyInfo[cSKey[i]].bOnEvent[KS_PRESS] && !m_tKeyInfo[cSKey[i]].bOnEvent[KS_PUSH])
			{
				m_tKeyInfo[cSKey[i]].bOnEvent[KS_PRESS] = true;
				m_tKeyInfo[cSKey[i]].bOnEvent[KS_PUSH] = true;
			}

			// 이전프레임에 눌렀을 경우
			else if (m_tKeyInfo[cSKey[i]].bOnEvent[KS_PRESS])
				m_tKeyInfo[cSKey[i]].bOnEvent[KS_PRESS] = false;
		}

		// 이전프레임에 키를 누르다 지금 키를 안누를 경우
		else if (m_tKeyInfo[cSKey[i]].bOnEvent[KS_PRESS] || m_tKeyInfo[cSKey[i]].bOnEvent[KS_PUSH])
		{
			m_tKeyInfo[cSKey[i]].bOnEvent[KS_PRESS] = false;
			m_tKeyInfo[cSKey[i]].bOnEvent[KS_PUSH] = false;
			m_tKeyInfo[cSKey[i]].bOnEvent[KS_RELEASE] = true;
		}

		else if (m_tKeyInfo[cSKey[i]].bOnEvent[KS_RELEASE])
		{
			m_tKeyInfo[cSKey[i]].bOnEvent[KS_RELEASE] = false;
		}
	}
}

void CInput::UpdateAxis(float fTime)
{
	auto	iter = m_mapAxis.begin();
	auto	iterEnd = m_mapAxis.end();

	for (; iter != iterEnd; ++iter)
	{
		PKeyAxis	pAxis = iter->second;

		auto	iterKey = pAxis->KeyList.begin();
		auto	iterKeyEnd = pAxis->KeyList.end();

		float	fScale = 0.f;

		for (; iterKey != iterKeyEnd; ++iterKey)
		{
			if (m_tKeyInfo[(*iterKey).cKey].bOnEvent[KS_PUSH])
				fScale += (*iterKey).fScale;
		}

		pAxis->func(fScale, fTime);
	}
}

void CInput::UpdateAction(float fTime)
{
	auto	iter = m_mapAction.begin();
	auto	iterEnd = m_mapAction.end();

	// Ctrl, Alt, Shift 키 체크
	unsigned char	cSKey[KU_END] = { DIK_LCONTROL, DIK_LALT, DIK_LSHIFT };

	if (m_eInputType == IT_WINDOW)
	{
		cSKey[KU_CTRL] = VK_CONTROL;
		cSKey[KU_ALT] = VK_MENU;
		cSKey[KU_SHIFT] = VK_SHIFT;
	}

	for (; iter != iterEnd; ++iter)
	{
		PKeyAction	pAction = iter->second;

		auto	iterKey = pAction->KeyList.begin();
		auto	iterKeyEnd = pAction->KeyList.end();

		for (; iterKey != iterKeyEnd; ++iterKey)
		{
			bool	bSKeyEnable = true;

			for (int i = 0; i < KU_END; ++i)
			{
				if ((*iterKey).bSKey[i])
				{
					if (!m_tKeyInfo[cSKey[i]].bOnEvent[KS_PUSH])
					{
						bSKeyEnable = false;
						break;
					}
				}

				else
				{
					if (m_tKeyInfo[cSKey[i]].bOnEvent[KS_PUSH])
					{
						bSKeyEnable = false;
						break;
					}
				}
			}

			if (pAction->func[AKS_PRESS] != nullptr)
			{
				if (m_tKeyInfo[(*iterKey).cKey].bOnEvent[KS_PRESS] && bSKeyEnable)
					pAction->func[AKS_PRESS](fTime);
			}

			if (pAction->func[AKS_PUSH] != nullptr)
			{
				if (m_tKeyInfo[(*iterKey).cKey].bOnEvent[KS_PUSH] && bSKeyEnable)
					pAction->func[AKS_PUSH](fTime);
			}

			if (pAction->func[AKS_RELEASE] != nullptr)
			{
				if (m_tKeyInfo[(*iterKey).cKey].bOnEvent[KS_RELEASE] && bSKeyEnable)
					pAction->func[AKS_RELEASE](fTime);
			}

			if (pAction->func[AKS_DOUBLE] != nullptr)
			{
				bool	bDoubleClick = false;

				if (m_tKeyInfo[(*iterKey).cKey].bOnEvent[KS_PRESS] &&
					(*iterKey).fKeyTime == 0.f)
					(*iterKey).fKeyTime += fTime;

				else if ((*iterKey).fKeyTime > 0.f)
				{
					(*iterKey).fKeyTime += fTime;

					if ((*iterKey).fKeyTime >= m_fDoubleKeyTime)
					{
						bDoubleClick = false;
						(*iterKey).fKeyTime = 0.f;
					}

					else
					{
						if (m_tKeyInfo[(*iterKey).cKey].bOnEvent[KS_PRESS])
						{
							bDoubleClick = true;
							(*iterKey).fKeyTime = 0.f;
						}
					}
				}

				if (bDoubleClick && bSKeyEnable)
					pAction->func[AKS_DOUBLE](fTime);
			}
		}
	}
}

void CInput::ReadKeyboard()
{
	HRESULT result = m_pKeyboard->GetDeviceState(256, m_KeyState);

	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
			m_pKeyboard->Acquire();
	}
}

void CInput::ReadMouse()
{
	HRESULT result = m_pMouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);

	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
			m_pMouse->Acquire();
	}
}

void CInput::AddAxisKey(const string & strName, unsigned char cKey, float fScale)
{
	if (m_eInputType == IT_WINDOW)
		cKey = ConvertKey(cKey);

	PKeyAxis	pAxis = FindAxis(strName);

	if (!pAxis)
	{
		pAxis = new KeyAxis;
		pAxis->strName = strName;

		hash<string>	hs;

		size_t	iKey = hs(strName);

		m_mapAxis.insert(make_pair(iKey, pAxis));
	}

	KeyAxisInfo	tInfo = {};

	tInfo.cKey = cKey;
	tInfo.fScale = fScale;

	pAxis->KeyList.push_back(tInfo);

	auto	iter = m_UseKeyList.begin();
	auto	iterEnd = m_UseKeyList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == cKey)
			return;
	}

	m_UseKeyList.push_back(cKey);
}

void CInput::BindAxis(const string & strName, void(*pFunc)(float, float))
{
	PKeyAxis	pAxis = FindAxis(strName);

	if (!pAxis)
	{
		pAxis = new KeyAxis;
		pAxis->strName = strName;

		hash<string>	hs;

		size_t	iKey = hs(strName);

		m_mapAxis.insert(make_pair(iKey, pAxis));
	}

	pAxis->func = pFunc;
}

void CInput::AddActionKey(const string & strName, unsigned char cKey)
{
	if (m_eInputType == IT_WINDOW)
		cKey = ConvertKey(cKey);

	PKeyAction pAction = FindAction(strName);

	if (!pAction)
	{
		pAction = new KeyAction;
		pAction->strName = strName;

		hash<string>	hs;

		size_t	iKey = hs(strName);

		m_mapAction.insert(make_pair(iKey, pAction));
	}

	KeyActionInfo	tInfo = {};

	tInfo.cKey = cKey;

	pAction->KeyList.push_back(tInfo);

	auto	iter = m_UseKeyList.begin();
	auto	iterEnd = m_UseKeyList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == cKey)
			return;
	}

	m_UseKeyList.push_back(cKey);
}

void CInput::AddActionKeyUnion(const string & strName, unsigned char cKey, KEY_UNION eType,
	bool bCheck)
{
	if (m_eInputType == IT_WINDOW)
		cKey = ConvertKey(cKey);

	PKeyAction	pAction = FindAction(strName);

	if (!pAction)
	{
		pAction = new KeyAction;
		pAction->strName = strName;

		hash<string>	hs;

		size_t	iKey = hs(strName);

		m_mapAction.insert(make_pair(iKey, pAction));
	}

	auto	iter = pAction->KeyList.begin();
	auto	iterEnd = pAction->KeyList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter).cKey == cKey)
		{
			(*iter).bSKey[eType] = bCheck;
			return;
		}
	}
}

void CInput::BindAction(const string & strName, ACTION_KEY_STATE eType, void(*pFunc)(float))
{
	PKeyAction	pAction = FindAction(strName);

	if (!pAction)
	{
		pAction = new KeyAction;
		pAction->strName = strName;

		hash<string>	hs;

		size_t	iKey = hs(strName);

		m_mapAction.insert(make_pair(iKey, pAction));
	}

	pAction->func[eType] = pFunc;
}

PKeyAxis CInput::FindAxis(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapAxis.find(iKey);

	if (iter == m_mapAxis.end())
		return nullptr;

	return iter->second;
}

PKeyAction CInput::FindAction(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapAction.find(iKey);

	if (iter == m_mapAction.end())
		return nullptr;

	return iter->second;
}

unsigned char CInput::ConvertKey(unsigned char cKey)
{
	switch (cKey)
	{
	case DIK_ESCAPE:
		return VK_ESCAPE;
	case DIK_1:
		return '1';
	case DIK_2:
		return '2';
	case DIK_3:
		return '3';
	case DIK_4:
		return '4';
	case DIK_5:
		return '5';
	case DIK_6:
		return '6';
	case DIK_7:
		return '7';
	case DIK_8:
		return '8';
	case DIK_9:
		return '9';
	case DIK_0:
		return '0';
	case DIK_MINUS:
		return VK_OEM_MINUS;
	case DIK_EQUALS:
		return '=';
	case DIK_BACK:
		return VK_BACK;
	case DIK_TAB:
		return VK_TAB;
	case DIK_Q:
		return 'Q';
	case DIK_W:
		return 'W';
	case DIK_E:
		return 'E';
	case DIK_R:
		return 'R';
	case DIK_T:
		return 'T';
	case DIK_Y:
		return 'Y';
	case DIK_U:
		return 'U';
	case DIK_I:
		return 'I';
	case DIK_O:
		return 'O';
	case DIK_P:
		return 'P';
	case DIK_LBRACKET:
		return '[';
	case DIK_RBRACKET:
		return ']';
	case DIK_RETURN:
		return VK_RETURN;
	case DIK_LCONTROL:
		return VK_CONTROL;
	case DIK_A:
		return 'A';
	case DIK_S:
		return 'S';
	case DIK_D:
		return 'D';
	case DIK_F:
		return 'F';
	case DIK_G:
		return 'G';
	case DIK_H:
		return 'H';
	case DIK_J:
		return 'J';
	case DIK_K:
		return 'K';
	case DIK_L:
		return 'L';
	case DIK_SEMICOLON:
		return ';';
	case DIK_APOSTROPHE:
		return '\'';
	case DIK_GRAVE:
		return '`';
	case DIK_LSHIFT:
		return VK_SHIFT;
	case DIK_BACKSLASH:
		return '\\';
	case DIK_Z:
		return 'Z';
	case DIK_X:
		return 'X';
	case DIK_C:
		return 'C';
	case DIK_V:
		return 'V';
	case DIK_B:
		return 'B';
	case DIK_N:
		return 'N';
	case DIK_M:
		return 'M';
	case DIK_COMMA:
		return ',';
	case DIK_PERIOD:
		return '.';
	case DIK_SLASH:
		return '/';
	case DIK_RSHIFT:
		return VK_RSHIFT;
	case DIK_MULTIPLY:
		return VK_MULTIPLY;
	case DIK_LMENU:
		return VK_LMENU;
	case DIK_SPACE:
		return VK_SPACE;
	case DIK_CAPITAL:
		return VK_CAPITAL;
	case DIK_F1:
		return VK_F1;
	case DIK_F2:
		return VK_F2;
	case DIK_F3:
		return VK_F3;
	case DIK_F4:
		return VK_F4;
	case DIK_F5:
		return VK_F5;
	case DIK_F6:
		return VK_F6;
	case DIK_F7:
		return VK_F7;
	case DIK_F8:
		return VK_F8;
	case DIK_F9:
		return VK_F9;
	case DIK_F10:
		return VK_F10;
	case DIK_NUMLOCK:
		break;
	case DIK_SCROLL:
		break;
	case DIK_NUMPAD7:
		break;
	case DIK_NUMPAD8:
		break;
	case DIK_NUMPAD9:
		break;
	case DIK_SUBTRACT:
		break;
	case DIK_NUMPAD4:
		break;
	case DIK_NUMPAD5:
		break;
	case DIK_NUMPAD6:
		break;
	case DIK_ADD:
		break;
	case DIK_NUMPAD1:
		break;
	case DIK_NUMPAD2:
		break;
	case DIK_NUMPAD3:
		break;
	case DIK_NUMPAD0:
		break;
	case DIK_DECIMAL:
		break;
	case DIK_OEM_102:
		break;
	case DIK_F11:
		return VK_F11;
	case DIK_F12:
		return VK_F12;
	case DIK_F13:
		break;
	case DIK_F14:
		break;
	case DIK_F15:
		break;
	case DIK_NEXTTRACK:
		break;
	case DIK_NUMPADENTER:
		break;
	case DIK_RCONTROL:
		return VK_RCONTROL;
	case DIK_MUTE:
		break;
	case DIK_CALCULATOR:
		break;
	case DIK_PLAYPAUSE:
		break;
	case DIK_MEDIASTOP:
		break;
	case DIK_VOLUMEDOWN:
		break;
	case DIK_VOLUMEUP:
		break;
	case DIK_WEBHOME:
		break;
	case DIK_DIVIDE:
		break;
	case DIK_SYSRQ:
		break;
	case DIK_RMENU:
		return VK_RMENU;
	case DIK_PAUSE:
		break;
	case DIK_HOME:
		return VK_HOME;
	case DIK_UP:
		return VK_UP;
	case DIK_PRIOR:
		return VK_PRIOR;
	case DIK_LEFT:
		return VK_LEFT;
	case DIK_RIGHT:
		return VK_RIGHT;
	case DIK_END:
		return VK_END;
	case DIK_DOWN:
		return VK_DOWN;
	case DIK_NEXT:
		return VK_NEXT;
	case DIK_INSERT:
		return VK_INSERT;
	case DIK_DELETE:
		return VK_DELETE;
	case DIK_LWIN:
		break;
	case DIK_RWIN:
		break;
	case DIK_APPS:
		break;
	case DIK_POWER:
		break;
	case DIK_SLEEP:
		break;
	case DIK_WAKE:
		break;
	case DIK_WEBSEARCH:
		break;
	case DIK_WEBFAVORITES:
		break;
	case DIK_WEBREFRESH:
		break;
	case DIK_WEBSTOP:
		break;
	case DIK_WEBFORWARD:
		break;
	case DIK_WEBBACK:
		break;
	case DIK_MYCOMPUTER:
		break;
	case DIK_MAIL:
		break;
	case DIK_MEDIASELECT:
		break;
	}

	return 0xff;
}
