#pragma once

enum LogType {
		ERROR,
		WARNING,
		INFO
};

struct LogEntry{
	LogType mType;
	std::string mText;
	//Date, time, other stuff maybe
}

class Logger {
public:
	Logger();
	~Logger();
	static void Log(std::string file);
	static void Log(std::string file, LogType type);
	static void Log(std::string file, LogType type, bool logToFile);

	bool IsLoggingType(LogType type);
	void StartLoggingType(LogType type);
	void StopLoggingType(LogType type);

	bool LogsToFile();
private:
	static Logger* mInstance;
	std::unordered_map<LogType, bool> mActiveLoggingTypes;
	std::vector<LogEntry> mLogs;
};