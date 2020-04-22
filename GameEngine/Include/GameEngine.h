
#pragma once

#include "Types.h"



#define GRAVITY 9.8f


#define BOOM assert(false);




// Path Key
#define	ROOT_PATH		"RootPath"
#define	RESOURCE_PATH	"ResourcePath"
#define	SHADER_PATH		"ShaderPath"
#define	TEXTURE_PATH	"TexturePath"
#define	SOUND_PATH		"SoundPath"

// Shader Key
#define	STANDARD_COLOR_SHADER		"StandardColorShader"
#define	STANDARD_TEX_SHADER			"StandardTexShader"
#define	STANDARD_ANIM2D_SHADER		"StandardAnim2DShader"
#define	STANDARD_COLLIDER_SHADER	"StandardColliderShader"
#define	STANDARD_OUTLINE_SHADER		"StandardOutLineShader"
#define	STANDARD_ANIM2D_OUTLINE_SHADER		"StandardAnim2DOutLineShader"
#define	STANDARD_STATIC_INSTANCING_SHADER	"StandardStaticInstancingShader"
#define	STANDARD_ANIM2D_INSTANCING_SHADER	"StandardAnim2DInstancingShader"
#define	FULLSCREEN_SHADER			"FullScreenShader"
#define	UI_SHADER					"UIShader"
#define	UI_ANIM2D_SHADER			"UIAnim2DShader"
#define	UI_BAR_SHADER				"UIBarShader"
#define	TILEMAP_SHADER				"TileMapShader"

// InputLayout Key
#define	POS_COLOR_LAYOUT	"PosColorLayout"
#define	POS_UV_LAYOUT		"PosUVLayout"
#define	COLLIDER_LAYOUT		"ColliderLayout"
#define TILEMAP_INSTANCING_LAYOUT	"TileMapInstancingLayout"
#define	STATIC_INSTANCING_LAYOUT	"StaticInstancingLayout"
#define ANIM2D_INSTANCING_LAYOUT	"Anim2DInstancingLayout"


// Constant Buffer Key
#define	TRANSFORM_CBUFFER	"TransformCBuffer"
#define	MATERIAL_CBUFFER	"MaterialCBuffer"
#define	ANIM2D_CBUFFER		"Anim2DCBuffer"
#define	BAR_CBUFFER			"BarCBuffer"
#define	OUTLINE_CBUFFER		"OutLineCBuffer"
#define	TILEMAP_CBUFFER		"TileMapCBuffer"
#define	PAPERBURN_CBUFFER	"PaperBurnCBuffer"

// Render State Key
#define	RENDERSTATE_ALPHABLEND	"AlphaBlend"
#define	RENDERSTATE_NONEDEPTH	"NoneDepth"
#define	RENDERSTATE_CULLNONE	"CullNone"



template <typename T>
size_t GetTypeID()
{
	return typeid(T).hash_code();
}