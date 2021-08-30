#pragma once
#include <Windows.h>
#include "UNITS.h"


using namespace CoreGex::Maths;

namespace CoreGex
{

	namespace D3
	{

		[System::FlagsAttribute]
public enum class LightType
{
	PointLight=1,
	SpotLight=2,
	DirectionLight=3,

};

//#define    POINTLIGHT           1           /// Point Light
//#define    SPOTLIGHT            2           /// Spot Light
//#define    DIRECTIONALLIGHT     3           /// Directional Light
//#define    FORCELIGHT           0x7fffffff  /// Force Light  

public ref  class Lights	
{
public:
	Lights(void);
	~Lights(void);


	/////////////////// Basic Functions  ////////////////
      int AddLight();
	  bool Deletelight(int ID);
	  void EnableLight(int ID, bool value);

	  /////  Set Light Functions
	  void SetLightType(int ID,LightType value);

	  void SetDiffuse(int ID,TRLCOLOR^ value);
	  void SetAmbient(int ID, TRLCOLOR^ value);
	  void SetSpecular(int ID,TRLCOLOR^ value);

	  void SetLightPosition(int ID,TRLVECTOR3^ value);
	  void SetLightDirection(int ID,TRLVECTOR3^ value);

      void SetRange(int ID,float value);          
      void SetFalloff(int ID,float value);         
      void SetAttenuation0(int ID,float value);    
      void SetAttenuation1(int ID,float value);    
      void SetAttenuation2(int ID,float value);     
      void SetTheta(int ID,float value);           
      void SetPhi(int ID,float value); 




      ///// Get Light Functions
	  DWORD GetLightType(int ID);

	  TRLCOLOR^ GetDiffuse(int ID);
	  TRLCOLOR^ GetAmbient(int ID);
	  TRLCOLOR^ GetSpecular(int ID);

	  TRLVECTOR3^ GetLightPosition(int ID);
	  TRLVECTOR3^ GetLightDirection(int ID);

      float GetRange(int ID);          
      float GetFalloff(int ID);         
      float GetAttenuation0(int ID);    
      float GetAttenuation1(int ID);    
      float GetAttenuation2(int ID);     
      float GetTheta(int ID);           
      float GetPhi(int ID); 
	  void UpdateLights(int ID);
	  void UpdateAllLights();


	  bool IsEnabled(int ID);





};

	}
}