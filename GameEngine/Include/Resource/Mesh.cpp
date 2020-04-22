#include "Mesh.h"
#include "../Device.h"
#include "Material.h"

CMesh::CMesh()	:
	m_pLayout(nullptr)
{
	m_pMaterial = new CMaterial;

	m_pMaterial->Init();

	m_vMin = Vector3(10000000.f, 10000000.f, 10000000.f);
	m_vMax = Vector3(-10000000.f, -10000000.f, -10000000.f);
}

CMesh::~CMesh()
{
	SAFE_RELEASE(m_pMaterial);

	for (size_t i = 0; i < m_vecMeshContainer.size(); ++i)
	{
		for (size_t j = 0; j < m_vecMeshContainer[i]->vecIB.size(); ++j)
		{
			SAFE_RELEASE(m_vecMeshContainer[i]->vecIB[j].pBuffer);
		}

		SAFE_RELEASE(m_vecMeshContainer[i]->tVB.pBuffer);
		SAFE_DELETE(m_vecMeshContainer[i]);
	}

	m_vecMeshContainer.clear();
}

void CMesh::SetMaterial(CMaterial * pMaterial)
{
	SAFE_RELEASE(m_pMaterial);
	m_pMaterial = pMaterial;

	if (m_pMaterial)
		m_pMaterial->AddRef();
}

CMaterial * CMesh::GetMaterial() const
{
	m_pMaterial->AddRef();
	return m_pMaterial;
}

size_t CMesh::GetContainerCount() const
{
	return m_vecMeshContainer.size();
}

size_t CMesh::GetSubsetCount(size_t iContainer) const
{
	return m_vecMeshContainer[iContainer]->vecIB.size();
}

Vector3 CMesh::GetMin() const
{
	return m_vMin;
}

Vector3 CMesh::GetMax() const
{
	return m_vMax;
}

bool CMesh::CreateMesh(ID3D11InputLayout* pLayout, const string & strName, const void * pVertices,
	int iVtxSize, int iVtxCount, D3D11_USAGE eVtxUsage,
	D3D11_PRIMITIVE_TOPOLOGY ePrimitive, const void * pIndices,
	int iIdxSize, int iIdxCount, D3D11_USAGE eIdxUsage, DXGI_FORMAT eFmt)
{
	m_pLayout = pLayout;

	SetName(strName);

	if (!AddVertexBuffer(pVertices, iVtxSize, iVtxCount, eVtxUsage,
		ePrimitive))
		return false;

	if (pIndices)
	{
		if (!AddIndexBuffer(pIndices, iIdxSize, iIdxCount, eIdxUsage,
			eFmt, m_vecMeshContainer[0]))
			return false;
	}

	return true;
}

void CMesh::Render()
{
	// 정점 구조 지정.
	CONTEXT->IASetInputLayout(m_pLayout);

	size_t iContainer = m_vecMeshContainer.size();

	for (size_t i = 0; i < iContainer; ++i)
	{
		PMeshContainer	pContainer = m_vecMeshContainer[i];

		// 그려낼 도형의 위상구조를 지정한다.
		CONTEXT->IASetPrimitiveTopology(pContainer->ePrimitive);

		// 그려낼 버텍스 버퍼를 지정한다.
		UINT	iStride = pContainer->tVB.iSize;
		UINT	iOffset = 0;
		CONTEXT->IASetVertexBuffers(0, 1, &pContainer->tVB.pBuffer,
			&iStride, &iOffset);

		// 서브셋 수만큼 반복하며 그려낸다.
		size_t	iSubset = pContainer->vecIB.size();

		if (iSubset > 0)
		{
			for (size_t j = 0; j < iSubset; ++j)
			{
				PIndexBuffer	pIdxBuffer = &pContainer->vecIB[j];

				CONTEXT->IASetIndexBuffer(pIdxBuffer->pBuffer,
					pIdxBuffer->eFmt, 0);
				CONTEXT->DrawIndexed(pIdxBuffer->iCount, 0, 0);
			}
		}

		else
		{
			CONTEXT->Draw(pContainer->tVB.iCount, 0);
		}
	}
}

