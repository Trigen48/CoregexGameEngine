#include "GameSound.h"
#include "CL.h"
#include "Sound.h"

static cl<SoundFile> as;

static HWND win;

static bool Detect(int ID);
static bool Detect(int ID)
{
	if(ID<0 || ID>as.Count()-1) return false;

	return true;
}


CoreGex::Media::GameSound::GameSound(void)
{
	as= cl<SoundFile>();
}

int CoreGex::Media::GameSound::AddNew()
{
	as.Add(SoundFile());
	return as.Count()-1;
}

bool CoreGex::Media::GameSound::Init(int ID,Control^window)
{

	if(ID== as.Count())
	{
		AddNew();

	}
	else
	{
				if(!Detect(ID))return false;
	}
	
	if(win==NULL)win=static_cast<HWND>( window->Handle.ToPointer());
	
	return as[ID].Init(win);
}

bool CoreGex::Media::GameSound::Destroy(int ID)
{	
	if(!Detect(ID)) return false;
	as[ID].Destroy();
	as.Remove(ID);
return true;
}

bool CoreGex::Media::GameSound::Load(int ID,String ^File)
{
	if(ID== as.Count())
	{
		AddNew();

	}
	else
	{
				if(!Detect(ID))return false;
	}
	std::string h;
	for(int x=0;x<File->Length;x++)
	{
		h.push_back((char)File[x]);
	}

	return as[ID].Load(h.c_str());
}

bool CoreGex::Media::GameSound::Play(int ID)
{
	if(!Detect(ID)) return false;
	return as[ID].Play();
}

	bool CoreGex::Media::GameSound::IsPlaying(int ID)
	{
		if(!Detect(ID)) return false;
		return as[ID].IsPlaying();
	}

	bool CoreGex::Media::GameSound::IsStoped(int ID)
	{
		if(!Detect(ID)) return false;
	return as[ID].IsStoped();
	}

	bool CoreGex::Media::GameSound::Stop(int ID)
	{
		if(!Detect(ID)) return false;
		return as[ID].Stop();

	}

	bool CoreGex::Media::GameSound::Pause(int ID)
	{
		if(!Detect(ID)) return false;
		return as[ID].Pause();
	}

	bool CoreGex::Media::GameSound::SetVolume(int ID,long value)
	{
	if(!Detect(ID)) return false;
	return as[ID].SetVolume(value);
	}

	bool CoreGex::Media::GameSound::SetSpeed(int ID,long value)
	{
		if(!Detect(ID)) return false;
		return as[ID].SetSpeed(value);
	}

	bool CoreGex::Media::GameSound::SetPosition(int ID,long value)
	{
		if(!Detect(ID)) return false;
		return as[ID].SetPosition(value);

	}

	long CoreGex::Media::GameSound::GetVolume(int ID)
	{
		if(!Detect(ID)) return -1;
		return as[ID].GetVolume();
	}

	long CoreGex::Media::GameSound::GetSpeed(int ID)
	{
		if(!Detect(ID)) return -1;
		return as[ID].GetSpeed();
		
	}

	long CoreGex::Media::GameSound::GetPosition(int ID)
	{
		if(!Detect(ID)) return -1;
		return as[ID].GetPosition();
	}

	bool CoreGex::Media::GameSound::DestroyAll()
	{

	for(int x=0;x<as.Count();x++)
	{
		as[x].Destroy();
	}

	as.Clear();
		return true;
	}