#include "AudioClass.h"
#include <iostream>
#include <string>
CoreGex::Media::AudioClass::AudioClass()
{
	_audio= new AudioFile();
}

bool CoreGex::Media::AudioClass::Load(System::String ^ File)
{    
	LPCWSTR lpwstrFile;
	std::basic_string<WCHAR> g;

	for(int x=0;x<File->Length;x++)
	{
		WCHAR w=File[x];
		g+=w;
	}
	
	lpwstrFile= g.c_str();
	
	return _audio->Load(lpwstrFile);
}

bool CoreGex::Media::AudioClass::Play()
{
	return _audio->Play();
}

bool CoreGex::Media::AudioClass::Pause()
{
	return _audio->Pause();
}

bool CoreGex::Media::AudioClass::SetVolume(int Level)
{
	return _audio->SetVolume(Level);
	//_audio->
}

bool CoreGex::Media::AudioClass::Stop()
{
	return _audio->Stop();
}

bool CoreGex::Media::AudioClass::SetSpeed(int speed)
{	
	return _audio->SetSpeed(speed);
}

bool CoreGex::Media::AudioClass::Loop(bool OnOff)
{
	return _audio->Loop(OnOff);
}

System::Int64 CoreGex::Media::AudioClass::GetDuration()
{	
	unsigned long val=_audio->GetDuration();
	return val;
}

System::Int64 CoreGex::Media::AudioClass::GetCurrectPosition()
{	
	return System::Int64( _audio->GetCurrectPosition());
}

bool CoreGex::Media::AudioClass::SetPosition(System::Int64 position)
{	
	//long vv=position->(long)position

	return _audio->SetPosition(0);
}

bool CoreGex::Media::AudioClass::Destroy()
{
	if(!_audio->Destroy()) return false;
	return true;
}

int  CoreGex::Media::AudioClass::GetSpeed()
{
	return _audio->GetSpeed();
}

bool CoreGex::Media::AudioClass::Update()
{
	return _audio->Update();
}

int CoreGex::Media::AudioClass::GetVolume()
{
	return _audio->GetVolume();
}
