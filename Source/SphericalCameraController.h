#ifndef INC_SPHERICALCAMERA_H_
#define INC_SPHERICALCAMERA_H_

#include "CameraController.h"

class CSphericalCameraController : public CCameraController
{
private:
	float m_Zoom = 50.f;
	float theta = 0.f;
	float sigma = 0.f;
	float distance = 10.f;

	static constexpr float m_ZoomSpeed = 15.f;
	static constexpr float m_RotationSpeed = 30.f;
public:
	void AddZoom(float Zoom) {m_Zoom+=Zoom;}
	void SetZoom(float Zoom) {m_Zoom=Zoom;}
	
	void SetCamera(CCamera *Camera) const;
	void Update(float ElapsedTime);
};

#endif
