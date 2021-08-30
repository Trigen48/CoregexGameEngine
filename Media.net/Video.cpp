#include "Video.h"
#include "CL.h"
#include "MediaVideo.h"
#include <string>

static cl<VideoFile> av;

static bool Detect(int ID);
static bool Detect(int ID)
{
	if(ID<0 || ID>av.Count()-1) return false;

	return true;
}


CoreGex::Media::Video::Video()
{
	av= cl<VideoFile>();
}

int CoreGex::Media::Video::AddNew()
{
	av.Add(VideoFile());

	return av.Count()-1;
}

bool CoreGex::Media::Video::Load(int ID,System::String^ File, System::Windows::Forms::Control ^ Control)
{
	if(ID== av.Count())
	{
		AddNew();

	}
	else
	{
				if(!Detect(ID))return false;
	}
	
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

	return av[ID].Load(lpwstrFile,hWnd);
}

bool CoreGex::Media::Video::Play(int ID)
{
	if(!Detect(ID)) return false;
return av[ID].Play();

}

bool CoreGex::Media::Video::Pause(int ID)
{
	if(!Detect(ID)) return false;
return av[ID].Pause();
}

bool CoreGex::Media::Video::SetVolume(int ID,int Level)
{
	if(!Detect(ID)) return false;
	return av[ID].SetVolume(Level);
}

bool CoreGex::Media::Video::Stop(int ID)
{
	if(!Detect(ID)) return false;
	return av[ID].Stop();
}

bool CoreGex::Media::Video::SetSpeed(int ID,int speed)
{
	if(!Detect(ID)) return false;
return av[ID].SetSpeed(speed);
}

bool CoreGex::Media::Video::Loop(int ID,bool OnOff)
{
	if(!Detect(ID)) return false;
return av[ID].Loop(OnOff);
}

long CoreGex::Media::Video::GetDuration(int ID)
{
	if(!Detect(ID)) return -1;
return av[ID].GetDuration();
}

long CoreGex::Media::Video::GetCurrectPosition(int ID)
{
	if(!Detect(ID)) return -1;
return av[ID].GetCurrectPosition();
}

bool CoreGex::Media::Video::SetPosition(int ID,long position)
{
	if(!Detect(ID)) return false;
	return av[ID].SetPosition(position);

}

bool CoreGex::Media::Video::Destroy(int ID)
{
	if(!Detect(ID)) return false;
	if(!av[ID].Destroy()) return false;
	av.Remove(ID);

return true;
}

int CoreGex::Media::Video::GetSpeed(int ID)
{
	if(!Detect(ID)) return -1;
	return av[ID].GetSpeed();
}

bool CoreGex::Media::Video::Update(int ID)
{
	if(!Detect(ID)) return false;
return av[ID].Update();
}

bool CoreGex::Media::Video::DestroyAll()
{
	for(int x=0;x<av.Count();x++)
	{
		av[x].Destroy();
	}

	av.Clear();
	return true;
}