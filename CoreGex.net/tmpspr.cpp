#include "tmpspr.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <winnt.h>
// include the basic windows header files and the Direct3D header file
#include <windowsx.h>
#include <d3d9.h>
#include "D3dx9core.h"
#include "CL.h"


#pragma comment(lib,"d3d9.lib")

#ifdef _DEBUG
  #pragma comment(lib,"d3dx9d.lib")
#else
  #pragma comment(lib,"d3dx9.lib")
#endif


extern int gwidth;
extern int gheight;

//extern LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
extern LPDIRECT3DDEVICE9 d3d;    // the pointer to the device class
static const DWORD tri_fvf=D3DFVF_XYZRHW|D3DFVF_DIFFUSE;
ID3DXSprite* sprite;

struct SpriteData
{
IDirect3DTexture9* image;
int Swidth;
int Sheight;
float rot;
LPCSTR file;
D3DXVECTOR2 center;
D3DXVECTOR2 position;
D3DXVECTOR2 scale;
D3DXMATRIX mat;


};

static void Transform(SpriteData* dd);
static void Transform(SpriteData *dd)
{
	D3DXMATRIX t;

	//D3DXMatrixTranslation(&t,dd->sx,dd->sy,dd->sz);
	//D3DXMatrixRotationZ(&r,dd->rot);
	//dd->mat= t+r;

	D3DXMatrixTransformation2D(&t,NULL,NULL,&dd->scale,&dd->center,dd->rot,&dd->position);
	dd->mat=t;
}

static int trigen=0;

//SpriteData *SS;

static cl<SpriteData>SS;

static DWORD tri=D3DXSPRITE_ALPHABLEND;
static bool detect(int input);
static bool Recreate();

CoreGex::D2::Sprites::Sprites()
{
	
D3DXCreateSprite(d3d, &sprite);

}

int CoreGex::D2::Sprites::AddNew()
{
	SpriteData p;
	ZeroMemory(&p, sizeof(p));
	p.scale= D3DXVECTOR2(1,1);
	p.position= D3DXVECTOR2(0,0);
	p.rot=0;
	
	Transform(&p);
	SS.Add(p);
	return SS.Count()-1;
}

