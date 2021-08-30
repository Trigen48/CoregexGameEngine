#include "Draw.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <winnt.h>
// include the basic windows header files and the Direct3D header file
#include <windowsx.h>
#include <d3d9.h>
#include "D3dx9core.h"
#include "C.h"
#include "CL.h"

#pragma comment(lib,"d3d9.lib")

#ifdef _DEBUG
  #pragma comment(lib,"d3dx9d.lib")
#else
  #pragma comment(lib,"d3dx9.lib")
#endif


extern int gwidth;
extern int gheight;


//bool SetFont(System::String^ name, int size);

//extern LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
extern LPDIRECT3DDEVICE9 d3d;    // the pointer to the device class
static const DWORD tri_fvf=D3DFVF_XYZRHW|D3DFVF_DIFFUSE;

struct tri_vertex{
    float x, y, z, rhw;  // The transformed(screen space) position for the vertex.
    DWORD colour;        // The vertex colour.
};


struct line_vertex{
    float x, y, z, rhw;  // The transformed(screen space) position for the vertex.
    DWORD colour;        // The vertex colour.
};

struct Fontx
{
int sizeN;
LPCSTR FontN;
ID3DXFont *gfont;
};

cl<Fontx> fntz;


static bool FontSet=false;

static int id=0;

CoreGex::D2::Draw::Draw()
{
	fntz=cl<Fontx>();

	Fontx e;
	e.FontN="Arial";
	e.sizeN=10;
	fntz.Add(e);
}

bool CoreGex::D2::Draw::SetDefaultFont(int Index)
{
	if( fntz.Count() > Index && Index > -1)
	{
			id=Index;
	}
	else
	{
		fntz.Add(Fontx());
		id=Index;
	}
	return true;
}

bool CoreGex::D2::Draw::DrawRect(float x, float y,int height, int width, int R, int G, int B){

d3d->SetFVF(tri_fvf);
static tri_vertex fan1[]={
   {x,y,1,1,D3DCOLOR_XRGB(R, G, B)},{x,  y,1,1,D3DCOLOR_XRGB(R, G, B)},{width,  y,1,1,D3DCOLOR_XRGB(R, G, B)},
   {width,height,1,1,D3DCOLOR_XRGB(R, G, B)},{x,height,1,1,D3DCOLOR_XRGB(R, G, B)},{  x,  y,1,1,D3DCOLOR_XRGB(R, G, B)}
};


   d3d->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,  //PrimitiveType
                                 4,                  //PrimitiveCount
                                 fan1,               //pVertexStreamZeroData
                                 sizeof(tri_vertex));//VertexStreamZeroStride


   return true;
}


bool CoreGex::D2::Draw::DrawRect(float x, float y,int height, int width, int color){

d3d->SetFVF(tri_fvf);
static tri_vertex fan1[]={
   {x,y,1,1,D3DCOLOR_XRGB(color, color, color)},{x,  y,1,1,D3DCOLOR_XRGB(color, color, color)},{width,  y,1,1,D3DCOLOR_XRGB(color, color, color)},
   {width,height,1,1,D3DCOLOR_XRGB(color, color, color)},{x,height,1,1,D3DCOLOR_XRGB(color, color, color)},{  x,  y,1,1,D3DCOLOR_XRGB(color, color, color)}
};


   d3d->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,  //PrimitiveType
                                 4,                  //PrimitiveCount
                                 fan1,               //pVertexStreamZeroData
                                 sizeof(tri_vertex));//VertexStreamZeroStride


   return true;
}

bool CoreGex::D2::Draw::DrawTextA(System::String^ Text, float x , float y,int R,int G, int B)
{
	
int hr=0;

if (FontSet==false)
{
	SetFont(gcnew System::String(fntz[id].FontN),fntz[id].sizeN);
}

                 
    RECT font_rect={0,0,gwidth,gheight};
int font_height=0;
   SetRect(&font_rect,(int)x,(int)y,gwidth,gheight);
   

  fntz[id].gfont->DrawTextA(NULL,        //pSprite
                                GetString(Text),      //pString
                                -1,          //Count
                                &font_rect,  //pRect
                                DT_LEFT|DT_WORDBREAK, //Format,
                                D3DCOLOR_XRGB(R, G, B)); //Color          

 

   return true;
         
}



