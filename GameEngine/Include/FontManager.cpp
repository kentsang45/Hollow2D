#include "FontManager.h"
#include "Device.h"

DEFINITION_SINGLE(CFontManager)

CFontManager::CFontManager() :
	m_pWriteFactory(nullptr)
{
}

CFontManager::~CFontManager()
{
	SAFE_RELEASE_NORMAL_MAP(m_mapTextFormat);
	SAFE_RELEASE_NORMAL_MAP(m_mapBrush);
	SAFE_RELEASE(m_pWriteFactory);
}

bool CFontManager::Init()
{
	// DirectWrite 팩토리 생성 함수
	// HRESULT DWriteCreateFactory(DWRITE_FACTORY_TYPE factoryType, REFIID iid, IUnknown **factory);

	// 1. DWRITE_FACTORY_TYPE factoryType - 팩토리를 공유할지 격리할지를 정한다.  격리할 시 DWRITE_FACTORY_TYPE_ISOLATED 
	// 2. REFIID iid - DirectWrite 팩토리 인터페이스를 식별하는 GUID 값
	// 3. 생성 된 DirectWrite 팩토리를 반환 받을 포인터
	if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pWriteFactory), (IUnknown**)&m_pWriteFactory)))
		return false;

	CreateTextFormat("NormalText", TEXT("궁서체"), DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_ULTRA_EXPANDED, 20.f, TEXT("ko"));
	CreateTextFormat("NormalText1", TEXT("Noto Sans CJK KR Black"), DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_ULTRA_EXPANDED, 20.f, TEXT("ko"));

	return true;
}

bool CFontManager::CreateTextFormat(const string& strName, const TCHAR * pFontName, int iWeight, int iStyle, int iStretch, float fSize,
	const TCHAR * pLocalName)
{
	IDWriteTextFormat*	pFormat = FindFont(strName);

	if (pFormat)
		return false;

	/*
	텍스트 레이아웃에 사용되는 텍스트 생성방식

	HRESULT CreateTextFormat(1, 2, 3, 4, 5, 6, 7, 8)
	1. WCHAR const* fontFamilyName	-	폰트의 이름.
	2. IDWriteFontCollection* fontCollection	- 안 쓰면 nullptr, ex) Arial 폰트는 Arial Baclk 같은 컬렉션을 가지고 있다.
	3. DWRITE_FONT_WEIGHT fontWeight	- 폰트의 굵기, DWRITE_FONT_WEIGHT 열거체의 값 중 적절한 크기로 가져다 쓰면 된다.
	4. DWRITE_FONT_STYLE fontStyle	-	폰트 스타일, DWRITE_FONT_STYLE 열거체 / 보통, 경사, 기울임 스타일들이 있다.
	5. DWRITE_FONT_STRETCH fontStretch	-	원래 글자크기에서 늘어짐의 정도
	6. FLOAT fontSize	-	글자 크기
	7. WCHAR const* localeName	- 언어의 지역 이름. 미국은 en-us 이고 한국은 ko-KR 일본은 ja-JP 이며 영국은 en-uk 이다.
	8. IDWriteTextFormat** textFormat	-	결과가 저장될 IDWriteTextFormat 포인터
	*/

	if (FAILED(m_pWriteFactory->CreateTextFormat(pFontName, nullptr, (DWRITE_FONT_WEIGHT)iWeight,
		(DWRITE_FONT_STYLE)iStyle, (DWRITE_FONT_STRETCH)iStretch, fSize, pLocalName, &pFormat)))
		return false;

	m_mapTextFormat.insert(make_pair(strName, pFormat));

	return true;
}

ID2D1SolidColorBrush * CFontManager::CreateColor(float r, float g, float b, float a)
{
	ID2D1SolidColorBrush*	pBrush = FindBrush(r, g, b, a);

	if (pBrush)
		return pBrush;

	// 지정된 색과 기본 불투명도가 1.f인 새 브러쉬를 만든다.
	// HRESULT ID2D1RenderTarget::CreateSolidColorBrush(1, 2)
	// 1. const D2D1_COLOR_F &color		- D2D1::ColorF 구조체, 단순 r,g,b,a 를 채워주는 구조체이다.
	// 2. ID2D1SolidColorBrush **solidColorBrush	-	반환 받을 브러쉬의 포인터
	if (FAILED(_RENDERTARGET2D->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &pBrush)))
		return nullptr;

	m_mapBrush.insert(make_pair(CreateColorKey(r, g, b, a), pBrush));

	return pBrush;
}

