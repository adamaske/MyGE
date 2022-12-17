#include "pch.h"
#include "Logger.h"

Logger::Logger()
{
	mInstance = this;

	mInstance->mActiveLoggingTypes[WARNING] = true;

	mInstance->mActiveLoggingTypes[ERROR] = true;

	mInstance->mActiveLoggingTypes[INFO] = true;
}

Logger::~Logger()
{
}

void Logger::Log(std::string file)
{
	std::cout << file << "\n";
}

void Logger::Log(std::string file, LogType type)
{
	//If we are currently logging this type to the output window
	if (mInstance->IsLoggingType(type)) {
		Log(file);
	}
}

void Logger::Log(std::string file, LogType type, bool logToFile)
{
	Log(file, type);
	if (logToFile) {
		mInstance->mLogs.push_back(LogEntry{ type, file });
	}
}

bool Logger::IsLoggingType(LogType type) {
	return mInstance->mActiveLoggingTypes[type];
}

void Logger::StartLoggingType(LogType type)
{
	mInstance->mActiveLoggingTypes[type] = true;
}

void Logger::StopLoggingType(LogType type)
{
	mInstance->mActiveLoggingTypes[type] = false
}

bool Logger::LogsToFile()
{
	//Create file,
	std::string fileName = "";
	std::string filePath = "../Resources/Logs/";
	filePath.append(fileName);
	std::string fileType = ".txt";
	filePath.append(fileType);
	std::ifstream file("../Resources/Logs/" + fileName + ".txt");
	if (file.is_open()) {

	}
	else {
		Log("Could not create file to output logs to!", ERROR);
	}
}
