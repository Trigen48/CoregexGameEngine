#pragma once
#include <windows.h>

#include <direct.h>
#include <dshow.h>



class  VideoFile
{

public:

	VideoFile();

bool Load(LPCWSTR lpwstrFile,HWND hWnd);
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


private:
	IGraphBuilder   *m_pGraph;
	IMediaControl   *m_pMediaControl;
	IMediaEvent	   *m_pEvent;
    IBasicAudio     *m_pBasic;
    IMediaSeeking   *m_pSeeking;
	IMediaPosition  *m_pPosition;
	IVideoWindow    *m_pVidWin;


	IBasicVideo*				pBasicVideo;

	IMediaPosition*				pMediaPosition;

	// mike - 130808 - media seeking for extra video information
	IMediaSeeking*				pMediaSeeking;

	IDvdGraphBuilder*			pDVDGraph;
	IDvdInfo2*					pDVDInfo;
	IDvdControl2*				pDVDControl;
	IVideoWindow*				pVideo;

	IBaseFilter*				pSplitter;
	IBaseFilter*				pDSound;

	bool playing;
	bool paused;
	int Speed;
	bool loop;
	HWND _win;

};


