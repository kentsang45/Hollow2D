#pragma once

#include "../GameEngine.h"

class ENGINE_DLL CResourceManager
{
private:
	unordered_map<size_t, class CMesh*>	m_mapMesh;
	unordered_map<size_t, class CTexture*>	m_mapTexture;
	unordered_map<size_t, class CMaterial*>	m_mapMaterial;
	unordered_map<size_t, ID3D11SamplerState*>	m_mapSampler;
	unordered_map<size_t, class CRenderState*>	m_mapRenderState;
	unordered_map<size_t, class CAnimation2DSequence*>	m_mapAnim2DSequence;
	list<string>			m_DefaultMeshList;
	list<string>			m_DefaultTextureList;
	list<string>			m_DefaultRenderStateList;
	list<string>			m_DefaultMaterialList;
	unordered_map<size_t, class CMaterial*>::iterator m_MaterialIter;

	// SOUND
	unordered_map<size_t, class CSound*>				m_mapSound;
	unordered_map<size_t, ChannelGroup*>				m_mapChannelGroup;
	ChannelGroup*										m_pMasterGroup;
	System*		m_pSystem;


public:
	// MFC¸¦ À§ÇÑ
	void ClearMaterialIterator();
	class CMaterial* GetCurrentMaterial();
	void NextMaterial();

public:
	bool Init();
	void ChangeScene();
	bool CreateMesh(const string& strInputLayoutName, const string& strName, const void* pVertices,
		int iVtxSize, int iVtxCount, D3D11_USAGE eVtxUsage,
		D3D11_PRIMITIVE_TOPOLOGY ePrimitive,
		const void* pIndices = nullptr, int iIdxSize = 0, int iIdxCount = 0,
		D3D11_USAGE eIdxUsage = D3D11_USAGE_DEFAULT,
		DXGI_FORMAT eFmt = DXGI_FORMAT_R32_UINT);
	class CMesh* FindMesh(const string& strName);

	bool LoadTexture(const string& strName, const TCHAR* pFileName,
		const string& strPathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const string& strName, const TCHAR* pFullPath);
	bool LoadTexture(const string& strName, const vector<const TCHAR*>& vecFileName,
		const string& strPathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const string& strName, const vector<const TCHAR*>& vecFullPath);

	class CTexture* FindTexture(const string& strName);

	bool CreateMaterial(const string& strName);

	class CMaterial* FindMaterial(const string& strName);
	
	bool CreateSampler(const string& strName, D3D11_FILTER eFilter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_MODE eAddrU = D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_MODE eAddrV = D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_MODE eAddrW = D3D11_TEXTURE_ADDRESS_WRAP,
		UINT iMaxAnisotropy = 0);

	ID3D11SamplerState* FindSampler(const string& strName);

	bool CreateBlendState(const string& strName, BOOL bAlphaCoverage = FALSE,
		BOOL bIndependent = FALSE);
	bool AddBlendDesc(const string& strName, BOOL bBlendEnable = TRUE, D3D11_BLEND eSrc = D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND eDest = D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP eOp = D3D11_BLEND_OP_ADD,
		D3D11_BLEND eSrcAlpha = D3D11_BLEND_ONE, D3D11_BLEND eDestAlpha = D3D11_BLEND_ZERO, D3D11_BLEND_OP eOpAlpha = D3D11_BLEND_OP_ADD,
		UINT8 iWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL);

	bool CreateDepthStencil(const string& strName, BOOL bDepthEnable = TRUE, D3D11_DEPTH_WRITE_MASK eDepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,
		D3D11_COMPARISON_FUNC eDepthFunc = D3D11_COMPARISON_LESS, BOOL bStencilEnable = FALSE,
		UINT8 iStencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK, UINT8 iStencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK,
		D3D11_DEPTH_STENCILOP_DESC tFrontFace = { D3D11_STENCIL_OP_KEEP , D3D11_STENCIL_OP_KEEP , D3D11_STENCIL_OP_KEEP , D3D11_COMPARISON_ALWAYS },
		D3D11_DEPTH_STENCILOP_DESC tBackFace = { D3D11_STENCIL_OP_KEEP , D3D11_STENCIL_OP_KEEP , D3D11_STENCIL_OP_KEEP , D3D11_COMPARISON_ALWAYS });

	bool CreateRasterizerState(const string& strName, D3D11_FILL_MODE eFillMode = D3D11_FILL_SOLID,
		D3D11_CULL_MODE eCullMode = D3D11_CULL_BACK, BOOL bFrontCounterClockwise = FALSE,
		INT iDepthBias = 0, FLOAT fDepthBiasClamp = 0.f, FLOAT fSlopeScaledDepthBias = 0.f,
		BOOL bDepthClipEnable = TRUE, BOOL bScissorEnable = FALSE,
		BOOL bMultisampleEnable = FALSE, BOOL bAntialiasedLineEnable = FALSE);

	class CRenderState* FindRenderState(const string& strName);

	bool CreateAnimation2DSequence(const string& strName, bool bLoop, float fPlayTime, int iFrameCount);
	bool AddAnimation2DSequenceTexture(const string& strSequenceName,
		const string& strName, const TCHAR* pFileName, const string& strPathName = TEXTURE_PATH);
	bool AddAnimation2DSequenceFrameInfo(const string& strName, const Vector2& vStart, const Vector2& vEnd);
	bool SetAnimation2DSequenceFrameInfoAll(const string& strName, const Vector2& vStart, const Vector2& vEnd);

	class CAnimation2DSequence* FindAnimation2DSequence(const string& strName);



	///////////////////////////////////////////////////////////////////////////////////////// SOUND
	bool LoadSound(const string& strName, bool bLoop, const char* pFileName, const string& strPathName = SOUND_PATH);
	bool CreateSoundChannelGroup(const string& strName);
	class CSound* FindSound(const string& strName);
	ChannelGroup* FindSoundChannelGroup(const string& strName);
	void UpdateSound();
	void Play(class CSound* pSound, const string& strGroup);
	void Pause(class CSound* pSound, const string& strGroup);
	void Stop(const string& strGroup);
	void SetVolume(int iVolume, const string& strGroup);
	void Mute(const string& strGroup);
	void UnMute(const string& strGroup);
	void Mute();
	void UnMute();








	DECLARE_SINGLE(CResourceManager)
};

