#pragma once

#include <windows.h>
#include <iostream>
#include <fstream>
#include "cl.h"
#include "Utils.h"
#include "StringUtils.h"

using namespace std;

namespace CoreGex
{

	namespace Assets
	{

		public ref class exAssets
		{

			public:

					exAssets(void);

					~exAssets(void);

					// Pack
					bool _stdcall CreateNewPack();

					bool _stdcall AddFile(System::String^ File);

					bool _stdcall AddFile(System::String^ File,System::String ^ EntryName);

					bool _stdcall AddFile(System::String^ File,bool Compressed);

					bool _stdcall AddFile(System::String^ File,System::String ^ EntryName,bool Compressed);

					// Pack Files
					bool _stdcall Pack(System::String^ File);

					// Load Pack
					bool _stdcall LoadPack(System::String^ File);
					bool _stdcall LoadPackNative(BYTE* File,int offset, int length);

					bool _stdcall LoadPack(System::Byte File[],int offset, int length);

					// Get Data
					bool _stdcall GetData(System::String^ EntryName, System::String^ OutFile);
					bool _stdcall GetData(int Index, System::String^ OutFile);

					BYTE* _stdcall GetDataByteNative(System::String^ EntryName);
					BYTE* _stdcall GetDataByteNative(int Index);

					BYTE* _stdcall GetDataByte(System::String^ EntryName);
					BYTE* _stdcall GetDataByte(int Index);

					ULONG _stdcall GetFileSize(System::String^ EntryName);

					ULONG _stdcall GetFileSize(int Index);

					ULONG _stdcall GetFilesCount();

					bool _stdcall ClosePack();


		    private:
				FILE *fi;

				cl<FileEntry> *Files;
				ULONG off;
				bool isopen;

				ULONG GetFileSizeF(System::String^ File);

				System::String^ GetFileName(System::String^ File);

				void WriteUL(ULONG value);  

				void WriteL(LONG value);  

				ULONG GetUL();   

				LONG GetL();

				void WriteHeader();

				System::String^ ReadString();
		};

	}

}