void CMesh::Render(int iContainer, int iSubset)
{
	// 정점 구조 지정.
	CONTEXT->IASetInputLayout(m_pLayout);

	PMeshContainer	pContainer = m_vecMeshContainer[iContainer];

	// 그려낼 도형의 위상구조를 지정한다.
	CONTEXT->IASetPrimitiveTopology(pContainer->ePrimitive);

	// 그려낼 버텍스 버퍼를 지정한다.
	UINT	iStride = pContainer->tVB.iSize;
	UINT	iOffset = 0;
	CONTEXT->IASetVertexBuffers(0, 1, &pContainer->tVB.pBuffer,
		&iStride, &iOffset);

	// 서브셋 수만큼 반복하며 그려낸다.
	if (!pContainer->vecIB.empty())
	{
		if (iSubset < pContainer->vecIB.size())
		{
			PIndexBuffer	pIdxBuffer = &pContainer->vecIB[iSubset];

			CONTEXT->IASetIndexBuffer(pIdxBuffer->pBuffer,
				pIdxBuffer->eFmt, 0);
			CONTEXT->DrawIndexed(pIdxBuffer->iCount, 0, 0);
		}
	}

	else
	{
		CONTEXT->Draw(pContainer->tVB.iCount, 0);
	}
}

void CMesh::RenderInstancing(PInstancingBuffer pInstancing)
{
	size_t iContainer = m_vecMeshContainer.size();

	for (size_t i = 0; i < iContainer; ++i)
	{
		PMeshContainer	pContainer = m_vecMeshContainer[i];

		// 그려낼 도형의 위상구조를 지정한다.
		CONTEXT->IASetPrimitiveTopology(pContainer->ePrimitive);

		ID3D11Buffer*	pBuffer[2]	= { pContainer->tVB.pBuffer , pInstancing->pBuffer};
		UINT	iStride[2]	= { pContainer->tVB.iSize , pInstancing->iSize};
		UINT	iOffset[2]	= {};

		// 그려낼 버텍스 버퍼를 지정한다.
		CONTEXT->IASetVertexBuffers(0, 2, pBuffer, iStride, iOffset);

		// 서브셋 수만큼 반복하며 그려낸다.
		size_t	iSubset = pContainer->vecIB.size();

		if (iSubset > 0)
		{
			for (size_t j = 0; j < iSubset; ++j)
			{
				PIndexBuffer	pIdxBuffer = &pContainer->vecIB[j];

				CONTEXT->IASetIndexBuffer(pIdxBuffer->pBuffer,
					pIdxBuffer->eFmt, 0);
				CONTEXT->DrawIndexedInstanced(pIdxBuffer->iCount, pInstancing->iCount, 0, 0, 0);
			}
		}

		else
		{
			CONTEXT->DrawInstanced(pContainer->tVB.iCount, pInstancing->iCount, 0, 0);
		}
	}
}

void CMesh::RenderInstancing(int iContainer, int iSubset, PInstancingBuffer pInstancing)
{
	PMeshContainer	pContainer = m_vecMeshContainer[iContainer];

	// 그려낼 도형의 위상구조를 지정한다.
	CONTEXT->IASetPrimitiveTopology(pContainer->ePrimitive);

	ID3D11Buffer*	pBuffer[2] = { pContainer->tVB.pBuffer , pInstancing->pBuffer };
	UINT	iStride[2] = { pContainer->tVB.iSize , pInstancing->iSize };
	UINT	iOffset[2] = {};

	// 그려낼 버텍스 버퍼를 지정한다.
	CONTEXT->IASetVertexBuffers(0, 2, pBuffer, iStride, iOffset);

	// 서브셋 수만큼 반복하며 그려낸다.
	if (!pContainer->vecIB.empty())
	{
		if (iSubset < pContainer->vecIB.size())
		{
			PIndexBuffer	pIdxBuffer = &pContainer->vecIB[iSubset];

			CONTEXT->IASetIndexBuffer(pIdxBuffer->pBuffer,
				pIdxBuffer->eFmt, 0);
			CONTEXT->DrawIndexedInstanced(pIdxBuffer->iCount, pInstancing->iCount, 0, 0, 0);
		}
	}

	else
	{
		CONTEXT->DrawInstanced(pContainer->tVB.iCount, pInstancing->iCount, 0, 0);
	}
}

