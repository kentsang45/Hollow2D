#include "Object/GameObject.h"



class CoinUI : public CGameObject
{
	GAMEOBJECT_DEFAULT();

public:
	CoinUI();
	~CoinUI();

private:
	class CUIAnimation* m_pUI;

	bool m_bOn;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	// void ClickCallback(float fTime);

	void BreakHP();
	void Normal();
	void Empty();

private:
	bool m_bEmpty;
};

