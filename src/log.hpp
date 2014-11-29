#ifndef SAMPLE_LOG_HPP
#define SAMPLE_LOG_HPP 1

#include <string>
#include <ostream>

#include <boost/log/core.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/attributes/constant.hpp>


#define LOG(logger, level) BOOST_LOG_SEV(logger, level)
#define LOG_DEBUG(logger) LOG(logger, sample::log::debug)
#define LOG_INFO(logger) LOG(logger, sample::log::info)
#define LOG_WARNING(logger) LOG(logger, sample::log::warning)
#define LOG_ERROR(logger) LOG(logger, sample::log::error)
#define LOG_FATAL(logger) LOG(logger, sample::log::fatal)


namespace sample
{

namespace log
{

enum severity_level {
	debug, info, warning, error, fatal
};


template<typename CharT, typename TraitsT>
inline std::basic_ostream<CharT, TraitsT>& operator<< (
	std::basic_ostream< CharT, TraitsT>& strm, enum severity_level lvl)
{
	static const char* const str_level[] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR",
		"FATAL"
	};

	if (static_cast<std::size_t>(lvl) < (sizeof(str_level)
		/ sizeof(*str_level))) {
		strm << str_level[lvl];
	}
	else {
		strm << static_cast<int>(lvl);
	}

	return strm;
}


class named_severity_logger_mt :
	public boost::log::sources::severity_logger_mt<severity_level> {
public:
	named_severity_logger_mt(std::string name) :
		boost::log::sources::severity_logger_mt<severity_level>() {
		this->add_attribute("Tag",
			boost::log::attributes::constant<std::string>(name));
	}
};


/**
 * Initialises logging. Must be called only once. Logs are written to file.
 * Every 10 megabytes, the log file rotates.
 *
 * @param fname_base rotating file base name. E.g. log.1, log.2, log.n.
 */
void init(std::string fname_base);

} // namespace log.

} // namespace sample.


#endif /* SAMPLE_LOG_HPP */