ID2D1SolidColorBrush * CFontManager::CreateColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	ID2D1SolidColorBrush*	pBrush = FindBrush(r, g, b, a);

	if (pBrush)
		return pBrush;

	// 지정된 색과 기본 불투명도가 1.f인 새 브러쉬를 만든다.
	// HRESULT ID2D1RenderTarget::CreateSolidColorBrush(1, 2)
	// 1. const D2D1_COLOR_F &color		- D2D1::ColorF 구조체, 단순 r,g,b,a 를 채워주는 구조체이다.
	// 2. ID2D1SolidColorBrush **solidColorBrush	-	반환 받을 브러쉬의 포인터
	if (FAILED(_RENDERTARGET2D->CreateSolidColorBrush(D2D1::ColorF(r / 255.f, g / 255.f, b / 255.f, a / 255.f), &pBrush)))
		return nullptr;

	m_mapBrush.insert(make_pair(CreateColorKey(r, g, b, a), pBrush));

	return pBrush;
}

ID2D1SolidColorBrush * CFontManager::CreateColor(const Vector4 & vColor)
{
	ID2D1SolidColorBrush*	pBrush = FindBrush(vColor);

	if (pBrush)
		return pBrush;

	// 지정된 색과 기본 불투명도가 1.f인 새 브러쉬를 만든다.
	// HRESULT ID2D1RenderTarget::CreateSolidColorBrush(1, 2)
	// 1. const D2D1_COLOR_F &color		- D2D1::ColorF 구조체, 단순 r,g,b,a 를 채워주는 구조체이다.
	// 2. ID2D1SolidColorBrush **solidColorBrush	-	반환 받을 브러쉬의 포인터
	if (FAILED(_RENDERTARGET2D->CreateSolidColorBrush(D2D1::ColorF(vColor.x, vColor.y, vColor.z, vColor.w), &pBrush)))
		return nullptr;

	m_mapBrush.insert(make_pair(CreateColorKey(vColor), pBrush));

	return pBrush;
}

ID2D1SolidColorBrush * CFontManager::CreateColor(UINT iColor)
{
	ID2D1SolidColorBrush*	pBrush = FindBrush(iColor);

	if (pBrush)
		return pBrush;

	// float타입으로  iColor를  분리한다.
	float	r, g, b, a;

	b = (iColor & 0x000000ff) / 255.f;
	g = ((iColor >> 8) & 0x000000ff) / 255.f;
	r = ((iColor >> 16) & 0x000000ff) / 255.f;
	a = ((iColor >> 24) & 0x000000ff) / 255.f;

	// 지정된 색과 기본 불투명도가 1.f인 새 브러쉬를 만든다.
	// HRESULT ID2D1RenderTarget::CreateSolidColorBrush(1, 2)
	// 1. const D2D1_COLOR_F &color		- D2D1::ColorF 구조체, 단순 r,g,b,a 를 채워주는 구조체이다.
	// 2. ID2D1SolidColorBrush **solidColorBrush	-	반환 받을 브러쉬의 포인터
	if (FAILED(_RENDERTARGET2D->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &pBrush)))
		return nullptr;

	m_mapBrush.insert(make_pair(iColor, pBrush));

	return pBrush;
}

ID2D1SolidColorBrush * CFontManager::FindBrush(float r, float g, float b, float a)
{
	UINT	iKey = CreateColorKey(r, g, b, a);

	auto	iter = m_mapBrush.find(iKey);

	if (iter == m_mapBrush.end())
		return nullptr;

	return iter->second;
}

ID2D1SolidColorBrush * CFontManager::FindBrush(BYTE r, BYTE g, BYTE b, BYTE a)
{
	UINT	iKey = CreateColorKey(r, g, b, a);

	auto	iter = m_mapBrush.find(iKey);

	if (iter == m_mapBrush.end())
		return nullptr;

	return iter->second;
}

ID2D1SolidColorBrush * CFontManager::FindBrush(const Vector4 & vColor)
{
	UINT	iKey = CreateColorKey(vColor);

	auto	iter = m_mapBrush.find(iKey);

	if (iter == m_mapBrush.end())
		return nullptr;

	return iter->second;
}

ID2D1SolidColorBrush * CFontManager::FindBrush(UINT iColor)
{
	auto	iter = m_mapBrush.find(iColor);

	if (iter == m_mapBrush.end())
		return nullptr;

	return iter->second;
}

