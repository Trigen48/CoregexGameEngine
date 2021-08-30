#include "MediaVideo.h"
#include <string>

#pragma comment ( lib, "winmm.lib" )

#pragma comment ( lib, "quartz.lib" )
#pragma comment ( lib, "msacm32.lib" )
#pragma comment ( lib, "strmiids.lib" )

VideoFile::VideoFile()
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

	//_win= CreateWindowExA(
}

bool VideoFile::Load(LPCWSTR lpwstrFile,HWND hWnd)
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

	if(!m_pMediaControl)
	{
		return FALSE;
	}

	m_pGraph->QueryInterface(
		IID_IMediaEvent,
		(void **)&m_pEvent);

	if(!m_pEvent)
	{
		
		return FALSE;
	}


		m_pGraph->QueryInterface(
		IID_IVideoWindow,
		(void **)&m_pVidWin);

	if(!m_pVidWin)
	{
		
		return FALSE;
	}



	playing=false;
	Stop();

	ret=m_pGraph->RenderFile(
		lpwstrFile, 
		NULL);
	if(ret!=S_OK)
	{
        
		return FALSE;
	}

	if (m_pGraph->QueryInterface ( IID_IBasicAudio, ( void** ) &m_pBasic ) )
	{

		return false;
	}



	// get the MediaPosition interface
	if (m_pGraph->QueryInterface ( IID_IMediaPosition, ( void** )&m_pPosition ) ) 
	{
		
		return false;
	}

	
	if (m_pGraph->QueryInterface ( IID_IMediaSeeking, ( void** )&m_pSeeking ) ) 
	{
		
		return false;
	}

	/*m_pVidWin->put_Owner((OAHWND)hWnd);
	m_pVidWin->put_WindowState(WS_CHILD | WS_CLIPSIBLINGS);*/

	m_pVidWin->put_AutoShow(OAFALSE); 
	m_pVidWin->put_Owner((OAHWND)hWnd);
	m_pVidWin->put_WindowState( WS_CLIPSIBLINGS | WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE );
	//m_pVidWin->

	RECT rc;
	GetClientRect(hWnd, &rc);
	m_pVidWin->SetWindowPosition(0, 0, rc.right, rc.bottom);
	m_pVidWin->put_Visible(OATRUE);  

	

	return TRUE;
}
bool VideoFile::Play()
{

	if (playing==true)
	{
		return false;
	}


	if(m_pMediaControl->Run()==S_OK)
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

bool VideoFile::Pause()
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

bool VideoFile::SetVolume(int Level)
{

	if (Level<0)
	{
		Level=100;
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
bool VideoFile::Stop()
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
bool VideoFile::SetSpeed(int speed)
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
bool VideoFile::Loop(bool OnOff)
{

	loop=OnOff;

	return true;
}

long VideoFile::GetDuration()
{

__int64 d=NULL;


if(FAILED(m_pSeeking->GetDuration(&d)))
{
	return 0;
}


	return d;
}
long VideoFile::GetCurrectPosition()
{
__int64 d=NULL;



if(FAILED(m_pSeeking->GetCurrentPosition(&d)))
{
	return 0;
}


	return d;
}

bool VideoFile::SetPosition(long position)
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
bool VideoFile::Destroy()
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
int VideoFile::GetSpeed()
{
	return Speed;
}
bool VideoFile::Update()
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