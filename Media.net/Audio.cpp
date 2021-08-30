#include "Audio.h"

#include "CL.h"
#include "MediaMusic.h"
#include <string>

static cl<AudioFile> at;

static bool Detect(int ID);
static bool Detect(int ID)
{
	if(ID<0 || ID>at.Count()-1) return false;

	return true;
}


CoreGex::Media::Audio::Audio()
{
	at= cl<AudioFile>();
	
}

int CoreGex::Media::Audio::AddNew()
{
	at.Add(AudioFile());

	return at.Count()-1;
}

bool CoreGex::Media::Audio::Load(int ID,System::String ^ File)
{    
	if(ID== at.Count())
	{
		AddNew();

	}
	else
	{
				if(!Detect(ID))return false;
	}


	LPCWSTR lpwstrFile;
		
	std::basic_string<WCHAR> g;

	for(int x=0;x<File->Length;x++)
	{
		WCHAR w=File[x];
		g+=w;
	}

	lpwstrFile= g.c_str();

	return at[ID].Load(lpwstrFile);
}

bool CoreGex::Media::Audio::Play(int ID)
{
	if(!Detect(ID)) return false;
	return at[ID].Play();

}

bool CoreGex::Media::Audio::Pause(int ID)
{
	if(!Detect(ID)) return false;
	return at[ID].Pause();
}

bool CoreGex::Media::Audio::SetVolume(int ID,int Level)
{
	if(!Detect(ID)) return false;
	return at[ID].SetVolume(Level);
}

bool CoreGex::Media::Audio::Stop(int ID)
{
	if(!Detect(ID)) return false;
return at[ID].Stop();
}

bool CoreGex::Media::Audio::SetSpeed(int ID,int speed)
{
	if(!Detect(ID)) return false;
	return at[ID].SetSpeed(speed);
}

bool CoreGex::Media::Audio::Loop(int ID,bool OnOff)
{
	if(!Detect(ID)) return false;
	return at[ID].Loop(OnOff);
}

long CoreGex::Media::Audio::GetDuration(int ID)
{
	if(!Detect(ID)) return -1;
	if(!Detect(ID)) return false;
return at[ID].GetDuration();
}

long CoreGex::Media::Audio::GetCurrectPosition(int ID)
{
	if(!Detect(ID)) return -1;
return at[ID].GetCurrectPosition();
}

bool CoreGex::Media::Audio::SetPosition(int ID,long position)
{
	if(!Detect(ID)) return false;
return at[ID].SetPosition(position);

}

bool CoreGex::Media::Audio::Destroy(int ID)
{
	if(!Detect(ID)) return false;
	if(!at[ID].Destroy()) return false;
	at.Remove(ID);
return true;
}

int  CoreGex::Media::Audio::GetSpeed(int ID)
{
	if(!Detect(ID)) return -1;
	return at[ID].GetSpeed();
}

bool CoreGex::Media::Audio::Update(int ID)
{
	if(!Detect(ID)) return false;
	return at[ID].Update();
}

bool CoreGex::Media::Audio::DestroyAll()
{
	for(int x=0;x<at.Count();x++)
	{
		at[x].Destroy();
	}

	at.Clear();	
	return true;
}