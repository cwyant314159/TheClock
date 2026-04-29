set(EXE_NAME "clock")

set(SOURCES
    main.cpp
    clocks/centisecond_clock.cpp
    clocks/compound_clock.cpp
    clocks/simple_clock.cpp
    components/dial.cpp
    components/hand.cpp
    components/pin.cpp
    components/tick_marks.cpp
    time_sources/local_time_source.cpp
    time_sources/utc_time_source.cpp
    utils/conversions.cpp
    utils/time_point.cpp
)

add_executable(${EXE_NAME})
target_sources(${EXE_NAME} PRIVATE ${SOURCES})
target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(${EXE_NAME} PRIVATE -Wall -Wextra)
target_link_libraries(${EXE_NAME} PRIVATE m raylib)
