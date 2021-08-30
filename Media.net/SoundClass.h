#pragma once
#include <Windows.h>
#include "Sound.h"
using namespace System::Windows::Forms;
using namespace System;

namespace CoreGex
{

namespace Media
{

	public ref class SoundClass
	{
		public:
			SoundClass(void);	
			bool Destroy();
			bool Init(Control^ window);
			bool Load(String ^File);
			bool Play();
			bool Stop();
			bool Pause();
			bool SetVolume(System::Int64 value);
			bool SetSpeed(System::Int64 value);
			bool SetPosition(System::Int64 value);
			bool IsPlaying();
			bool IsStoped();

			System::Int64 GetVolume();
			System::Int64 GetSpeed();
			System::Int64 GetPosition();

		private:
			SoundFile* _sound;
	};

}
}