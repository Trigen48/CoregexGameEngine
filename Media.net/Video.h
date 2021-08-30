#pragma once

#include <WIndows.h>

namespace CoreGex
{

	namespace Media
	{

public ref class  Video
{
public:

public:

	Video();
	int AddNew();
bool Load(int ID,System::String^ File, System::Windows::Forms::Control ^ Control);
bool Play(int ID);
bool Pause(int ID);
bool SetVolume(int ID,int Level);
bool Stop(int ID);

bool SetSpeed(int ID,int speed);
bool Loop(int ID,bool OnOff);
long GetDuration(int ID);
long GetCurrectPosition(int ID);
bool SetPosition(int ID,long position);
bool Destroy(int ID);
int GetSpeed(int ID);
bool Update(int ID);
bool DestroyAll();
};

	}
}