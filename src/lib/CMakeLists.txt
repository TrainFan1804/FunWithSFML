find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

add_library(Application Application.cpp
        triangle_classic triangle_classic.cpp
        square_party square_party.cpp
        vector_helper vector_helper.cpp)

target_include_directories(Application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(FunWithSFML PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)
