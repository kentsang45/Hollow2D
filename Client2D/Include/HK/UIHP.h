#include "Object/GameObject.h"

enum HP_STATE
{
	HP_NORMAL,
	HP_BREAKING,
	HP_EMPTY,
	HP_END
};

class UIHP : public CGameObject
{
	GAMEOBJECT_DEFAULT();

public:
	UIHP();
	~UIHP();

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
	HP_STATE m_eState;
};

