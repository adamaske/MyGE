#pragma once
#include <cstdint>    //does not work well on mac
#include <string>
#include <cstdio>
#include "AL/al.h"
#include "AL/alc.h"
/// Structure to contain WAVE file data.
struct wave_t
{
    //BOol to know if this file was loaded correctly
    bool bValid = true;
    uint32_t size;              ///< Size of the WAVE file.
    uint32_t chunkSize;         ///< Size of the fmt chunk.
    uint32_t sampleRate;        ///< Sample rate of the audio.
    uint32_t avgBytesPerSec;    ///< Average byte rate.
    uint32_t dataSize;          ///< Size of the data chunk.
    short formatType;           ///< Audio format.
    short channels;             ///< Number of audio channels.
    short bytesPerSample;       ///< Number of bytes per sample.
    short bitsPerSample;        ///< Number of bits per sample.

    ALuint frequency;
    ALenum format;

    unsigned char* buffer;      ///< Buffer to hold audio data.
   
};

/// Class to handle loading of Microsoft signed 16-bit PCM WAVE audio files.
class WavFileReader
{
public:
    WavFileReader() {

    };
    /// Loads a given wave file, fills wave_t structure with wave data.
    /**
        \param File path relative to execution directory.
        \param Pointer to a wave_t structure to contain the wave data.
    **/
   bool loadWave(std::string filePath, wave_t* wavePtr);

private:
    /// Error handling function.
    /**
        Always returns false, outputs argumen string to the command line.
        \param Error message to output.
    **/
    bool endOnError(std::string errmsg);
};
