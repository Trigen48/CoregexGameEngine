#pragma once
#include <d3d9.h>
#include "D3dx9core.h"



struct SpriteData
{
	IDirect3DTexture9* image;
	int Swidth;
	int Sheight;
	float rot;
	D3DXVECTOR2 center;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXMATRIX mat;
	ID3DXSprite* sprite;
};
