
#pragma once

#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#include "Flag.h"
#include "Macro.h"

using namespace DirectX;

#define		PI	3.141592f

static float DegreeToRadian(float fAngle)
{
	return fAngle / 180.f * PI;
}

static float RadianToDegree(float fAngle)
{
	return fAngle * 180.f / PI;
}
