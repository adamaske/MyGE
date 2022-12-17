#include "pch.h"
#include "Logger.h"

Logger::Logger()
{
	
}

Logger::~Logger()
{
	GetInstance().LogsToFile();
}

void Logger::Init()
{
	GetInstance().StartLoggingType(ERROR);
	GetInstance().StartLoggingType(WARNING);
	GetInstance().StartLoggingType(INFO);
}

void Logger::Log(std::string file)
{
	std::cout << file << "\n";
}

void Logger::Log(std::string file, LogType type)
{
	//If we are currently logging this type to the output window
	if (GetInstance().IsLoggingType(type)) {
		GetInstance().Log(file);
	}
}

void Logger::Log(std::string file, LogType type, bool logToFile)
{
	GetInstance().Log(file, type);
	if (logToFile) {
		GetInstance().mLogs.push_back(LogEntry{ type, file });
	}
}

bool Logger::IsLoggingType(LogType type) {
	return GetInstance().mActiveLoggingTypes[type];
}

void Logger::StartLoggingType(LogType type)
{
	GetInstance().mActiveLoggingTypes[type] = true;
}

void Logger::StopLoggingType(LogType type)
{
	GetInstance().mActiveLoggingTypes[type] = false;
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
		GetInstance().Log("Could not create file to output logs to!", ERROR);
	}
}
