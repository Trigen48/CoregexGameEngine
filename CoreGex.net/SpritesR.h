#pragma once
#include <windows.h>
#include "Units.h"
#include "Sprites.h"
#include "Def.h"
using namespace CoreGex::Maths;



namespace CoreGex
{

	namespace D2
	{


public ref class SpritesRaw
{
public:

	/////////////// Structures  //////////////////////
	SpritesRaw();
	
    /////////////////  Basic calls //////////////////////////
	bool Init();
	int AddNew();
	bool LoadSprite(int ID,System::String ^FileName); // Loaded a sprite file and returns its ID
	bool LoadSprite(int ID,System::String ^FileName, int width, int height); // Loaded a sprite file and returns its ID
	bool LoadSprite(int ID,System::String ^FileName, int width, int height,int transparentkey);
	bool LoadSprite(int ID,System::String ^FileName, int width, int height,int transparentkey,SpriteFormat fmt);

	bool LoadSprite(int ID,BYTE* FileName, ULONG Size); // Loaded a sprite file and returns its ID
	bool LoadSprite(int ID,BYTE* FileName, ULONG Size, int width, int height); // Loaded a sprite file and returns its ID
	bool LoadSprite(int ID,BYTE* FileName, ULONG Size, int width, int height,int transparentkey);
	bool LoadSprite(int ID,BYTE* FileName, ULONG Size, int width, int height,int transparentkey,SpriteFormat fmt);

    bool RenderSprite(int ID,int color);
	bool RenderSprite(int ID,int R, int G, int B);
	bool RenderSprite(int ID,int R, int G, int B,int A);
    bool SetSpriteDraw(int ID,SpriteFlag MODE);
	/////////////////// RECTANGLE^ /////////////////

    bool RenderSprite(int ID,RECTANGLE^ rect,int color);
	bool RenderSprite(int ID,RECTANGLE^ rect,int R, int G, int B);
	bool RenderSprite(int ID,RECTANGLE^ rect,int R, int G, int B,int A);
	
	//bool SetCentre(int ID,int x,int y);
	//////////////////Set Sprite/////////////////////
	bool SetSize(int ID,int width,int height);
	int GetWidth(int ID);
	int GetHeight(int ID); 


	////////////////// FRAME^ ///////////////////////

    bool RenderSprite(int ID,FRAME^ frame,int color);
	bool RenderSprite(int ID,FRAME^ frame,int R, int G, int B);
	bool RenderSprite(int ID,FRAME^ frame,int R, int G, int B,int A);

	bool ScaleSprite(int ID,float value);
	bool ScaleSprite(int ID,float x,float y);

	/////////// Positioning, Scaling and moving ///////////////////
	bool SetPosition(int ID,float x, float y);
	bool MoveX(int ID,float value);
	bool MoveY(int ID,float value);
	bool Rotate(int ID, float value);
    float GetX(int ID);
	float GetY(int ID);
	float GetScaleX(int ID);
	float GetScaleY(int ID);
	////////////////////////////Labling///////////////////////////////
	int GetItems();

	///////////////   Class Checking    ////////////////////////////
	bool OnLost(int ID);
    bool OnReset(int ID);
    bool Destroy(int ID);
	bool DestroyAll();

};

	}
}