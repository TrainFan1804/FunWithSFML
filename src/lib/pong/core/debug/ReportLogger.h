#ifndef REPORTLOGGER_H
#define REPORTLOGGER_H

#include <fstream>
#include <string>

class ReportLogger
{
public:
    ReportLogger(const std::string &filename);
    ~ReportLogger();
    void log(const std::string &message);
    void log(const std::string &message, const std::string &log_type);
private:
    std::ofstream _log_file;
    std::string get_current_timestamp();
};

#endif // REPORTLOGGER_H
