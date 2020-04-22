#pragma once

#include "../GameEngine.h"

typedef struct _tagInstancingList
{
	RENDER_GROUP	eGroup;
	size_t	iSerialNumber;
	vector<class CSceneComponent*>	vecList;
	size_t				iAddCount;
	PInstancingBuffer	pBuffer;
}InstancingList, *PInstancingList;





class ENGINE_DLL CRenderManager
{
private:
	vector<class CSceneComponent*>	m_vecRender[RG_END];
	size_t		m_iAddCount[RG_END];
	RENDER_MODE	m_eRenderMode;
	class CDepthStencilState*	m_pNoneDepth;
	class CRasterizerState*		m_pCullNone;
	vector<InstancingList>		m_vecInstancing;
	vector<PStaticInstancingData>	m_vecStaticData;
	size_t		m_iInstancingAddCount;
	vector<InstancingList>		m_vecAnim2DInstancing;
	size_t		m_iAnim2DInstancingAddCount;
	vector<PAnim2DInstancingData>	m_vecAnim2DData;
	int			m_iTotalRenderCount;

	

	unordered_map<size_t, class CCustomRenderTarget*> m_mapRenderTarget;

	class CCustomRenderTarget* m_p2DMainTarget;
	class CCustomRenderTarget* m_p2DFinalTarget;

	ID2D1RenderTarget* m_p2DMainRenderTarget;
	ID2D1RenderTarget* m_p2DFinalRenderTarget;

public:
	void SetRenderMode(RENDER_MODE eMode);
	RENDER_MODE GetRenderMode()	const;

	ID2D1RenderTarget* Get2DMainRenderTarget() const;
	ID2D1RenderTarget* Get2DFinalRenderTarget() const;

public:
	bool Init();
	void AddRenderer(class CSceneComponent* pCom);
	void ComputeRender();
	void Render(float fTime);

	bool CreateRenderTarget(const string& strName, DXGI_FORMAT eTargetFmt,
		const Vector3& vPos, const Vector3& vScale,
		const Resolution& tRS, bool bOnDebug = true,
		const Vector4& vClearColor = Vector4(0.f, 0.f, 0.f, 0.f),
		DXGI_FORMAT eDepthFmt = DXGI_FORMAT_UNKNOWN);

	class CCustomRenderTarget* FindRenderTarget(const string& strName);


private:
	void RenderInstancing(float fTime, RENDER_GROUP eGroup);

private:
	static bool SortY(class CSceneComponent* pSrc, class CSceneComponent* pDest);
	static bool SortZ(class CSceneComponent* pSrc, class CSceneComponent* pDest);
	static bool UISortZOrder(class CSceneComponent * pSrc, class CSceneComponent * pDest);
	DECLARE_SINGLE(CRenderManager)
};

