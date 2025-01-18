add_library(
        ReportLogger ReportLogger.cpp
)

target_include_directories(ReportLogger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})