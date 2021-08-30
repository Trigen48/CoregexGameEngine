#pragma once
#include "MediaVideo.h"
#include <windows.h>

namespace CoreGex
{

	namespace Media
	{

		public ref class  VideoClass
		{

			public:

				VideoClass();
				bool Load(System::String^ File, System::Windows::Forms::Control ^ Control);
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

		private:
			VideoFile * _video;
		};

	}
}