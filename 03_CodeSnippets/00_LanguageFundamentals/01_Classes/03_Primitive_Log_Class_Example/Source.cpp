#include<iostream>

class Log {

public:
	const int LogLevelError = 0;
    const int LogLevelWarning = 1;
    const int LogLevelInfo = 2;

private: 
	int log_level_ = LogLevelInfo;

public: 
	void SetLevel(int level) {
		log_level_ = level;
	}

	void Info(const char* message) {
		if( log_level_ >= LogLevelInfo)
			std::cout << "[INFO]: "<< message << std::endl;
	}

	void Warn(const char* message) {
		if( log_level_ >= LogLevelWarning) 
			std::cout << "[WARNING]: "<< message << std::endl;
	}

	void Error(const char* message) {
		if( log_level_ >= LogLevelError)
			std::cout << "[ERROR]: "<< message << std::endl;
	}

};

int main() {
	
	Log log;
	log.SetLevel(log.LogLevelError);
	log.Error("Hello");
	log.Warn("Hello");
	log.Info("Hello");

	std::cin.get();
}