#include "pch.h"

#include "AudioSystem.h"
#include "../Audio/WavFileReader.h"
#include "../Components/Components.h"
#include "../Registry.h"


AudioSystem::AudioSystem()
{
    mReader = new WavFileReader();
}

void AudioSystem::Init()
{
    //
    std::cout << "AudioSystem starting INIT!" << std::endl;

    std::cout << "Intializing OpenAL!" << std::endl;
    mDevice = alcOpenDevice(NULL);
    if (mDevice)
    {
        mContext = alcCreateContext(mDevice, NULL);
        alcMakeContextCurrent(mContext);
    }
    else {
        Logger::Log("AUDIO DEVICE NOT LAUNCHED!");
    }

    // Generate buffers
    alGetError();

    //Get every audio source
    auto sources = Registry::Instance().GetComponents<AudioSourceComponent>();
    //Det er audio systemet sin jobb å "Initte" sourcene, audiosource er bare info kontainer
    for (auto source : sources) {

        //
        alGetError();
        alGenBuffers(1, &source->mBuffer);
        std::cout << " AUDIO  CREATED : " << source->mBuffer << std::endl;
        checkError("alGenBuffers");
        alGenSources(1, &source->mSource);

        std::cout << " AUDIO SOURCE CREATED : " << source->mSource << std::endl;
        checkError("alGenSources");
        alSourcef(source->mSource, AL_PITCH, 1.0f);
        alSourcef(source->mSource, AL_GAIN, source->mGain);

        //What gameobject is this source attatched to
        auto gameObjectID = source->mGO;
        //Get the transform of that gameobject
        auto transform = Registry::Instance().GetComponent<TransformComponent>(gameObjectID);
        //Stores the position of the transform in vec3
        glm::vec3 position = glm::vec3(transform->mMatrix[3].x, transform->mMatrix[3].y, transform->mMatrix[3].z);

        //Feed the position to the AL 
        ALfloat temp[3] = { position.x, position.y, position.z};
        alSourcefv(source->mSource, AL_POSITION, temp);
        //Feed the velocity to AL
        glm::vec3 velocity = transform->mVelocity;
        ALfloat temp2[3] = { 0,0,0 };
        alSourcefv(source->mSource, AL_VELOCITY, temp2);

        alSourcei(source->mSource, AL_LOOPING, source->bLoop);

        //Check if the filepath is valid for creating a wave file
        wave_t file = LoadWave(source->mFilePath);
        if (!file.bValid) {
            Logger::Log("AUDIO FILE NOT VALID");
            return;
        }
        source->mFile = file;

        alGetError();
        // file.format
        std::cout << file.dataSize << ", " << file.frequency << std::endl;
        alBufferData(source->mBuffer, file.format, file.buffer, file.dataSize, file.frequency);
        checkError("alBufferData");
        alSourcei(source->mSource, AL_BUFFER, source->mBuffer);
        checkError("alSourcei (loadWave)");

    }
}

