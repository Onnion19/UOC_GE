#include "CameraManager.h"
#include "SphericalCameraController.h"
#include "FPSCameraController.h"
#include "CameraController.h"
#include "Frustum.h"
#include "InputManager.h"

#include <cassert>

CCameraManager::CCameraManager()
{
	m_Frustum = std::make_unique<CFrustum>();
	CreatePlayerDefaultCamera();
}


void CCameraManager::AddCameraController(TCameraControllerType CameraControllerType, std::string_view Name, const XMFLOAT3& Position, float Zoom)
{
	assert(m_CameraControllers.find(Name.data()) == m_CameraControllers.end());
	std::unique_ptr<CCameraController>l_CameraController;

	switch (CameraControllerType)
	{
	case TCameraControllerType::SPHERICAL_CAMERA_CONTROLLER:
		l_CameraController = std::make_unique<CSphericalCameraController>();
		static_cast<CSphericalCameraController*>(l_CameraController.get())->SetZoom(Zoom);
		break;
	case TCameraControllerType::FPS_CAMERA_CONTROLLER:
		l_CameraController = std::make_unique<CFPSCameraController>();
		break;
	}
	l_CameraController->SetPosition(Position);
	m_CameraControllers[Name.data()] = std::move(l_CameraController);
}

void CCameraManager::ChangeVision()
{
	auto iter = m_CameraControllers.find(m_CameraControllerControl);
	if (iter != m_CameraControllers.end()) {
		iter++;
		m_CameraControllerVision = (iter != m_CameraControllers.end()) ? iter->first : m_CameraControllers.begin()->first;
	}
}

void CCameraManager::onStartElement(const std::string& elem, MKeyValue& atts)
{
	if (elem == "SphericalCameraController")
	{
		float l_Zoom = 0.f;
		XMFLOAT3 l_Position{};
		std::string_view l_Name = atts["name"];
		std::string_view l_PosX = atts["posx"];
		std::string_view l_PosY = atts["posy"];
		std::string_view l_PosZ = atts["posz"];
		std::string_view l_ZoomStr = atts["zoom"];

		sscanf_s(l_PosX.data(), "%f", &l_Position.x);
		sscanf_s(l_PosY.data(), "%f", &l_Position.y);
		sscanf_s(l_PosZ.data(), "%f", &l_Position.z);
		sscanf_s(l_ZoomStr.data(), "%f", &l_Zoom);

		AddCameraController(TCameraControllerType::SPHERICAL_CAMERA_CONTROLLER, l_Name, l_Position, l_Zoom);
	}
	else if (elem == "FPSCameraController")
	{
		XMFLOAT3 l_Position{};
		std::string_view l_Name = atts["name"];
		std::string_view l_PosX = atts["posx"];
		std::string_view l_PosY = atts["posy"];
		std::string_view l_PosZ = atts["posz"];

		sscanf_s(l_PosX.data(), "%f", &l_Position.x);
		sscanf_s(l_PosY.data(), "%f", &l_Position.y);
		sscanf_s(l_PosZ.data(), "%f", &l_Position.z);

		AddCameraController(TCameraControllerType::FPS_CAMERA_CONTROLLER, l_Name, l_Position);
	}
	else
	{
		// Wrong camera on start element
		//assert(false);
	}
}

bool CCameraManager::SphereVisible(const XMFLOAT3& Center, float Radius) const
{
	return m_Frustum->SphereVisible(Center, Radius);
}

bool CCameraManager::BoxVisible(const XMFLOAT3& max, const XMFLOAT3& min) const
{
	return m_Frustum->BoxVisible(max, min);
}

CCameraController* CCameraManager::GetCameraController(const std::string& Name) const
{
	auto iter = m_CameraControllers.find(Name);
	return (iter != m_CameraControllers.end()) ? iter->second.get() : nullptr;
}

void CCameraManager::Update(float ElapsedTime)
{
	auto iter = m_CameraControllers.find(m_CameraControllerControl);
	if (iter != m_CameraControllers.end()) {
		assert(iter->second);
		iter->second->Update(ElapsedTime);
		iter->second->SetCamera(&m_Camera);
	}
	UpdateFrustumCamera();
}

void CCameraManager::UpdateFrustumCamera()
{
	// To verify it expects the preMultiplication of (M)VP matrix
	m_Frustum->Update(m_Camera.GetView() * m_Camera.GetProjection());
}

void CCameraManager::CreatePlayerDefaultCamera()
{
	m_CameraControllers.emplace("player", std::make_unique<CFPSCameraController>());
	m_CameraControllerControl = "player";
	m_CameraControllerVision = "plyaer";
}


void CCameraManager::Load(std::string_view Filename)
{
	std::string file{ Filename };
	xmlParseFile(std::move(file));
}
