#pragma once
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <vcclr.h>

namespace CoreGex
{
	namespace D2
	{


public ref class Draw
{
public:

	Draw();

bool drawLine(float x1, float y1, float x2, float y2, int color);
bool drawLine(float x1, float y1, float x2, float y2, int R,int G, int B);
bool DrawRect(float x, float y,int height, int width, int R, int G, int B);
bool DrawRect(float x, float y,int height, int width, int color);

bool DrawTextA(System::String^ Text, float x , float y,int R,int G, int B);
bool DrawTextA(System::String^ Text, float x , float y,int color);

bool SetDefaultFont(int Index);

bool SetTextSize(int size);
bool SetTextName(System::String^ name);
bool SetFont(System::String^ name, int size);
bool SetFont(int index, System::String^ name, int size);

bool OnLost();
bool OnReset();
bool Destroy();

};

	}
}