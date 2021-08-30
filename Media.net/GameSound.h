#pragma once
#include <Windows.h>

using namespace System::Windows::Forms;
using namespace System;

namespace CoreGex
{

	namespace Media
	{

public ref class GameSound
{
public:
	GameSound(void);
	
	bool DestroyAll();

bool Destroy(int ID);
	bool Init(int ID,Control^ window);
	int AddNew();
	bool Load(int ID,String ^File);
	bool Play(int ID);
	bool Stop(int ID);
	bool Pause(int ID);
	bool SetVolume(int ID,long value);
	bool SetSpeed(int ID,long value);
	bool SetPosition(int ID,long value);
	bool IsPlaying(int ID);
	bool IsStoped(int ID);

	long GetVolume(int ID);
	long GetSpeed(int ID);
	long GetPosition(int ID);

};

	}
}