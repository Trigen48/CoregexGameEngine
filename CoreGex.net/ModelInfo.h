#pragma once

#include <d3dx9.h>
#include <d3dx9core.h>


#define ColorVertexF (D3DFVF_XYZ| D3DFVF_DIFFUSE)

#define TextureVertexF 0xff

struct ColorVertex
{
public:
	float  x
		  ,y
		  ,z;
	DWORD color;

	ColorVertex()
	{

	}

	ColorVertex(int X,int Y, int Z,DWORD Color)
	{
		x=X;
		y=Y;
		z=Z;
		color=Color;
	}
};