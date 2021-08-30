#pragma once
#include "Model.h"

namespace CoreGex
{

	
	namespace Meshes
	{


		public ref class ColorModel : Model
		{
		public:

			ColorModel(void);

						//Model(void);


			

			virtual void Render();

			virtual void Destroy();

			virtual TRLVECTOR3^ GetPosition();

			virtual void SetPosition(TRLVECTOR3^ Position);

			virtual TRLVECTOR3^ GetScale();
			virtual void SetScale(TRLVECTOR3^ Scale);

	    	bool LoadModel(System::String ^ file);
			bool Init();

		private:
			TRLVECTOR3^ pos;
			TRLVECTOR3^ scale;

			ColorVertex * ModelInfo;
			LPDIRECT3DVERTEXBUFFER9* buff;
			D3DXMATRIX *mtrx;
			
		};

	}

}