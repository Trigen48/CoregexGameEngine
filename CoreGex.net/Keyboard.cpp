

#include"Keyboard.h"
#include <dinput.h>


#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
using namespace System;
using namespace System::Runtime::InteropServices;

/************************************************************************/
/* Name:		CInput													*/
/* Description:	define variables and call init functions				*/
/************************************************************************/

static	LPDIRECTINPUT8			m_pDIObject;
static	LPDIRECTINPUTDEVICE8	m_pDIKeyboardDevice;

static	char					KeyBuffer[256];
static System::IntPtr hInstance;
CoreGex::Input::Keyboard::Keyboard(void)
{
m_pDIObject = NULL;
m_pDIKeyboardDevice = NULL;
hInstance = Marshal::GetHINSTANCE(Keyboard::typeid->Module);
}//CInput

/************************************************************************/
/* Name:		~CInput													*/
/* Description:	release DirectInput object and devices					*/
/************************************************************************/

void CoreGex::Input::Keyboard::Destroy(void)
{
if(m_pDIKeyboardDevice != NULL)
 {
 m_pDIKeyboardDevice->Unacquire();
 m_pDIKeyboardDevice->Release();
 m_pDIKeyboardDevice = NULL;
 }

if(m_pDIObject != NULL)
 {
 m_pDIObject->Release();
 m_pDIObject = NULL;
 }
}//~CInput

/************************************************************************/
/* Name:		InitDirectInput											*/
/* Description:	create DirectInput object								*/
/************************************************************************/



/************************************************************************/
/* Name:		InitKeyboard											*/
/* Description:	init keyboard device									*/
/************************************************************************/

bool CoreGex::Input::Keyboard::InitKeyboard(System::Windows::Forms::Control^ Control)
{
			
//System::IntPtr^ Window

if(FAILED(DirectInput8Create(static_cast<HINSTANCE>( hInstance.ToPointer() ),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&m_pDIObject,NULL)))
 {


 return false;
 }



if(FAILED(m_pDIObject->CreateDevice(GUID_SysKeyboard,&m_pDIKeyboardDevice,NULL)))
 {

 return false;
 }

if(FAILED(m_pDIKeyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
 {

 return false;
 }

if(FAILED(m_pDIKeyboardDevice->SetCooperativeLevel(static_cast<HWND>( Control->Handle.ToPointer()),DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
 {

 return false;
 }

if(FAILED(m_pDIKeyboardDevice->Acquire()))
 {
	 
 return false;
 }

return true;
}//InitKeyboard

/************************************************************************/
/* Name:		Update													*/
/* Description:	update state of keyboard device							*/
/************************************************************************/

bool Update(void)
{
if(FAILED(m_pDIKeyboardDevice->GetDeviceState(sizeof(KeyBuffer),(LPVOID)&KeyBuffer)))
 {

 return false;
 }

return true;
}//Update

/************************************************************************/
/* Name:		KeyPressed												*/
/* Description:	check if key has been pressed							*/
/************************************************************************/

bool CoreGex::Input::Keyboard::KeyPressed(int Key)
{

	Update();




if(KeyBuffer[Key] & 0x80)
 {
 return true;
 }

return false;
}//KeyPressed


bool CoreGex::Input::Keyboard::KeyPressed(Keys Key)
{

	Update();

	



if(KeyBuffer[((BYTE)Key)] & 0x80)
 {
 return true;
 }

return false;
}//KeyPressed