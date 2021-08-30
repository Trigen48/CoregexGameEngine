#pragma once
#include <windows.h>
#include <direct.h>
#include <dshow.h>




class AudioFile
{

public:
	AudioFile();

bool Load(LPCWSTR lpwstrFile);
bool Play();
bool Pause();
bool SetVolume(int Level);
bool Stop();

bool SetSpeed(int speed);
bool Loop(bool OnOff);
long GetDuration();
long GetCurrectPosition();
bool SetPosition(long position);
bool Destroy();
int GetSpeed();
bool Update();
int GetVolume();
private:
	IGraphBuilder   *m_pGraph;
	IMediaControl   *m_pMediaControl;
	IMediaEvent	   *m_pEvent;
    IBasicAudio     *m_pBasic;
    IMediaSeeking   *m_pSeeking;
	IMediaPosition  *m_pPosition;
	bool playing;
	bool paused;
	int Speed;
	bool loop;

};


