#include "SpritesR.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <winnt.h>
// include the basic windows header files and the Direct3D header file
#include <windowsx.h>
#include <d3d9.h>
#include "D3dx9core.h"
#include "CL.h"
#include "Transform.h"

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


static int trigen=0;

//SpriteData *SSR;

static cl<SpriteData>SSR;

static DWORD tri=D3DXSPRITE_ALPHABLEND;
static bool detect(int input);
static bool Recreate();

CoreGex::D2::SpritesRaw::SpritesRaw()
{
	


}

int CoreGex::D2::SpritesRaw::AddNew()
{
	SpriteData p;
	ZeroMemory(&p, sizeof(p));
	D3DXCreateSprite(d3d, &p.sprite);
	p.scale= D3DXVECTOR2(1,1);
	p.position= D3DXVECTOR2(0,0);
	p.rot=0;
	
	Transform(&p);
	SSR.Add(p);
	return SSR.Count()-1;
}

bool CoreGex::D2::SpritesRaw::SetSpriteDraw(int ID, SpriteFlag MODE)
{
	switch (MODE)
	{
	case SpriteFlag::DONOTSAVESTATE:
		tri = D3DXSPRITE_DONOTSAVESTATE;
		break;

	case SpriteFlag::DONOTMODIFY_RENDERSTATE:
		tri = D3DXSPRITE_DONOTMODIFY_RENDERSTATE;
		break;

	case SpriteFlag::OBJECTSPACE:
		tri = D3DXSPRITE_OBJECTSPACE;
		break;


	case SpriteFlag::BILLBOARD:
		tri = D3DXSPRITE_BILLBOARD;
		break;


	case SpriteFlag::ALPHABLEND:
		tri = D3DXSPRITE_ALPHABLEND;
		break;


	case SpriteFlag::SORT_TEXTURE:
		tri = D3DXSPRITE_SORT_TEXTURE;
		break;


	case SpriteFlag::SORT_DEPTH_FRONTTOBACK:
		tri = D3DXSPRITE_SORT_DEPTH_FRONTTOBACK;
		break;


	case SpriteFlag::SORT_DEPTH_BACKTOFRONT:
		tri = D3DXSPRITE_SORT_DEPTH_BACKTOFRONT;
		break;


	case SpriteFlag::DO_NOT_ADDREF_TEXTURE:
		tri = D3DXSPRITE_DO_NOT_ADDREF_TEXTURE;
		break;


	default:
		tri = D3DXSPRITE_ALPHABLEND;
		break;
	}

	return true;
}
bool CoreGex::D2::SpritesRaw::LoadSprite(int ID,System::String ^FileName )
{
	return LoadSprite(ID,FileName,D3DX_DEFAULT,D3DX_DEFAULT,255,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::SpritesRaw::LoadSprite(int ID,System::String ^FileName, int width, int height)
{
	return LoadSprite(ID,FileName,width,height,255,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::SpritesRaw::LoadSprite(int ID,System::String ^FileName, int width, int height,int transparentkey)
{
	return LoadSprite(ID,FileName,width,height,transparentkey,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::SpritesRaw::LoadSprite(int ID, System::String^ FileName, int width, int height, int transparentkey, SpriteFormat fmt)
{

	if (SSR.Count() == ID)
	{
		AddNew();
	}
	else if (detect(ID) == false) return false;

	std::string s = std::string();

	for (int x = 0; x < FileName->Length; x++)
	{
		s.push_back((char)(byte)FileName[x]);
	}

	LPCSTR filename = s.c_str();

	if (width <= 0 && height <= 0)
	{
		SSR[ID].Swidth = -1;
		SSR[ID].Sheight = -1;

	}
	//D3DXCreateTextureFromFile(d3d,filename, &SSR[ID].image);

	//D3DXCreateTextureFromFile(

	if (D3DXCreateTextureFromFile(
		d3d,
		filename,				// Our texture image!
		&SSR[ID].image) != S_OK)				// the returned texture, if success
	{
		return false;

	}

	D3DSURFACE_DESC dec;

	SSR[ID].image->GetLevelDesc(0, &dec);
	if (width <= 0 || height <= 0)
	{

		if (width <= 0) SSR[ID].Swidth = dec.Width;
		if (height < 0) SSR[ID].Sheight = dec.Height;
		SSR[ID].center = D3DXVECTOR2(dec.Width / 2, dec.Height / 2);
	}
	else
	{
		//float r=1000.0f;
		float tx = 1, ty = 1;
		//(float)width/
			//tx=(((float)dec.Width/(float)gwidth )*(float)width)/1000.0f;
		//	ty=(((float)dec.Height/(float)gheight )*(float)height)/1000.0f;


		if (width != gwidth || height != gheight)
		{

			tx = (float)width / (float)dec.Width;
			ty = (float)height / (float)dec.Height;


			//ScaleSprite(ID,tx,ty);
			SSR[ID].center = D3DXVECTOR2((dec.Width / 2) * tx, (dec.Height / 2) * ty);
		}
		else
		{


			if (width == gwidth)
			{

				tx = (float)width / (float)dec.Width;
			}

			if (height == gheight)
			{
				ty = (float)height / (float)dec.Height;
			}


			//ScaleSprite(ID,tx,ty);
			SSR[ID].center = D3DXVECTOR2(dec.Width / 2, dec.Height / 2);
		}

		SSR[ID].Swidth = width;
		SSR[ID].Sheight = height;
		ScaleSprite(ID, tx, ty);
	}

	return true;
}


// Load Sprite In Bytes
bool CoreGex::D2::SpritesRaw::LoadSprite(int ID,BYTE* FileName, ULONG Size )
{
	return LoadSprite(ID,FileName,Size,D3DX_DEFAULT,D3DX_DEFAULT,255,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::SpritesRaw::LoadSprite(int ID,BYTE* FileName, ULONG Size, int width, int height)
{
	return LoadSprite(ID,FileName,Size,width,height,255,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::SpritesRaw::LoadSprite(int ID,BYTE* FileName, ULONG Size, int width, int height,int transparentkey)
{
	return LoadSprite(ID,FileName,Size,width,height,transparentkey,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::SpritesRaw::LoadSprite(int ID, BYTE* FileName, ULONG Size, int width, int height, int transparentkey, SpriteFormat fmt)
{

	if (SSR.Count() == ID)
	{
		AddNew();
	}
	else if (detect(ID) == false) return false;


	if (width <= 0 && height <= 0)
	{
		SSR[ID].Swidth = -1;
		SSR[ID].Sheight = -1;

	}
	//2289436780

	
	UINT loadResult = D3DXCreateTextureFromFileInMemory(
		d3d,
		FileName,					// Our texture image!
		(UINT)Size,					// FileSize
		&SSR[ID].image);

	//D3DXCreateTextureFromFile(d3d,filename, &SSR[ID].image);
	if (loadResult != S_OK)		// the returned texture, if success
	{
		return false;

	}

	D3DSURFACE_DESC dec;

	SSR[ID].image->GetLevelDesc(0, &dec);
	if (width <= 0 || height <= 0)
	{

		if (width <= 0) SSR[ID].Swidth = dec.Width;
		if (height < 0) SSR[ID].Sheight = dec.Height;
		SSR[ID].center = D3DXVECTOR2(dec.Width / 2, dec.Height / 2);
	}
	else
	{
		//float r=1000.0f;
		float tx = 1, ty = 1;
		//(float)width/
			//tx=(((float)dec.Width/(float)gwidth )*(float)width)/1000.0f;
		//	ty=(((float)dec.Height/(float)gheight )*(float)height)/1000.0f;


		if (width != gwidth || height != gheight)
		{

			tx = (float)width / (float)dec.Width;
			ty = (float)height / (float)dec.Height;


			//ScaleSprite(ID,tx,ty);
			SSR[ID].center = D3DXVECTOR2((dec.Width / 2) * tx, (dec.Height / 2) * ty);
		}
		else
		{


			if (width == gwidth)
			{

				tx = (float)width / (float)dec.Width;
			}

			if (height == gheight)
			{
				ty = (float)height / (float)dec.Height;
			}


			//ScaleSprite(ID,tx,ty);
			SSR[ID].center = D3DXVECTOR2(dec.Width / 2, dec.Height / 2);
		}

		SSR[ID].Swidth = width;
		SSR[ID].Sheight = height;
		ScaleSprite(ID, tx, ty);
	}

	return true;

}

bool CoreGex::D2::SpritesRaw::Init()
{
	/*if(D3DXCreateSprite(d3d, &SSR[ID].sprite )!=S_OK)
	{
	return false;
	}*/

	return true;
}

// Rendering

bool CoreGex::D2::SpritesRaw::SetPosition(int ID,float x, float y)
{
	if(detect(ID)==false)
	{
		return false;
	}

	SSR[ID].position= D3DXVECTOR2(x,y);
    Transform(&SSR[ID]);

	return true;
}




bool CoreGex::D2::SpritesRaw::RenderSprite(int ID,int color)
{
	return RenderSprite(ID,color,color,color,255);
}

bool CoreGex::D2::SpritesRaw::RenderSprite(int ID,int R, int G, int B)
{
	return RenderSprite(ID,R,G,B,255);
}

bool CoreGex::D2::SpritesRaw::RenderSprite(int ID,int R, int G, int B,int A)
{
		if(detect(ID)==false)
	{
		return false;
	}

//	d3d->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	//SSR[ID].position.x=SSR[ID].sx;
	//SSR[ID].position.y=SSR[ID].sy;
	//SSR[ID].position.z=SSR[ID].sz;


	SSR[ID].sprite->Begin(tri);

    //Transform(&SSR[ID]);
	SSR[ID].sprite->SetTransform(&SSR[ID].mat);
	SSR[ID].sprite->Draw(SSR[ID].image,NULL,NULL,NULL,D3DCOLOR_ARGB(A,R, G, B));
		
	SSR[ID].sprite->Flush();

	SSR[ID].sprite->End();
	//d3d->SetRenderState(D3DRS_ALPHATESTENABLE, false);
return true;
}


/// Movement
bool CoreGex::D2::SpritesRaw::Rotate(int ID, float value)
{

	if(detect(ID)==false)
	{
		return false;
	}
	SSR[ID].rot= value;
	Transform(&SSR[ID]);
	return true;
}

bool CoreGex::D2::SpritesRaw::MoveX(int ID,float value)
{
	if(detect(ID)==false)
	{
		return false;
	}
		SSR[ID].position.x+=value;
		Transform(&SSR[ID]);
	return true;
}

bool CoreGex::D2::SpritesRaw::MoveY(int ID,float value)
{
	if(detect(ID)==false)
	{
		return false;
	}
	SSR[ID].position.y+=value;
	Transform(&SSR[ID]);
	return true;
}

float CoreGex::D2::SpritesRaw::GetX(int ID)
{
		if(detect(ID)==false)
	{
		return false;
	}
	return SSR[ID].position.x;
}

float CoreGex::D2::SpritesRaw::GetY(int ID)
{
		if(detect(ID)==false)
	{
		return false;
	}
	return SSR[ID].position.y;
}


bool CoreGex::D2::SpritesRaw::OnLost(int ID)
{
		if(detect(ID)==false)
	{
		return false;
	}
	SSR[ID].sprite->OnLostDevice();
	return true;
}

bool CoreGex::D2::SpritesRaw::OnReset(int ID)
{
		if(detect(ID)==false)
	{
		return false;
	}
SSR[ID].sprite->OnResetDevice();
return true;
}

bool CoreGex::D2::SpritesRaw::Destroy(int ID)
{
		if(detect(ID)==false)
	{
		return false;
	}
		SSR[ID].image->Release();
		SSR[ID].sprite->Release();
		SSR.Remove(ID);
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

bool CoreGex::D2::SpritesRaw::RenderSprite(int ID,RECTANGLE^ rect,int color)
{
return RenderSprite(ID,rect,color,color,color,255);
}

bool CoreGex::D2::SpritesRaw::RenderSprite(int ID,RECTANGLE^ rect,int R, int G, int B)
{
	return RenderSprite(0,rect,R,G,B,255);
}

bool CoreGex::D2::SpritesRaw::RenderSprite(int ID, RECTANGLE^ rect, int R, int G, int B, int A)
{
	if (detect(ID) == false)
	{
		return false;
	}

	RECT rct;

	rct.bottom = rect->bottom;
	rct.left = rect->left;
	rct.right = rect->right;
	rct.top = rect->top;

	SSR[ID].sprite->Begin(tri);

	//Transform(&SSR[ID]);
	SSR[ID].sprite->SetTransform(&SSR[ID].mat);

	SSR[ID].sprite->Draw(SSR[ID].image, &rct, NULL, NULL, D3DCOLOR_ARGB(A, R, G, B));


	SSR[ID].sprite->Flush();

	SSR[ID].sprite->End();

	return true;
}


/////////////////////////////////////////////////////////////////////////
//////////////////////////// FRAME^ ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CoreGex::D2::SpritesRaw::RenderSprite(int ID,FRAME^ frame,int color)
{
	return RenderSprite(ID,frame,color,color,color,255);
}

bool CoreGex::D2::SpritesRaw::RenderSprite(int ID,FRAME^ frame,int R, int G, int B)
{
	return RenderSprite(ID,frame,R,G,B,255);
}

bool CoreGex::D2::SpritesRaw::RenderSprite(int ID, FRAME^ frame, int R, int G, int B, int A)
{
	if (detect(ID) == false)
	{
		return false;
	}

	RECTANGLE^ rct;

	rct->bottom = frame->y + frame->size;
	rct->left = frame->x;
	rct->right = frame->x + frame->size;
	rct->top = frame->y;


	return RenderSprite(ID, rct, R, G, B, A);
}

bool CoreGex::D2::SpritesRaw::SetSize(int ID, int width, int height)
{
	if (detect(ID) == false)
	{
		return false;
	}

	D3DSURFACE_DESC dec;


	SSR[ID].image->GetLevelDesc(0, &dec);

	if (width <= 0 || height <= 0)

	{


		if (width <= 0) SSR[ID].Swidth = dec.Width;

		if (height < 0) SSR[ID].Sheight = dec.Height;

		SSR[ID].center = D3DXVECTOR2(dec.Width / 2, dec.Height / 2);

	}

	else

	{

		//float r=1000.0f;

		float tx = 1, ty = 1;

		if (width != gwidth || height != gheight)
		{

			tx = (float)width / (float)dec.Width;
			ty = (float)height / (float)dec.Height;


			ScaleSprite(ID, tx, ty);
			SSR[ID].center = D3DXVECTOR2((dec.Width / 2) * tx, (dec.Height / 2) * ty);
		}
		else
		{


			if (width == gwidth)
			{

				tx = (float)width / (float)dec.Width;
			}




			if (height == gheight)
			{
				ty = (float)height / (float)dec.Height;
			}


			ScaleSprite(ID, tx, ty);
			SSR[ID].center = D3DXVECTOR2(dec.Width / 2, dec.Height / 2);
		}


		//SSR[ID].Swidth=width;
	//	SSR[ID].Sheight=height;
		//return true;
	}

	return true;
}

int CoreGex::D2::SpritesRaw::GetWidth(int ID)
{
	if (detect(ID) == false)
	{
		return false;
	}
	return SSR[ID].Swidth;
}

int CoreGex::D2::SpritesRaw::GetHeight(int ID)
{
	if (detect(ID) == false)
	{
		return false;
	}
	return SSR[ID].Sheight;
}

static bool detect(int input)
{

	if(SSR.Count()<input)
	{
		return false;
	}

	if(input<0)
	{
		return false;
	}

	return true;


}

int CoreGex::D2::SpritesRaw::GetItems()
{
	return SSR.Count();
}

bool CoreGex::D2::SpritesRaw::ScaleSprite(int ID,float value)
{
return ScaleSprite(0,value,value);
}

bool CoreGex::D2::SpritesRaw::ScaleSprite(int ID,float x,float y)
{
	if(detect(ID)==false)
	{
		return false;
	}
	SSR[ID].scale=D3DXVECTOR2(x,y);
	Transform(&SSR[ID]);
	return true;
}

float CoreGex::D2::SpritesRaw::GetScaleX(int ID)
{
	if(detect(ID)==false)
	{
		return -1;
	}
	return SSR[ID].scale.x;
}

float CoreGex::D2::SpritesRaw::GetScaleY(int ID)
{
	if(detect(ID)==false)
	{
		return -1;
	}
	return SSR[ID].scale.y;
}

bool CoreGex::D2::SpritesRaw::DestroyAll()
{

	for (int x = 0; x < GetItems(); x++)
	{

		//if (SSR[x].image != NULL)
			SSR[x].image->Release();

		//if (SSR[x].sprite != NULL)
			SSR[x].sprite->Release();
	}
	SSR.Clear();
	//SSR[ID].sprite->Release();
	return true;
}