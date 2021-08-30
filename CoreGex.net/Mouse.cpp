#include "Mouse.h"
#include <dinput.h>
using namespace System;
using namespace System::Runtime::InteropServices;
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")


static LPDIRECTINPUTDEVICE8 dinmouse;    // the pointer to the mouse device
static DIMOUSESTATE mousestate;    // the storage for the mouse-information
static LPDIRECTINPUT8 din;    // the pointer to our DirectInput interface

	static bool					    m_bInverted;
						
	static float                    m_fSensitivity=1;
	static float					m_fCursorX,
						        	m_fCursorY;
	static int						m_iHotSpotX,
							        m_iHotSpotY;
	static DWORD					m_dwAxes,
							        m_dwButtons,
							        m_dwCursorColor;
                              

extern int gwidth;
extern int gheight;
static System::IntPtr hInstance;

CoreGex::Input::Mouse::Mouse(void)
{
	hInstance = Marshal::GetHINSTANCE(Mouse::typeid->Module);
}



bool CoreGex::Input::Mouse::InitMouse(System::Windows::Forms::Control^ Control)
{
	
	    DirectInput8Create(static_cast<HINSTANCE>( hInstance.ToPointer() ),    // the handle to the application
                       DIRECTINPUT_VERSION,    // the compatible version
                       IID_IDirectInput8,    // the DirectInput interface version
                       (void**)&din,    // the pointer to the interface
                       NULL);    // COM stuff, so we'll set it to NULL


	    din->CreateDevice(GUID_SysMouse,
                      &dinmouse,
                      NULL);

		dinmouse->SetDataFormat(&c_dfDIMouse);

		dinmouse->SetCooperativeLevel(static_cast<HWND>( Control->Handle.ToPointer()), DISCL_EXCLUSIVE | DISCL_FOREGROUND);

		return true;
}


bool CoreGex::Input::Mouse::Update(void)
{
dinmouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mousestate);
dinmouse->Acquire();
return true;
}

void CoreGex::Input::Mouse::Destroy(void)
{
	
dinmouse->Unacquire();    // make sure the mouse in unacquired
    din->Release();    // close DirectInput before exiting
}


void CoreGex::Input::Mouse::Dispatch()
{
	dinmouse->Unacquire();    // make sure the mouse in unacquired
}

float CoreGex::Input::Mouse::GetXPos()
{




 return mousestate.lX* m_fSensitivity;
}


float CoreGex::Input::Mouse::GetYPos()
{

	


 return mousestate.lY* m_fSensitivity;
}



float CoreGex::Input::Mouse::GetZPos()
{


	

 return mousestate.lZ* m_fSensitivity;
}





bool CoreGex::Input::Mouse::GetButton(BUTTON MOUSEZ)
{


if(mousestate.rgbButtons[(BYTE)MOUSEZ] & 0x80)
 {
 return true;
 }

return false;

}

float CoreGex::Input::Mouse::GetAbsoluteX(void)
{
return m_fCursorX;
}//GetAbsoluteX

/************************************************************************/
/* Name:		GetAbsoluteY											*/
/* Description:	return absolute y of cursor								*/
/************************************************************************/

float CoreGex::Input::Mouse::GetAbsoluteY(void)
{
return m_fCursorY;
}//GetAbsoluteY


bool CoreGex::Input::Mouse::SetAttributes(bool inverted,float Sensitivity)
{
m_bInverted = inverted;
m_fSensitivity = Sensitivity;

return true;
}//SetAttributes

bool CoreGex::Input::Mouse::LockMouseOn(int x,int y)
{
	SetCursorPos(x,y);
	return true;
}