void AudioSystem::OnUpdate(float deltaTime)
{
    //USE THIS FOR EACH FRAME
   //Gets a vector of all listener components
    if (!Registry::Instance().Has<AudioListenerComponent>()) {
        Logger::Log("AudioSystem NO AUDIO LISTENERS");

        return;
    }

    //USE THIS FOR EACH FRAME
   //Gets a vector of all listener components
    if (!Registry::Instance().Has<AudioSourceComponent>()) {
        Logger::Log("AudioSystem NO AUDIO SOURCES");

        return;
    }

    auto listeners = Registry::Instance().GetComponents<AudioListenerComponent>();
    //Go through all listenrs
    for (auto listener : listeners) {
        ALfloat posVec[3];
        ALfloat velVec[3];
        ALfloat headVec[6];

        auto transform = Registry::Instance().GetComponent<TransformComponent>(listener->mGO);

        glm::vec3 pos = glm::vec3(transform->mMatrix[3].x, transform->mMatrix[3].y, transform->mMatrix[3].z);
        glm::vec3 vel = transform->mVelocity;
        glm::vec3 dir = transform->mForward;
        glm::vec3 up = glm::vec3(0, 1, 0);

        posVec[0] = 0.f;
        posVec[1] = 0.f;
        posVec[2] = 0.f;
        velVec[0] = 0;
        velVec[1] = 0;
        velVec[2] = 0;
        headVec[0] = dir.x;
        headVec[1] = dir.y;
        headVec[2] = dir.z;
        headVec[3] = up.x;
        headVec[4] = up.y;
        headVec[5] = up.z;

        alListenerfv(AL_POSITION, posVec);
        alListenerfv(AL_VELOCITY, velVec);
        alListenerfv(AL_ORIENTATION, headVec);

    }
    //Gets a vector of all source components
    auto sources = Registry::Instance().GetComponents<AudioSourceComponent>();

    for (auto source : sources)
    {

        if (Input::IsKeyDown(GLFW_KEY_SPACE))
        {
            if (!source->bPlaying) {
                source->bPlaying = !source->bPlaying;
                Logger::Log("CHANGED PLAY STATE");
                alSourcePlay(source->mSource);
            }
           
        }

        
   //    if (Input::IsKeyDown(GLFW_KEY_SPACE))
   //    {
   //        if (source->bPlaying) {
   //            source->bPlaying = false;
   //            alSourceStop(source->mSource);
   //            Logger::Log("SHOULD NOT PLAY!", INFO);
   //        }
   //        else {
   //
   //            Logger::Log("SHOULD PLAY NOW!", INFO);
   //            source->bPlaying = true;
   //            alSourcePlay(source->mSource);
   //        }
   //
   //
   //    }
   //
   //  continue;
   //  //Example
   //  if (!source->bPlaying)
   //  {
   //      if (source->bShouldPlay)
   //      {
   //          alSourcePlay(source->mSource);
   //          source->bPlaying = true;
   //          source->bShouldPlay = false;
   //          source->bShouldStop = false;
   //      }
   //      else
   //      {
   //          //Do nothing
   //      }
   //  }
   //  else {
   //      if (source->bShouldStop) {
   //          source->bPlaying = false;
   //          alSourceStop(source->mSource);
   //          source->bShouldStop = false;
   //          source->bShouldPlay = false;
   //      }
   //  }
   //  
   //
   }

   
    

  

    
    
}

void AudioSystem::CleanUp()
{
    mContext = alcGetCurrentContext();
    mDevice = alcGetContextsDevice(mContext);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(mContext);
    alcCloseDevice(mDevice);
}

//loads the .wav file
wave_t AudioSystem::LoadWave(std::string filePath)
{
    std::cout << "Loading wave file!\n";
    ALuint frequency{};
    ALenum format{};
    wave_t* waveData = new wave_t();
    if (!mReader->loadWave(filePath, waveData))
    {
        std::cout << "Error loading wave file!\n";
        waveData->bValid = false;
        return *waveData;
    }

    frequency = waveData->sampleRate;
    waveData->frequency = frequency;
    switch (waveData->bitsPerSample)
    {
    case 8:
        switch (waveData->channels)
        {
        case 1: format = AL_FORMAT_MONO8;

            waveData->format = format;
            std::cout << "Format: 8bit Mono\n";
            break;
        case 2: format = AL_FORMAT_STEREO8;
            waveData->format = format;
            std::cout << "Format: 8bit Stereo\n";
            break;
        default: break;
        }
        break;
    case 16:
        switch (waveData->channels)
        {
        case 1: format = AL_FORMAT_MONO16;
            waveData->format = format;
            std::cout << "Format: 16bit Mono\n";
            break;
        case 2: format = AL_FORMAT_STEREO16;
            waveData->format = format;
            std::cout << "Format: 16bit Stereo\n";
            break;
        default: break;
        }
        break;
    default: break;
    }
    if (waveData->buffer == NULL)
    {
        std::cout << "NO WAVE DATA!\n";
    }

    std::ostringstream i2s;
    i2s << waveData->dataSize;
    std::cout << "DataSize: " << i2s.str() << " bytes\n";
   
    return *waveData;
}


bool AudioSystem::checkError(std::string name)
{
    switch (alGetError())
    {
    case AL_NO_ERROR:
        break;
    case AL_INVALID_NAME:
        std::cout << "OpenAL Error: " + name + ": Invalid name!\n";
        return false;
    case AL_INVALID_ENUM:
        std::cout << "OpenAL Error: " + name + ": Invalid enum!\n";
        return false;
    case AL_INVALID_VALUE:
        std::cout << "OpenAL Error: " + name + ": Invalid value!\n";
        return false;
    case AL_INVALID_OPERATION:
        std::cout << "OpenAL Error: " + name + ": Invalid operation!\n";
        return false;
    case AL_OUT_OF_MEMORY:
        std::cout << "OpenAL Error: " + name + ": Out of memory!\n";
        return false;
    default: break;
    }
    return true;
}


