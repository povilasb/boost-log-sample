#include <iostream>

#include "log.hpp"


static sample::log::named_severity_logger_mt logger("main");


int
main(void)
{
	sample::log::init("sample.log");

	std::cout << "Boost.Log sample" << std::endl;

	LOG_INFO(logger) << "Sample started.";
	LOG_WARNING(logger) << "Warning log.";
	LOG_ERROR(logger) << "Error log.";
	LOG_INFO(logger) << "Sample finished.";

	return 0;
}
