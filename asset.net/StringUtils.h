#pragma once

#include <Windows.h>
#include <iostream>

using namespace std;


inline bool CompareStringLP(string left,string right)
{
	if(left.size()!=right.size()) return false;

	for(UINT x=0;x<left.size();x++)
	{
		if((int)left[x]!=(int)right[x]) return false;
	}

	return true;
}