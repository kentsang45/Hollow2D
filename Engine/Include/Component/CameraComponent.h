#pragma once
#include "SceneComponent.h"
class ENGINE_DLL CCameraComponent :
	public CSceneComponent
{
	friend class CGameObject;
	friend class CCameraManager;

protected:
	CCameraComponent();
	CCameraComponent(const CCameraComponent& com);
	~CCameraComponent();

protected:
	CAMERA_TYPE		m_eCameraType;
	Matrix			m_matView;
	Matrix			m_matProj;

public:
	CAMERA_TYPE GetCameraType()	const;
	void SetCameraType(CAMERA_TYPE eType);
	Matrix GetViewMatrix()	const;
	Matrix GetProjMatrix()	const;

private:
	void ComputeMatrix();

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

