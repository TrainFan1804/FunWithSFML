#ifndef REPORTLOGGER_H
#define REPORTLOGGER_H

#include <fstream>
#include <string>

class ReportLogger
{
public:
    enum LoggerStatus { DEBUG, ERROR };

    static ReportLogger &get_instance();

    void log(const std::string &message);
    void log(const std::string &message, LoggerStatus status);
private:
    ReportLogger();
    ~ReportLogger();

    std::ofstream _log_file;
    std::string get_current_timestamp();
    std::string get_status_string(LoggerStatus status);
};

#endif // REPORTLOGGER_H
