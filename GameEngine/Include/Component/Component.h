#pragma once

#include "../Ref.h"

class ENGINE_DLL CComponent :
	public CRef
{
	friend class CGameObject;

protected:
	CComponent();
	CComponent(const CComponent& com);
	virtual ~CComponent() = 0;
	
protected:
	class CGameObject*			m_pOwner;
	bool	m_bTickUpdate;
	COMPONENT_TYPE	m_eComType;
	class CScene*		m_pScene;

public:
	COMPONENT_TYPE GetComponentType()	const;
	void SetOwner(class CGameObject* pOwner);
	CGameObject* GetOwner()	const;
	void SetScene(class CScene* pScene);
	class CScene* GetScene()	const;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Render(float fTime);
	virtual void RenderInstancing(float fTime, PInstancingBuffer pBuffer);
};

