#pragma once

namespace CoreGex
{

	namespace Maths
	{


public ref class TRLCOLOR
{
public:

	TRLCOLOR()
	{
		R=0;
		G=0;
		B=0;
		A=0;
	}

	inline TRLCOLOR(int color)
	{
		R=color;
		G=color;
		B=color;
		A=255;
	};

	inline TRLCOLOR(int color,int alpha)
	{
		R=color;
		G=color;
		B=color;
		A=alpha;
	};

	inline TRLCOLOR(int r,int g,int b)
	{
		R=r;
		G=g;
		B=b;
		A=255;
	};

	inline TRLCOLOR(int r,int g,int b,int a)
	{
		R=r;
		G=g;
		B=b;
		A=a;
	};

public:
	int R,G,B,A;
};


public ref class TRLVECTOR2
{
public:

	TRLVECTOR2()
	{
		X=0;
		Y=0;
	}

	inline TRLVECTOR2(int value)
	{
		X=value;
		Y=value;
	};

	inline TRLVECTOR2(int x,int y)
	{
		X=x;
		Y=y;
	};

public:
	int X,Y;
};


public ref class TRLVECTOR3
{
public:

	TRLVECTOR3()
	{
		X=0;
		Y=0;
		Z=0;
	}

	inline TRLVECTOR3(int value)
	{
		X=value;
		Y=value;
		Z=value;
	};

	inline TRLVECTOR3(int x,int y)
	{
		X=x;
		Y=y;
		Z=0;
	};

	inline TRLVECTOR3(int x,int y,int z)
	{
		X=x;
		Y=y;
		Z=z;
	};

public:
	int X,Y,Z;
};


public ref class TRLVECTOR4
{
	public:

		TRLVECTOR4()
		{
			X=0;
			Y=0;
			Z=0;
			W=0;
		}

	inline TRLVECTOR4(int value)
	{
		X=value;
		Y=value;
		Z=value;
		W=value;
	};

	inline TRLVECTOR4(int x,int y)
	{
		X=x;
		Y=y;
		Z=0;
		W=0;
	};

	inline TRLVECTOR4(int x,int y,int z)
	{
		X=x;
		Y=y;
		Z=z;
		W=0;
	};

	inline TRLVECTOR4(int x,int y,int z,int w)
	{
		X=x;
		Y=y;
		Z=z;
		W=w;
	};

public:
	int X,Y,Z,W;
};


public ref class RECTANGLE

	{
		public:

			RECTANGLE()
			{

			}

             int top;
			 int left;
			 int bottom;
			 int right;
	};
	

public ref class FRAME
	{
	public:
		FRAME()
		{

		}
		int x,y;
		int size;
	};

}
}