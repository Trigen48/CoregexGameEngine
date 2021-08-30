#include "Asset.h"
#include "cl.h"
#include "StringUtils.h"





// Values to byte converters
System::String^ MediaDev::Assets::AssetNative::ReadString()
{

	System::String^ temp="";

	int l= 	fgetc(fi);

	for(int x=0;x<l;x++)
	{
		temp+=	fgetc(fi);
	}


	return temp;
}
void MediaDev::Assets::AssetNative::WriteUL(ULONG value)
{     

	//BYTE* byteArray = new BYTE[4];       
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
void MediaDev::Assets::AssetNative::WriteL(LONG value)      
{
          
	//BYTE* byteArray = new BYTE[2];
           
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
ULONG MediaDev::Assets::AssetNative::GetUL()
       
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
LONG MediaDev::Assets::AssetNative::GetL()   
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
void MediaDev::Assets::AssetNative::WriteHeader(bool encr)
{
	fwrite("APF",1,3,fi);
	if(encr) fputc((1),fi); else fputc((0),fi);
	WriteUL((ULONG)(*Files).Count());

	for(int x=0;x<(*Files).Count();x++)
	{
		FileEntry ff=(*Files)[x];

		fputc(((BYTE)ff.FileName.size()),fi);
		fwrite(ff.FileName.c_str(),1,ff.FileName.size(),fi);
		//fl.write(,);
		WriteUL(ff.OffSet+off);
		WriteUL(ff.FileSize);
	}

}


ULONG MediaDev::Assets::AssetNative::GetFileSizeF(System::String^ File)
{
	ifstream f(NetString(File),ios::binary);

	if(!f.is_open() ||!f.good()) return -1;

	f.seekg(0,ios::end);
	ULONG t;
	t= (ULONG)f.tellg();
	f.close();
	return t;
}
System::String^ MediaDev::Assets::AssetNative::GetFileName(System::String^ File)
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

MediaDev::Assets::AssetNative::AssetNative(void)
{

ULONG off=8;
isopen=false;
encrypted=false;

Files= new cl<FileEntry>;
fi=new FILE();
}

MediaDev::Assets::AssetNative::~AssetNative(void)
{
	Enc=NULL;
	Dec=NULL;
	fi=NULL;
}

// Encryption Algorithm
void MediaDev::Assets::AssetNative::CreateEncryption()
{

	cl<BYTE> tmp= cl<BYTE>();
	
	Enc= new BYTE[255];

	for(int x=0;x<256;x++)
	{
		tmp.Add(x);
	}
		
	int bx=0;


	while (tmp.Count()!=0)
	{

		//Enc[bx];
		int id=rand() % tmp.Count();
		memcpy(&Enc[bx],&tmp[id],sizeof(BYTE));
		
		tmp.Remove(id);
		bx++;
	}


}
bool MediaDev::Assets::AssetNative::CreateDecryption()
{
	if(Enc==NULL) return false;

	Dec= new BYTE[255];

	for(int x=0;x<256;x++)
	{
		Dec[Enc[x]]=x;
	}

	return true;
}
void MediaDev::Assets::AssetNative::CreateEncryption(BYTE* enc)
{
	Enc=enc;
}
BYTE* MediaDev::Assets::AssetNative::GetEncryption()
{
	return Enc;
}
bool MediaDev::Assets::AssetNative::LoadEncryption(System::String^ encFile)
{
	//if(Enc==NULL) return false;

	std::ifstream f(NetString(encFile), ios::binary);

	// check if the file exists or readable
	if(!f.is_open()){f.close(); return false;}



	f.seekg(0, ios::end);

	if(f.tellg()<255)
	{
		f.close();
		return false;
	}


	Enc= new BYTE[255];


	f.seekg(0,ios::beg);

	for(int x=0;x<256;x++)
	{
		Enc[x]=f.get();
	}
	f.close();
	
	return true;
}
bool MediaDev::Assets::AssetNative::SaveEncryption(System::String^ encFile)
{
	if(Enc==NULL) return false;

	ofstream f(NetString(encFile), ios::binary);

	if(!f.good()){f.close(); return false;}

	for(int x=0;x<256;x++)
	{
		f.put(Enc[x]);
	}

	f.flush();
	f.close();
	return true;
}

// Encrypt (*Files)
bool MediaDev::Assets::AssetNative::EncryptFileA(System::String^ InFile,System::String^ OutFile)
{
	if(Enc==NULL) return false;

	ifstream r(NetString(InFile), ios::binary);

	if(!r.is_open())
	{
		r.close();
		return false;
	}

	ofstream w(NetString(OutFile), ios::binary);

	if(!w.good())
	{
		r.close();
		w.close();
		return false;
	}

	while(r.good())
	{
		BYTE lp=Enc[r.get()];
		
		if(r.good()) w.put(lp) ;
		
	}

	r.close();
	w.flush();
	w.close();

	return true;

}
BYTE* MediaDev::Assets::AssetNative::GetEncryptedFileA(System::String^ InFile,System::String^ OutFile)
{

	std::streamoff l;
	if(Enc==NULL) return NULL;

	ifstream r(NetString(InFile), ios::binary);

	if(!r.is_open())
	{
		r.close();
		return false;
	}

	r.seekg(0,ios::end);

	l= r.tellg();

	r.seekg(0,ios::beg);

	BYTE* tmp= new BYTE[(UINT)l];

	int p=0;
	while(r.good())
	{
		BYTE lp=Enc[r.get()];
		
		if(r.good()) tmp[p]=lp ;
			p++;
	}

	r.close();

	return tmp;
}

// File
bool MediaDev::Assets::AssetNative::DecryptFileA(System::String^ InFile,System::String^ OutFile)
{
		if(Dec==NULL) return false;
		

	ifstream r(NetString(InFile), ios::binary);

	if(!r.is_open())
	{
		r.close();
		return false;
	}

	ofstream w(NetString(OutFile), ios::binary);

	if(!w.good())
	{
		r.close();
		w.close();
		return false;
	}

	while(r.good())
	{
		BYTE lp=Dec[r.get()];
		
		if(r.good()) w.put(lp) ;
		
	}

	r.close();
	w.flush();
	w.close();

	return true;
}
BYTE* MediaDev::Assets::AssetNative::GetDecryptedFileA(System::String^ InFile,System::String^ OutFile)
{
			if( Dec==NULL) return NULL;

				std::streamoff l;

	ifstream r(NetString(InFile), ios::binary);

	if(!r.is_open())
	{
		r.close();
		return false;
	}

	r.seekg(0,ios::end);

	l= r.tellg();

	r.seekg(0,ios::beg);

	BYTE* tmp= new BYTE[(UINT)l];

	int p=0;
	while(r.good())
	{
		BYTE lp=Dec[r.get()];
		
		if(r.good()) tmp[p]=lp ;
			p++;
	}

	r.close();

	return tmp;
}

// Pack (*Files)
bool MediaDev::Assets::AssetNative::CreateNewPack()
{
	(*Files)= cl<FileEntry>();
	off=8;
	//ULONG off=8;
	isopen=false;
	encrypted=false;

	
//ULONG off=8;
//isopen=false;
//encrypted=false;

//Files= new cl<FileEntry>;
//fi=new FILE();
	return true;
}

bool MediaDev::Assets::AssetNative::AddFile(System::String^ File)
{
	FileEntry file;



	file.FileName= NetString(GetFileName(File));
	file.FileSize= GetFileSizeF(File);
	file.FullFile=NetString(File);
	file.OffSet=0;
	if((*Files).Count()>0)
	{
		int i= (*Files).Count()-1;
	
		file.OffSet= (*Files)[i].OffSet+(*Files)[i].FileSize;
	}

	if(file.FileName.size()==0 || file.FileSize==-1) return false;
	
	off+=9+(file.FileName.size());

	(*Files).Add(file);

	return true;
}

bool MediaDev::Assets::AssetNative::Pack(System::String^ File)
{
	//fl= ofstream(File,ios::binary);
	fi=fopen(NetString(File).data(),"wb");
	if(fi==NULL || (*Files).Count()==0){fclose(fi); return false;}

	WriteHeader(false);
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

bool MediaDev::Assets::AssetNative::PackAndEncrypt(System::String^ File)
{
	//fl= ofstream(File,ios::binary);

	if(fi==NULL || (*Files).Count()==0){fclose(fi); return false;}

	WriteHeader(true);
	for(int x=0;x<(*Files).Count();x++)
	{
		FileEntry ff=(*Files)[x];
		ifstream r(ff.FullFile, ios::binary);

		if(!r.is_open()){r.close();fclose(fi); return false;}

		while(r.good())
		{
			BYTE t= r.get();

			if(r.good()) fputc((Enc[t]),fi);;

		}
		r.close();
		fflush(fi);
	}



	fflush(fi);
	//fflush(fi);
	fclose(fi);
	return true;
		return true;
}

bool MediaDev::Assets::AssetNative::LoadPack(System::String^ File)
{
	if(isopen) fclose(fi);
	//fs= ifstream(File,ios::binary);
	fi=fopen(NetString(File).c_str(),"rb");
	if(fi==NULL) {fclose(fi); return false;}
	    

	try
	{

	if( fgetc(fi)!='A'||  fgetc(fi)!='P'|| fgetc(fi)!='F'){fclose(fi); return false;}

     encrypted=  fgetc(fi)==1? true:false;
	
	 ULONG filez= GetUL();
	 
	 CreateNewPack();

	 for(ULONG x=0;x<filez;x++)
	 {
		 FileEntry fe;
		 fe.FileName= NetString(ReadString());
		 fe.OffSet=GetUL();
		 fe.FileSize=GetUL();

		 (*Files).Add(fe);
		 
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

bool MediaDev::Assets::AssetNative::LoadPack(BYTE* File,int offset, int length)
{
	return true;
}
	
// Get Data
bool MediaDev::Assets::AssetNative::GetData(System::String^ EntryName, System::String^ OutFile)
{
	if(!isopen) return false;

	for(int x=0;x<(*Files).Count();x++)
	{
		if(CompareStringLP(NetString(EntryName),(*Files)[x].FileName)==true)
		{
			return GetData(x,OutFile);
		}
	}

	return false;
}

bool MediaDev::Assets::AssetNative::GetData(int Index, System::String^ OutFile)
{
	if(!isopen || (*Files).Count()<=Index|| Index<0) return false;

	ofstream w(NetString(OutFile),ios::binary);

	if(!w.good()){w.close(); return false;}

	FileEntry fe= (*Files)[Index];

	//fs.seekg(0,ios::beg);
	fseek(fi,fe.OffSet,0);
	//fs.seekg(,ios::beg);
	

	//w.write(fs.);
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

BYTE* MediaDev::Assets::AssetNative::GetDataByte(System::String^ EntryName)
{
	if(!isopen) return NULL;
	
	for(int x=0;x<((*Files)).Count();x++)
	{
		if(CompareStringLP(NetString(EntryName),(*Files)[x].FileName)==true)
		{
		return GetDataByte(x);
		}
	}
	return NULL;
}

BYTE* MediaDev::Assets::AssetNative::GetDataByte(int Index)
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
		
// Get Encrypted Data
bool MediaDev::Assets::AssetNative::GetEncryptedData(System::String^ EntryName, System::String^ OutFile)
{
	if(!isopen) return false;

	for(int x=0;x<(*Files).Count();x++)
	{
		if(CompareStringLP(NetString(EntryName),(*Files)[x].FileName)==true)
		{
			return GetEncryptedData(x,OutFile);
		}
	}

	return false;
}

bool MediaDev::Assets::AssetNative::GetEncryptedData(int Index, System::String^ OutFile)
{
	if(!isopen || (*Files).Count()<=Index|| Index<0 ||Dec==NULL) return false;

	ofstream w(NetString(OutFile),ios::binary);

	if(!w.good()){w.close(); return false;}

	FileEntry fe= (*Files)[Index];

	//fs.seekg(0,ios::beg);
	fseek(fi,fe.OffSet,0);
	

	//w.write(fs.);
	ULONG x=fe.FileSize;

	while(x>0)
	{
		w.put(Dec[ fgetc(fi)]);

		x--;
	}
	w.flush();
	w.close();
	return true;
}

BYTE* MediaDev::Assets::AssetNative::GetEncryptedDataByte(System::String^ EntryName)
{
	if(!isopen) return NULL;

	for(int x=0;x<(*Files).Count();x++)
	{
		if(CompareStringLP(NetString(EntryName),(*Files)[x].FileName)==true)
		{
			return GetEncryptedDataByte(x);
		}
	}
		return NULL;
}

BYTE* MediaDev::Assets::AssetNative::GetEncryptedDataByte(int Index)
{

	if(!isopen || (*Files).Count()<=Index|| Index<0||Dec==NULL) return NULL;



	FileEntry fe= (*Files)[Index];
	BYTE* d=new BYTE[fe.FileSize];

	fseek(fi,fe.OffSet,0);
	

	for(ULONG x=0;x<fe.FileSize;x++)
	{
		d[x]=Dec[ fgetc(fi)];
	}

	return d;
}

ULONG MediaDev::Assets::AssetNative::GetFileSize(System::String^ EntryName)
{
	if(!isopen) return -1;

	for(int x=0;x<(*Files).Count();x++)
	{
		if(CompareStringLP(NetString(EntryName),(*Files)[x].FileName)==true)
		{
			return GetFileSize(x);
		}
	}

	return -1;
}

ULONG MediaDev::Assets::AssetNative::GetFileSize(int Index)
{
	if(!isopen || (*Files).Count()<=Index|| Index<0) return -1;
	return  (*Files)[Index].FileSize;
}

ULONG MediaDev::Assets::AssetNative::GetFilesCount()
{
	if(!isopen) return -1;

	return (*Files).Count();
}

bool MediaDev::Assets::AssetNative::PackIsEncrypted()
{

	return encrypted;
}

bool MediaDev::Assets::AssetNative::ClosePack()
{
	fclose(fi);

	fclose(fi);
	fi=NULL;
	isopen=false;
	return true;
}