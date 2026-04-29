set(EXE_NAME "prototype-clock")

add_executable(${EXE_NAME})
target_sources(${EXE_NAME} PRIVATE main.c)
target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(${EXE_NAME} PRIVATE -Wall -Wextra)
target_link_libraries(${EXE_NAME} PRIVATE m raylib)
