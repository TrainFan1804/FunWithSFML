#include "ReportLogger.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

ReportLogger &ReportLogger::get_instance()
{
    static ReportLogger instance;
    return instance;
}

void ReportLogger::log(const std::string &message)
{
    log(message, LoggerStatus::DEBUG);
}

void ReportLogger::log(const std::string &message, LoggerStatus status)
{
    std::string timestamp = get_current_timestamp();
    std::string formatted_message = "[" + timestamp + "] " + get_status_string(status) + ": " + message; 
    _log_file << formatted_message << std::endl;
}

ReportLogger::ReportLogger()
{
    _log_file.open("Debug.log", std::ios::app);
    if (!_log_file.is_open()) throw std::runtime_error("Couldn't open log file");
}

ReportLogger::~ReportLogger()
{
    if (_log_file.is_open())
    {
        _log_file.close();
    }
}

std::string ReportLogger::get_current_timestamp() 
{
    auto time_now = std::time(nullptr);
    auto tm = *std::localtime(&time_now);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    return oss.str();
}

std::string ReportLogger::get_status_string(LoggerStatus status)
{
    switch (status) 
    {
    case DEBUG: return "DEBUG";
    case ERROR: return "ERROR";
    default: return "UNKNOWN";
    }
}
