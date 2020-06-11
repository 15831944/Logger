#include "logger.hpp"

int main()
{
	thatboy::logger::FileLogger logger("log.txt");
	logger.log("hello world ", "你好，世界 ");
	thatboy::logger::log(logger, "测试Log &", 233);
	thatboy::logger::log(thatboy::logger::FileLogger("log.txt"), "测试Log &&", 233);
	return 0;
}