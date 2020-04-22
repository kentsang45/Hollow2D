#include "Object/GameObject.h"


class HKButton : public CGameObject
{
	GAMEOBJECT_DEFAULT();

public:
	HKButton();
	~HKButton();

private:
	class CUIButton* m_pButton;

	bool m_bOn;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void ClickCallback(float fTime);


};

