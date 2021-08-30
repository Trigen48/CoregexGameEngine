#pragma once
#include <windows.h>
#include "MediaMusic.h"

namespace CoreGex
{
	namespace Media
	{
		public ref class AudioClass
		{
			public:
				AudioClass();

				bool Load(System::String ^File);
				bool Play();
				bool Pause();
				bool SetVolume(int Level);
				bool Stop();

				bool SetSpeed(int speed);
				bool Loop(bool OnOff);
				System::Int64 GetDuration();
				System::Int64 GetCurrectPosition();
				bool SetPosition(System::Int64 position);

				bool Destroy();
				int GetSpeed();
				bool Update();
				int GetVolume();
			private:
				AudioFile *_audio;
		};

	}
}