#include "logger.hpp"

namespace Engine {
    namespace Logger {

        _Logger::_Logger(const std::string & file_name)
        {
            log_file.open(file_name.c_str());
        }

        _Logger::~_Logger()
        {
            log_file.close();
        }

        void _Logger::log(std::string log_message)
        {
            log_file << "LOG MESSAGE: " << log_message << std::endl;
        }
    }
}
