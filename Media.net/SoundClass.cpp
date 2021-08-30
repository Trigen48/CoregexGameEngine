#include "SoundClass.h"

CoreGex::Media::SoundClass::SoundClass(void)
{
	_sound= new SoundFile();
}

bool CoreGex::Media::SoundClass::Init(Control^window)
{
	HWND win=NULL;
	if(window!= nullptr)
	{
		win=static_cast<HWND>( window->Handle.ToPointer());
	}
	return _sound->Init(win);
}

bool CoreGex::Media::SoundClass::Destroy()
{	
	_sound->Destroy();
	return true;
}

bool CoreGex::Media::SoundClass::Load(String ^File)
{
	std::string h;
	for(int x=0;x<File->Length;x++)
	{
		h.push_back((char)File[x]);
	}
	return _sound->Load(h.c_str());
}

bool CoreGex::Media::SoundClass::Play()
{	
	return _sound->Play();
}

bool CoreGex::Media::SoundClass::IsPlaying()
{
	return _sound->IsPlaying();
}

bool CoreGex::Media::SoundClass::IsStoped()
{
	return _sound->IsStoped();
}

bool CoreGex::Media::SoundClass::Stop()
{
	return _sound->Stop();
}

bool CoreGex::Media::SoundClass::Pause()
{
	return _sound->Pause();
}

bool CoreGex::Media::SoundClass::SetVolume(System::Int64 value)
{
	return _sound->SetVolume(value);
}

bool CoreGex::Media::SoundClass::SetSpeed(System::Int64 value)
{
	return _sound->SetSpeed(value);
}

bool CoreGex::Media::SoundClass::SetPosition(System::Int64 value)
{
	return _sound->SetPosition(value);
}

System::Int64 CoreGex::Media::SoundClass::GetVolume()
{
	return _sound->GetVolume();
}

System::Int64 CoreGex::Media::SoundClass::GetSpeed()
{
	return _sound->GetSpeed();
}

System::Int64 CoreGex::Media::SoundClass::GetPosition()
{
	return _sound->GetPosition();
}
