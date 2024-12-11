add_executable(FunWithSFML main.cpp)

add_subdirectory(lib)

target_link_libraries(FunWithSFML PRIVATE Application)
