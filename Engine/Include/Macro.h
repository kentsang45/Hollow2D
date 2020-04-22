
#pragma once

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr; }

#ifdef ENGINE_EXPORT
#define	ENGINE_DLL	__declspec(dllexport)
#else
#define	ENGINE_DLL	__declspec(dllimport)
#endif // ENGINE_EXPORT

#define	DECLARE_SINGLE(Type)	\
private:\
	static Type*	m_pInst;\
public:\
	static Type* GetInst()\
	{\
		if(!m_pInst)\
			m_pInst = new Type;\
		return m_pInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_pInst);\
	}\
private:\
	Type();\
	~Type();

#define	DEFINITION_SINGLE(Type)	Type* Type::m_pInst = nullptr;
#define	GET_SINGLE(Type)	Type::GetInst()
#define	DESTROY_SINGLE(Type)	Type::DestroyInst()

#define	DEVICE		GET_SINGLE(CDevice)->GetDevice()
#define	CONTEXT		GET_SINGLE(CDevice)->GetContext()
#define	SWAPCHAIN	GET_SINGLE(CDevice)->GetSwapChain()
#define	_RESOLUTION	GET_SINGLE(CDevice)->GetResolution()
#define	_RENDERTARGET2D			GET_SINGLE(CDevice)->Get2DRenderTarget()
#define	_RENDERTARGET2DMAIN		GET_SINGLE(CRenderManager)->Get2DMainRenderTarget()
#define	_RENDERTARGET2DUI		GET_SINGLE(CRenderManager)->Get2DFinalRenderTarget()

#define	WINDOWINSTANCE	GET_SINGLE(CEngine)->GetWindowInstance()
#define	WINDOWHANDLE	GET_SINGLE(CEngine)->GetWindowHandle()





#define	SAFE_DELETE_NORMAL_VECLIST(p)	\
{\
auto	iter = p.begin();\
auto	iterEnd = p.end();\
for(; iter != iterEnd; ++iter)\
{\
	SAFE_DELETE((*iter));\
}\
p.clear();\
}

#define	SAFE_DELETE_VECLIST(p)	\
{\
auto	iter = p.begin();\
auto	iterEnd = p.end();\
for(; iter != iterEnd; ++iter)\
{\
	(*iter)->Kill();\
	SAFE_DELETE((*iter));\
}\
p.clear();\
}

#define	SAFE_DELETE_NORMAL_MAP(p)	\
{\
auto	iter = p.begin();\
auto	iterEnd = p.end();\
for(; iter != iterEnd; ++iter)\
{\
	SAFE_DELETE(iter->second);\
}\
p.clear();\
}

#define	SAFE_DELETE_MAP(p)	\
{\
auto	iter = p.begin();\
auto	iterEnd = p.end();\
for(; iter != iterEnd; ++iter)\
{\
	iter->second->Kill();\
	SAFE_DELETE(iter->second);\
}\
p.clear();\
}

#define	SAFE_RELEASE_NORMAL_VECLIST(p)	\
{\
auto	iter = p.begin();\
auto	iterEnd = p.end();\
for(; iter != iterEnd; ++iter)\
{\
	SAFE_RELEASE((*iter));\
}\
p.clear();\
}

#define	SAFE_RELEASE_VECLIST(p)	\
{\
auto	iter = p.begin();\
auto	iterEnd = p.end();\
for(; iter != iterEnd; ++iter)\
{\
	(*iter)->Kill();\
	SAFE_RELEASE((*iter));\
}\
p.clear();\
}

#define	SAFE_RELEASE_NORMAL_MAP(p)	\
{\
auto	iter = p.begin();\
auto	iterEnd = p.end();\
for(; iter != iterEnd; ++iter)\
{\
	SAFE_RELEASE(iter->second);\
}\
p.clear();\
}

#define	SAFE_RELEASE_MAP(p)	\
{\
auto	iter = p.begin();\
auto	iterEnd = p.end();\
for(; iter != iterEnd; ++iter)\
{\
	iter->second->Kill();\
	SAFE_RELEASE(iter->second);\
}\
p.clear();\
}

#define	GAMEOBJECT_DEFAULT()	\
private:\
	friend class CScene;
