#include "Lights.h"
#include "CL.h"

#include <d3d9.h>
#include "D3dx9core.h"
#pragma comment(lib,"d3d9.lib") 
#pragma comment(lib,"d3d9.lib")

#ifdef _DEBUG
  #pragma comment(lib,"d3dx9d.lib")
#else
  #pragma comment(lib,"d3dx9.lib")
#endif



extern LPDIRECT3D9 d3;    // the pointer to our Direct3D interface
extern LPDIRECT3DDEVICE9 d3d;    // the pointer to the device class

struct LIGHTVAR
{
int LightNumber;
D3DLIGHT9 light;
bool Enabled;

};

static cl<LIGHTVAR> LVAR;

static bool detect(int input);
static bool Recreate();
static bool Delete(int ID);

static bool detect(int input)
{

	if(LVAR.Count()<input)
	{
		return false;
	}

	if(input<0)
	{
		return false;
	}

	return true;


}
static bool Recreate()
{
	
	LVAR.Add(LIGHTVAR());

   return true;
}


static bool Delete(int ID)
{
	if(detect(ID)==false)
	{
		return false;
	}

if (LVAR.Count()==0) 
{

	if (ID==0)
	{

		return true;
	}

	

return false;
}


LVAR.Remove(ID);

return true;

}


CoreGex::D3::Lights::Lights(void)
{
	LVAR= cl<LIGHTVAR>();
}


