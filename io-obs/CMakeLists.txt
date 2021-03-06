project(input-overlay)

find_path(UIOHOOK_INCLUDE_DIR uiohook.h)
find_library(UIOHOOK_LIBRARY uiohook)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(MSVC)
    set(input-overlay_PLATFORM_DEPS
        w32-pthreads
        XInput9_1_0)

    add_definitions(-DHAVE_XINPUT=1)
endif()

if(UNIX)
    add_definitions(-DLINUX_INPUT=1)
endif()

macro(use_cxx14)
    if (CMAKE_VERSION VERSION_LESS "3.1")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
        endif ()
    else ()
        set (CMAKE_CXX_STANDARD 14)
    endif ()
endmacro(use_cxx14)

use_cxx14()

#find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

if(NOT Qt5Widgets_FOUND)
    message(FATAL_ERROR "Failed to find Qt5")
endif()

set(input-overlay_SOURCES
    input_overlay.cpp
    sources/input_source.cpp
    sources/input_source.hpp
    sources/input_source.cpp
    sources/input_history.cpp
    sources/input_history.hpp
    hook/hook_helper.cpp
    hook/hook_helper.hpp
    hook/gamepad_hook.cpp
    hook/gamepad_hook.hpp
    util/util.cpp
    util/util.hpp
    util/overlay.cpp
    util/overlay.hpp
    util/layout_constants.hpp
    util/xinput.cpp
    util/xinput.hpp
    util/element/element.cpp
    util/element/element.hpp
    util/element/element_texture.cpp
    util/element/element_texture.hpp
    util/element/element_button.cpp
    util/element/element_button.hpp
    util/element/element_mouse_wheel.cpp
    util/element/element_mouse_wheel.hpp
    util/element/element_trigger.cpp
    util/element/element_trigger.hpp
    util/element/element_analog_stick.cpp
    util/element/element_analog_stick.hpp
    util/element/element_text.cpp
    util/element/element_text.hpp
    util/element/element_gamepad_id.cpp
    util/element/element_gamepad_id.hpp
    util/element/element_mouse_movement.cpp
    util/element/element_mouse_movement.hpp
    util/element/element_dpad.cpp
    util/element/element_dpad.hpp
    util/element/element_data_holder.cpp
    util/element/element_data_holder.hpp
    gui/io_settings_dialog.cpp
    gui/io_settings_dialog.hpp
    gui/ui_settings_dialog.hpp
    ../ccl/ccl.cpp
    ../ccl/ccl.hpp)

add_library(input-overlay MODULE
        ${input-overlay_SOURCES})

include_directories(
    ${UIOHOOK_INCLUDE_DIR}
    SYSTEM "${CMAKE_SOURCE_DIR}/libobs"
    "../../../UI/obs-frontend-api"
    ${Qt5Core_INCLUDES}
    ${Qt5Widgets_INCLUDES})

target_link_libraries(input-overlay
    libobs
    Qt5::Widgets
    obs-frontend-api
    ${input-overlay_PLATFORM_DEPS}
    ${UIOHOOK_LIBRARY})

install_obs_plugin_with_data(input-overlay data)
