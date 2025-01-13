add_subdirectory(resmg)

add_library(
        Pong pong.cpp
        pong_data.cpp
        Ball.cpp
        Player.cpp
)

target_include_directories(Pong PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Pong PRIVATE FontManager)
