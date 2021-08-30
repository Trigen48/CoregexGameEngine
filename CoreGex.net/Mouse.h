#include <windows.h>



namespace CoreGex
{

	namespace Input
	{

[System::FlagsAttribute]
public enum class BUTTON : BYTE
{
MOUSE_LEFTBUTTON		=0,
MOUSE_RIGHTBUTTON		=1,
MOUSE_MIDDLEBUTTON	    =2,
MOUSE_4BUTTON		    =3,
MOUSE_5BUTTON		    =4,
MOUSE_6BUTTON		    =5,
MOUSE_7BUTTON		    =6,
MOUSE_8BUTTON		    =7

};

public ref class Mouse
{
public:

	Mouse(void);
	bool  InitMouse(System::Windows::Forms::Control^ Control);
	void  Destroy(void);
    float GetXPos();
	float GetYPos();
    float GetZPos();
    bool  GetButton(BUTTON MOUSEZ);
	bool  Update();
	float GetAbsoluteY();
    float GetAbsoluteX();
	bool  SetAttributes(bool inverted,float Sensitivity);
	bool  LockMouseOn(int x,int y);
	void Dispatch();
};

	}
}