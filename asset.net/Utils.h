#pragma once
#include <Windows.h>
#include <iostream>

using namespace std;


struct FileEntry
{
	public:
		ULONG FileSize,OffSet;
		bool Compressed;
		string entryName,FullFile;
};


inline string NetString(System::String^ Text)
{

	string t="";

	for(int x=0;x<Text->Length;x++)
	{
		t.push_back((char)Text[x]);
	}

	
	
	return t;
}

//BYTE* NetByte(System::String^