CoreGex::D3::Lights::~Lights(void)
{
	LVAR.Clear();
}


	/////////////////// Basic Functions  ////////////////
      int CoreGex::D3::Lights::AddLight()
	  {
		  Recreate();
		  int ID=LVAR.Count()-1;

		  ZeroMemory( &LVAR[ID].light, sizeof(D3DLIGHT9) );

	LVAR[ID].light.Type=D3DLIGHT_POINT;           
    LVAR[ID].light.Diffuse=D3DXCOLOR(1.0f,1.0f,1.0f,0);         
    LVAR[ID].light.Specular=D3DXCOLOR(0,0,0,0);        
    LVAR[ID].light.Ambient=D3DXCOLOR(0,0,0,0);        
    LVAR[ID].light.Position=D3DXVECTOR3(0,0,0);         
    LVAR[ID].light.Direction=D3DXVECTOR3(0,0,0);     

    LVAR[ID].light.Range=200;            
    LVAR[ID].light.Falloff=0;         
    LVAR[ID].light.Attenuation0=0.1f;  
    LVAR[ID].light.Attenuation1=0;     
    LVAR[ID].light.Attenuation2=0;    
    LVAR[ID].light.Theta=0;           
    LVAR[ID].light.Phi=0;     
	LVAR[ID].Enabled=false;
	LVAR[ID].LightNumber=ID;
			    d3d->SetLight( LVAR[ID].LightNumber, &LVAR[ID].light );
            d3d->LightEnable( LVAR[ID].LightNumber, LVAR[ID].Enabled ); 


		  

		  return ID;
	  }

	  bool CoreGex::D3::Lights::Deletelight(int ID)
	  {



		 return Delete(ID);
	  }

	  void CoreGex::D3::Lights::EnableLight(int ID, bool value)
	  {

  if(detect(ID)==false)
	{
		return ;
	}

  d3d->SetLight(LVAR[ID].LightNumber,&LVAR[ID].light);
            d3d->LightEnable( LVAR[ID].LightNumber, value ); 
			LVAR[ID].Enabled=value;
	  }


	  /////  Set Light Functions
	  void CoreGex::D3::Lights::SetLightType(int ID,LightType value)
	  {
		    if(detect(ID)==false)
	{
		return ;
	}

			LVAR[ID].light.Type=(D3DLIGHTTYPE)value;


	  }

	  void CoreGex::D3::Lights::SetDiffuse(int ID,TRLCOLOR^ value)
	  {
		    if(detect(ID)==false)
	{
		return ;
	}
		  LVAR[ID].light.Diffuse= D3DXCOLOR(value->R,value->G,value->B,value->A);
	  }

	  void CoreGex::D3::Lights::SetAmbient(int ID, TRLCOLOR^ value)
	  {
		    if(detect(ID)==false)
	{
		return ;
	}
LVAR[ID].light.Ambient= D3DXCOLOR(value->R,value->G,value->B,value->A);
	  }

	  void CoreGex::D3::Lights::SetSpecular(int ID,TRLCOLOR^ value)
	  {
		    if(detect(ID)==false)
	{
		return ;
	}
		  LVAR[ID].light.Specular= D3DXCOLOR(value->R,value->G,value->B,value->A);
	  }


	  void CoreGex::D3::Lights::SetLightPosition(int ID,TRLVECTOR3^ value)
	  {
		    if(detect(ID)==false)
	{
		return ;
	}
		  LVAR[ID].light.Position=D3DXVECTOR3(value->X,value->Y,value->Z);
	  }

	  void CoreGex::D3::Lights::SetLightDirection(int ID,TRLVECTOR3^ value)
	  {
		    if(detect(ID)==false)
	{
		return ;
	}
		  LVAR[ID].light.Direction= D3DXVECTOR3(value->X,value->Y,value->Z);
	  }


      void CoreGex::D3::Lights::SetRange(int ID,float value)   
	  {
		    if(detect(ID)==false)
	{
		return ;
	}
		  LVAR[ID].light.Range=value;
	  }

      void CoreGex::D3::Lights::SetFalloff(int ID,float value) 
	  {

		    if(detect(ID)==false)
	{
		return ;
	}
		  LVAR[ID].light.Falloff=value;
	  }

      void CoreGex::D3::Lights::SetAttenuation0(int ID,float value) 
	  {
		    if(detect(ID)==false)
	{
		return ;
	}
		  LVAR[ID].light.Attenuation0=value;
	  }

      void CoreGex::D3::Lights::SetAttenuation1(int ID,float value)   
	  {
		    if(detect(ID)==false)
	{
		return ;
	}
		  LVAR[ID].light.Attenuation1=value;
	  }

      void CoreGex::D3::Lights::SetAttenuation2(int ID,float value)   
	  {
		    if(detect(ID)==false)
	{
		return ;
	}
		  LVAR[ID].light.Attenuation2=value;
	  }

      void CoreGex::D3::Lights::SetTheta(int ID,float value)     
	  {
		    if(detect(ID)==false)
	{
		return ;
	}
		  LVAR[ID].light.Theta=value;
	  }

      void CoreGex::D3::Lights::SetPhi(int ID,float value) 
	  {
		    if(detect(ID)==false)
	{
		return ;
	}
		  LVAR[ID].light.Phi=value;
	  }



      ///// Get Light Functions
	  DWORD CoreGex::D3::Lights::GetLightType(int ID)
	  {
		    if(detect(ID)==false)
	{
		return NULL;
	}
		  return LVAR[ID].light.Type;
	  }

	  TRLCOLOR^ CoreGex::D3::Lights::GetDiffuse(int ID)
	  {
		    if(detect(ID)==false)
	{
		return gcnew TRLCOLOR();
	}
		 return gcnew TRLCOLOR(LVAR[ID].light.Diffuse.r,LVAR[ID].light.Diffuse.g,LVAR[ID].light.Diffuse.b,LVAR[ID].light.Diffuse.a);
	  }

	  TRLCOLOR^ CoreGex::D3::Lights::GetAmbient(int ID)
	  {
		    if(detect(ID)==false)
	{
		return gcnew TRLCOLOR();
	}
		  return gcnew TRLCOLOR(LVAR[ID].light.Ambient.r,LVAR[ID].light.Ambient.g,LVAR[ID].light.Ambient.b,LVAR[ID].light.Ambient.a);
	  }

	  TRLCOLOR^ CoreGex::D3::Lights::GetSpecular(int ID)
	  {
		    if(detect(ID)==false)
	{
		return gcnew TRLCOLOR();
	}
		  return gcnew TRLCOLOR(LVAR[ID].light.Specular.r,LVAR[ID].light.Specular.g,LVAR[ID].light.Specular.b,LVAR[ID].light.Specular.a);
	  }

	  TRLVECTOR3^ CoreGex::D3::Lights::GetLightPosition(int ID)
	  {
		    if(detect(ID)==false)
	{
		return gcnew TRLVECTOR3();
	}
		  return gcnew TRLVECTOR3(LVAR[ID].light.Position.x,LVAR[ID].light.Position.y,LVAR[ID].light.Position.z);
	  }

	  TRLVECTOR3^ CoreGex::D3::Lights::GetLightDirection(int ID)
	  {
		    if(detect(ID)==false)
	{
		return gcnew TRLVECTOR3();
	}
		   return gcnew TRLVECTOR3(LVAR[ID].light.Direction.x,LVAR[ID].light.Direction.y,LVAR[ID].light.Direction.z);
	  }

      float CoreGex::D3::Lights::GetRange(int ID)  
	  {
		    if(detect(ID)==false)
	{
		return 0;
	}
		   return LVAR[ID].light.Range;
	  }

      float CoreGex::D3::Lights::GetFalloff(int ID) 
	  {
		  		    if(detect(ID)==false)
	{
		return 0;
	}
		  return LVAR[ID].light.Falloff;
	  }

      float CoreGex::D3::Lights::GetAttenuation0(int ID) 
	  {
		  		    if(detect(ID)==false)
	{
		return 0;
	}
		  return LVAR[ID].light.Attenuation0;
	  }

      float CoreGex::D3::Lights::GetAttenuation1(int ID)  
	  {
		  		    if(detect(ID)==false)
	{
		return 0;
	}
		  return LVAR[ID].light.Attenuation1;
	  }

      float CoreGex::D3::Lights::GetAttenuation2(int ID)  
	  {
		  		    if(detect(ID)==false)
	{
		return 0;
	}
		  return LVAR[ID].light.Attenuation2;
	  }

      float CoreGex::D3::Lights::GetTheta(int ID) 
	  {
		  		    if(detect(ID)==false)
	{
		return 0;
	}
		  return LVAR[ID].light.Theta;
	  }

      float CoreGex::D3::Lights::GetPhi(int ID) 
	  {
		  		    if(detect(ID)==false)
	{
		return 0;
	}
		  return LVAR[ID].light.Phi;
	  }

	  bool CoreGex::D3::Lights::IsEnabled(int ID)
	  {
		  		    if(detect(ID)==false)
	{
		return false;
	}
		  return LVAR[ID].Enabled;
	  }

	 void CoreGex::D3::Lights::UpdateLights(int ID)
	 {

			if(detect(ID)==false)
			{
				return ;
			}
			d3d->SetLight( LVAR[ID].LightNumber, &LVAR[ID].light );

	 }

	  void CoreGex::D3::Lights::UpdateAllLights()
	  {

			for(int ID=0;ID<LVAR.Count();ID++)
			{
				d3d->SetLight( LVAR[ID].LightNumber, &LVAR[ID].light );
			}

	  }