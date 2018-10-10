/**
 * This file is part of input-overlay
 * which is licenced under the
 * MOZILLA PUBLIC LICENCE 2.0
 * See LICENSE or mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/input-overlay
 */

#pragma once

#ifndef CCT

#ifndef WINDOWS
#ifdef _WIN32
#define WINDOWS
#else
#define LINUX
#endif
#endif /* WINDOWS / LINUX */

#ifdef LINUX
#ifndef VC_KP_UP /* keypad arrows are undefined on linux */
#define VC_KP_UP 0xEE48
#define VC_KP_DOWN 0xEE4B
#define VC_KP_LEFT 0xEE4D
#define VC_KP_RIGHT 0xEE50
#endif

#endif

#endif /* CCT */

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define GET_PROPS(S)    (obs_properties_get(props, S))
#define GET_BOOL(X)     (obs_data_get_bool(s, X))
#define UTIL_MAX(a,b)               (((a) > (b)) ? (a) : (b))
#define UTIL_MIN(a,b)               (((a) < (b)) ? (a) : (b))
#define UTIL_CLAMP(lower, x, upper) (UTIL_MIN(upper, UTIL_MAX(x, lower)))

#define DEAD_ZONE(x, dz)    ((x < dz) && (x > -dz))

#define warning(format, ...) blog(LOG_WARNING, "[%s] " format, \
		obs_source_get_name(m_source), ##__VA_ARGS__)

/* Lang Input Overlay */
#define S_OVERLAY_FILE              "overlay_image"
#define S_LAYOUT_FILE               "layout_file"
#define S_CONTROLLER_ID             "controller_id"
#define S_CONTROLLER_L_DEAD_ZONE    "controller_l_deadzone"
#define S_CONTROLLER_R_DEAD_ZONE    "controller_r_deadzone"
#define S_MOUSE_SENS                "mouse_sens"
#define S_MOUSE_DEAD_ZONE           "mouse_deadzone"
#define S_MONITOR_USE_CENTER        "monitor_use_center"
#define S_MONITOR_H_CENTER          "monitor_h_center"
#define S_MONITOR_V_CENTER          "monitor_v_center"
#define S_RELOAD_PAD_DEVICES		"reload_pads"

#define T_(v)                       obs_module_text(v)
#define T_OVERLAY_FILE              T_("OverlayFile")
#define T_LAYOUT_FILE               T_("LayoutFile")
#define T_FILTER_IMAGE_FILES        T_("Filter.ImageFiles")
#define T_FILTER_TEXT_FILES         T_("Filter.TextFiles")
#define T_FILTER_ALL_FILES          T_("Filter.AllFiles")
#define T_RELOAD_PAD_DEVICES		T_("Gamepad.Reload")
#define T_CONTROLLER_ID             T_("GamepadId")
#define T_CONROLLER_L_DEADZONE      T_("Gamepad.LeftDeadZone")
#define T_CONROLLER_R_DEADZONE      T_("Gamepad.RightDeadZone")
#define T_MOUSE_SENS                T_("Mouse.Sensitivity")
#define T_MOUSE_DEAD_ZONE           T_("Mouse.Deadzone")
#define T_MONITOR_USE_CENTER        T_("Mouse.UseCenter")
#define T_MONITOR_H_CENTER          T_("Monitor.CenterX")
#define T_MONITOR_V_CENTER          T_("Monitor.CenterY")

/* Lang Input History */
#define S_OVERLAY_HISTORY_SIZE          "history_size"
#define S_OVERLAY_FIX_CUTTING           "fix_cutting"
#define S_OVERLAY_INCLUDE_MOUSE	        "include_mouse"
#define S_OVERLAY_INCLUDE_PAD           "include_pad"
#define S_OVERLAY_INTERVAL              "interval"
#define S_OVERLAY_CLEAR_HISTORY         "clear_history"
#define S_OVERLAY_ENABLE_REPEAT_KEYS    "repeat_keys"
#define S_OVERLAY_ENABLE_AUTO_CLEAR     "auto_clear"
#define S_OVERLAY_AUTO_CLEAR_INTERVAL   "auto_clear_interval"
#define S_OVERLAY_ICON_V_SPACE          "icon_v_space"
#define S_OVERLAY_ICON_H_SPACE          "icon_h_space"

#define S_OVERLAY_MODE                  "mode"
#define S_OVERLAY_KEY_NAME_PATH         "key_name_path"
#define S_OVERLAY_USE_FALLBACK_NAME     "use_fallback_names"
#define S_OVERLAY_DIRECTION             "direction"
#define S_OVERLAY_DIRECTION_UP          "up"
#define S_OVERLAY_DIRECTION_DOWN        "down"
#define S_OVERLAY_DIRECTION_LEFT        "left"
#define S_OVERLAY_DIRECTION_RIGHT       "right"

#define S_OVERLAY_KEY_ICON_PATH         "key_icon_path"
#define S_OVERLAY_KEY_ICON_CONFIG_PATH  "key_icon_config"

#define S_OVERLAY_FONT                  "font"
#define S_OVERLAY_FONT_COLOR            "color"
#define S_OVERLAY_OUTLINE               "outline"
#define S_OVERLAY_OUTLINE_SIZE          "outline_size"
#define S_OVERLAY_OUTLINE_COLOR         "outline_color"
#define S_OVERLAY_OUTLINE_OPACITY       "outline_opacity"
#define S_OVERLAY_OPACITY               "opacity"
#define S_OVERLAY_COMMAND_MODE          "command_mode"

