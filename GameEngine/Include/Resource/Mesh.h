#pragma once

#include "../Ref.h"

typedef struct _tagMeshContainer
{
	VertexBuffer	tVB;
	vector<IndexBuffer>	vecIB;
	D3D11_PRIMITIVE_TOPOLOGY	ePrimitive;
}MeshContainer, *PMeshContainer;

class ENGINE_DLL CMesh	:
	public CRef
{
	friend class CResourceManager;

protected:
	CMesh();
	virtual ~CMesh() = 0;

protected:
	vector<PMeshContainer>	m_vecMeshContainer;
	ID3D11InputLayout*		m_pLayout;
	class CMaterial*		m_pMaterial;
	Vector3					m_vMin;
	Vector3					m_vMax;

public:
	void SetMaterial(class CMaterial* pMaterial);
	class CMaterial* GetMaterial()	const;
	size_t GetContainerCount()	const;
	size_t GetSubsetCount(size_t iContainer)	const;
	Vector3 GetMin()	const;
	Vector3 GetMax()	const;

public:
	bool CreateMesh(ID3D11InputLayout* pLayout, const string& strName, const void* pVertices,
		int iVtxSize, int iVtxCount, D3D11_USAGE eVtxUsage,
		D3D11_PRIMITIVE_TOPOLOGY ePrimitive,
		const void* pIndices = nullptr, int iIdxSize = 0, int iIdxCount = 0,
		D3D11_USAGE eIdxUsage = D3D11_USAGE_DEFAULT, 
		DXGI_FORMAT eFmt = DXGI_FORMAT_R32_UINT);
	void Render();
	void Render(int iContainer, int iSubset);
	void RenderInstancing(PInstancingBuffer pInstancing);
	void RenderInstancing(int iContainer, int iSubset, PInstancingBuffer pInstancing);

private:
	bool AddVertexBuffer(const void* pVertices,
		int iVtxSize, int iVtxCount, D3D11_USAGE eVtxUsage,
		D3D11_PRIMITIVE_TOPOLOGY ePrimitive);
	bool AddIndexBuffer(const void* pIndices, int iIdxSize, int iIdxCount,
		D3D11_USAGE eIdxUsage, DXGI_FORMAT eFmt, PMeshContainer pContainer);
};

