#pragma once

namespace CoreGex
{

	namespace Engine
	{

		[System::FlagsAttribute]
public enum class DisplayFormat
{
	UNKNOWN				 =  0,
    DF32A				 = 21,
    DF32X				 = 22,

	D16S				 = 23,
    D16A				 = 25,
    DF24S		         = 75,
    DF24X		         = 77,
	DF16                 = 80,
};

[System::FlagsAttribute]
public enum class RenderMode : DWORD
{
	HardwareRender=1,
	ReferenceRender=2,
	SoftwareRender=3,
};

[System::FlagsAttribute]
public enum class VertexProccesing
{
	PureDeviceVertex=16,
	SoftwareVertex=32,
	HardwareVertex=64,
	MixedVertex=128,
	BestSuitable=256,

};

public value struct DeviceSettings
{
public:
	int AdapterID;
	bool Windowed;
	bool EnableAutoDepthStencil;
	DisplayFormat AutoDepthStencilFormat;
	RenderMode DeviceMode;
	VertexProccesing Vertex;
		int Width,Height;
	DisplayFormat Display;
	int RefreshRate;
};

public value struct DisplayMode
{
public:
	int Width,Height;
	DisplayFormat Display;
	int RefreshRate;
};

public value struct DisplayAdapter
{
public:
	int AdapterID;
};



	}

}