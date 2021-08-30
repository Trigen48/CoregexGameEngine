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


		public ref class Sprite
		{
		public:

			/////////////// Structures  //////////////////////
			Sprite();
	
			/////////////////  Basic calls //////////////////////////
			bool LoadSprite(System::String ^FileName); // Loaded a sprite file and returns its ID
			bool LoadSprite(System::String ^FileName, int width, int height); // Loaded a sprite file and returns its ID
			bool LoadSprite(System::String ^FileName, int width, int height,int transparentkey);
			bool LoadSprite(System::String ^FileName, int width, int height,int transparentkey,SpriteFormat fmt);

			bool LoadSprite(BYTE* FileName, ULONG Size); // Loaded a sprite file and returns its ID
			bool LoadSprite(BYTE* FileName, ULONG Size, int width, int height); // Loaded a sprite file and returns its ID
			bool LoadSprite(BYTE* FileName, ULONG Size, int width, int height,int transparentkey);
			bool LoadSprite(BYTE* FileName, ULONG Size, int width, int height,int transparentkey,SpriteFormat fmt);

			bool RenderSprite(int color);
			bool RenderSprite(int R, int G, int B);
			bool RenderSprite(int R, int G, int B,int A);
			bool SetSpriteDraw(SpriteFlag MODE);
			/////////////////// RECTANGLE^ /////////////////

			bool RenderSprite(RECTANGLE^ rect,int color);
			bool RenderSprite(RECTANGLE^ rect,int R, int G, int B);
			bool RenderSprite(RECTANGLE^ rect,int R, int G, int B,int A);
	
			//bool SetCentre(int x,int y);
			//////////////////Set Sprite/////////////////////
			bool SetSize(int width,int height);
			int GetWidth();
			int GetHeight(); 


			////////////////// FRAME^ ///////////////////////

			bool RenderSprite(FRAME^ frame,int color);
			bool RenderSprite(FRAME^ frame,int R, int G, int B);
			bool RenderSprite(FRAME^ frame,int R, int G, int B,int A);

			bool ScaleSprite(float value);
			bool ScaleSprite(float x,float y);

			/////////// Positioning, Scaling and moving ///////////////////
			bool SetPosition(float x, float y);
			bool MoveX(float value);
			bool MoveY(float value);
			bool Rotate( float value);
			float GetX();
			float GetY();
			float GetScaleX();
			float GetScaleY();
			bool IsLoaded();
			////////////////////////////Labling///////////////////////////////


			///////////////   Class Checking    ////////////////////////////
			bool OnLost();
			bool OnReset();
			bool Destroy();

		private:
			SpriteData* data;
			DWORD tri_fvf;
			DWORD tri;
			void Transform();
			bool _IsOk;
	
		};

	}
}