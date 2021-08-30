#pragma once

#include <windows.h>
#include <iostream>
#include <fstream>
#include "cl.h"
#include "Utils.h"
#include "StringUtils.h"
#include "exAssets.h"

using namespace std;

CoreGex::Assets::exAssets::exAssets(void)
{
	ULONG off=8;
	isopen=false;

	Files= new cl<FileEntry>;
	fi=new FILE();
}

CoreGex::Assets::exAssets::~exAssets(void)
{
	fi=NULL;
}

// Pack
bool _stdcall CoreGex::Assets::exAssets::CreateNewPack()
{
	if(isopen)
	{
		(*Files).Clear();
	}

	(*Files)= cl<FileEntry>();
	off=7;
	isopen=false;
	return true;
}

bool _stdcall CoreGex::Assets::exAssets::AddFile(System::String^ File)
{
	return AddFile(File,GetFileName(File),false);
}

bool _stdcall CoreGex::Assets::exAssets::AddFile(System::String^ File,System::String ^ EntryName)
{
	return AddFile(File,EntryName,false);
}

bool _stdcall CoreGex::Assets::exAssets::AddFile(System::String^ File,bool Compressed)
{
	return AddFile(File,GetFileName(File),Compressed);
}

bool _stdcall CoreGex::Assets::exAssets::AddFile(System::String^ File,System::String ^ EntryName,bool Compressed)
{
	FileEntry file;
	//
	file.entryName= NetString(EntryName);
	file.FileSize= GetFileSizeF(File);
	file.FullFile=NetString(File);
	file.OffSet=0;
	file.Compressed=Compressed;

	if((*Files).Count()>0)
	{
		int i= (*Files).Count()-1;
	
		file.OffSet= (*Files)[i].OffSet+(*Files)[i].FileSize;
	}

	if(file.entryName.size()==0 || file.FileSize==-1) return false;
	
	off+= 10 + (file.entryName.size());

	(*Files).Add(file);

	return true;
}

// Pack Files
bool _stdcall CoreGex::Assets::exAssets::Pack(System::String^ File)
{
						
	fi=fopen(NetString(File).data(),"wb");

	if(fi==NULL || (*Files).Count()==0)
	{
		fclose(fi);
		return false;
	}

	WriteHeader();
	for(int x=0;x<(*Files).Count();x++)
	{
	
		FileEntry ff=(*Files)[x];
		ifstream r(ff.FullFile,ios::binary);

		if(!r.is_open()){r.close();fclose(fi); return false;}

		while(r.good())
		{
			BYTE t= r.get();

			if(r.good()) fputc((t),fi);

		}
			r.close();
			fflush(fi);
	}


	//fflush(fi);
	fclose(fi);
	return true;
}

// Load Pack
bool _stdcall CoreGex::Assets::exAssets::LoadPack(System::String^ File)
{
	if(isopen) fclose(fi);
	//fs= ifstream(File,ios::binary);
	fi=fopen(NetString(File).c_str(),"rb");
	if(fi==NULL) {fclose(fi); return false;}
	    

	try
	{

		if( fgetc(fi)!='I'||  fgetc(fi)!='G'|| fgetc(fi)!='P')
		{
			fclose(fi);
			return false;
		}

		ULONG filez= GetUL();
	 
		CreateNewPack();

		for(ULONG x=0;x<filez;x++)
		{
			FileEntry fe;
			fe.entryName= NetString(ReadString());
			fe.OffSet=GetUL();
			fe.FileSize=GetUL();
			
			fe.Compressed=(bool)fgetc(fi);

				/*	fputc(((BYTE)ff.entryName.size()),fi);
		fwrite(ff.entryName.c_str(),1,ff.entryName.size(),fi);
		WriteUL(ff.OffSet+off);
		WriteUL(ff.FileSize);
		fputc(ff.Compressed? 1:0,fi);*/


			Files->Add(fe);
		}
		isopen=true;
	}
	catch(exception ex)
	{
		fclose(fi);
		throw exception("Could Not load File");
	}


	return true;
}

bool _stdcall CoreGex::Assets::exAssets::LoadPackNative(BYTE* File,int offset, int length)
{

	return true;
}

bool _stdcall CoreGex::Assets::exAssets::LoadPack(System::Byte File[],int offset, int length)
{

	return true;
}
	

// Get Data
bool _stdcall CoreGex::Assets::exAssets::GetData(System::String^ EntryName, System::String^ OutFile)
{
	if(!isopen) return false;

	for(int x=0;x<(*Files).Count();x++)
	{
		if(CompareStringLP(NetString(EntryName),(*Files)[x].entryName)==true)
		{
			return GetData(x,OutFile);
		}
	}

	return false;
}


bool _stdcall CoreGex::Assets::exAssets::GetData(int Index, System::String^ OutFile)
{
	if(!isopen || (*Files).Count()<=Index|| Index<0) return false;

	ofstream w(NetString(OutFile),ios::binary);

	if(!w.good()){w.close(); return false;}

	FileEntry fe= (*Files)[Index];
	fseek(fi,fe.OffSet,0);
	ULONG x=fe.FileSize;

	while(x>0)
	{
		w.put( fgetc(fi));
		x--;
	}

	w.flush();
	w.close();
	return true;
}

BYTE* _stdcall CoreGex::Assets::exAssets::GetDataByteNative(System::String^ EntryName)
{
	if(!isopen) 
		return NULL;
	
	for(int x=0;x<Files->Count();x++)
	{
		if(CompareStringLP(NetString(EntryName),(*Files)[x].entryName)==true)
		{
			return GetDataByteNative(x);
		}
	}
	return NULL;
}

