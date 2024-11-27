#find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

add_executable(FunWithSFML main.cpp)

add_subdirectory(lib)

target_link_libraries(FunWithSFML PRIVATE Application)
