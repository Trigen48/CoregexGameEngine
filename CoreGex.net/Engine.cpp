#include "Engine.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <winnt.h>
// include the basic windows header files and the Direct3D header file
#include <windowsx.h>
#include "D3dx9core.h"

#pragma comment(lib,"d3d9.lib")

#ifdef _DEBUG
#pragma comment(lib,"d3dx9.lib")
#else
#pragma comment(lib,"d3dx9d.lib")
#endif



/// Variables 
LPDIRECT3D9 d3;    
LPDIRECT3DDEVICE9 d3d; 
static D3DPRESENT_PARAMETERS d3dpp;
static bool dvt=false;

int gwidth,gheight;


//camera variables
static float FarPlanevalue=100;
static float NearPlanevalue=1.0;
static float Radial=45;
static float Degree=45;
static bool IsRadial=true;
static float ASP=0;
static bool ISRHV=false;
static float CameraSpeed=0.500;
 void SetupView();

 static bool ZENABLE=false;


static bool ZWRITE=true;
static bool AlphaBlendr =false;
static bool Lightingr=false;

static bool FogEN=false;
static bool FogREN=false;
static float ZFogStart=0.0f;
static float ZFogEnd=0.0f;
static CoreGex::Engine::TRLFOGMODE KMODE= CoreGex::Engine::TRLFOGMODE::NONE;


static D3DXVECTOR3 toDvector(TRLVECTOR3^ value);
static TRLVECTOR3^ toTvector(D3DXVECTOR3 value);
static D3DXCOLOR toDcolor(TRLCOLOR^ value);
static TRLCOLOR^ toTcolor(D3DXCOLOR value);

static D3DXVECTOR3 toDvector(TRLVECTOR3^ value)
{
	return D3DXVECTOR3(value->X,value->Y,value->Z);
}

static TRLVECTOR3^ toTvector(D3DXVECTOR3 value)
{
	return gcnew TRLVECTOR3(value.x,value.y,value.z);
}

static D3DXCOLOR toDcolor(TRLCOLOR^ value)
{
	return D3DXCOLOR(value->R,value->G,value->B,value->A);
}

static TRLCOLOR^ toTcolor(D3DXCOLOR value)
{
	return gcnew TRLCOLOR(value.r,value.g,value.b,value.a);
}


static CoreGex::Engine::DeviceSettings strst;

/////////////////////////////////////////////////////








static D3DPRESENT_PARAMETERS GetParm(CoreGex::Engine::DeviceSettings^ settings);
static D3DPRESENT_PARAMETERS GetParm(CoreGex::Engine::DeviceSettings^ settings)
{
	D3DPRESENT_PARAMETERS d3tmp ;
	d3tmp.BackBufferWidth            = settings->Width; 
	d3tmp.BackBufferHeight           = settings->Height;
	d3tmp.BackBufferFormat           =(D3DFORMAT)settings->Display;
	//d3tmp.BackBufferCount            = 1;
	//d3tmp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	//d3tmp.MultiSampleQuality         = 0;
	//d3tmp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	//d3tmp.hDeviceWindow              = mhMainWnd;
	d3tmp.Windowed                   = settings->Windowed;
	d3tmp.EnableAutoDepthStencil     = settings->EnableAutoDepthStencil; 
	d3tmp.AutoDepthStencilFormat     = (D3DFORMAT)settings->AutoDepthStencilFormat;
	//d3tmp.Flags                      = 0;
	d3tmp.FullScreen_RefreshRateInHz = d3tmp.Windowed?0: settings->RefreshRate;
	//d3tmp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	return d3tmp;
}

