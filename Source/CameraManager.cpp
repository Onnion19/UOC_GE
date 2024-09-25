#include "CameraManager.h"
#include "SphericalCameraController.h"
#include "FPSCameraController.h"
#include "CameraController.h"
#include "Frustum.h"
#include "InputManager.h"

CCameraManager::CCameraManager()
{
	//TO DO : Construir la instancia del Frustum de la cámara
	//TO DO : Construir una instancia de CFPSCameraController e insertarla en la variable miembro m_CameraControllers con nombre "player"
	//TO DO : Establecer la varaible m_CameraControllerControl a "player"
	//TO DO : Establecer la varaible m_CameraControllerVision a "player"
}

CCameraManager::~CCameraManager()
{
	//TO DO : Recorrer todo el mapa de CameraController y eliminar los controladores de cámara utilizando la macro CHECKED_DELETE
	//TO DO : Eliminar la instancia de frustum de cámara utilizando la macro CHECKED_DELETE
}

void CCameraManager::AddCameraController(TCameraControllerType CameraControllerType, const std::string &Name, const XMFLOAT3 &Position, float Zoom)
{
	CCameraController *l_CameraController=NULL;
		
	switch(CameraControllerType)
	{
		case SPHERICAL_CAMERA_CONTROLLER:
			//TO DO : Construir una instancia de tipo CSphericalCameraController en la variable l_CameraController
			//TO DO : Establecer el Zoom en el controlador de cámara utilizando el método SetZoom de la clase CSphericalCameraController pasándole el parámetro Zoom
			break;
		case FPS_CAMERA_CONTROLLER:
			//TO DO : Construir una instancia de tipo CFPSCameraController en la variable l_CameraController
			break;
	}
	//TO DO : Establecer la posición en el controlador de cámara utilizando el método SetPosition 
	//TO DO : Insertar el controlador de cámara en la variable miembro m_CameraControllers según la clave Name
}

void CCameraManager::ChangeVision()
{
	//TO DO : Utilizar el método find de la instancia m_CameraControllers para encontrar el controlador de cámara m_CameraControllerControl
	//TO DO : Si encontramos el controlador de cámara avanzamos al siguiente controlador de cámara
	//TO DO : Si el controlador de cámara no es el end del m_CameraControllers asignamos a m_CameraControllerVision el first del iterador
	//TO DO : Si el controlador de cámara es el end del m_CameraControllers asignamos a m_CameraControllerVision el first del begin m_CameraControllers
}

void CCameraManager::onStartElement(const std::string &elem, MKeyValue &atts)
{
	if(elem=="SphericalCameraController")
    {
		float l_Zoom;
		XMFLOAT3 l_Position;
		std::string l_Name=atts["name"];
		std::string l_PosX=atts["posx"];
		std::string l_PosY=atts["posy"];
		std::string l_PosZ=atts["posz"];
		std::string l_ZoomStr=atts["zoom"];
	  	  
		sscanf_s(l_PosX.c_str(),"%f",&l_Position.x);
		sscanf_s(l_PosY.c_str(),"%f",&l_Position.y);
		sscanf_s(l_PosZ.c_str(),"%f",&l_Position.z);
		sscanf_s(l_ZoomStr.c_str(),"%f",&l_Zoom);
	  
		//TO DO : Añadir un controlador de cámara esférica utilizando el método AddCameraController
    }
	else if(elem=="FPSCameraController")
    {
		//TO DO : Recoger el nombre del controlador de cámara de los atributos del xml name
		//NOTA : Basarse en cómo recoge la posición de los atributos xml en la cámara de tipo SphericalCameraController
		//TO DO : Recoger la posición x del controlador de cámara de los atributos del xml posx
		//TO DO : Recoger la posición y del controlador de cámara de los atributos del xml posy
		//TO DO : Recoger la posición z del controlador de cámara de los atributos del xml posz
		//TO DO : Añadir un controlador de cámara FPS utilizando el método AddCameraController
    }
}

bool CCameraManager::SphereVisible(const XMFLOAT3 &Center, float Radius) const
{
	//TO DO : Utiliza el método SphereVisible de la instancia m_Frustum para saber si una esfera es visible por el frustum de cámara
}

bool CCameraManager::BoxVisible( const XMFLOAT3 &max, const XMFLOAT3 &min ) const
{
	//TO DO : Utiliza el método BoxVisible de la instancia m_Frustum para saber si una caja es visible por el frustum de cámara
}

CCameraController * CCameraManager::GetCameraController(const std::string &Name) const
{
	//TO DO : Buscamos el controlador de cámara utilizando el método find de m_CameraControllers
	//TO DO : Si lo encontramos devolvemos el second del iterador que nos devuelve el método find de m_CameraControllers
	//TO DO : Devuelve NULL en caso de no encontrar el controlador de cámara
}

void CCameraManager::Update(float ElapsedTime)
{
	//TO DO : Actualiza el controlador de cámara con nombre m_CameraControllerControl utilizando el método Update
	//TO DO : Establece el controlador de cámara con nombre m_CameraControllerVision utilizando el método SetCamera
	//TO DO : Llamar al método UpdateFrustumCamera para que se actualice el Frustum de la cámara
}

void CCameraManager::UpdateFrustumCamera()
{
	//TO DO : Actualiza el frustum de la cámara llamando al método Update de la variable miembro m_Frustum pasándoel las matrices de View y de Proyección de la instancia m_Camera
}

void CCameraManager::Load(const std::string &Filename)
{
	//TO DO : Parsea el fichero xml Filename utilizando el método xmlParseFile
}
