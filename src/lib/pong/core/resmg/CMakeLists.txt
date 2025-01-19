add_library(
        ResourceManager ResourceManager.cpp
)

target_link_libraries(ResourceManager PRIVATE ReportLogger)

target_include_directories(ResourceManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})