#pragma once

#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <Audioclient.h>

class CControlAudio
{
public:
	CControlAudio();
	~CControlAudio();
public:
	void InitConfig();
	void SetAudio();
	void ResetAudio();
	void AddAudio();
	void PlusAudio();
private:
	IMMDeviceEnumerator* m_lpDeviceEnumerator;
	IMMDevice* m_lpDevice;
	IAudioEndpointVolume* m_lpAudioEndpointVolume;
	IAudioClient* m_lpAudioClient;
};

