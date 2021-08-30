#pragma once
#include "Units.h"
#include "ModelInfo.h"

using namespace CoreGex::Maths ;

namespace CoreGex
{

	
	namespace Meshes
	{
		
		interface class  Model
		{
	
		public:
	
			//Model(void);

			void Render();

			void Destroy();

			TRLVECTOR3^ GetPosition();

			void SetPosition(TRLVECTOR3^ Position);

			TRLVECTOR3^ GetScale();
			void SetScale(TRLVECTOR3^ Scale);

		};

	}

}