bool CoreGex::D2::Draw::DrawTextA(System::String^ Text, float x , float y,int color)
{
	int count=0;
int hr=0;

if (FontSet==false)
{
	SetFont(gcnew System::String(fntz[id].FontN),fntz[id].sizeN);
}
                 


RECT font_rect={0,0,gwidth,gheight};
int font_height;
   SetRect(&font_rect,(int)x,(int)y,gwidth,gheight);

   font_height=fntz[id].gfont->DrawTextA(NULL,        //pSprite
                               GetString(Text),      //pString
                                -1,          //Count
                                &font_rect,  //pRect
                                DT_LEFT|DT_WORDBREAK, //Format,
                                D3DCOLOR_XRGB(color, color, color)); //Color       
   
   return true;
         
}

bool CoreGex::D2::Draw::SetTextSize(int size)
{
fntz[id].sizeN=size;
 D3DXCreateFontA(d3d,fntz[id].sizeN, 0,fntz[id].sizeN,1,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH|FF_DONTCARE,fntz[id].FontN, &fntz[id].gfont);     
     FontSet=true;
	return true;
}


bool CoreGex::D2::Draw::SetTextName(System::String^ name)
{

	fntz[id].FontN=GetString(name);
 D3DXCreateFontA(d3d,fntz[id].sizeN, 0,fntz[id].sizeN,1,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH|FF_DONTCARE,fntz[id].FontN, &fntz[id].gfont);     
     FontSet=true;
	return true;
}

bool CoreGex::D2::Draw::SetFont(System::String^ name, int size)
{

	return SetFont(id,name,size);
}

bool CoreGex::D2::Draw::SetFont(int index, System::String^ name, int size)
{

	if( fntz.Count() > index && index > -1)
	{
			//id=Index;
	}
	else
	{
		fntz.Add(Fontx());
		//id=index;
	}

fntz[index].sizeN=size;
fntz[index].FontN=GetString(name);



 D3DXCreateFontA(d3d,fntz[index].sizeN, 0,fntz[index].sizeN,1,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH|FF_DONTCARE,fntz[index].FontN, &fntz[index].gfont);     
 
 FontSet=true;

 return true;
}

bool CoreGex::D2::Draw::drawLine(float x1, float y1, float x2, float y2, int color)
{
d3d->SetFVF(tri_fvf);
	line_vertex xx[]={{x1,y1,1,1,D3DCOLOR_XRGB(color, color, color)},{x2,y2,1,1,D3DCOLOR_XRGB(color, color, color)}};
 

      d3d->DrawPrimitiveUP(D3DPT_LINELIST,         //PrimitiveType
                                    2,              //PrimitiveCount
                                    xx,            //pVertexStreamZeroData
                                    sizeof(line_vertex));   //VertexStreamZeroStride

	  return true;
}


bool CoreGex::D2::Draw::drawLine(float x1, float y1, float x2, float y2, int R,int G, int B)
{
d3d->SetFVF(tri_fvf);
	line_vertex xx[]={{x1,y1,1,1,D3DCOLOR_XRGB(R, G, B)},{x2,y2,1,1,D3DCOLOR_XRGB(R, G, B)}};
 

      d3d->DrawPrimitiveUP(D3DPT_LINELIST,         //PrimitiveType
                                    2,              //PrimitiveCount
                                    xx,            //pVertexStreamZeroData
                                    sizeof(line_vertex));   //VertexStreamZeroStride

	  return true;
}


bool CoreGex::D2::Draw::OnLost()
{

	for(int x=0;x<fntz.Count();x++)
	{
		

		fntz[x].gfont->OnLostDevice();

	}
	return true;
}

bool CoreGex::D2::Draw::OnReset()
{
	for(int x=0;x<fntz.Count();x++)
	{
		

		fntz[x].gfont->OnResetDevice();

	}

	return true;
}

bool CoreGex::D2::Draw::Destroy()
{
	//fntz[id].gfont->;
	for(int x=0;x<fntz.Count();x++)
	{
		
		fntz[x].gfont->Release();
	}

	fntz.Clear();
	return true;
}