#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <winnt.h>
// include the basic windows header files and the Direct3D header file
#include <windowsx.h>
#include <d3d9.h>
#include "D3dx9core.h"
#include "Def.h"


//static void Transform(SpriteData* dd);
__inline void Transform(SpriteData *dd)
{
	//D3DXMATRIX t;
	D3DXMatrixTransformation2D(&dd->mat,NULL,NULL,&dd->scale,&dd->center,dd->rot,&dd->position);
	//=t;
	dd->sprite->SetTransform(&dd->mat);
}