static DWORD BestDevice(CoreGex::Engine::RenderMode settings);
static DWORD BestDevice(CoreGex::Engine::DeviceSettings^ settings)
{
D3DCAPS9 caps;
//d3d->GetDeviceCaps();
d3->GetDeviceCaps(settings->AdapterID,(D3DDEVTYPE)settings->DeviceMode,&caps);

DWORD devBehaviorFlags = 0;
if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	devBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
else
      devBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

// If pure device and HW T&L supported
if( caps.DevCaps & D3DDEVCAPS_PUREDEVICE &&
      devBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
            devBehaviorFlags |= D3DCREATE_PUREDEVICE;

return devBehaviorFlags;
}

static void SetupWindow(Control^ window,CoreGex::Engine::DeviceSettings^ settings ,bool SetWindowed);
static void SetupWindow(Control^ window,CoreGex::Engine::DeviceSettings^ settings ,bool SetWindowed)
{

	HWND Window=static_cast<HWND>( window->Handle.ToPointer());
	      // Switch to full screen mode.
      if( !SetWindowed )
      {
            // Are we already in full screen mode?
            if( !settings->Windowed )
                  return;

            // Get the current screen resolution.
            int width  = GetSystemMetrics(SM_CXSCREEN);
            int height = GetSystemMetrics(SM_CYSCREEN);

            // Change the window style to a more full screen
            // friendly style.
            SetWindowLongPtr(Window, GWL_STYLE, WS_POPUP);

            // If we call SetWindowLongPtr, MSDN states that we need
            // to call SetWindowPos for the change to take effect.
            // In addition, we need to call this function anyway
            // to update the window dimensions.
            SetWindowPos(Window, HWND_TOP, 0, 0,
                  width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
      }
      // Switch to windowed mode.
      else

      {
            // Are we already in windowed mode?
            if( settings->Windowed )
                   return;

            // Default to a client rectangle of 800x600.
			RECT R = {0, 0, 800, 600};
			if(settings->Width!=0|| settings->Height!=0) 
			{
				R.right=settings->Width;
				R.bottom= settings->Height;
			}


            AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);

            // Change the window style to a more windowed
            // friendly style.
			SetWindowLongPtr(Window,GWL_STYLE,WS_OVERLAPPEDWINDOW);

            // If we call SetWindowLongPtr, MSDN states that we
            // need to call SetWindowPos for the change to take effect.
            // In addition, we need to call this function anyway to
            // update the window dimensions.
            SetWindowPos(Window, HWND_TOP, 100, 100,
                  R.right, R.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
      }



}

static void ResetWindow();
static void ResetWindow()
{
		      // Switch to full screen mode.
	if( !d3dpp.Windowed)
      {
            // Are we already in full screen mode?


            // Get the current screen resolution.
            int width  = GetSystemMetrics(SM_CXSCREEN);
            int height = GetSystemMetrics(SM_CYSCREEN);

            // Change the window style to a more full screen
            // friendly style.
			SetWindowLongPtr(d3dpp.hDeviceWindow, GWL_STYLE, WS_POPUP);

            // If we call SetWindowLongPtr, MSDN states that we need
            // to call SetWindowPos for the change to take effect.
            // In addition, we need to call this function anyway
            // to update the window dimensions.
            SetWindowPos(d3dpp.hDeviceWindow, HWND_TOP, 0, 0,
                  width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
      }
      // Switch to windowed mode.
      else

      {
            // Are we already in windowed mode?


            // Default to a client rectangle of 800x600.
			RECT R = {0, 0, 800, 600};
			if(d3dpp.BackBufferWidth!=0|| d3dpp.BackBufferHeight!=0) 
			{
				R.right=d3dpp.BackBufferWidth;
				R.bottom= d3dpp.BackBufferHeight;
			}


            AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);

            // Change the window style to a more windowed
            // friendly style.
			SetWindowLongPtr(d3dpp.hDeviceWindow,GWL_STYLE,WS_OVERLAPPEDWINDOW);

            // If we call SetWindowLongPtr, MSDN states that we
            // need to call SetWindowPos for the change to take effect.
            // In addition, we need to call this function anyway to
            // update the window dimensions.
            SetWindowPos(d3dpp.hDeviceWindow, HWND_TOP, 100, 100,
                  R.right, R.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
      }

}

CoreGex::Engine::Engine::Engine()
{
}
CoreGex::Engine::DeviceSettings^ CoreGex::Engine::Engine::GetSettings()
{
	return strst;
}

void CoreGex::Engine::Engine::ApplySettings(DeviceSettings^ settings)
{
	d3dpp= GetParm(settings);
	strst=(DeviceSettings)settings;
}


void CoreGex::Engine::Engine::Destroy()
{
	d3d->Release();    // close and release the 3D device
    d3->Release();    // close and release Direct3D
}

bool CoreGex::Engine::Engine::InitEngine(Control^ window)
{

	DeviceSettings^ dv=DeviceSettings();

	dv->Height=768;
	dv->Width=1024;
	dv->AutoDepthStencilFormat= DisplayFormat::DF24S;
	dv->Display = DisplayFormat::DF32X;
	dv->EnableAutoDepthStencil=true;
	
	dv->AdapterID=0;
	dv->DeviceMode= RenderMode::HardwareRender;
	dv->Vertex= VertexProccesing::HardwareVertex;
	dv->Windowed=true;
	dv->RefreshRate= dv->Windowed? dv->RefreshRate=0:60;
	return InitEngine(window,dv);
	
}



bool CoreGex::Engine::Engine::InitEngine(Control^ window,DeviceSettings^ settings)
{

	if(!dvt){d3= Direct3DCreate9(D3D_SDK_VERSION); dvt=true;}
	if(!d3) return false;
	HWND Window=static_cast<HWND>( window->Handle.ToPointer());
	
	// Device Paremeters
	d3dpp							 = GetParm(settings);
	d3dpp.hDeviceWindow				 = Window;
	d3dpp.Flags						 = 0;
	d3dpp.BackBufferCount			 = 1;
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality         = 0;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	d3dpp.PresentationInterval		 = D3DPRESENT_INTERVAL_IMMEDIATE;
	

	SetupWindow(window,settings,settings->Windowed);
	strst=(DeviceSettings)settings;
	DWORD tb;

	gwidth=d3dpp.BackBufferWidth;
	gheight= d3dpp.BackBufferHeight;

	if(settings->Vertex== VertexProccesing::BestSuitable)tb= BestDevice(settings); else tb=(DWORD)settings->Vertex;
	// Setup Window
	HRESULT HR;
		HR=d3->CreateDevice(
			settings->AdapterID,							// primary adapter
			(D3DDEVTYPE)settings->DeviceMode,            // device type
		Window,									    // window associated with device
		(DWORD)tb,											// vertex processing
	    &d3dpp,									    // present parameters
	    &d3d);										// return created device

		


	return HR==D3D_OK? true : false;
}

bool CoreGex::Engine::Engine::ModeAllowed(DeviceSettings ^settings)
{
	if(!dvt){d3= Direct3DCreate9(D3D_SDK_VERSION); dvt=true;}
		D3DDISPLAYMODE mode;
		mode.Format= (D3DFORMAT)settings->Display;
		mode.Height= settings->Height;
		mode.RefreshRate=settings->RefreshRate;
		mode.Width= settings->Width;
	return d3->CheckDeviceType(D3DADAPTER_DEFAULT, (D3DDEVTYPE)settings->DeviceMode, mode.Format, mode.Format, settings->Windowed)==D3D_OK? true:false;
}

//Render
bool CoreGex::Engine::Engine::Render()
{
	return Render(0,0,0,255);
}

bool CoreGex::Engine::Engine::Render(int Color)
{
	return Render(Color,Color,Color,255);
}

bool CoreGex::Engine::Engine::Render(int R,int G, int B)
{
return Render(R,G,B,255);
}

bool CoreGex::Engine::Engine::Render(int R,int G, int B,int A)
{
	d3d->Clear(0, NULL, D3DCLEAR_TARGET| D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(R,G,B), 1.0f, 0);
	d3d->BeginScene();
	
	return true;
}

bool CoreGex::Engine::Engine::Render(TRLCOLOR^ Color)
{
	return Render(Color->R,Color->G,Color->B,Color->A);
}

bool CoreGex::Engine::Engine::EndRender()
{
	d3d->EndScene();
	d3d->Present(0, 0, 0, 0);
	return true;
	
}

bool CoreGex::Engine::Engine::IsLost()
{
      HRESULT hr = d3d->TestCooperativeLevel();

      // If the device is lost and cannot be reset yet, then
      // sleep for a bit and we'll try again on the next
      // message loop cycle.
      if( hr == D3DERR_DEVICELOST )
      {
            Sleep(20);
            return true;
      }
	  return false;

}

bool CoreGex::Engine::Engine::CanReset()
{
	HRESULT hr = d3d->TestCooperativeLevel();
	return hr == D3DERR_DEVICENOTRESET ?true:false;
}

bool CoreGex::Engine::Engine::InternalError()
{
	HRESULT hr = d3d->TestCooperativeLevel();
	return hr == D3DERR_DRIVERINTERNALERROR?true:false;
}

bool CoreGex::Engine::Engine::Reset()
{
	ResetWindow();
	return d3d->Reset(&d3dpp)==D3D_OK? true:false;
}

void CoreGex::Engine::Engine::SetFarPlane(float value)
{
FarPlanevalue=value;
}

void CoreGex::Engine::Engine::SetNearPlane(float value)
{
NearPlanevalue=value;
}

void CoreGex::Engine::Engine::SetRadial(float value)
{
Radial=value;
}

void CoreGex::Engine::Engine::SetDegree(float value)
{
	Degree=value;
}

void CoreGex::Engine::Engine::SetAspectRatio(float value)
{
	ASP=value;
}

void CoreGex::Engine::Engine::SetToRightHandSide()
{
	ISRHV=true;
}

void CoreGex::Engine::Engine::SetToLeftHandSide()
{
ISRHV=false;
}

void CoreGex::Engine::Engine::SetZEnable(bool option)
{
	d3d->SetRenderState(D3DRS_ZENABLE,option);
	ZENABLE=option;
}

bool CoreGex::Engine::Engine::GetZEnableStatus()
{
	return ZENABLE;
}

void CoreGex::Engine::Engine::TurnOnZwrite(bool option)
{
	
d3d->SetRenderState( D3DRS_ZWRITEENABLE, option );
	ZWRITE= option;

}

bool CoreGex::Engine::Engine::GetZwriteState()
{
	
	return ZWRITE;
}

void CoreGex::Engine::Engine::TurnOnAlphablending(bool option)
{
	AlphaBlendr=option;

    d3d->SetRenderState( D3DRS_ALPHABLENDENABLE, option );
}


bool CoreGex::Engine::Engine::GetAlphaBlendState()
{
	return AlphaBlendr;
}

void CoreGex::Engine::Engine::SetDesBlend()
{
	d3d->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
}

void CoreGex::Engine::Engine::TurnOnLighting(bool option)
{
	Lightingr=option;
	d3d->SetRenderState( D3DRS_LIGHTING,  option );
	
}

bool CoreGex::Engine::Engine::GetLightingState()
{
	return Lightingr;
}

void CoreGex::Engine::Engine::TurnOnFog(bool option)
{
d3d->SetRenderState(D3DRS_FOGENABLE,option);
FogEN=option;
}

bool CoreGex::Engine::Engine::GetFogState()
{
return FogEN;
}

void CoreGex::Engine::Engine::TurnOnRangeFog(bool option)
{
	d3d->SetRenderState(D3DRS_RANGEFOGENABLE,option);
	FogREN=option;
}
bool CoreGex::Engine::Engine::GetRangeFogState()
{
return FogREN;
}

void CoreGex::Engine::Engine::FogStart(float value)
{
d3d->SetRenderState(D3DRS_FOGSTART,*(DWORD*)(&value));
ZFogStart=value;

}

void CoreGex::Engine::Engine::FogEnd(float value)
{
d3d->SetRenderState(D3DRS_FOGEND,*(DWORD*)(&value));
ZFogEnd=value;

}

float CoreGex::Engine::Engine::GetFogStart()
{
	return ZFogStart;
}

float CoreGex::Engine::Engine::GetFogEnd()
{
	return ZFogEnd;
}

void CoreGex::Engine::Engine::FogMode(TRLFOGMODE mode)
{

d3d->SetRenderState(D3DRS_FOGVERTEXMODE,(DWORD)mode);
   KMODE=mode;

}

CoreGex::Engine::TRLFOGMODE CoreGex::Engine::Engine::GetFogMode()
{
	return KMODE;
}

void CoreGex::Engine::Engine::SetFogColor(TRLCOLOR^ color)
{
d3d->SetRenderState(D3DRS_FOGCOLOR,D3DCOLOR_COLORVALUE(color->R,color->G,color->B,color->A));
FOGC= (TRLCOLOR^)color;
}

TRLCOLOR^ CoreGex::Engine::Engine::GetFogColor()
{
	return FOGC;
}

void CoreGex::Engine::Engine::SetAmbientLighting(TRLCOLOR^ value)
{
	
	d3d->SetRenderState( D3DRS_AMBIENT, toDcolor(value) );
}