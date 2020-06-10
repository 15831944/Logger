#include "logger.hpp"

int main()
{
	thatboy::logger::log("hello world ", "你好，世界 ");
	thatboy::logger::log(std::clog, "hello world ", "你好，世界 ");
	return 0;
}