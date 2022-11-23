#pragma once
#include "AL/al.h"
#include "AL/alc.h"
#include <string>
#include <vector>
#include "../Systems/System.h"
#include "../glm/glm.hpp"


class AudioSystem : public System
{
public:
    AudioSystem();

    //Initliaze all sources and listnerers
    virtual void Init() override;
    //Each frame
    virtual void OnUpdate(float deltaTime) override;

    /// Cleans up and shuts down OpenAl.
    void CleanUp();

    wave_t LoadWave(std::string filePath);
   
    bool checkError(std::string name);
private:
    ALCdevice* mDevice{ nullptr };                 ///< Pointer to the ALC Device.
    ALCcontext* mContext{ nullptr };               ///< Pointer to the ALC Context.

    class WavFileReader* mReader;
};