BYTE* _stdcall CoreGex::Assets::exAssets::GetDataByteNative(int Index)
{
	if(!isopen || Files->Count()<=Index|| Index<0) 
		return NULL;

	FileEntry fe= (*Files)[Index];
	BYTE* d=new BYTE[fe.FileSize];

	fseek(fi,fe.OffSet,0);
	
	for(ULONG x=0;x<fe.FileSize;x++)
	{
		d[x]= fgetc(fi);
	}

	return d;
}

BYTE* _stdcall CoreGex::Assets::exAssets::GetDataByte(System::String^ EntryName)
{
	if(!isopen) return NULL;
	
	for(int x=0;x<((*Files)).Count();x++)
	{
		if(CompareStringLP(NetString(EntryName),(*Files)[x].entryName)==true)
		{
			return GetDataByte(x);
		}
	}
	return NULL;
}

BYTE* _stdcall CoreGex::Assets::exAssets::GetDataByte(int Index)
{
	if(!isopen || (*Files).Count()<=Index|| Index<0) return NULL;

	FileEntry fe= (*Files)[Index];
	BYTE* d=new BYTE[fe.FileSize];

	fseek(fi,fe.OffSet,0);
	
	for(ULONG x=0;x<fe.FileSize;x++)
	{
		d[x]= fgetc(fi);
	}

	return d;
}


ULONG _stdcall CoreGex::Assets::exAssets::GetFileSize(System::String^ EntryName)
{
	if(!isopen) return -1;

	for(int x=0;x<Files->Count();x++)
	{
		if(CompareStringLP(NetString(EntryName),(*Files)[x].entryName)==true)
		{
			return GetFileSize(x);
		}
	}

	return -1;
}

ULONG _stdcall CoreGex::Assets::exAssets::GetFileSize(int Index)
{
	if(!isopen || Files->Count()<=Index|| Index<0) return -1;
	return  (*Files)[Index].FileSize;
}

ULONG _stdcall CoreGex::Assets::exAssets::GetFilesCount()
{
	if(!isopen) return -1;
	return Files->Count();
}

bool _stdcall CoreGex::Assets::exAssets::ClosePack()
{

	if(isopen)
	{
		fclose(fi);
		fclose(fi);
		fi=NULL;
	}

	Files->Clear();
	isopen=false;
	return true;
}

ULONG CoreGex::Assets::exAssets::GetFileSizeF(System::String^ File)
{
	ifstream f(NetString(File),ios::binary);

	if(!f.is_open() ||!f.good()) return -1;

	f.seekg(0,ios::end);
	ULONG t;
	t= (ULONG)f.tellg();
	f.close();
	return t;
}

System::String^ CoreGex::Assets::exAssets::GetFileName(System::String^ File)
{
	int l= (NetString(File)).size();
	int last=0;

	System::String^ t;
	try
	{
		for(int x=0;x<l;x++)
		{
			if((*File)[x]=='\\' && x+1!=l) last=x+1;
		}
		t="";
		for(int x=last;x<l;x++)
		{
			t+=(*File)[x];
		}
	}
	catch(exception ex)
	{
		throw new exception("Could not get filename");
	}
	return t;
}

void CoreGex::Assets::exAssets::WriteUL(ULONG value)
{     
	try   
	{ 
		fputc(((char)((value & 0xFF000000) >> 24)),fi);
		fputc(((char)((value & 0x00FF0000) >> 16)),fi);
		fputc(((char)((value & 0x0000FF00) >> 8)),fi);
		fputc(((char)((value & 0X000000FF))),fi);
	} 
	catch(exception ex)  
	{
		throw exception("Error encoding data <en1>");      
	}
      
}  

void CoreGex::Assets::exAssets::WriteL(LONG value)      
{
	try 
	{
		fputc(((char)((value >> 8) & 0XFF)),fi);
		fputc(((char)((value & 0XFF))),fi);
	}
	catch(exception ex)  
	{       
		throw exception("Error encoding data <en2>");   
	}
}  

ULONG CoreGex::Assets::exAssets::GetUL()
{         
	ULONG t = 0;
	try  
	{         
		t =  ((UINT) fgetc(fi)) << 24;
		t |= ((UINT) fgetc(fi)) << 16;
		t |= ((UINT) fgetc(fi)) << 8;
		t |= ((UINT) fgetc(fi));
              
		return t;
	}  
	catch(exception ex)     
	{
		throw exception("Error decoding data <de1>"); 
	}
       
}   

LONG CoreGex::Assets::exAssets::GetL()   
{
	LONG t = 0;
	try         
	{
		t |= ((UINT) fgetc(fi)) << 8;
		t |= ((UINT) fgetc(fi));
		return t;
	}  
	catch(exception ex) 
	{
		throw exception("Error decoding data <de2>"); 
	}
}

void CoreGex::Assets::exAssets::WriteHeader()
{
	fwrite("IGP",1,3,fi);

	WriteUL((ULONG)(*Files).Count());

	for(int x=0;x<(*Files).Count();x++)
	{
		FileEntry ff=(*Files)[x];
		fputc(((BYTE)ff.entryName.size()),fi);
		fwrite(ff.entryName.c_str(),1,ff.entryName.size(),fi);
		WriteUL(ff.OffSet+off);
		WriteUL(ff.FileSize);
		fputc(ff.Compressed? 1:0,fi);
	}
}

System::String^ CoreGex::Assets::exAssets::ReadString()
{
	System::String^ temp="";
	int l= 	fgetc(fi);
	for(int x=0;x<l;x++)
	{
		temp+=	fgetc(fi);
	}
	return temp;
}
		