#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>


namespace Engine {
    namespace Logger {
        class _Logger {
        public:
            _Logger(const std::string & file_name);
            ~_Logger();

           void log(std::string log_message);
        private:
           std::ofstream log_file;
        };
    }
}

#endif // LOGGER_HPP
