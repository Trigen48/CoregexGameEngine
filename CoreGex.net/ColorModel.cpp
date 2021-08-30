#include "ColorModel.h"

extern int gwidth;
extern int gheight;


//bool SetFont(System::String^ name, int size);

//extern LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
extern LPDIRECT3DDEVICE9 d3d;    // the pointer to the device class


CoreGex::Meshes::ColorModel::ColorModel(void)
{


}

void CoreGex::Meshes::ColorModel::Render()
{



	d3d->SetStreamSource(0,(*buff),0,sizeof(ColorVertex));
    //draw triangle (NEW)
    d3d->DrawPrimitive(D3DPT_TRIANGLELIST,0,1);

}

void CoreGex::Meshes::ColorModel::Destroy()
{
}

TRLVECTOR3^ CoreGex::Meshes::ColorModel::GetPosition()
{
	return pos;
}

void CoreGex::Meshes::ColorModel::SetPosition(TRLVECTOR3^ Position)
{
}

TRLVECTOR3^ CoreGex::Meshes::ColorModel::GetScale()
{
	return scale;
}

void CoreGex::Meshes::ColorModel::SetScale(TRLVECTOR3^ Scale)
{
}

bool CoreGex::Meshes::ColorModel::LoadModel(System::String ^ file)
{

	return true;
}
	ColorVertex n[3];
bool CoreGex::Meshes::ColorModel::Init()
{
		d3d->SetFVF(ColorVertexF);
		ModelInfo= new ColorVertex[3];


	ModelInfo[0]=ColorVertex(-2.0f, 1.0f,10.0f,0xffff0000);
	ModelInfo[1]=ColorVertex(-3.0f,-1.0f,10.0f,0xff00ff00);
	ModelInfo[2]=ColorVertex(-1.0f,-1.0f,10.0f,0xff0000ff);


	n[0]=ColorVertex(-2.0f, 1.0f,10.0f,0xffff0000);
	n[1]=ColorVertex(-3.0f,-1.0f,10.0f,0xff00ff00);
	n[2]=ColorVertex(-1.0f,-1.0f,10.0f,0xff0000ff);

	buff= new LPDIRECT3DVERTEXBUFFER9();
	
	mtrx= new D3DXMATRIX();
	//buff= new LPDIRECT3DVERTEXBUFFER9();
	VOID* pData;
	HRESULT l=NULL;

	l=d3d->CreateVertexBuffer(sizeof(n),
    D3DUSAGE_WRITEONLY,
	ColorVertexF,
    D3DPOOL_MANAGED,
	(buff),
    NULL);

	
	if(l!= S_OK) 
	{
			return false;
	}
	
	//lock buffer (NEW)
	(*buff)->Lock(0,sizeof(pData),(void**)&(pData),0);

	//copy data to buffer (NEW)
	memcpy(pData,(n),sizeof(n));

	//unlock buffer (NEW)
	(*buff)->Unlock();
	d3d->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	return true;
}