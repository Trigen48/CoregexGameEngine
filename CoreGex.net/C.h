#pragma once

#include <wtypes.h>

#include <vector>
#include <string>

#include <vcclr.h>

using namespace System;
using namespace System::Runtime::InteropServices;


// get string from System::String
static std::vector< gcroot<IntPtr> >* m_vec_hglobal;


static char* GetString(System::String^ Text)
{
	if(m_vec_hglobal==NULL)
	{

m_vec_hglobal = new std::vector< gcroot<System::IntPtr> >(); 
	}

	IntPtr temp=Marshal::StringToHGlobalAnsi(Text);
	char* temS=reinterpret_cast<char*>(static_cast<void*>(temp));
	m_vec_hglobal->push_back(temp);


	return temS;
}


static std::string GetStringS(System::String^ Text)
{
	IntPtr temp=Marshal::StringToHGlobalAnsi(Text);
	std::string temS=reinterpret_cast<char*>(static_cast<void*>(temp));
	m_vec_hglobal->push_back(temp);
	
	return temS;
}

