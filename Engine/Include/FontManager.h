#pragma once

#include "GameEngine.h"

class ENGINE_DLL CFontManager
{
private:
	IDWriteFactory*		m_pWriteFactory;
	unordered_map<string, IDWriteTextFormat*>	m_mapTextFormat;
	unordered_map<UINT, ID2D1SolidColorBrush*>	m_mapBrush;

public:
	bool Init();
	bool CreateTextFormat(const string& strName, const TCHAR* pFontName, int iWeight, int iStyle, int iStretch, float fSize,
		const TCHAR* pLocalName);

public:
	ID2D1SolidColorBrush* CreateColor(float r, float g, float b, float a);
	ID2D1SolidColorBrush* CreateColor(BYTE r, BYTE g, BYTE b, BYTE a);
	ID2D1SolidColorBrush* CreateColor(const Vector4& vColor);
	ID2D1SolidColorBrush* CreateColor(UINT iColor);

public:
	ID2D1SolidColorBrush* FindBrush(float r, float g, float b, float a);
	ID2D1SolidColorBrush* FindBrush(BYTE r, BYTE g, BYTE b, BYTE a);
	ID2D1SolidColorBrush* FindBrush(const Vector4& vColor);
	ID2D1SolidColorBrush* FindBrush(UINT iColor);

public:
	UINT CreateColorKey(float r, float g, float b, float a);
	UINT CreateColorKey(BYTE r, BYTE g, BYTE b, BYTE a);
	UINT CreateColorKey(const Vector4& vColor);

public:
	IDWriteTextLayout* CreateTextLayout(const TCHAR* pText, IDWriteTextFormat* pFormat, float fWidth, float fHeight);
	IDWriteTextLayout* CreateTextLayout(const TCHAR* pText, const string& strFormat, float fWidth, float fHeight);

public:
	IDWriteTextFormat* FindFont(const string& strName);

	DECLARE_SINGLE(CFontManager)
};