bool CoreGex::D2::Sprites::SetSpriteDraw(int ID,SpriteFlag MODE)
{
	switch(MODE)
	{
	case 0:
		tri=D3DXSPRITE_DONOTSAVESTATE;
		break;

	case 1:
		tri=D3DXSPRITE_DONOTMODIFY_RENDERSTATE;
		break;

	case 2:
		tri=D3DXSPRITE_OBJECTSPACE;
		break;


	case 3:
		tri=D3DXSPRITE_BILLBOARD;
		break;


	case 4:
		tri=D3DXSPRITE_ALPHABLEND;
		break;


	case 5:
		tri=D3DXSPRITE_SORT_TEXTURE ;
		break;


	case 6:
		tri=D3DXSPRITE_SORT_DEPTH_FRONTTOBACK;
		break;


	case 7:
		tri=D3DXSPRITE_SORT_DEPTH_BACKTOFRONT;
		break;


	case 8:
		tri=D3DXSPRITE_DO_NOT_ADDREF_TEXTURE;
		break;


	default :
		tri=D3DXSPRITE_ALPHABLEND;
		break;
	}

	return true;
}
bool CoreGex::D2::Sprites::LoadSprite(int ID,System::String ^FileName )
{



	return LoadSprite(ID,FileName,D3DX_DEFAULT,D3DX_DEFAULT,255,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::Sprites::LoadSprite(int ID,System::String ^FileName, int width, int height)
{
	return LoadSprite(ID,FileName,width,height,255,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::Sprites::LoadSprite(int ID,System::String ^FileName, int width, int height,int transparentkey)
{
	return LoadSprite(ID,FileName,width,height,transparentkey,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::Sprites::LoadSprite(int ID,System::String ^FileName, int width, int height,int transparentkey,SpriteFormat fmt)
{

	if(SS.Count() == ID)
	{
		AddNew();
	}
	else if(detect(ID)==false) return false;

	std::string s= std::string();

	for(int x=0;x<FileName->Length;x++)
	{
		s.push_back((char)(byte)FileName[x]);
	}

		LPCSTR filename= s.c_str();

if(width<=0 && height<=0)
{
SS[ID].Swidth=-1;
SS[ID].Sheight=-1;

}
//D3DXCreateTextureFromFile(d3d,filename, &SS[ID].image);

    if(D3DXCreateTextureFromFileExA(
		d3d,
		filename,				// Our texture image!
		width,				// width
		height,				// height
		D3DX_DEFAULT,				// MIP levels
		0,							// usage
		(D3DFORMAT)fmt,				// texture format
		D3DPOOL_MANAGED,			// mem pool
		D3DX_DEFAULT,				// filter
		D3DX_DEFAULT,				// MIP filter
		transparentkey,				// transparent color key
		NULL,						// image info struct
		NULL,						// palette
		&SS[ID].image)!=S_OK)				// the returned texture, if success
	{
		return false;
	
	}
	
	D3DSURFACE_DESC dec;
	
SS[ID].image->GetLevelDesc(0,&dec);
if(width<=0 && height<=0)
{
SS[ID].Swidth=dec.Width;
SS[ID].Sheight=dec.Height;

}
else
{
	float r=1000.0f;
	//ScaleSprite(ID,(float)width/r,(float)height/r);

}

	

SS[ID].center= D3DXVECTOR2(dec.Width/2,dec.Height/2);
SS[ID].file=filename;

return true;

}
bool CoreGex::D2::Sprites::Init()
{
	if(D3DXCreateSprite(d3d, &sprite )!=S_OK)
	{
	return false;
	}

	return true;
}

// Rendering

bool CoreGex::D2::Sprites::SetPosition(int ID,float x, float y)
{
	if(detect(ID)==false)
	{
		return false;
	}

	//SS[ID].sx=x;
	//SS[ID].sy=y;
	SS[ID].position= D3DXVECTOR2(x,y);
	//D3DXMATRIX m,r,s;

    Transform(&SS[ID]);
	//D3DXMatrixTranslation(&m,x,y,z);
	//D3DXMatrixScaling(&s,x,y,z);
	//SS[ID].mat= m+s+r;

	return true;
}




bool CoreGex::D2::Sprites::RenderSprite(int ID,int color)
{
	return RenderSprite(ID,color,color,color,255);
}

bool CoreGex::D2::Sprites::RenderSprite(int ID,int R, int G, int B)
{
	return RenderSprite(ID,R,G,B,255);
}

bool CoreGex::D2::Sprites::RenderSprite(int ID,int R, int G, int B,int A)
{
		if(detect(ID)==false)
	{
		return false;
	}

//	d3d->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	//SS[ID].position.x=SS[ID].sx;
	//SS[ID].position.y=SS[ID].sy;
	//SS[ID].position.z=SS[ID].sz;


	sprite->Begin(tri);

    
	sprite->SetTransform(&SS[ID].mat);
	sprite->Draw(SS[ID].image,NULL,NULL,NULL,D3DCOLOR_ARGB(A,R, G, B));
		
	sprite->Flush();

	sprite->End();
	//d3d->SetRenderState(D3DRS_ALPHATESTENABLE, false);
return true;
}


/// Movement
bool CoreGex::D2::Sprites::Rotate(int ID, float value)
{

	if(detect(ID)==false)
	{
		return false;
	}
	SS[ID].rot=value;
	Transform(&SS[ID]);
	return true;
}

bool CoreGex::D2::Sprites::MoveX(int ID,float value)
{
	if(detect(ID)==false)
	{
		return false;
	}
		SS[ID].position.x+=value;
		Transform(&SS[ID]);
	return true;
}

bool CoreGex::D2::Sprites::MoveY(int ID,float value)
{
	if(detect(ID)==false)
	{
		return false;
	}
	SS[ID].position.y+=value;
	Transform(&SS[ID]);
	return true;
}

float CoreGex::D2::Sprites::GetX(int ID)
{
		if(detect(ID)==false)
	{
		return false;
	}
	return SS[ID].position.x;
}

float CoreGex::D2::Sprites::GetY(int ID)
{
		if(detect(ID)==false)
	{
		return false;
	}
	return SS[ID].position.y;
}


bool CoreGex::D2::Sprites::OnLost(int ID)
{
		if(detect(ID)==false)
	{
		return false;
	}
	sprite->OnLostDevice();
	return true;
}

bool CoreGex::D2::Sprites::OnReset(int ID)
{
		if(detect(ID)==false)
	{
		return false;
	}
sprite->OnResetDevice();
return true;
}

bool CoreGex::D2::Sprites::Destroy(int ID)
{
		if(detect(ID)==false)
	{
		return false;
	}
		SS[ID].image->Release();
		SS.Remove(0);
return true;
}

///////////////////////Newest Functions////////////////////////////////////
/////////////////////// Seen///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////





static D3DXVECTOR3 to3(D3DXVECTOR2 v);
static D3DXVECTOR3 to3(D3DXVECTOR2 v)
{
	return D3DXVECTOR3(v.x,v.y,0.0f);
}

bool CoreGex::D2::Sprites::RenderSprite(int ID,RECTANGLE^ rect,int color)
{
return RenderSprite(ID,rect,color,color,color,255);
}

bool CoreGex::D2::Sprites::RenderSprite(int ID,RECTANGLE^ rect,int R, int G, int B)
{
	return RenderSprite(0,rect,R,G,B,255);
}

bool CoreGex::D2::Sprites::RenderSprite(int ID,RECTANGLE^ rect,int R, int G, int B,int A)
{
	if(detect(ID)==false)
	{
		return false;
	}

		RECT rct;

	rct.bottom= rect->bottom;
	rct.left= rect->left;
	rct.right= rect->right;
	rct.top= rect->top;

	sprite->Begin(tri);
		

			//SpriteRotate2d(ID);
			
	sprite->Draw(SS[ID].image,&rct,NULL,NULL,D3DCOLOR_ARGB(A,R, G, B));

		
	sprite->Flush();
	
	sprite->End();
	
return true;
}


/////////////////////////////////////////////////////////////////////////
//////////////////////////// FRAME^ ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CoreGex::D2::Sprites::RenderSprite(int ID,FRAME^ frame,int color)
{
	return RenderSprite(ID,frame,color,color,color,255);
}

bool CoreGex::D2::Sprites::RenderSprite(int ID,FRAME^ frame,int R, int G, int B)
{
	return RenderSprite(ID,frame,R,G,B,255);
}

bool CoreGex::D2::Sprites::RenderSprite(int ID,FRAME^ frame,int R, int G, int B,int A)
{
	if(detect(ID)==false)
	{
		return false;
	}

		RECTANGLE^ rct;
	
	rct->bottom= frame->y+frame->size;
	rct->left= frame->x;
	rct->right= frame->x+ frame->size;
	rct->top= frame->y;

	
return RenderSprite(ID,rct,R,G,B,A);
}

bool CoreGex::D2::Sprites::SetSpriteData(int ID,int width,int height)
	{
	if(detect(ID)==false)
	{
		return false;
	}
		SS[ID].Swidth=width;
		SS[ID].Sheight=height;
		return true;
	}

int CoreGex::D2::Sprites::GetWidth(int ID)
	{
	if(detect(ID)==false)
	{
		return false;
	}
		return SS[ID].Swidth;
	}

int CoreGex::D2::Sprites::GetHeight(int ID)
	{
			if(detect(ID)==false)
	{
		return false;
	}
		return SS[ID].Sheight;
	}

static bool detect(int input)
{

	if(SS.Count()<input)
	{
		return false;
	}

	if(input<0)
	{
		return false;
	}

	return true;


}

int CoreGex::D2::Sprites::GetItems()
{
	return SS.Count();
}

bool CoreGex::D2::Sprites::DeleteItem(int ID)
{
	if(detect(ID)==false)
	{
		return false;
	}

	SS[ID].image->Release();

return true;

}

bool CoreGex::D2::Sprites::ScaleSprite(int ID,float value)
{
return ScaleSprite(0,value,value);
}

bool CoreGex::D2::Sprites::ScaleSprite(int ID,float x,float y)
{
	if(detect(ID)==false)
	{
		return false;
	}
	SS[ID].scale=D3DXVECTOR2(x,y);
	Transform(&SS[ID]);
	return true;
}

float CoreGex::D2::Sprites::GetScaleX(int ID)
{
	if(detect(ID)==false)
	{
		return -1;
	}
	return SS[ID].scale.x;
}

float CoreGex::D2::Sprites::GetScaleY(int ID)
{
	if(detect(ID)==false)
	{
		return -1;
	}
	return SS[ID].scale.y;
}

bool CoreGex::D2::Sprites::DestroyAll()
{

	for(int x=0;x<GetItems();x++)
	{
		SS[x].image->Release();
	}
	SS.Clear();
	sprite->Release();
	return true;
}