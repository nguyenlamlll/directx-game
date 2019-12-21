#pragma once

#include <mmsystem.h>
#include "dsound.h"
#include "windows.h"
#include <unordered_map>
#include <string>
#include <iostream>

#include "SoundNames.h"

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

class Sound
{
private:
	Sound(HWND hWnd);
	static Sound * m_instance;
	IDirectSound8* m_pDevice;
	IDirectSoundBuffer* m_primaryBuffer;
	std::unordered_map<std::string, IDirectSoundBuffer8*> m_soundBufferMap;

public:
	struct WaveHeaderStruct
	{
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

	void static initialize(HWND hWnd);
	static Sound* getInstance();

	float volume;

	void loadResources();
	void setVolume(float percentage, std::string name = "");
	void loadSound(char* fileName, std::string name);
	void play(std::string name, bool infiniteLoop = false, int times = 1);
	void stop(std::string name = "");
	float getVolume();
	~Sound();
	bool isMute;
	void unMute();
	void cleanUp();
	
};

