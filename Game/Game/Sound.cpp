#include "stdafx.h"
#include "Sound.h"

Sound* Sound::m_instance = nullptr;

Sound::Sound(HWND hWnd)
{
	m_primaryBuffer = 0;
	HRESULT result;
	DSBUFFERDESC bufferDesc; //describe the buffer
	result = DirectSoundCreate8(NULL, &m_pDevice, NULL);

	if (FAILED(result))
	{
		std::cout << "Can not create device";
	}

	result = m_pDevice->SetCooperativeLevel(hWnd, DSSCL_PRIORITY); // set the cooperative level.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	result = m_pDevice->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);

	if (FAILED(result))
	{
		std::cout << "Can not create primaryBuffer";
	}
	volume = 95.0f;
	isMute = false;
	loadResources();
}

Sound::~Sound()
{
	for (auto it = m_soundBufferMap.begin(); it != m_soundBufferMap.end(); it++)
	{
		if (it->second)
		{
			it->second->Release();
			it->second = nullptr;
		}

	}

	if (m_primaryBuffer)
		m_primaryBuffer->Release();
	if (m_pDevice)
		m_pDevice->Release();
	m_pDevice = nullptr;
	m_primaryBuffer = nullptr;
}

void Sound::initialize(HWND hWnd)
{
	if (m_instance == nullptr)
	{
		m_instance = new Sound(hWnd);
	}
}

Sound * Sound::getInstance()
{
	if (m_instance == nullptr)
	{
		MessageBox(NULL, L"Failed to create Sound System", L"Error", MB_OK);
	}
	else 
	{
		return m_instance;
	}
}



void Sound::loadResources()
{
	this->loadSound((char*)"Resources/sound/background-level-1.wav", "background-level-1");
	this->loadSound((char*)"Resources/sound/background-boss-level.wav", "background-boss-level");
}

float Sound::getVolume()
{
	return volume;
}

void Sound::loadSound(char* fileName, std::string name)
{
	if (m_soundBufferMap.find(name) != m_soundBufferMap.end())
		return;
	FILE* filePtr;
	WaveHeaderStruct waveHeaderStruct;
	IDirectSoundBuffer* tempBuffer;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
	unsigned char* wavData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;

	int error = fopen_s(&filePtr, fileName, "rb");
	if (error != 0)
	{
		std::cout << " Can not load " << fileName << "\n";
		return;
	}

	fread(&waveHeaderStruct, sizeof(WaveHeaderStruct), 1, filePtr);
	if ((waveHeaderStruct.format[0] != 'W') || (waveHeaderStruct.format[1] != 'A') ||
		(waveHeaderStruct.format[2] != 'V') || (waveHeaderStruct.format[3] != 'E'))
	{
		std::cout << " file format does not support" << fileName << "\n";
	}

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = waveHeaderStruct.sampleRate;
	waveFormat.wBitsPerSample = waveHeaderStruct.bitsPerSample;
	waveFormat.nChannels = waveHeaderStruct.numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	bufferDesc.dwBufferBytes = waveHeaderStruct.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer8* secondaryBuffer = 0;
	IDirectSoundBuffer8** pSecondaryBuffer = &secondaryBuffer;

	m_pDevice->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	auto result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&(*pSecondaryBuffer));

	tempBuffer->Release();
	tempBuffer = 0;

	if (FAILED(result))
	{
		std::cout << " Can not create secondaryBuffer " << "\n";
		return;
	}

	fseek(filePtr, sizeof(WaveHeaderStruct), SEEK_SET);
	wavData = new unsigned char[waveHeaderStruct.dataSize];
	fread(wavData, waveHeaderStruct.dataSize, 1, filePtr);

	error = fclose(filePtr);
	if (error != 0)
	{
		std::cout << " Can not close file " << "\n";
	}

	result = (*pSecondaryBuffer)->Lock(0, waveHeaderStruct.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);

	if (FAILED(result))
	{
		return;
	}

	memcpy(bufferPtr, wavData, waveHeaderStruct.dataSize);

	(*pSecondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);

	if (wavData != NULL)
		delete[] wavData;

	wavData = 0;
	long tempVolume = (volume) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
	(*pSecondaryBuffer)->SetVolume(tempVolume);
	m_soundBufferMap[name] = secondaryBuffer;
}


void Sound::play(std::string name, bool infiniteLoop, int times)
{
	if (isMute)
	{
		return;
	}

	std::unordered_map< std::string, IDirectSoundBuffer8*> ::iterator it;
	it = m_soundBufferMap.find(name);
	if (it == m_soundBufferMap.end()) return;

	if (infiniteLoop)
	{
		it->second->Play(0, 0, DSBPLAY_LOOPING);
	}
	else
	{
		it->second->Stop();
		it->second->SetCurrentPosition(0);
		it->second->Play(0, 0, times - 1);
	}
}

void Sound::stop(std::string name)
{
	if (name == "")
	{
		for (auto it = m_soundBufferMap.begin(); it != m_soundBufferMap.end(); it++)
		{
			it->second->Stop();
			it->second->SetCurrentPosition(0);
		}
	}
	else
	{
		std::unordered_map<std::string, IDirectSoundBuffer8*> ::iterator it;
		it = m_soundBufferMap.find(name);
		if (it == m_soundBufferMap.end())
			return;
		else
		{
			it->second->Stop();
			it->second->SetCurrentPosition(0);
		}
	}
}

void Sound::setVolume(float percentage, std::string name)
{
	volume = percentage;
	if (name == "")
	{
		long volumne = (percentage) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
		for (auto it = m_soundBufferMap.begin(); it != m_soundBufferMap.end(); it++)
		{
			it->second->SetVolume(volumne);
		}
	}
	else
	{
		std::unordered_map< std::string, IDirectSoundBuffer8*> ::iterator it;
		it = m_soundBufferMap.find(name);
		if (it == m_soundBufferMap.end())
			return;
		long volumne = (percentage) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
		it->second->SetVolume(volumne);
	}
}

void Sound::cleanUp()
{
	delete this;
}