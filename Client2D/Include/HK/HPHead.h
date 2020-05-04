#include "Object/GameObject.h"



class HPHead : public CGameObject
{
	GAMEOBJECT_DEFAULT();

public:
	HPHead();
	~HPHead();

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