bool CMesh::AddVertexBuffer(const void * pVertices, int iVtxSize,
	int iVtxCount, D3D11_USAGE eVtxUsage, 
	D3D11_PRIMITIVE_TOPOLOGY ePrimitive)
{
	PMeshContainer	pContainer = new MeshContainer;

	m_vecMeshContainer.push_back(pContainer);

	pContainer->ePrimitive = ePrimitive;

	pContainer->tVB.iSize = iVtxSize;
	pContainer->tVB.iCount = iVtxCount;
	pContainer->tVB.eUsage = eVtxUsage;

	D3D11_BUFFER_DESC	tDesc = {};

	tDesc.ByteWidth = iVtxSize * iVtxCount;
	tDesc.Usage = eVtxUsage;

	if (eVtxUsage == D3D11_USAGE_DYNAMIC)
		tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	else if (eVtxUsage == D3D11_USAGE_STAGING)
		tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;

	tDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
	D3D11_SUBRESOURCE_DATA	tData = {};

	tData.pSysMem = pVertices;

	if (FAILED(DEVICE->CreateBuffer(&tDesc, &tData, &pContainer->tVB.pBuffer)))
		return false;

	// 정점정보를 조사하여 위치를 얻어오고 얻어온 위치를 비교하여 최소값과 최대값을 얻어온다.
	for (int i = 0; i < iVtxCount; ++i)
	{
		unsigned char*	pVtx = ((unsigned char*)pVertices) + (i * iVtxSize);

		Vector3	vPos;
		memcpy(&vPos, pVtx, sizeof(Vector3));

		if (vPos.x < m_vMin.x)
			m_vMin.x = vPos.x;

		else if (vPos.x > m_vMax.x)
			m_vMax.x = vPos.x;

		if (vPos.y < m_vMin.y)
			m_vMin.y = vPos.y;

		else if (vPos.y > m_vMax.y)
			m_vMax.y = vPos.y;

		if (vPos.z < m_vMin.z)
			m_vMin.z = vPos.z;

		else if (vPos.z > m_vMax.z)
			m_vMax.z = vPos.z;
	}

	return true;
}

bool CMesh::AddIndexBuffer(const void * pIndices, int iIdxSize, 
	int iIdxCount, D3D11_USAGE eIdxUsage, DXGI_FORMAT eFmt, 
	PMeshContainer pContainer)
{
	IndexBuffer	tIB = {};

	tIB.eFmt = eFmt;
	tIB.eUsage = eIdxUsage;
	tIB.iSize = iIdxSize;
	tIB.iCount = iIdxCount;

	D3D11_BUFFER_DESC	tDesc = {};

	tDesc.ByteWidth = iIdxSize * iIdxCount;
	tDesc.Usage = eIdxUsage;

	if (eIdxUsage == D3D11_USAGE_DYNAMIC)
		tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	else if (eIdxUsage == D3D11_USAGE_STAGING)
		tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;

	tDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA	tData = {};

	tData.pSysMem = pIndices;

	if (FAILED(DEVICE->CreateBuffer(&tDesc, &tData, &tIB.pBuffer)))
		return false;

	pContainer->vecIB.push_back(tIB);

	return true;
}
