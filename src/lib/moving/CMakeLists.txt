add_library(
        Moving moving.cpp
        ParticleSystem.cpp
)

target_include_directories(Moving PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})