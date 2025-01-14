add_library(
        EventHandler event_handler.cpp
)

target_include_directories(EventHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})