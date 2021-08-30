#include "MediaMusic.h"

#pragma comment ( lib, "winmm.lib" )

#pragma comment ( lib, "quartz.lib" )
#pragma comment ( lib, "msacm32.lib" )
#pragma comment ( lib, "strmiids.lib" )


AudioFile::AudioFile()
{
	m_pGraph=NULL;
	m_pMediaControl=NULL;
	m_pEvent=NULL;
    m_pBasic = NULL;
    m_pSeeking = NULL;
	m_pPosition=NULL;
	playing=false;
	paused=false;
	Speed=0;
	loop=false;
}
bool AudioFile::Load(LPCWSTR lpwstrFile)
{
    CoInitialize(NULL);

	HRESULT ret;
	//-----------------------------------
    // Create the filter graph manager.
    CoCreateInstance(CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC, 
        IID_IGraphBuilder,
		(void **)&m_pGraph);


	//-----------------------------------
	//Get a Media Control Interface.
    m_pGraph->QueryInterface(
		IID_IMediaControl,
		(void **)&m_pMediaControl);

	if(FAILED(m_pMediaControl))
	{
		return FALSE;
	}

	m_pGraph->QueryInterface(
		IID_IMediaEvent,
		(void **)&m_pEvent);



	playing=false;
	Stop();

	ret=m_pGraph->RenderFile(
		lpwstrFile, 
		NULL);

	if(FAILED(ret))
	{
		return false;
	}

	m_pGraph->QueryInterface ( IID_IBasicAudio, ( void** ) &m_pBasic );

	// get the MediaPosition interface
	m_pGraph->QueryInterface ( IID_IMediaPosition, ( void** )&m_pPosition );



	m_pGraph->QueryInterface ( IID_IMediaSeeking, ( void** )&m_pSeeking ) ;

	//m_pMediaControl->Run();

	return TRUE;
}
bool AudioFile::Play()
{

	if (playing==true)
	{
		return false;
	}


	if(!FAILED(m_pMediaControl->Run()))
	{
		paused=false;
		playing=true;
	}
	else
	{
		return false;
	}

	return true;

}
bool AudioFile::Pause()
{

	if(playing==false)
	{
		return false;
	}

	if(paused==true)
	{
		return false;
	}

if(m_pMediaControl->Pause()==S_OK)
{
}
else
{
	return false;
}


playing=false;
paused=true;

	return true;
}
bool AudioFile::SetVolume(int Level)
{

	if (Level<0)
	{
		Level=0;
	}

	if (Level>100)
	{
		Level=100;
	}

	HMIXER m_hMixer = NULL;
	// get dwLineID
		DWORD m_dwVolumeControlID = 0;
		MIXERLINE mxl;
		mxl.cbStruct = sizeof(MIXERLINE);
		mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
		if (::mixerGetLineInfo(reinterpret_cast<HMIXEROBJ>(m_hMixer),
							   &mxl,
							   MIXER_OBJECTF_HMIXER |
							   MIXER_GETLINEINFOF_COMPONENTTYPE)
			!= MMSYSERR_NOERROR)
			return false;

		// get dwControlID
		MIXERCONTROL mxc;
		MIXERLINECONTROLS mxlc;
		mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
		mxlc.dwLineID = mxl.dwLineID;
		mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
		mxlc.cControls = 1;
		mxlc.cbmxctrl = sizeof(MIXERCONTROL);
		mxlc.pamxctrl = &mxc;
		if (::mixerGetLineControls(reinterpret_cast<HMIXEROBJ>(m_hMixer),
								   &mxlc,
								   MIXER_OBJECTF_HMIXER |
								   MIXER_GETLINECONTROLSF_ONEBYTYPE)
			!= MMSYSERR_NOERROR)
			return false;

		// store dwControlID
		DWORD m_dwMinimum = mxc.Bounds.dwMinimum;
		DWORD m_dwMaximum = mxc.Bounds.dwMaximum;
		m_dwVolumeControlID = mxc.dwControlID;

		// set volume
		DWORD dwVal = (DWORD)(((m_dwMaximum - m_dwMinimum)/100.0f) * Level);
		MIXERCONTROLDETAILS_UNSIGNED mxcdVolume = { dwVal };
		MIXERCONTROLDETAILS mxcd;
		mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
		mxcd.dwControlID = m_dwVolumeControlID;
		mxcd.cChannels = 1;
		mxcd.cMultipleItems = 0;
		mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
		mxcd.paDetails = &mxcdVolume;
		if (::mixerSetControlDetails(reinterpret_cast<HMIXEROBJ>(m_hMixer),
									 &mxcd,
									 MIXER_OBJECTF_HMIXER |
									 MIXER_SETCONTROLDETAILSF_VALUE)
			!= MMSYSERR_NOERROR)
				return false;
	
	if (m_hMixer != NULL)
	{
		BOOL bSucc = (::mixerClose(m_hMixer) == MMSYSERR_NOERROR);
		m_hMixer = NULL;
	}
	else
	{
		// basic audio interface required for music volume change
		if ( !m_pBasic )
		{
			return false;
		}
		long PLevel = -2500 - (Level * -25);
		if(Level>0)
			m_pBasic->put_Volume ( PLevel );
		else
			m_pBasic->put_Volume ( -10000 );
	}

	return true;
}

