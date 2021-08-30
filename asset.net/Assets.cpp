#include "Assets.h"
#include "Asset.h"
#include "Utils.h"

using namespace std;

static Asset ast;

	MediaDev::Assets::AssetNative::AssetNative()
	{
		ast= Asset();
	}

	MediaDev::Assets::AssetNative::~AssetNative(void)
	{
	}


	// Encryption Algorithm
	void MediaDev::Assets::AssetNative::CreateEncryption()
	{
		ast.CreateEncryption();
	}

	bool MediaDev::Assets::AssetNative::CreateDecryption()
	{
		return ast.CreateDecryption();
	
	}

	void MediaDev::Assets::AssetNative::CreateEncryption(BYTE* enc)
	{
		ast.CreateEncryption(enc);

	}

	bool MediaDev::Assets::AssetNative::LoadEncryption(System::String^ enc)
	{
		
		return ast.LoadEncryption(NetString(enc));
	}

	BYTE* MediaDev::Assets::AssetNative::GetEncryption()
	{
		return ast.GetEncryption();
	}

	bool MediaDev::Assets::AssetNative::SaveEncryption(String^ encFile)
	{
		return ast.SaveEncryption(NetString(encFile));
	}


	// Encrypt Files
	bool MediaDev::Assets::AssetNative::EncryptFileA(String^ InFile,String^ OutFile)
	{
		return ast.EncryptFileA(NetString(InFile),NetString(OutFile));
	}

	BYTE* MediaDev::Assets::AssetNative::GetEncryptedFileA(String^ InFile,String^ OutFile)
	{
		return ast.GetEncryptedFileA(NetString(InFile),NetString(OutFile));
	}

	// Decrypt Files
	bool MediaDev::Assets::AssetNative::DecryptFileA(String^ InFile,String^ OutFile)
	{
		return ast.DecryptFileA(NetString(InFile),NetString(OutFile));
	}

	BYTE* MediaDev::Assets::AssetNative::GetDecryptedFileA(String^ InFile,String^ OutFile)
	{
		return ast.GetDecryptedFileA(NetString(InFile),NetString(OutFile));
	}

	// Pack
	bool MediaDev::Assets::AssetNative::CreateNewPack()
	{
		return ast.CreateNewPack();
	}

	bool MediaDev::Assets::AssetNative::AddFile(String^ File)
	{
		return ast.AddFile(NetString(File));
	}


	// Pack Files
	bool MediaDev::Assets::AssetNative::Pack(String^ File)
	{
		return ast.Pack(NetString(File));
	}

	bool MediaDev::Assets::AssetNative::PackAndEncrypt(String^ File)
	{
		return ast.PackAndEncrypt(NetString(File));
	}
	
	// Load Pack
	bool MediaDev::Assets::AssetNative::LoadPack(String^ File)
	{
		return ast.LoadPack(NetString(File));
	}

	bool MediaDev::Assets::AssetNative::LoadPack(BYTE* File,int offset, int length)
	{
		return ast.LoadPack(File,offset,length);
	}
	
	// Get Data
	bool MediaDev::Assets::AssetNative::GetData(String^ EntryName, String^ OutFile)
	{
		return ast.GetData(NetString(EntryName),NetString(OutFile));
	}

	bool MediaDev::Assets::AssetNative::GetData(int Index, String^ OutFile)
	{
		return ast.GetData(Index,NetString(OutFile));
	}

	BYTE* MediaDev::Assets::AssetNative::GetDataByte(String^ EntryName)
	{
		return ast.GetDataByte(NetString(EntryName));
	}

	BYTE* MediaDev::Assets::AssetNative::GetDataByte(int Index)
	{
		return ast.GetDataByte(Index);
	}

	// Get Encrypted Data
	bool MediaDev::Assets::AssetNative::GetEncryptedData(String^ EntryName, String^ OutFile)
	{
		return ast.GetEncryptedData(NetString(EntryName),NetString(OutFile));
	}

	bool MediaDev::Assets::AssetNative::GetEncryptedData(int Index, String^ OutFile)
	{
		return ast.GetEncryptedData(Index,NetString(OutFile));
	}

	BYTE* MediaDev::Assets::AssetNative::GetEncryptedDataByte(String^ EntryName)
	{
		return ast.GetEncryptedDataByte(NetString(EntryName));
	}

	BYTE* MediaDev::Assets::AssetNative::GetEncryptedDataByte(int Index)
	{
		return ast.GetEncryptedDataByte(Index);
	}

	ULONG MediaDev::Assets::AssetNative::GetFileSize(String^ EntryName)
	{
		return ast.GetFileSize(NetString(EntryName));
	}

	ULONG MediaDev::Assets::AssetNative::GetFileSize(int Index)
	{
		return ast.GetFileSize(Index);
	}

	ULONG MediaDev::Assets::AssetNative::GetFilesCount()
	{
		return  ast.GetFilesCount();
	}

	bool MediaDev::Assets::AssetNative::PackIsEncrypted()
	{
		return ast.PackIsEncrypted();
	}

	bool MediaDev::Assets::AssetNative::ClosePack()
	{
		return ast.ClosePack();
	}
