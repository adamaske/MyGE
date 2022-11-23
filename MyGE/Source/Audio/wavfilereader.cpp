#define _CRT_SECURE_NO_DEPRECATE // using this to bypass deprecation
#include "WavFileReader.h"
#include <iostream>

bool WavFileReader::loadWave(std::string filePath, wave_t* wavePtr)
{
    std::cout << "Loading "+ filePath + " from disk\n";
    FILE* fp = NULL;
    fp = std::fopen(filePath.c_str(), "rb");
    if (fp == NULL)    {
        return endOnError("FileHandler error: File not found.\n");
    }

    char type[4];

    std::fread(type, sizeof(char), 4, fp);
    if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
    {
        return endOnError("FileHandler error: RIFF header missing or invalid.\n");
    }

    std::fread(&wavePtr->size, sizeof(uint32_t), 1, fp);
    std::fread(type, sizeof(char), 4, fp);
    if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
    {
        return endOnError("FileHandler error: WAVE header missing or invalid.\n");
    }

    std::fread(type, sizeof(char), 4, fp);
    if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
    {
        return endOnError("FileHandler error: fmt header missing or invalid.\n");
    }

    std::fread(&wavePtr->chunkSize,       sizeof(uint32_t), 1, fp);
    std::fread(&wavePtr->formatType,      sizeof(short), 1, fp);
    std::fread(&wavePtr->channels,        sizeof(short), 1, fp);
    std::fread(&wavePtr->sampleRate,      sizeof(uint32_t), 1, fp);
    std::fread(&wavePtr->avgBytesPerSec,  sizeof(uint32_t), 1, fp);
    std::fread(&wavePtr->bytesPerSample,  sizeof(short), 1, fp);
    std::fread(&wavePtr->bitsPerSample,   sizeof(short), 1, fp);

    std::fread(type, sizeof(char), 4, fp);
    if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
    {
        return endOnError("FileHandler error: data header missing or invalid.\n");
    }

    std::fread(&wavePtr->dataSize, sizeof(uint32_t), 1, fp);

    wavePtr->buffer = new unsigned char[wavePtr->dataSize];
    //static_cast just to get rid of compiler warning
    uint32_t result = static_cast<uint32_t>(std::fread(wavePtr->buffer, sizeof(char), wavePtr->dataSize, fp));
    if (result != wavePtr->dataSize)
    {
        return endOnError("Wav-file read error: fread result mismatch.\n");
    }

    if (ferror(fp))
    {
        return endOnError("Wav-file read error: fstream error.");
    }

    if (wavePtr->buffer == NULL)
    {
        return endOnError("Wav-file read error: Wave Data pointer is NULL.\n");
    }

    std::fclose(fp);
    std::cout << "Loading complete!\n";
    return true;
}

bool WavFileReader::endOnError(std::string errmsg)
{
    std::cout << errmsg;
    return false;
}
