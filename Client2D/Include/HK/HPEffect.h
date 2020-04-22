#include "Object/GameObject.h"



class HPEffect : public CGameObject
{
	GAMEOBJECT_DEFAULT();

public:
	HPEffect();
	~HPEffect();

private:
	class CUIImage* m_pUI;

	bool m_bOn;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	// void ClickCallback(float fTime);

	void SetDown();

	void BreakHP();
	void Normal();
	void Empty();

private:
	bool m_bEmpty;
	float m_fLifeTime = 0.f;
	float m_fLifeTotalTime;
	float m_fMoveSpeed;

	bool m_bSizeDecider = false;
	int m_iDir;

	bool m_bDirDecider = false;
};

