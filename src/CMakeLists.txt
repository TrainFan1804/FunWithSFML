find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

add_executable(FunWithSFML main.cpp)

target_link_libraries(FunWithSFML PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)

include(GNUInstallDirs)
#install(TARGETS FunWithSFML 
    #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    #RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
