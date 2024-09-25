#include "UOCEngine.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "EffectManager.h"
#include "DebugRender.h"
#include "CameraManager.h"
#include "DebugRender.h"
#include "FBXManager.h"
#include "RenderableObjectManager.h"
#include "TextureManager.h"
#include "VertexTypes.h"

CUOCEngine *CUOCEngine::m_UOCEngine=NULL;

CUOCEngine::CUOCEngine()
//TO DO : Inicializar la variable miembro m_RenderManager a NULL
//TO DO : Inicializar la variable miembro m_DrawAntTweakBar a false
//TO DO : Inicializar la variable miembro m_EffectManager a NULL
//TO DO : Inicializar la variable miembro m_InputManager a NULL
//TO DO : Inicializar la variable miembro m_CameraManager a NULL
//TO DO : Inicializar la variable miembro m_PreviousTime a 0
//TO DO : Inicializar la variable miembro m_DebugRender a NULL
//TO DO : Inicializar la variable miembro m_FBXManager a NULL
//TO DO : Inicializar la variable miembro m_RenderableObjectManager a NULL
//TO DO : Inicializar la variable miembro m_TextureManager a NULL
{
}

CUOCEngine::~CUOCEngine()
{
}

CUOCEngine * CUOCEngine::GetEngine()
{
	//TO DO : Implementar el patrón Singleton, si la instancia m_UOCEngine es NULL crearla
	//TO DO : Devolver la instancia m_UOCEngine
}

void CUOCEngine::Init(HWND hWnd, int Width, int Height)
{
	//TO DO : Construye la variable miembro m_RenderManager
	//TO DO : Llama al método Init de la variable miembro m_RenderManager

	//TO DO : Construye la variable miembro m_InputManager
	//TO DO : Construye la variable miembro m_EffectManager

	//TO DO : Construye la variable miembro m_DebugRender pasando el parámetro el Device de la variable miembro m_RenderManager

	//TO DO : Construye la variable miembro m_CameraManager
	//TO DO : Llama al método Load de la variable miemtro m_CameraManager para cargar el fichero xml "./DATA/XML/cameras.xml"

	//TO DO : Construye la variable miembro m_FBXManager
	//TO DO : Construye la variable miembro m_RenderableObjectManager
	//TO DO : Construye la variable miembro m_TextureManager
	//TO DO : Inicializa la variable miembro m_PreviousTime asignándole el valor que devuelve la función timeGetTime()
}

void CUOCEngine::Update()
{
	//TO DO : Calcula el elapsed time del frame, para ello recoges el tiempo actual con la función timeGetTime() y le decrementamos el m_PreviousTime. Este valor se calcula en milisegundos y lo transformamos en segundos multiplicando por 0.001f
	//TO DO : Asignamos a la variable m_PreviousTime el tiempo actual de este frame que hemos capturado en el TO DO anterior

	//TO DO : Llamamos al método Update de la variable miembro m_InputManager para actualizar el Input

	CCameraController *l_CameraController=m_CameraManager->GetCameraController("player");
	
	CKeyboardInput *l_KeyboardInput=m_InputManager->GetKeyboard();

	//TO DO : Si la tecla DIK_TAB se pulsa en este frame (utilizamos el método KeyBecomesPressed de la instancia del KeyboardInput l_KeyboardInput), cambiamos el controlador de cámara que se utiliza para pintar con el método ChangeVision del m_CameraManager
	//TO DO : Si la tecla DIK_C se pulsa en este frame, cambiamos el controlador de cámara que se utiliza para control con el método ChangeControl del m_CameraManager
	//TO DO : Actualizamos el m_CameraManager llamando al método Update
	//TO DO : Actualizamos el m_RenderableObjectManager llamando al método Update
}

void CUOCEngine::Render()
{
	//TO DO : Llamar al método BeginRenderDX de la instancia m_RenderManager
	ID3D11DeviceContext *l_DeviceContext=m_RenderManager->GetDeviceContext();

	//TO DO : Si debemos pintar en modo sólido (utilizamos el métod GetPaintSolid de la clase m_RenderManager), establecemos el renderstate de sólido utilizando el método SetSolidRenderState de la clase m_RenderManager
	//TO DO : En caso contrario establecemos el render state en modo alambre utilizando el método SetWireframeRenderState de la clase m_RenderManager
	//TO DO : Recoger la matriz de view de la cámara de la variable miembro m_CameraManager
	//TO DO : Recoger la matriz de proyección de la cámara de la variable miembro m_CameraManager
	//TO DO : Establecer la variable miembro m_View de la variable miembro estática m_SceneConstantBufferParameters de la clase CEffectManager, el valor será la matriz transpuesta de la matriz de View que hemos recogido en el TODO anterior, para realizar la matriz transpuesta utilizamos la función de DirectX XMMatrixTranspose
	//TO DO : Establecer la variable miembro m_Projection de la variable miembro estática m_SceneConstantBufferParameters de la clase CEffectManager, el valor será la matriz transpuesta de la matriz de Projection que hemos recogido en el TODO anterior, para realizar la matriz transpuesta utilizamos la función de DirectX XMMatrixTranspose
	//TO DO : Establecer las constantes de escena en la variable miembro m_EffectManager utilizando el método SetSceneConstantBuffer
	//TO DO : Llamar al método Render de la variable miembro m_RenderableObjectManager

	
	if(m_RenderManager->DrawAxisGrid())
	{
		//TO DO : Crear una variable de tipo XMMATRIX que contendrá la matriz de mundo y asignarle el valor identidad mediante la función DirectX:::XMMatrixIdentity
		//TO DO : Establecer en la variable miembro m_World de la variable miembro estática m_ObjectConstantBufferParameters de la clase CEffectManager, estableceremos la matriz transpuesta de la variable de mundo que hemos creado en el TO DO anterior
		//TO DO : Llamar al método SetObjectConstantBuffer de la variable miembro m_EffectManager para establecer las constantes de objeto
		//TO DO : Llamar al método DrawAxis de la variable miembro m_DebugRender con un Size de 8.0f
		//TO DO : Llamar al método DrawGrid de la variable miembro m_DebugRender con un Size de 1.0f y color blanco
		//TO DO : Llamar al método DrawCube de la variable miembro m_DebugRender con un Size de 3.0f y color blanco
		//TO DO : Llamar al método DrawSphere de la variable miembro m_DebugRender con un Size de 0.5f y color blanco
	}

	//TO DO : Llamar al método EndRenderDX de la instancia m_RenderManager
}

void CUOCEngine::Destroy()
{
	//TO DO : Destruir la variable miembro m_DebugRender utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_InputManager utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_CameraManager utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_EffectManager utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_FBXManager utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_RenderableObjectManager utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_TextureManager utilizando la macro CHECKED_DELETE
	//TO DO : Llamar al método Destroy de la variable miembro m_RenderManager
	//TO DO : Destruir la variable miembro m_RenderManager utilizando la macro CHECKED_DELETE
}