int AudioFile::GetVolume()
{
	int Level=0;

	HMIXER m_hMixer = NULL;
	// get dwLineID
		DWORD m_dwVolumeControlID = 0;
		MIXERLINE mxl;
		mxl.cbStruct = sizeof(MIXERLINE);
		mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
		if (::mixerGetLineInfo(reinterpret_cast<HMIXEROBJ>(m_hMixer),
							   &mxl,
							   MIXER_OBJECTF_HMIXER |
							   MIXER_GETLINEINFOF_COMPONENTTYPE)
			!= MMSYSERR_NOERROR)
			return -1;

		// get dwControlID
		MIXERCONTROL mxc;
		MIXERLINECONTROLS mxlc;
		mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
		mxlc.dwLineID = mxl.dwLineID;
		mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
		mxlc.cControls = 1;
		mxlc.cbmxctrl = sizeof(MIXERCONTROL);
		mxlc.pamxctrl = &mxc;
		if (::mixerGetLineControls(reinterpret_cast<HMIXEROBJ>(m_hMixer),
								   &mxlc,
								   MIXER_OBJECTF_HMIXER |
								   MIXER_GETLINECONTROLSF_ONEBYTYPE)
			!= MMSYSERR_NOERROR)
			return -1;

		// store dwControlID
		DWORD m_dwMinimum = mxc.Bounds.dwMinimum;
		DWORD m_dwMaximum = mxc.Bounds.dwMaximum;
		m_dwVolumeControlID = mxc.dwControlID;

		// set volume
		DWORD dwVal = (DWORD)(((m_dwMaximum - m_dwMinimum)/100.0f) * Level);
		MIXERCONTROLDETAILS_UNSIGNED mxcdVolume = { dwVal };
		MIXERCONTROLDETAILS mxcd;
		mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
		mxcd.dwControlID = m_dwVolumeControlID;
		mxcd.cChannels = 1;
		mxcd.cMultipleItems = 0;
		mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
		mxcd.paDetails = &mxcdVolume;
		if (::mixerSetControlDetails(reinterpret_cast<HMIXEROBJ>(m_hMixer),
									 &mxcd,
									 MIXER_OBJECTF_HMIXER |
									 MIXER_SETCONTROLDETAILSF_VALUE)
			!= MMSYSERR_NOERROR)
				return -1;
	
	if (m_hMixer != NULL)
	{
		BOOL bSucc = (::mixerClose(m_hMixer) == MMSYSERR_NOERROR);
		m_hMixer = NULL;
		Level=-1;
	}
	else
	{
		// basic audio interface required for music volume change
		if ( !m_pBasic )
		{
			return false;
		}
		long PLevel = -2500 - (Level * -25);
		if(Level>0)
			m_pBasic->put_Volume ( PLevel );
		else
			m_pBasic->put_Volume ( -10000 );

		long* val= new long();
		m_pBasic->get_Volume(val);
		Level= (int)val;
	}

	return Level;
}
bool AudioFile::Stop()
{

	if (playing==false)
	{
		return false;
	}

	__int64 pos = 0;
 if (FAILED(m_pSeeking->SetPositions ( &pos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning )))
 {
	 return false;
 }

if(m_pMediaControl->Stop()==S_OK)
{


	playing=false;
}
else
{
	return false;
}

	

	return true;
}
bool AudioFile::SetSpeed(int speed)
{

	if ( speed < 0 )
	{
		
		return false;
	}

	m_pMediaControl->Pause();
	m_pSeeking->SetRate( (double)speed/100.0 );
	m_pPosition->put_Rate( (double)speed/100.0 );
	m_pMediaControl->Run();


	Speed=speed;
	return true;
}
bool AudioFile::Loop(bool OnOff)
{

	loop=OnOff;

	return true;
}
long AudioFile::GetDuration()
{

	__int64 d=NULL;


	if(FAILED(m_pSeeking->GetDuration(&d)))
	{
		return 0;
	}


	return d;
}
long AudioFile::GetCurrectPosition()
{
	__int64 d=NULL;


	if(FAILED(m_pSeeking->GetCurrentPosition(&d)))
	{
		return 0;
	}


	return d;
}
bool AudioFile::SetPosition(long position)
{

	__int64 c=position;

	Pause();

	if(FAILED(m_pSeeking->SetPositions ( &c, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning )))
	{
		return false;
	}

	Play();

	return true;

}
bool AudioFile::Destroy()
{
	m_pGraph->Release();
	m_pMediaControl->Release();
	m_pEvent->Release();
    m_pBasic->Release();
    m_pSeeking->Release();
	m_pPosition->Release();

	m_pGraph= NULL;
	m_pMediaControl= NULL;
	m_pEvent= NULL;
    m_pBasic= NULL;
    m_pSeeking= NULL;
	m_pPosition= NULL;


	return true;
}
int  AudioFile::GetSpeed()
{
	return Speed;
}
bool AudioFile::Update()
{

__int64 d=NULL;
__int64 c=NULL;
__int64 pos = 0;

	switch(loop)
	{

	case true:
	


if(FAILED(m_pSeeking->GetPositions(&c,&d)))
{
	return false;
}

if(d==c)
{



if(!m_pMediaControl)
{
	return false;
}

if(!m_pSeeking)
{
	return false;
}

m_pMediaControl->Stop();
m_pSeeking->SetPositions ( &pos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning );
m_pMediaControl->Run();

}
else
{
	return false;
}

break;


	case false:
m_pMediaControl->Stop();
m_pSeeking->SetPositions ( &pos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning );
return true;
		break;

	}

return true;
}