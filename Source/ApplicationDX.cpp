#include "ApplicationDX.h"
#include <assert.h>
#include "defines.h"
#include "DebugRender.h"
#include "Camera.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "EffectManager.h"
#include "VertexTypes.h"
#include "Player.h"
#include "FBXManager.h"
#include "EffectManager.h"
#include "UOCEngine.h"
#include "RenderManager.h"

CApplicationDX::CApplicationDX()
: m_Player(NULL)
{
}

CApplicationDX::~CApplicationDX()
{
	//TO DO : Llamar al método Destroy de la clase singleton CUOCEngine
	//TO DO : Hacer el CHECKED_DELETE del singleton de la clase CUOCEngine
	//TO DO : Hacer el CHECKED_DELETE de la instancia del Player
}

void CApplicationDX::Init(HWND hWnd, int Width, int Height)
{
	//TO DO : Inicializar el motor llamando al método Init de la clase singleton CUOCEngine
	//TO DO : Crear la instancia de la clase CPlayer
	//TO DO : Llamar al método Load del FBXManager del motor y cargar el fichero fbx "data/models/world/World.fbx"
}

void CApplicationDX::Render()
{
	//TO DO : Llamar al método Render de la clase singleton CUOCEngine
}

void CApplicationDX::Update()
{
	//TO DO : Llamar al método Update de la clase singleton CUOCEngine
	//TO DO : Llamar al método Update de la instancia player pasándole el elapsed time del motor
}

LRESULT WINAPI CApplicationDX::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
    {
		case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
		case WM_KEYDOWN:
		{
			switch( wParam )
			{
				case VK_ESCAPE:
					PostQuitMessage( 0 );
					return 0;
					break;
			}
		}
    }
    return DefWindowProc( hWnd, msg, wParam, lParam );
}
