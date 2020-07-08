#include "logger.hpp"

int main()
{
	std::ofstream ofs("log.txt", std::ios::app);
	thatboy::logger::StreamLogger logger(ofs);
	logger.log("test logger");
	ofs.close();
	logger.log("test logger on close");
	ofs.open("log.txt", std::ios::app);
	logger.log("test logger reopen");
	ofs.close();

	thatboy::logger::FileLogger fileLogger("log.txt");
	fileLogger.log("test filelogger");
	fileLogger.close();
	fileLogger.log("test filelogger on close");
	fileLogger.open("log.txt");
	fileLogger.log("test filelogger reopen");
	fileLogger.close();	
	
	thatboy::logger::FileNELogger fileNeLogger("log.txt");
	fileNeLogger.log("test fileNelogger");

	return 0;
}