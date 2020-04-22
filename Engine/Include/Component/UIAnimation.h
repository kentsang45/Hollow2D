#pragma once

#include "UI.h"


class ENGINE_DLL CUIAnimation : public CUI
{
	friend class CGameObject;

protected:
	CUIAnimation();
	CUIAnimation(const CUIAnimation& com);
	virtual ~CUIAnimation();

protected:
	Vector4			m_vColor;

	class CTexture*	m_pTexture;
	class CAnimation2D* m_pAnim;

public:
	void SetTexture(const string& strName, const TCHAR* pFileName = nullptr,
		const string& strPathName = TEXTURE_PATH);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);



	void CreateAnim2D();
	void AddAnim2DSequence(const std::string& strName);
	void ChangeAnimation(const std::string& strName);
	void SetReturnSequenceName(const std::string& strName, const std::string& strReturnName);

	virtual class CStaticMesh* GetMesh();

	bool IsAnimationOver() const;

};

