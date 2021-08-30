#include "Sprite.h"
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
extern LPDIRECT3DDEVICE9 d3d;    // the pointer to the device class

CoreGex::D2::Sprite::Sprite()
{

	data= new SpriteData();	
	_IsOk=false;

	if(D3DXCreateSprite(d3d, &data->sprite)==S_OK)
	{
		data->scale= D3DXVECTOR2(1,1);
		data->position= D3DXVECTOR2(0,0);
		data->rot=0;
		Transform();
		_IsOk=true;
	}

	tri_fvf=D3DFVF_XYZRHW|D3DFVF_DIFFUSE;
	tri=D3DXSPRITE_ALPHABLEND;
}
bool CoreGex::D2::Sprite::IsLoaded()
{
	return _IsOk;
}

void CoreGex::D2::Sprite::Transform()
{
	D3DXMatrixTransformation2D(&data->mat,NULL,NULL,&data->scale,&data->center,data->rot,&data->position);
	data->sprite->SetTransform(&data->mat);
}

bool CoreGex::D2::Sprite::SetSpriteDraw(SpriteFlag MODE)
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
bool CoreGex::D2::Sprite::LoadSprite(System::String ^FileName )
{
	return LoadSprite(FileName,D3DX_DEFAULT,D3DX_DEFAULT,255,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::Sprite::LoadSprite(System::String ^FileName, int width, int height)
{
	return LoadSprite(FileName,width,height,255,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::Sprite::LoadSprite(System::String ^FileName, int width, int height,int transparentkey)
{
	return LoadSprite(FileName,width,height,transparentkey,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::Sprite::LoadSprite(System::String ^FileName, int width, int height,int transparentkey,SpriteFormat fmt)
{

	std::string s= std::string();

	for(int x=0;x<FileName->Length;x++)
	{
		s.push_back((char)(byte)FileName[x]);
	}

	LPCSTR filename= s.c_str();

	if(width<=0 && height<=0)
	{
		data->Swidth=-1;
		data->Sheight=-1;
	}

    if(D3DXCreateTextureFromFile(d3d,filename,&data->image)!=S_OK)	
	{
		return false;
	}
	
	D3DSURFACE_DESC dec;
	
	data->image->GetLevelDesc(0,&dec);
	if(width<=0 || height<=0)
	{
		if(width<=0) data->Swidth=dec.Width;
		if(height<0) data->Sheight=dec.Height;
		data->center= D3DXVECTOR2(dec.Width/2,dec.Height/2);
	}
	else
	{
		float tx=1,ty=1;
		if(width!= gwidth || height!=gheight)
		{
			tx=(float)width/ (float)dec.Width;
			ty=(float)height/(float)dec.Height;
			//ScaleSprite(tx,ty);
			data->center= D3DXVECTOR2((dec.Width/2)*tx,(dec.Height/2)*ty);
		}
		else
		{
			if(width== gwidth)
			{
				tx=(float)width/ (float)dec.Width;
			}

			if(height==gheight)
			{
				ty=(float)height/(float)dec.Height;
			}
			//ScaleSprite(tx,ty);
			data->center= D3DXVECTOR2(dec.Width/2,dec.Height/2);
		}

		data->Swidth=width;
		data->Sheight=height;
		ScaleSprite(tx,ty);
	}
	
	return true;

}


// Load Sprite In Bytes
bool CoreGex::D2::Sprite::LoadSprite(BYTE* FileName, ULONG Size )
{
	return LoadSprite(FileName,Size,D3DX_DEFAULT,D3DX_DEFAULT,255,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::Sprite::LoadSprite(BYTE* FileName, ULONG Size, int width, int height)
{
	return LoadSprite(FileName,Size,width,height,255,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::Sprite::LoadSprite(BYTE* FileName, ULONG Size, int width, int height,int transparentkey)
{
	return LoadSprite(FileName,Size,width,height,transparentkey,SpriteFormat::UNKNOWN);
}

bool CoreGex::D2::Sprite::LoadSprite(BYTE* FileName, ULONG Size, int width, int height,int transparentkey,SpriteFormat fmt)
{

	if(width<=0 && height<=0)
	{
		data->Swidth=-1;
		data->Sheight=-1;
	}

	if(D3DXCreateTextureFromFileInMemory(
			d3d,
			FileName,					// Our texture image!
			(UINT)Size,					// FileSize
			&data->image)!=S_OK)		// the returned texture, if success
		{
			return false;
	
		}
	
	D3DSURFACE_DESC dec;


	data->image->GetLevelDesc(0,&dec);
	if(width<=0 || height<=0)
	{

		if(width<=0) {data->Swidth=dec.Width;}
		if(height<0) {data->Sheight=dec.Height;}
		data->center= D3DXVECTOR2(dec.Width/2,dec.Height/2);
	}
	else
	{
		//float r=1000.0f;
		float tx=1,ty=1;
	//(float)width/
		//tx=(((float)dec.Width/(float)gwidth )*(float)width)/1000.0f;
	//	ty=(((float)dec.Height/(float)gheight )*(float)height)/1000.0f;


		if(width!= gwidth || height!=gheight)
		{
		
			tx=(float)width/ (float)dec.Width;
			ty=(float)height/(float)dec.Height;


				//ScaleSprite(tx,ty);
			data->center= D3DXVECTOR2((dec.Width/2)*tx,(dec.Height/2)*ty);
		}
		else
		{

		
			if(width== gwidth)
			{

				tx=(float)width/ (float)dec.Width;
			}

			if(height==gheight)
			{
				ty=(float)height/(float)dec.Height;
			}


			//ScaleSprite(tx,ty);
			data->center= D3DXVECTOR2(dec.Width/2,dec.Height/2);
		}

		data->Swidth=width;
		data->Sheight=height;
		ScaleSprite(tx,ty);
	}
	
	return true;

}

// Rendering

bool CoreGex::D2::Sprite::SetPosition(float x, float y)
{
	data->position= D3DXVECTOR2(x,y);
    Transform();
	return true;
}

bool CoreGex::D2::Sprite::RenderSprite(int color)
{
	return RenderSprite(color,color,color,255);
}

bool CoreGex::D2::Sprite::RenderSprite(int R, int G, int B)
{
	return RenderSprite(R,G,B,255);
}

bool CoreGex::D2::Sprite::RenderSprite(int R, int G, int B,int A)
{


	data->sprite->Begin(tri);

    //Transform(&data);
	data->sprite->SetTransform(&data->mat);
	data->sprite->Draw(data->image,NULL,NULL,NULL,D3DCOLOR_ARGB(A,R, G, B));
		
	data->sprite->Flush();

	data->sprite->End();

	return true;
}


/// Movement
bool CoreGex::D2::Sprite::Rotate( float value)
{
	data->rot= value;
	Transform();
	return true;
}

bool CoreGex::D2::Sprite::MoveX(float value)
{

	data->position.x+=value;
	Transform();
	return true;
}

bool CoreGex::D2::Sprite::MoveY(float value)
{
	data->position.y+=value;
	Transform();
	return true;
}

float CoreGex::D2::Sprite::GetX()
{
	return data->position.x;
}

float CoreGex::D2::Sprite::GetY()
{
	return data->position.y;
}


bool CoreGex::D2::Sprite::OnLost()
{
	data->sprite->OnLostDevice();
	return true;
}

bool CoreGex::D2::Sprite::OnReset()
{
	data->sprite->OnResetDevice();
	return true;
}

bool CoreGex::D2::Sprite::Destroy()
{
	data->image->Release();
	data->sprite->Release();
	return true;
}

///////////////////////Newest Functions////////////////////////////////////
/////////////////////// Seen///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

bool CoreGex::D2::Sprite::RenderSprite(RECTANGLE^ rect,int color)
{
return RenderSprite(rect,color,color,color,255);
}

bool CoreGex::D2::Sprite::RenderSprite(RECTANGLE^ rect,int R, int G, int B)
{
	return RenderSprite(rect,R,G,B,255);
}

bool CoreGex::D2::Sprite::RenderSprite(RECTANGLE^ rect,int R, int G, int B,int A)
{

	RECT rct;

	rct.bottom= rect->bottom;
	rct.left= rect->left;
	rct.right= rect->right;
	rct.top= rect->top;

	data->sprite->Begin(tri);
		
    //Transform(&data);
	data->sprite->SetTransform(&data->mat);

	data->sprite->Draw(data->image,&rct,NULL,NULL,D3DCOLOR_ARGB(A,R, G, B));

		
	data->sprite->Flush();
	
	data->sprite->End();
	
return true;
}


/////////////////////////////////////////////////////////////////////////
//////////////////////////// FRAME^ ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CoreGex::D2::Sprite::RenderSprite(FRAME^ frame,int color)
{
	return RenderSprite(frame,color,color,color,255);
}

bool CoreGex::D2::Sprite::RenderSprite(FRAME^ frame,int R, int G, int B)
{
	return RenderSprite(frame,R,G,B,255);
}

bool CoreGex::D2::Sprite::RenderSprite(FRAME^ frame,int R, int G, int B,int A)
{

	RECTANGLE^ rct;
	
	rct->bottom= frame->y+frame->size;
	rct->left= frame->x;
	rct->right= frame->x+ frame->size;
	rct->top= frame->y;

	
return RenderSprite(rct,R,G,B,A);
}

bool CoreGex::D2::Sprite::SetSize(int width,int height)
{
	D3DSURFACE_DESC dec;
	data->image->GetLevelDesc(0,&dec);

	if(width<=0 || height<=0)
	{
		if(width<=0) data->Swidth=dec.Width;
		if(height<0) data->Sheight=dec.Height;
		data->center= D3DXVECTOR2(dec.Width/2,dec.Height/2);

	}
	else
	{

		float tx=1,ty=1;

		if(width!= gwidth || height!=gheight)
		{
		
			tx=(float)width/ (float)dec.Width;
			ty=(float)height/(float)dec.Height;
		

			ScaleSprite(tx,ty);
			data->center= D3DXVECTOR2((dec.Width/2)*tx,(dec.Height/2)*ty);
		}
		else
		{
			if(width== gwidth)
			{
				tx=(float)width/ (float)dec.Width;
			}
			if(height==gheight)
			{
				ty=(float)height/(float)dec.Height;
			}
			ScaleSprite(tx,ty);
			data->center= D3DXVECTOR2(dec.Width/2,dec.Height/2);
		}

	}

	return true;
}

int CoreGex::D2::Sprite::GetWidth()
{
	return data->Swidth;
}

int CoreGex::D2::Sprite::GetHeight()
{
	return data->Sheight;
}


bool CoreGex::D2::Sprite::ScaleSprite(float value)
{
	return ScaleSprite(value,value);
}

bool CoreGex::D2::Sprite::ScaleSprite(float x,float y)
{
	data->scale=D3DXVECTOR2(x,y);
	Transform();
	return true;
}

float CoreGex::D2::Sprite::GetScaleX()
{
	return data->scale.x;
}

float CoreGex::D2::Sprite::GetScaleY()
{
	return data->scale.y;
}
