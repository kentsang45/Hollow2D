#include "Device.h"

DEFINITION_SINGLE(CDevice)

CDevice::CDevice()	:
	m_pDevice(nullptr),
	m_pContext(nullptr),
	m_pSwapChain(nullptr),
	m_pTargetView(nullptr),
	m_pDepthView(nullptr),
	m_p2DTarget(nullptr),
	m_p2DFactory(nullptr)
{
	memset(m_fClearColor, 0, sizeof(float) * 4);

	// 배경 화면 핑크
	m_fClearColor[0] = 1.f;
	m_fClearColor[1] = 105.f / 255.f;
	m_fClearColor[2] = 180.f / 255.f;
}

CDevice::~CDevice()
{
	SAFE_RELEASE(m_p2DFactory);
	SAFE_RELEASE(m_p2DTarget);
	SAFE_RELEASE(m_pDepthView);
	SAFE_RELEASE(m_pTargetView);
	SAFE_RELEASE(m_pSwapChain);

	if (m_pContext)
		m_pContext->ClearState();

	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pDevice);
}

ID3D11Device * CDevice::GetDevice() const
{
	return m_pDevice;
}

ID3D11DeviceContext * CDevice::GetContext() const
{
	return m_pContext;
}

IDXGISwapChain * CDevice::GetSwapChain() const
{
	return m_pSwapChain;
}

Resolution CDevice::GetResolution() const
{
	return m_tRS;
}

Vector2 CDevice::GetDeviceToWindowRatio() const
{
	Vector2	vRatio;

	RECT	rc;

	GetClientRect(m_hWnd, &rc);

	float fWidth = (float)(rc.right - rc.left);
	float fHeight = (float)(rc.bottom - rc.top);

	vRatio.x = (float)m_tRS.iWidth / fWidth;
	vRatio.y = (float)m_tRS.iHeight / fHeight;

	return vRatio;
}



ID2D1RenderTarget * CDevice::Get2DRenderTarget() const
{
	return m_p2DTarget;
}


ID2D1Factory * CDevice::Get2DFactory() const
{
	return m_p2DFactory;
}

bool CDevice::Init(HWND hWnd, int iWidth, int iHeight, bool bWindowMode)
{
	m_hWnd	= hWnd;
	m_tRS.iWidth = iWidth;
	m_tRS.iHeight = iHeight;

	unsigned int	iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	iFlag |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	D3D_FEATURE_LEVEL	eFLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL	eFLevel1 = D3D_FEATURE_LEVEL_11_0;

	// 백버퍼를 만들기 위한 SwapChain 정보를 초기화한다.
	DXGI_SWAP_CHAIN_DESC	tSwapDesc = {};

	tSwapDesc.BufferDesc.Width = iWidth;
	tSwapDesc.BufferDesc.Height = iHeight;
	tSwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tSwapDesc.BufferDesc.RefreshRate.Numerator = 1;
	tSwapDesc.BufferDesc.RefreshRate.Denominator = 60;
	tSwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	tSwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tSwapDesc.BufferCount = 1;
	tSwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	tSwapDesc.OutputWindow = hWnd;
	tSwapDesc.SampleDesc.Count = 1;
	tSwapDesc.SampleDesc.Quality = 0;
	tSwapDesc.Windowed = bWindowMode;
	tSwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		0, iFlag, &eFLevel, 1, D3D11_SDK_VERSION, &tSwapDesc,
		&m_pSwapChain, &m_pDevice, &eFLevel1, &m_pContext)))
		return false;

	D3D11_FEATURE_DATA_THREADING	tThread = {};

	HRESULT result = m_pDevice->CheckFeatureSupport(D3D11_FEATURE_THREADING,
		&tThread, sizeof(tThread));

	//result = m_pDevice->CreateDeferredContext(0, )

	// Backbuffer 를 만들어준다.
	ID3D11Texture2D*	pBuffer = nullptr;

	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);

	// 렌더타겟뷰를 생성한다.
	m_pDevice->CreateRenderTargetView(pBuffer, 0, &m_pTargetView);

	SAFE_RELEASE(pBuffer);

	// Depth & Stencil Buffer를 만들어준다.
	D3D11_TEXTURE2D_DESC	tDepthDesc = {};

	tDepthDesc.Width = iWidth;
	tDepthDesc.Height = iHeight;
	tDepthDesc.ArraySize = 1;
	tDepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tDepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tDepthDesc.Usage = D3D11_USAGE_DEFAULT;
	tDepthDesc.SampleDesc.Count = 1;
	tDepthDesc.SampleDesc.Quality = 0;
	tDepthDesc.MipLevels = 1;

	m_pDevice->CreateTexture2D(&tDepthDesc, nullptr, &pBuffer);

	m_pDevice->CreateDepthStencilView(pBuffer, nullptr, &m_pDepthView);

	SAFE_RELEASE(pBuffer);

	// Device에 위에서 생성한 렌더타겟뷰와 뎁스스텐실뷰를 묶어준다.
	m_pContext->OMSetRenderTargets(1, &m_pTargetView, m_pDepthView);

	D3D11_VIEWPORT	tVP = {};

	tVP.Width = iWidth;
	tVP.Height = iHeight;
	tVP.MaxDepth = 1.f;

	m_pContext->RSSetViewports(1, &tVP);





	// 2D Factory를 만들어준다.
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_p2DFactory)))
		return false;
	IDXGISurface*	pBackSurface = nullptr;
	// 현재 BackBuffer의 Surface를 얻어온다.
	m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackSurface));
	// 2D용 렌더타겟을 만들어준다.
	// 단, 출력할 Surface는 위에서 얻어온 Backbuffer의 Surface로 지정하여 2D도 출력도 백버퍼에 출력될 수 있게
	// 만들어준다.
	D2D1_RENDER_TARGET_PROPERTIES	props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
	if (FAILED(m_p2DFactory->CreateDxgiSurfaceRenderTarget(pBackSurface, props, &m_p2DTarget)))
		return false;
	SAFE_RELEASE(pBackSurface);




	return true;
}

void CDevice::ClearTarget()
{
	m_pContext->ClearRenderTargetView(m_pTargetView, m_fClearColor);
	m_pContext->ClearDepthStencilView(m_pDepthView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void CDevice::Present()
{
	m_pSwapChain->Present(0, 0);
}
