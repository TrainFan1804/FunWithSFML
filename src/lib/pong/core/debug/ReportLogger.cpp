#include "ReportLogger.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

ReportLogger::ReportLogger(const std::string &filename)
{
    _log_file.open(filename, std::ios::app);
    if (!_log_file.is_open()) throw std::runtime_error("Couldn't open log file");
}

ReportLogger::~ReportLogger()
{
    if (_log_file.is_open())
    {
        _log_file.close();
    }
}

void ReportLogger::log(const std::string &message)
{
    log(message, "DEFAULT");
}

void ReportLogger::log(const std::string &message, const std::string &log_type)
{
    std::string timestamp = get_current_timestamp();
    std::string formatted_message = "[" + timestamp + "] " + log_type + ": " + message; 
    _log_file << formatted_message << std::endl;
}

std::string ReportLogger::get_current_timestamp() 
{
    auto time_now = std::time(nullptr);
    auto tm = *std::localtime(&time_now);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    return oss.str();
}