UINT CFontManager::CreateColorKey(float r, float g, float b, float a)
{
	UINT	iColor = 0;		// 4Byte 변수를 만든다. 1Byte 당 A, R, G, B 값을 넣을거다.
	BYTE	R, G, B, A;		// 색상 표현을 위해 1Byte변수 4개를 만든다.

	R = (BYTE)(r * 255);	// R = { 0 < R < 1 } 의 값이다. % 비율로 구하기 위해 (색상 비율 * 255) 을 해준다.
	G = (BYTE)(g * 255);
	B = (BYTE)(b * 255);
	A = (BYTE)(a * 255);


	// 색상은 R,G,B,A 순이 아니라 A,R,G,B 순으로 들어갈 것이다.
	// 먼저 A(알파) 값의 비트를 넣어준다.
	// 여기서 중요한건 비트는 오른쪽에서부터 채워진다.
	// A = 0x3A   이경우 int로 형변환되서 0x0000003A 가 된다.
	// iColor = iColor | A; 로 해도 똑같음
	iColor = A;

	iColor = (iColor << 8) | R;	// 비트를 8칸(1Byte) 왼쪽으로 밀어 넣고, 그 값을 또 R값을 가진 비트와 OR 연산을 하여 오른쪽 8칸(1Byte)을 채워준다.
	iColor = (iColor << 8) | G; // 비트를 8칸(1Byte) 또 왼쪽으로 밀어 넣고, 그 값을 또 G값을 가진 비트와 OR 연산을 하여 오른쪽 8칸(1Byte)을 채워준다.
	iColor = (iColor << 8) | B;

	return iColor;
}

UINT CFontManager::CreateColorKey(BYTE r, BYTE g, BYTE b, BYTE a)
{
	UINT	iColor = 0;

	iColor = a;

	iColor = (iColor << 8) | r;
	iColor = (iColor << 8) | g;
	iColor = (iColor << 8) | b;

	return iColor;
}

UINT CFontManager::CreateColorKey(const Vector4 & vColor)
{
	UINT	iColor = 0;
	BYTE	r, g, b, a;

	r = (BYTE)(vColor.x * 255);
	g = (BYTE)(vColor.y * 255);
	b = (BYTE)(vColor.z * 255);
	a = (BYTE)(vColor.w * 255);

	iColor = a;

	iColor = (iColor << 8) | r;
	iColor = (iColor << 8) | g;
	iColor = (iColor << 8) | b;

	return iColor;
}

IDWriteTextLayout * CFontManager::CreateTextLayout(const TCHAR * pText, IDWriteTextFormat * pFormat, float fWidth, float fHeight)
{
	IDWriteTextLayout*	pLayout = nullptr;

	// 문자열, 텍스트 제작 형식(Layout)을 만든다.
	//HRESULT IDWriteFactory::CreateTextLayout(1, 2, 3, 4, 5, 6)

	// 1. WCHAR const *string	-	생성할 문자열
	// 2. UINT32 stringLength	-	문자열의 길이
	// 3. IDWriteTextFormat *textFormat	-	문자열에 적용 할 형식을 나타내는 객체에 대한 포인터
	// 4. FLOAT maxWidth		-	문자열을 담는 상자의 너비
	// 5. FLOAT maxHeight		-	문자열을 담는 상자의 높이
	// 6. IDWriteTextLayout **textLayout	-	반환 받을 레이아웃의 포인터

	if (FAILED(m_pWriteFactory->CreateTextLayout(pText, lstrlen(pText), pFormat, fWidth, fHeight, &pLayout)))
		return nullptr;

	return pLayout;
}

IDWriteTextLayout * CFontManager::CreateTextLayout(const TCHAR * pText, const string & strFormat, float fWidth, float fHeight)
{
	IDWriteTextFormat*	pFormat = FindFont(strFormat);

	if (!pFormat)
		return nullptr;

	IDWriteTextLayout*	pLayout = nullptr;

	// 문자열, 텍스트 제작 형식(Layout)을 만든다.
	//HRESULT IDWriteFactory::CreateTextLayout(1, 2, 3, 4, 5, 6)

	// 1. WCHAR const* string	-	생성할 문자열
	// 2. UINT32 stringLength	-	문자열의 길이
	// 3. IDWriteTextFormat* textFormat	-	문자열에 적용 할 형식을 나타내는 객체에 대한 포인터
	// 4. FLOAT maxWidth	-	문자열을 담는 상자의 너비
	// 5. FLOAT maxHeight	-	문자열을 담는 상자의 높이
	// 6. IDWriteTextLayout** textLayout	-	반환 받을 레이아웃의 포인터

	if (FAILED(m_pWriteFactory->CreateTextLayout(pText, lstrlen(pText), pFormat, fWidth, fHeight, &pLayout)))
		return nullptr;

	return pLayout;
}

IDWriteTextFormat * CFontManager::FindFont(const string & strName)
{
	unordered_map<string, IDWriteTextFormat*>::iterator	iter = m_mapTextFormat.find(strName);

	if (iter == m_mapTextFormat.end())
		return nullptr;

	return iter->second;
}
