find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

add_subdirectory(pong)

add_library(Application Application.cpp
        triangle_classic.cpp
        square_party.cpp
        moving.cpp
        vector_helper.cpp)

target_include_directories(Application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Application PRIVATE sfml-graphics sfml-audio sfml-window sfml-system Pong)
