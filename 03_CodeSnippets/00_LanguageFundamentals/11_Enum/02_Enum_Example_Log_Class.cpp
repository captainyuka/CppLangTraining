#include<iostream>

class Log {

public:
	enum Level : char {
		kError, kWarning, kInfo
	};

	void SetLevel(Level level) {
		log_level_ = level;
	}

	void Info(const char* message) {
		if( log_level_ >= kInfo)
			std::cout << "[INFO]: "<< message << '\n';
	}

	void Warn(const char* message) {
		if( log_level_ >= kWarning) 
			std::cout << "[WARNING]: "<< message << '\n';
	}

	void Error(const char* message) {
		if (log_level_ >= kError)
			std::cout << "[ERROR]: " << message << '\n';
	}

private: 
	Level log_level_ = kInfo;

};



int main() {
	
	Log log;
	log.SetLevel(Log::kInfo);
	log.Error("Hello");
	log.Warn("Hello");
	log.Info("Hello");

	std::cin.get();
}
