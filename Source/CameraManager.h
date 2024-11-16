#ifndef INC_CAMERAMANAGER_H_
#define INC_CAMERAMANAGER_H_


#include <map>
#include <string>
#include <string_view>
#include "XMLParser.h"
#include "defines.h"
#include "Camera.h"
#include "Frustum.h"
#include "CameraController.h"
#include <memory>

class CCameraController;

class  CCameraManager final: public CXMLParser 
{
private:
	std::string												m_CameraControllerControl;
	std::string												m_CameraControllerVision;
	CCamera													m_Camera;
	std::unique_ptr<CFrustum> 												m_Frustum;
	std::map<std::string, std::unique_ptr<CCameraController>>				m_CameraControllers;
	
	void onStartElement(const std::string &elem, MKeyValue &atts);
	void UpdateFrustumCamera();
	void CreatePlayerDefaultCamera();
	void SetCamera(std::string_view name);
public:
	CCameraManager();
	~CCameraManager() = default;

	CCameraController * GetCameraController(const std::string &Name) const;
	void AddCameraController(TCameraControllerType CameraControllerType, std::string_view Name, const XMFLOAT3 &Position, float Zoom=0.0f);
	void ChangeVision();
	void ChangeControl() {m_CameraControllerControl=m_CameraControllerVision;}
	bool SphereVisible(const XMFLOAT3 &p, float radius) const;
	bool BoxVisible(const XMFLOAT3 &max, const XMFLOAT3 &min) const;
	void Load(std::string_view Filename);
	const CCamera & GetCamera() const {return m_Camera;}
	void Update(float ElapsedTime);
};

#endif
