#include <AudioEngine/AudioMaster.hpp>
#include <AudioEngine/SoundSource.hpp>
#include <Infrastructure/GameModule.hpp>
#include <iostream>

#ifdef _DEBUG
#define WAV_MYSTERY "../Assets/sound/Mystery.wav"
#define WAV_STEPS "../Assets/sound/Footsteps.wav"
#elif _RELEASE
#define WAV_MYSTERY "../Assets/sound/Mystery.wav"
#define WAV_STEPS "../Assets/sound/Footsteps.wav"
#elif _DEPLOY
#define WAV_MYSTERY "Assets/sound/Mystery.wav"
#define WAV_STEPS "Assets/sound/Footsteps.wav"
#endif

AudioEngine::AudioMaster *audioMaster;
AudioEngine::SoundSource *backgroundMusic;

bool IsPlaying = false;
AudioEngine::SoundSource *stepSound;

static void OnGameStart()
{
    audioMaster = AudioEngine::AudioMaster::GetInstance();
    backgroundMusic = new AudioEngine::SoundSource();
    stepSound = new AudioEngine::SoundSource();

    auto buffer = audioMaster->LoadSound(WAV_MYSTERY);
    backgroundMusic->SetLooping(true);
    backgroundMusic->SetGain(0.02F);
    backgroundMusic->Play(buffer);

    buffer = audioMaster->LoadSound(WAV_STEPS);
    stepSound->SetLooping(true);
    stepSound->Play(buffer);
    stepSound->Pause();
}

static void PlayStepSound(EventProcessing::KeyCode keyCode)
{
    if (IsPlaying)
    {
        return;
    }

    auto eventHandler = EventProcessing::EventHandler::GetInstance();
    
    if (eventHandler->IsKeyPressed(EventProcessing::KeyCode::W) ||
        eventHandler->IsKeyPressed(EventProcessing::KeyCode::A) ||
        eventHandler->IsKeyPressed(EventProcessing::KeyCode::S) ||
        eventHandler->IsKeyPressed(EventProcessing::KeyCode::D))
    {
        IsPlaying = true;
        stepSound->Continue();
    }
}

static void StopStepSound(EventProcessing::KeyCode keyCode)
{
    if (!IsPlaying)
    {
        return;
    }

    auto eventHandler = EventProcessing::EventHandler::GetInstance();

    if (!eventHandler->IsKeyPressed(EventProcessing::KeyCode::W) &&
        !eventHandler->IsKeyPressed(EventProcessing::KeyCode::A) &&
        !eventHandler->IsKeyPressed(EventProcessing::KeyCode::S) &&
        !eventHandler->IsKeyPressed(EventProcessing::KeyCode::D))
    {
        IsPlaying = false;
        stepSound->Pause();
    }
}

static void PlaySprintSound(EventProcessing::KeyCode keyCode)
{
    if (keyCode == EventProcessing::KeyCode::SHIFT)
    {
        stepSound->SetPitch(1.5f);
    }
}

static void StopSprintSound(EventProcessing::KeyCode keyCode)
{
    if (keyCode == EventProcessing::KeyCode::SHIFT)
    {
        stepSound->SetPitch(1.0f);
    }
}

static void OnGameEnd()
{
    delete audioMaster;
    delete backgroundMusic;
    delete stepSound;
}

GAME_MODULE()
{
	REGISTER_CALLBACK(OnGameStart, OnGameStart);
	REGISTER_CALLBACK(OnGameEnd, OnGameEnd);
    REGISTER_CALLBACK(OnKeyDown, PlayStepSound);
    REGISTER_CALLBACK(OnKeyUp, StopStepSound);
    REGISTER_CALLBACK(OnKeyDown, PlaySprintSound);
    REGISTER_CALLBACK(OnKeyUp, StopSprintSound);
    return true;
}
