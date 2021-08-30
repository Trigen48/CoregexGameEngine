#pragma once 
#include <Windows.h>
#include <iostream>

using namespace System;

inline const char* StringtoChar(System::String ^Text)
{

	char* s1=new char[Text->Length];
	char* s2=new char[Text->Length];

	for(int x=0;x<Text->Length;x++)
	{
		s1[x]= Text[x];
	}

	strcpy(s2,s1);

		std::string h;
	for(int x=0;x<Text->Length;x++)
	{
		h.push_back((char)Text[x]);
		
	}
	

	return h.c_str();
}


inline const WCHAR* StringtoWChar(System::String ^Text)
{
	const char* y=StringtoChar(Text);

	const WCHAR* s1=new WCHAR[Text->Length];
	
std::basic_string<WCHAR> t;

	for(int x=0;x<Text->Length;x++)
	{
		t.push_back((WCHAR)y[x]);
	}

	

	

	return t.c_str();
}