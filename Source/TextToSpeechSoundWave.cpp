#include "TextToSpeechSoundWave.h"
#include "TextToSpeechPCH.h"
#include "FMRTTSLib.h"

UTextToSpeechSoundWave::UTextToSpeechSoundWave(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}

bool UTextToSpeechSoundWave::Initialize(const FString &VoiceRequiredAttributes, const FString &VoiceOptionalAttributes, int32 Rate, const FString &Text)
{
	unsigned long BytesRead;
	uint8 *AudioBuffer_ = (uint8*)FMRTTSLib::FMRTTSLibMain::TextToWav(*VoiceRequiredAttributes, *VoiceOptionalAttributes, Rate, *Text, &BytesRead);
	
	if (AudioBuffer_)
	{
		NumChannels = 1;
		SampleRate = 44100;
		Duration = (BytesRead / 2) / 44100.0;
		SoundGroup = SOUNDGROUP_Voice;
		this->bStreaming = false;
		
		//TotalSamples = SamplesRead / 1000.0;
		//ChannelSizes.Add(BytesRead);

		QueueAudio((uint8*)AudioBuffer_, BytesRead);
		
		delete AudioBuffer_;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't generate wave from speech (may be voice not found, check VoiceRequiredAttributes)."));
	}

	return true;
}
