#include "Sound.h"

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

struct WaveHeader
	{
	public:
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};



SoundFile::SoundFile(void)
{
	volume=DSBVOLUME_MAX;
	position=0;
	//Init();
}


bool SoundFile::Init(HWND window)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
//	WAVEFORMATEX waveFormat;
		volume=DSBVOLUME_MAX;
	position=0;
	
	// Initialize the direct sound interface pointer for the default sound device.
	result = DirectSoundCreate8(NULL, &m_DirectSound, NULL);
	if(FAILED(result))
	{
		return false;
	}
	
	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	if(window!=NULL)
	{
		
		result = m_DirectSound->SetCooperativeLevel(window, DSSCL_PRIORITY);
	}
	else
	{
		
		result = m_DirectSound->SetCooperativeLevel(GetDesktopWindow() , DSSCL_NORMAL);
	}

	if(FAILED(result))
	{
		return false;
	}

	// Setup the primary buffer description.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME ;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Get control of the primary sound buffer on the default sound device.
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if(FAILED(result))
	{
		return false;
	}

	iny=true;
	return true;
}
void SoundFile::Destroy(void)
{	

	// Release the secondary sound buffer.
	if(m_secondaryBuffer)
	{
		(m_secondaryBuffer)->Release();
		m_secondaryBuffer = 0;
	}
		// Release the primary sound buffer pointer.
	if(m_primaryBuffer)
	{
		m_primaryBuffer->Release();
		m_primaryBuffer = 0;
	}

	// Release the direct sound interface pointer.
	if(m_DirectSound)
	{
		m_DirectSound->Release();
		m_DirectSound = 0;
	}



}

bool SoundFile::Load(LPCSTR File)
{
	//if(!iny) Init(wind);

		int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeader waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;


	// Open the wave file in binary.
	error = fopen_s(&filePtr, File, "rb");
	if(error != 0)
	{
		return false;
	}

	// Read in the wave file header.
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if(count != 1)
	{
		return false;
	}
	/*
	// Check that the chunk ID is the RIFF format.
	if((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') || 
	   (waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		return false;
	}

	// Check that the file format is the WAVE format.
	if((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
	   (waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		return false;
	}

	// Check that the sub chunk ID is the fmt format.
	if((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
	   (waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		return false;
	}

	// Check that the audio format is WAVE_FORMAT_PCM.
	if(waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}

	// Check that the wave file was recorded in stereo format.
	if(waveFileHeader.numChannels != 2)
	{
		return false;
	}

	// Check that the wave file was recorded at a sample rate of 44.1 KHz.
	if(waveFileHeader.sampleRate != 44100)
	{
		return false;
	}

	// Ensure that the wave file was recorded in 16 bit format.
	if(waveFileHeader.bitsPerSample != 16)
	{
		return false;
	}

	// Check for the data chunk header.
	if((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
	   (waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
	{
		return false;
	}

	*/


	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	waveFormat.wFormatTag = waveFileHeader.audioFormat;
	waveFormat.nSamplesPerSec = waveFileHeader.sampleRate;
	waveFormat.wBitsPerSample = waveFileHeader.bitsPerSample;
	waveFormat.nChannels = waveFileHeader.numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;
	
	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME ;
		     
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create a temporary sound buffer with the specific buffer settings.
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&m_secondaryBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the temporary buffer.
	tempBuffer->Release();
	tempBuffer = 0;

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(filePtr, sizeof(WaveHeader), SEEK_SET);

	// Create a temporary buffer to hold the wave file data.
	waveData = new unsigned char[waveFileHeader.dataSize];
	if(!waveData)
	{
		return false;
	}

	// Read in the wave file data into the newly created buffer.
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if(count != waveFileHeader.dataSize)
	{
		return false;
	}

	// Close the file once done reading.
	error = fclose(filePtr);
	if(error != 0)
	{
		return false;
	}

	// Lock the secondary buffer to write wave data into it.
	result = (m_secondaryBuffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if(FAILED(result))
	{
		return false;
	}

	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

	// Unlock the secondary buffer after the data has been written to it.
	result = (m_secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if(FAILED(result))
	{
		return false;
	}
	
	// Release the wave data since it was copied into the secondary buffer.
	delete [] waveData;
	waveData = 0;

	return true;
}

bool SoundFile::Play()
{

	// Set position at the beginning of the sound buffer.

	if(FAILED(m_secondaryBuffer->SetCurrentPosition(0)))
	{
		return false;
	}

	// Set volume of the buffer to 100%.
	
	if(FAILED(m_secondaryBuffer->SetVolume(volume)))
	{
		return false;
	}
	
	// Play the contents of the secondary sound buffer.
	if(FAILED(m_secondaryBuffer->Play(0, 0, 0)))
	{
		return false;
	}
	return true;
}

	bool SoundFile::IsPlaying()
	{
			LPDWORD g=0;
	m_secondaryBuffer->GetStatus(g);

	return true;
	}
	bool SoundFile::IsStoped()
	{
		return true;
	}



	bool SoundFile::Stop()
	{


	if(FAILED(m_secondaryBuffer->Stop()))
	{
		return false;
	}

	position=0;
		return true;
	}
	bool SoundFile::Pause()
	{
		return true;
	}

	bool SoundFile::SetVolume(long value)
	{
	
	if(FAILED(m_secondaryBuffer->SetVolume(value)))
	{
		return false;
	}
	volume=value;

		return true;
	}
	bool SoundFile::SetSpeed(long value)
	{
		return true;
	}

	bool SoundFile::SetPosition(long value)
	{

	if(FAILED(m_secondaryBuffer->SetCurrentPosition(position)))
	{
		return false;
	}

		return true;
	}

	long SoundFile::GetVolume()
	{
		//HRESULT
		if(FAILED(m_secondaryBuffer->GetVolume((LPLONG)volume)))
		{
			return -1;
		}

		return volume;
	}

	long SoundFile::GetSpeed()
	{

		return -1;
	}

	long SoundFile::GetPosition()
	{

		LPDWORD h1=0,h2=0;
		if(FAILED(m_secondaryBuffer->GetCurrentPosition(h1,h2)))
		{
			return -1;
		}
		


		return position;
	}