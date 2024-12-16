add_library(
        Pong pong.cpp
        pong_struct.cpp
        Ball.cpp
)

target_include_directories(Pong PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
