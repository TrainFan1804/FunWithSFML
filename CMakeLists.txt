cmake_minimum_required(VERSION 3.16)

project(LearnSFML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

add_executable(LearnSFML main.cpp
    car_street.cpp
    car_street.h
    street_gen.cpp
    street_gen.h
    street.h street.cpp

    cell_gen.cpp
    cell_gen.h
    map_test.cpp
    main_two.cpp

)

target_link_libraries(LearnSFML PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)

include(GNUInstallDirs)
install(TARGETS LearnSFML
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