#define T_OVERLAY_KEY_NAME_PATH         T_("Overlay.KeyTranslationPath")
#define T_OVERLAY_USE_FALLBACK_NAMES    T_("Overlay.UseFallback.Translation")
#define T_OVERLAY_KEY_ICON_PATH         T_("Overlay.KeyIconPath")
#define T_OVERLAY_KEY_ICON_CONFIG_PATH  T_("Overlay.KeyIconConfigPath")
#define T_OVERLAY_ICON_V_SPACE          T_("Overlay.KeyIconVSpace")
#define T_OVERLAY_ICON_H_SPACE          T_("Overlay.KeyIconHSpace")

#define T_OVERLAY_MODE                  T_("Overlay.Mode")
#define T_OVERLAY_MODE_TEXT             T_("Overlay.Mode.Text")
#define T_OVERLAY_MODE_ICON             T_("Overlay.Mode.Icons")
#define T_OVERLAY_DIRECTION             T_("Overlay.Direction")
#define T_OVERLAY_DIRECTION_UP          T_("Overlay.Direction.Up")
#define T_OVERLAY_DIRECTION_DOWN        T_("Overlay.Direction.Down")
#define T_OVERLAY_DIRECTION_LEFT        T_("Overlay.Direction.Left")
#define T_OVERLAY_DIRECTION_RIGHT       T_("Overlay.Direction.Right")

#define T_OVERLAY_FONT                  T_("OverlayFont")
#define T_OVERLAY_FONT_COLOR            T_("OverlayFontColor")
#define T_OVERLAY_DIRECTION_LABEL       T_("OverlayDirection.Label")
#define T_OVERLAY_HISTORY_SIZE          T_("OverlayHistory.Size")
#define T_OVERLAY_FIX_CUTTING           T_("Overlay.FixCutting")
#define T_OVERLAY_INCLUDE_MOUSE         T_("Overlay.IncludeMouse")
#define T_OVERLAY_INCLUDE_PAD           T_("Overlay.IncludePad")
#define T_OVERLAY_CLEAR_HISTORY         T_("Overlay.ClearHistory")
#define T_OVERLAY_OPACITY               T_("Overlay.Opacity")

#define T_OVERLAY_OUTLINE               T_("Overlay.Outline")
#define T_OVERLAY_OUTLINE_SIZE          T_("Overlay.Outline.Size")
#define T_OVERLAY_OUTLINE_COLOR         T_("Overlay.Outline.Color")
#define T_OVERLAY_OUTLINE_OPACITY       T_("Overlay.Outline.Opacity")
#define T_OVERLAY_INTERVAL              T_("Overlay.Update.Interval")
#define T_OVERLAY_ENABLE_REPEAT_KEYS    T_("Overlay.Enable.RepeatKeys")
#define T_OVERLAY_ENABLE_AUTO_CLEAR     T_("Overlay.Enable.AutoClear")
#define T_OVERLAY_AUTO_CLEAR_INTERVAL   T_("Overlay.AutoClear.Interval")

#define T_OVERLAY_COMMAND_MODE          T_("Overlay.Commandmode")

#define T_MENU_OPEN_SETTINGS		T_("Menu.InputOverlay.OpenSettings")

#define WHEEL_UP        -1
#define WHEEL_DOWN      1

/* These were free in uiohook.h */
#define VC_NONE               0xFFFF

#define VC_MOUSE_MASK         0xED00
#define VC_MOUSE_WHEEL_UP     0xED11
#define VC_MOUSE_WHEEL_DOWN   0xED12
#define VC_MOUSE_WHEEL	      0xED13

#define VC_MOUSE_BUTTON1      (MOUSE_BUTTON1 | VC_MOUSE_MASK)
#define VC_MOUSE_BUTTON2      (MOUSE_BUTTON2 | VC_MOUSE_MASK)
#define VC_MOUSE_BUTTON3      VC_MOUSE_WHEEL
#define VC_MOUSE_BUTTON4      (MOUSE_BUTTON4 | VC_MOUSE_MASK)
#define VC_MOUSE_BUTTON5      (MOUSE_BUTTON5 | VC_MOUSE_MASK)

/* These are used for Command mode */
#define CHAR_BACK           0x8
#define CHAR_ENTER          0xD

/* Gamepad constants */
#define VC_PAD_MASK         0xEC00
#define VC_STICK_DATA       0xEC30
#define VC_TRIGGER_DATA     0xEC31
#define VC_DPAD_DATA        0xEC32

#define PAD_TO_VC(a)        (a | VC_PAD_MASK)

#define PAD_ICON_COUNT      22
#define PAD_BUTTON_COUNT    17

#define PAD_BODY            17
#define PAD_PLAYER_1        18
#define PAD_PLAYER_2        19
#define PAD_PLAYER_3        20
#define PAD_PLAYER_4        21

#define PAD_A               0
#define PAD_B               1
#define PAD_X               2
#define PAD_Y               3
#define PAD_LB              4
#define PAD_RB              5
#define PAD_BACK            6
#define PAD_START           7
#define PAD_X_BOX_KEY	    8
#define PAD_L_ANALOG        9
#define PAD_R_ANALOG        10
#define PAD_DPAD_LEFT       11
#define PAD_DPAD_RIGHT      12
#define PAD_DPAD_UP         13
#define PAD_DPAD_DOWN       14
#define PAD_LT              15
#define PAD_RT              16

/* Get default key names from a libuiohook keycode */
const char* key_to_text(int key_code);

#include <string>
/* Creates string for obs to use as accepted files for a file dialog */
std::string util_file_filter(const char* display, const char* formats);

/* Changes slashes in path to fit Unix formatting */
void util_format_path(std::string& path);

void util_enable_mask(uint16_t& masks, uint16_t mask);
void util_disable_mask(uint16_t& masks, uint16_t mask);
void util_set_mask(uint16_t& masks, uint16_t mask, bool state);

uint16_t util_mouse_to_vc(int m);

#ifdef DEBUG
uint16_t random_vc();
#endif
