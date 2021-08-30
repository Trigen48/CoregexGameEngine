#include "VideoClass.h"
#include <iostream>
#include <string>
CoreGex::Media::VideoClass::VideoClass()
{
	_video= new VideoFile();
}

bool CoreGex::Media::VideoClass::Load(System::String^ File, System::Windows::Forms::Control ^ Control)
{

	LPCWSTR lpwstrFile;
	HWND hWnd;

	// Convert String 

	std::basic_string<WCHAR> g;

	for(int x=0;x<File->Length;x++)
	{
		WCHAR w=File[x];
		g+=w;
	}

	lpwstrFile= g.c_str();

	hWnd = static_cast<HWND>( Control->Handle.ToPointer());

	return _video->Load(lpwstrFile,hWnd);
}

bool CoreGex::Media::VideoClass::Play()
{	
	return _video->Play();
}

bool CoreGex::Media::VideoClass::Pause()
{
	return _video->Pause();
}

bool CoreGex::Media::VideoClass::SetVolume(int Level)
{
	return _video->SetVolume(Level);
}

bool CoreGex::Media::VideoClass::Stop()
{
	return _video->Stop();
}

bool CoreGex::Media::VideoClass::SetSpeed(int speed)
{	
	return _video->SetSpeed(speed);
}

bool CoreGex::Media::VideoClass::Loop(bool OnOff)
{
	return _video->Loop(OnOff);
}

System::Int64 CoreGex::Media::VideoClass::GetDuration()
{	
	return _video->GetDuration();
}

System::Int64 CoreGex::Media::VideoClass::GetCurrectPosition()
{	
	return _video->GetCurrectPosition();
}

bool CoreGex::Media::VideoClass::SetPosition(System::Int64 position)
{	
	return _video->SetPosition(position);
}

bool CoreGex::Media::VideoClass::Destroy()
{
	if(!_video->Destroy()) return false;
	return true;
}

int CoreGex::Media::VideoClass::GetSpeed()
{
	return _video->GetSpeed();
}

bool CoreGex::Media::VideoClass::Update()
{
	return _video->Update();
}
