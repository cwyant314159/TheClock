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

#
# Add the data library on macos to compensate for the lack of timezone support
# in the MacOS build tools.
#
if (APPLE)
    set(ENABLE_DATE_INSTALL OFF CACHE INTERNAL "Enable install")
    set(BUILD_TZ_LIB ON CACHE INTERNAL "Compile timezone library binary")
    set(USE_TZ_DB ON CACHE INTERNAL "Use timezone database")
    add_subdirectory(date)
endif ()