#pragma once


#include <Windows.h>
#include <iostream>
#include <fstream>

using namespace System;

namespace MediaDev
{

	namespace Assets
	{
public ref class AssetNative
{
public:
	AssetNative();
	~AssetNative(void);


	// Encryption Algorithm
	void CreateEncryption();

	bool CreateDecryption();

	void CreateEncryption(BYTE* enc);

	bool LoadEncryption(System::String^ enc);

	BYTE* GetEncryption();

	bool SaveEncryption(String^ encFile);


	// Encrypt Files
	bool EncryptFileA(String^ InFile,String^ OutFile);

	BYTE* GetEncryptedFileA(String^ InFile,String^ OutFile);

	// Decrypt Files
	bool DecryptFileA(String^ InFile,String^ OutFile);

	BYTE* GetDecryptedFileA(String^ InFile,String^ OutFile);

	// Pack
	bool CreateNewPack();

	bool AddFile(String^ File);


	// Pack Files
	bool Pack(String^ File);

	bool PackAndEncrypt(String^ File);
	
	// Load Pack
	bool LoadPack(String^ File);

	bool LoadPack(BYTE* File,int offset, int length);
	

	// Get Data
	bool GetData(String^ EntryName, String^ OutFile);

	bool GetData(int Index, String^ OutFile);

	BYTE* GetDataByte(String^ EntryName);

	BYTE* GetDataByte(int Index);

	// Get Encrypted Data
	bool GetEncryptedData(String^ EntryName, String^ OutFile);

	bool GetEncryptedData(int Index, String^ OutFile);

	BYTE* GetEncryptedDataByte(String^ EntryName);

	BYTE* GetEncryptedDataByte(int Index);

	ULONG GetFileSize(String^ EntryName);

	ULONG GetFileSize(int Index);

	ULONG GetFilesCount();

	bool PackIsEncrypted();

	bool ClosePack();

private:
	
	FILE ff;


};


}
}