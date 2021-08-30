#pragma once
#pragma once
#include <Windows.h>
#include <iostream>


// Engine Includes
#include "Settings.h"
#include "Units.h"

using namespace CoreGex::Maths;
using namespace System::Windows::Forms;
using namespace System;

namespace CoreGex
{

	namespace Engine
	{

		[System::FlagsAttribute]
	public enum class TRLFOGMODE
	{
    NONE                 = 0,
    EXP                  = 1,
    EXP2                 = 2,
    LINEAR               = 3,
	};

public ref class Engine
{
public:
	Engine();
	void Destroy();


	// init engine
	bool InitEngine(Control^ Window);
	bool InitEngine(Control^ window,DeviceSettings^ settings);
	bool ModeAllowed(DeviceSettings^ settings);

	//Render
	bool Render();
	bool Render(int Color);
	bool Render(int R,int G, int B);
	bool Render(int R,int G, int B,int A);
	bool Render(TRLCOLOR^ Color);	
	bool EndRender();
	bool IsLost();
	bool CanReset();
	bool InternalError();
	bool Reset();
	
		DeviceSettings^ GetSettings();
	void ApplySettings(DeviceSettings^ settings);

	// Settings
void SetFarPlane(float value);
void SetNearPlane(float value);
void SetRadial(float value);
void SetDegree(float value);
void SetAspectRatio(float value);
void SetToRightHandSide();
void SetToLeftHandSide();
void TurnOnZwrite(bool option);
bool GetZwriteState();
bool GetZEnableStatus();

void TurnOnAlphablending(bool option);
bool GetAlphaBlendState();

void SetDesBlend();

void SetZEnable(bool option);
void TurnOnLighting(bool option);
bool GetLightingState();
void SetAmbientLighting(TRLCOLOR^ value);	

	// Fog
void TurnOnFog(bool option);
bool GetFogState();
void TurnOnRangeFog(bool option);
bool GetRangeFogState();

void FogStart(float value);
void FogEnd(float value);

float GetFogStart();
float GetFogEnd();


void FogMode(TRLFOGMODE mode);
TRLFOGMODE GetFogMode();

void SetFogColor(TRLCOLOR^ color);
TRLCOLOR^ GetFogColor();


//lighting

private:
TRLCOLOR^ FOGC;

};

	}
}
