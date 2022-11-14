#include "GUID.h"
#include <random>

static std::random_device sRandomDevice;
static std::mt19937_64 sEngine(sRandomDevice());
static std::uniform_int_distribution<uint64_t> sUniformDistribution;

GUID::GUID() : mID(sUniformDistribution(sEngine)) 
{

}

GUID::GUID(uint64_t guid) : mID(guid) 
{
}
