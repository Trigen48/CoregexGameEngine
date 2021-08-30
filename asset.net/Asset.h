#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "CL.h"
#include "StringUtils.h"
#include "Utils.h"
using namespace std;




namespace MediaDev
{

	namespace Assets
	{



public ref class AssetNative
{
public:
	AssetNative(void);
	~AssetNative(void);

	
	// Encryption Algorithm
	void _stdcall CreateEncryption();
	bool _stdcall CreateDecryption();
	void _stdcall CreateEncryption(BYTE* enc);
	bool _stdcall LoadEncryption(System::String^ enc);
	BYTE* _stdcall GetEncryption();
	bool _stdcall SaveEncryption(System::String^ encFile);


	// Encrypt Files
	bool _stdcall EncryptFileA(System::String^ InFile,System::String^ OutFile);
	BYTE* _stdcall GetEncryptedFileA(System::String^ InFile,System::String^ OutFile);

	// Decrypt Files
	bool _stdcall DecryptFileA(System::String^ InFile,System::String^ OutFile);
	BYTE* _stdcall GetDecryptedFileA(System::String^ InFile,System::String^ OutFile);



	// Pack
	bool _stdcall CreateNewPack();
	bool _stdcall AddFile(System::String^ File);


	// Pack Files
	bool _stdcall Pack(System::String^ File);
	bool _stdcall PackAndEncrypt(System::String^ File);
	
	// Load Pack
	bool _stdcall LoadPack(System::String^ File);
	bool _stdcall LoadPack(BYTE* File,int offset, int length);
	

	// Get Data
	bool _stdcall GetData(System::String^ EntryName, System::String^ OutFile);
	bool _stdcall GetData(int Index, System::String^ OutFile);
	BYTE* _stdcall GetDataByte(System::String^ EntryName);
	BYTE* _stdcall GetDataByte(int Index);

	// Get Encrypted Data
	bool _stdcall GetEncryptedData(System::String^ EntryName, System::String^ OutFile);
	bool _stdcall GetEncryptedData(int Index, System::String^ OutFile);
	BYTE* _stdcall GetEncryptedDataByte(System::String^ EntryName);
	BYTE* _stdcall GetEncryptedDataByte(int Index);

	ULONG _stdcall GetFileSize(System::String^ EntryName);
	ULONG _stdcall GetFileSize(int Index);
	ULONG _stdcall GetFilesCount();
	bool _stdcall PackIsEncrypted();

	bool _stdcall ClosePack();


private:
	FILE *fi;
//ofstream fl;
bool encrypted;
//ifstream fs;
cl<FileEntry> *Files;
BYTE* Enc;
BYTE* Dec;
ULONG off;
bool isopen;

void WriteUL(ULONG value);
void WriteL(LONG value);
ULONG GetUL();
LONG GetL();
ULONG GetFileSizeF(System::String^ File);
System::String^ GetFileName(System::String^ File);
void WriteHeader(bool encr);
System::String^ ReadString();

};

	}
}