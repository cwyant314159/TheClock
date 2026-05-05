#
# raylib
#
set(CUSTOMIZE_BUILD OFF)
add_subdirectory(raylib EXCLUDE_FROM_ALL)

#
# raygui
#
add_library(raygui STATIC raygui_impl.c)
target_include_directories(raygui PUBLIC raygui/src)
target_link_libraries(raygui PUBLIC raylib)