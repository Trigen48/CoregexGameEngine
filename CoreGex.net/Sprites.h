#pragma once
#include <windows.h>
#include "Units.h"
#include "Def.h"

using namespace CoreGex::Maths;



namespace CoreGex
{

	namespace D2
	{

		[System::FlagsAttribute]
		public enum class SpriteFlag
		{
			DONOTSAVESTATE = 0,
			DONOTMODIFY_RENDERSTATE = 1,
			OBJECTSPACE = 2,
			BILLBOARD = 3,
			ALPHABLEND = 4,
			SORT_TEXTURE = 5,
			SORT_DEPTH_FRONTTOBACK = 6,
			SORT_DEPTH_BACKTOFRONT = 7,
			DO_NOT_ADDREF_TEXTURE = 8,
		};

		[System::FlagsAttribute]
		public enum class SpriteFormat
		{
			UNKNOWN = 0,
			DF32A = 21,
			DF32X = 22,

			D16S = 23,
			D16A = 25,
			DF24S = 75,
			DF24X = 77,
			DF16 = 80,
		};


		public ref class Sprites
		{
		public:

			/////////////// Structures  //////////////////////
			Sprites();

			/////////////////  Basic calls //////////////////////////

			int AddNew();
			bool LoadSprite(int ID, System::String^ FileName); // Loaded a sprite file and returns its ID
			bool LoadSprite(int ID, System::String^ FileName, int width, int height); // Loaded a sprite file and returns its ID
			bool LoadSprite(int ID, System::String^ FileName, int width, int height, int transparentkey);
			bool LoadSprite(int ID, System::String^ FileName, int width, int height, int transparentkey, SpriteFormat fmt);

			bool LoadSprite(int ID, BYTE* FileName, ULONG Size); // Loaded a sprite file and returns its ID
			bool LoadSprite(int ID, BYTE* FileName, ULONG Size, int width, int height); // Loaded a sprite file and returns its ID
			bool LoadSprite(int ID, BYTE* FileName, ULONG Size, int width, int height, int transparentkey);
			bool LoadSprite(int ID, BYTE* FileName, ULONG Size, int width, int height, int transparentkey, SpriteFormat fmt);

			bool RenderSprite(int ID, int color);
			bool RenderSprite(int ID, int R, int G, int B);
			bool RenderSprite(int ID, int R, int G, int B, int A);
			bool SetSpriteDraw(int ID, SpriteFlag MODE);
			/////////////////// RECTANGLE^ /////////////////

			bool RenderSprite(int ID, RECTANGLE^ rect, int color);
			bool RenderSprite(int ID, RECTANGLE^ rect, int R, int G, int B);
			bool RenderSprite(int ID, RECTANGLE^ rect, int R, int G, int B, int A);

			//bool SetCentre(int ID,int x,int y);
			//////////////////Set Sprite/////////////////////
			bool SetSpriteData(int ID, int width, int height);
			int GetWidth(int ID);
			int GetHeight(int ID);


			////////////////// FRAME^ ///////////////////////

			bool RenderSprite(int ID, FRAME^ frame, int color);
			bool RenderSprite(int ID, FRAME^ frame, int R, int G, int B);
			bool RenderSprite(int ID, FRAME^ frame, int R, int G, int B, int A);

			bool ScaleSprite(int ID, float value);
			bool ScaleSprite(int ID, float x, float y);

			/////////// Positioning, Scaling and moving ///////////////////
			bool SetPosition(int ID, float x, float y);
			bool MoveX(int ID, float value);
			bool MoveY(int ID, float value);
			bool Rotate(int ID, float value);
			float GetX(int ID);
			float GetY(int ID);
			float GetScaleX(int ID);
			float GetScaleY(int ID);
			////////////////////////////Labling///////////////////////////////
			int GetItems();
			bool DeleteItem(int ID);


			///////////////   Class Checking    ////////////////////////////
			bool OnLost(int ID);
			bool OnReset(int ID);
			bool Destroy(int ID);
			bool DestroyAll();

		};

	}
}