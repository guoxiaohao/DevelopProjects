#include "stdafx.h"
#include "ControlAudio.h"



CControlAudio::CControlAudio()
{
	CoInitialize(NULL);

	IMMDeviceEnumerator* m_lpDeviceEnumerator = nullptr;
	IMMDevice* m_lpDevice = nullptr;
	IAudioEndpointVolume* m_lpAudioEndpointVolume = nullptr;
	IAudioClient* m_lpAudioClient = nullptr;
}

CControlAudio::~CControlAudio()
{
	CoUninitialize();

	if (m_lpAudioClient!=nullptr)
	{
		m_lpAudioClient->Release();
		m_lpAudioClient = nullptr;
	}
	if (m_lpAudioEndpointVolume != nullptr)
	{
		m_lpAudioEndpointVolume->Release();
		m_lpAudioEndpointVolume = nullptr;
	}
	if (m_lpDevice != nullptr)
	{
		m_lpDevice->Release();
		m_lpDevice = nullptr;
	}
	if (m_lpDeviceEnumerator != nullptr)
	{
		m_lpDeviceEnumerator->Release();
		m_lpDeviceEnumerator = nullptr;
	}
}

void CControlAudio::InitConfig()
{
	HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
		(LPVOID*)&m_lpDeviceEnumerator);
	if (FAILED(hr))
	{
		return;
	}

	hr = m_lpDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &m_lpDevice);
	if (FAILED(hr))
	{
		m_lpDeviceEnumerator->Release();
		m_lpDeviceEnumerator = nullptr;
		return;
	}

	hr = m_lpDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (LPVOID*)&m_lpAudioEndpointVolume);
	if (FAILED(hr))
	{
		m_lpDevice->Release();
		m_lpDevice = nullptr;
		m_lpDeviceEnumerator->Release();
		m_lpDeviceEnumerator = nullptr;
		return;
	}

	hr = m_lpDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (LPVOID*)&m_lpAudioClient);
	if (FAILED(hr))
	{
		m_lpAudioEndpointVolume->Release();
		m_lpAudioEndpointVolume = nullptr;
		m_lpDevice->Release();
		m_lpDevice = nullptr;
		m_lpDeviceEnumerator->Release();
		m_lpDeviceEnumerator = nullptr;
		return;
	}
}

void CControlAudio::SetAudio()
{
	HRESULT hr = m_lpAudioEndpointVolume->SetMute(FALSE, NULL);
}

void CControlAudio::ResetAudio()
{
	HRESULT hr = m_lpAudioEndpointVolume->SetMute(TRUE, NULL);
}

void CControlAudio::AddAudio()
{
	float m_fVolumeValue;
	HRESULT hr = m_lpAudioEndpointVolume->GetMasterVolumeLevelScalar(&m_fVolumeValue);
	if (SUCCEEDED(hr))
	{
		m_fVolumeValue = m_fVolumeValue * 100;
		m_fVolumeValue = m_fVolumeValue + 1;
		m_fVolumeValue = m_fVolumeValue / 100;
		hr = m_lpAudioEndpointVolume->SetMasterVolumeLevelScalar(m_fVolumeValue, &GUID_NULL);
	}
}

void CControlAudio::PlusAudio()
{
	float m_fVolumeValue;
	HRESULT hr = m_lpAudioEndpointVolume->GetMasterVolumeLevelScalar(&m_fVolumeValue);
	if (SUCCEEDED(hr))
	{
		m_fVolumeValue = m_fVolumeValue * 100;
		m_fVolumeValue = m_fVolumeValue - 1;
		m_fVolumeValue = m_fVolumeValue / 100;
		hr = m_lpAudioEndpointVolume->SetMasterVolumeLevelScalar(m_fVolumeValue, &GUID_NULL);
	}
}