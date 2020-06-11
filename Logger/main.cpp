#include "logger.hpp"

int main()
{
	std::ofstream ofs("log.txt", std::ios::app);
	thatboy::logger::Logger logger(ofs);
	logger.log(thatboy::logger::LogLevel::Info, "This is ofstream logger.");
	thatboy::logger::log(logger, thatboy::logger::LogLevel::Info, "This is ofstream logger (g).");
	ofs.close();
	logger.log(thatboy::logger::LogLevel::Info, "THIS WON'T BE WRITTEN.");
	ofs.open("log.txt", std::ios::app);
	logger.log(thatboy::logger::LogLevel::Info, "This is ofstream logger -- again.");
	ofs.close();

	std::ofstream ofs2("log.txt", std::ios::app);
	logger.bind(ofs2);
	logger.log(thatboy::logger::LogLevel::Info, "This is ofstream logger -- again again.");
	ofs2.close();
	logger.unbind();
	logger.log(thatboy::logger::LogLevel::Info, "THIS WON'T BE WRITTEN.");

	std::ofstream ofs3("log.txt", std::ios::app);
	thatboy::logger::log(thatboy::logger::Logger(ofs3), thatboy::logger::LogLevel::Info, "This is ofstream logger &&.");

	thatboy::logger::FileLogger filelogger("log.txt");
	filelogger.log(thatboy::logger::LogLevel::Info, "This is file logger.");
	thatboy::logger::log(filelogger, thatboy::logger::LogLevel::Info, "This is file logger (g).");
	filelogger.close();
	filelogger.log(thatboy::logger::LogLevel::Info, "THIS WON'T BE WRITTEN.");

	thatboy::logger::log(thatboy::logger::FileLogger("log.txt"), thatboy::logger::LogLevel::Info, "This is file logger &&.");

	thatboy::logger::log(thatboy::logger::Logger(std::clog), thatboy::logger::LogLevel::Info, "This is clog logger (g).");
	thatboy::logger::Logger(std::clog).log(thatboy::logger::LogLevel::Info, "This is clog logger.");

	return 0;
}