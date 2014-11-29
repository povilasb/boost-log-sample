#include <string>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "log.hpp"


namespace sample
{

void
log::init(std::string fname_base)
{
	boost::log::register_simple_formatter_factory<log::severity_level, char>
		("Severity");

	boost::log::add_file_log(
		boost::log::keywords::file_name = fname_base + ".%N",
		boost::log::keywords::rotation_size = 1024 * 1024 * 10, // 10 MB;
		boost::log::keywords::format = "%LineID%. [%TimeStamp%]"
			"[%Severity%][%Tag%]: %Message%",
		boost::log::keywords::auto_flush = true
	);

	boost::log::add_common_attributes();
}

} // namespace sample.
