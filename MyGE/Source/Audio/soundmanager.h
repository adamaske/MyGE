#pragma once
#include "AL/al.h"
#include "AL/alc.h"
#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "soundsource.h"

/// Class handling OpenAL setup and management of sound sources.
/**
    Singleton class that creates and destroys sound sources.
**/
class SoundManager
{
public:
    struct AudioListenerComponent
    {
        glm::vec3 pos;
        glm::vec3 vel;
        glm::vec3 dir;
        glm::vec3 up;
        AudioListenerComponent()
        {
      //Could be something like this
          //pos = glm::vec3::ZERO;
          //vel = glm::vec3::ZERO;
          //dir = glm::vec3::UNIT_Z;
          //up = glm::vec3::UNIT_Y;

           pos = glm::vec3(0.0f, 0.0f, 0.0f);
           vel = glm::vec3(0.0f, 0.0f, 0.0f);
           dir = glm::vec3(0.0f, 0.0f, 1.0f);
           up = glm::vec3(0.0f, 1.0f, 0.0f);
          
        }
    };

    static SoundManager* getInstance()          ///< Get pointer to singleton instance.
    {
        if (!mInstance)
            mInstance = new SoundManager();
        return mInstance;
    }

    /// Initialises OpenAL.
    bool init();
    /// Cleans up and shuts down OpenAl.
    void cleanUp();

    /// Creates a new SoundSource with the given parameters.
    /**
        \param The name of the sound. (Not in use.)
        \param The source position as Vector3.
        \param File path relative to execution directory.
        \param Boolean to see if sound should loop or not.
    **/
    SoundSource* createSource(std::string name, glm::vec3 pos, std::string filePath = "", bool loop = false, float gain = 1.0);

    void updateListener(glm::vec3 pos, glm::vec3 vel, glm::vec3 dir, glm::vec3 up);

private:
    SoundManager();                         ///< Private constructor.
    SoundManager(SoundManager const&);      ///< Private copy constructor.
    void operator=(SoundManager const&);    ///< Private class assignment operator.
    static SoundManager* mInstance;         ///< Singleton instance pointer.
    /// Debug function.
    /**
        Checks for and outputs OpenAL errors.
    **/
    bool checkError();

    ALCdevice* mDevice{nullptr};                 ///< Pointer to the ALC Device.
    ALCcontext* mContext{nullptr};               ///< Pointer to the ALC Context.

    AudioListenerComponent mListener;               ///< The listener data structure. (Temporary)
};