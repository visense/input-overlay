/**
 * This file is part of input-overlay
 * which is licensed under the MPL 2.0 license
 * See LICENSE or mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/input-overlay
 */

#ifndef LAYOUT_CONSTANTS
#define LAYOUT_CONSTANTS

/* Prevent cropped textures from overlapping */
#define CFG_INNER_BORDER    3
#define CFG_OUTER_BORDER    1

#define CFG_DEBUG_FLAG      "debug"
#define CFG_DEFAULT_WIDTH   "default_width"
#define CFG_DEFAULT_HEIGHT  "default_height"
#define CFG_H_SPACE         "space_h"
#define CFG_V_SPACE         "space_v"

#define CFG_FLAGS           "flags"

#define CFG_TOTAL_WIDTH     "overlay_width"
#define CFG_TOTAL_HEIGHT    "overlay_height"

#define CFG_POS             "_pos"
#define CFG_MAPPING         "_mapping"
#define CFG_TYPE            "_type"
#define CFG_KEY_CODE        "_code"
#define CFG_WIDTH           "_width"
#define CFG_HEIGHT          "_height"
#define CFG_Z_LEVEL         "_z_level"
#define CFG_FIRST_ID        "first_element"
#define CFG_NEXT_ID         "_next"
#define CFG_SIDE            "_side"
#define CFG_STICK_RADIUS    "_stick_radius"
#define CFG_MOUSE_RADIUS    "_mouse_radius"
#define CFG_MOUSE_TYPE      "_mouse_type"
#define CFG_DIRECTION       "_direction"
#define CFG_TRIGGER_MODE    "_trigger_mode"
#define CFG_TEXT            "_text"
#define CFG_TEXT_RESET      "_reset_text"

/* Misc */
#define AXIS_MAX_AMPLITUDE  32767
#define STICK_DEAD_ZONE     100
/* ns after last scroll message until reset */
#define SCROLL_TIMEOUT      (120 * 1000 * 1000)

/* Text element formatting */
#define TEXT_FORMAT_WHEEL_AMOUNT    "%w"
#define TEXT_FORMAT_LMB_CLICKS      "%l"
#define TEXT_FORMAT_RMB_CLICKS      "%r"
#define TEXT_FORMAT_MMB_CLICKS      "%m"
#define TEXT_FORMAT_MOUSE_X         "%x"
#define TEXT_FORMAT_MOUSE_Y         "%y"

#define TEXT_FORMAT_WHEEL_FLAG      1 << 0
#define TEXT_FORMAT_LMB_FLAG        1 << 1
#define TEXT_FORMAT_RMB_FLAG        1 << 2
#define TEXT_FORMAT_MMB_FLAG        1 << 3
#define TEXT_FORMAT_MOUSE_X_FLAG    1 << 4
#define TEXT_FORMAT_MOUSE_Y_FLAG    1 << 5

enum overlay_flags
{
    FLAG_LEFT_STICK = 1 << 0,
    FLAG_RIGHT_STICK = 1 << 1,
    FLAG_GAMEPAD = 1 << 2,
    FLAG_MOUSE = 1 << 3,
    FLAG_TEXT = 1 << 4
};

enum dpad_direction
{
    DPAD_CENTER,
    DPAD_LEFT,
    DPAD_RIGHT,
    DPAD_UP,
    DPAD_DOWN,
    DPAD_TOP_LEFT,
    DPAD_TOP_RIGHT,
    DPAD_BOTTOM_LEFT,
    DPAD_BOTTOM_RIGHT
};

enum mouse_movement_type
{
    DOT,
    ARROW
};

enum element_side
{
    SIDE_INVALID = -1,
    SIDE_LEFT,
    SIDE_RIGHT
};

enum trigger_direction
{
    TRIGGER_UP,
    TRIGGER_DOWN,
    TRIGGER_LEFT,
    TRIGGER_RIGHT
};

enum icon_direction
{
    DIR_DOWN,
    DIR_UP,
    DIR_LEFT,
    DIR_RIGHT
};

enum button_state
{
    STATE_RELEASED,
    STATE_PRESSED,
};

enum wheel_direction
{
    WHEEL_DIR_UP = -1,
    WHEEL_DIR_NONE = 0,
    WHEEL_DIR_DOWN = 1
};

enum element_type
{
    INVALID = -1,
    TEXTURE,
    BUTTON,
    /* MOUSE_WHEEL was taken :( */
    MOUSE_SCROLLWHEEL,
    MOUSE_MOVEMENT,
    ANALOG_STICK,
    TRIGGER,
    /* Shows game pad number 1 through 4 */
    GAMEPAD_ID,
    TEXT,
    DPAD_STICK,
};

#endif