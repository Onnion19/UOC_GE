#ifndef __DEFINES_H
#define __DEFINES_H

#include <string>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

using DirectX::XMFLOAT3;
using DirectX::XMFLOAT4;
using DirectX::XMMATRIX;
using DirectX::XMVECTOR;

#define PATH_WORLD			".\\Data\\Models\\World\\"
#define PATH_TEXTURES		".\\Data\\Models\\Textures\\"

#define CHECKED_DELETE(x) if(x!=NULL) {delete x; x=NULL;}
#define CHECKED_RELEASE(x) if(x!=NULL) {x->Release(); x=NULL;}

#define LENGTH(a,b) sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z))

enum TCameraControllerType
{ 
	FPS_CAMERA_CONTROLLER=0,
	SPHERICAL_CAMERA_CONTROLLER
};

void GetFilename(const char *path, std::string *filename);

#define DEG2RAD(x) x*DirectX::XM_PI/180.0f
#define RAD2DEG(x) x*180.0f/DirectX::XM_PI

float DistanceSqrXZ(const XMFLOAT3 &PosA, const XMFLOAT3 &PosB);
float CalculateYAW(const XMFLOAT3 &VDir);
float DistanceSqr(const XMFLOAT3 &Pos1, const XMFLOAT3 &Pos2);

std::wstring str2wstr(const std::string &s);

#endif
