#pragma once

enum LogType {
		ERROR,
		WARNING,
		INFO
};

struct LogEntry {
	LogType mType;
	std::string mText;
	//Date, time, other stuff maybe
};

class Logger {
public:
	Logger();
	~Logger();

	static void Init();

	static void Log(std::string file);
	static void Log(std::string file, LogType type);
	static void Log(std::string file, LogType type, bool logToFile);

	static bool IsLoggingType(LogType type);
	bool IsLoggingTypeImpl(LogType type);

	static void StartLoggingType(LogType type);
	static void StopLoggingType(LogType type);
	bool LogsToFile();
private:
	static Logger& GetInstance() {
		static Logger instance;
		return instance;
	}
	//Changed to a vector from a unorered map, since we have to loop thorugh
	//it, I feel the vector should be faster than a map
	std::vector<std::pair<LogType, bool>> mActiveLoggingTypes{ {INFO, true},{ERROR,false},{WARNING, false} };
	std::vector<LogEntry> mLogs;

	//std::ostream mOut;
};

