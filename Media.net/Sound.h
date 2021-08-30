#pragma once
#pragma once
#include <Windows.h>
#include <iostream>



#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>


class SoundFile
{
public:
	SoundFile(void);
	void Destroy();
	bool Init(HWND);

	bool Load(LPCSTR File);
	bool Play();
	bool Stop();
	bool Pause();
	bool SetVolume(long value);
	bool SetSpeed(long value);
	bool SetPosition(long value);
	bool IsPlaying();
	bool IsStoped();

	long GetVolume();
	long GetSpeed();
	long GetPosition();
	
private:
	//HWND wind;
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;
	IDirectSoundBuffer8* m_secondaryBuffer;
	long volume;
	long position;
	bool iny;
};

