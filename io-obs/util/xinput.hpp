/**
 * This file is part of input-overlay
 * which is licensed under the MPL 2.0 license
 * See LICENSE or mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/input-overlay
 * 
 * based on https://forums.tigsource.com/index.php?PHPSESSID=biq1psqu44jbmc8if73olk4fh6&topic=26792.msg848190#msg848190
 * Thanks Microsoft for not allowing access to the guide button
 */

#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <stdio.h>
#include "util/vc/vc_stdint.h"

#define STICK_MAX_VAL   32767.f
#define TRIGGER_MAX_VAL 255.f

/**
 * Implementation of Xinput using 1.3
 * which allows access to the guide button
 * (The silver button in the middle of xbox controllers)
 */

enum button_state;

enum dpad_direction;

namespace xinput_fix
{

    enum gamepad_codes
    {
		CODE_DPAD_UP         = 0x0001,
		CODE_DPAD_DOWN       = 0x0002,
		CODE_DPAD_LEFT       = 0x0004,
		CODE_DPAD_RIGHT      = 0x0008,
		CODE_START           = 0x0010,
		CODE_BACK            = 0x0020,
        CODE_LEFT_THUMB      = 0x0040,
        CODE_RIGHT_THUMB     = 0x0080,
		CODE_LEFT_SHOULDER   = 0x0100,
		CODE_RIGHT_SHOULDER  = 0x0200,
        CODE_GUIDE           = 0x0400,
        CODE_A               = 0x1000,
        CODE_B               = 0x2000,
        CODE_X               = 0x4000,
        CODE_Y               = 0x8000
    };

	typedef struct
	{
		unsigned long   eventCount;
		WORD            wButtons;
		BYTE            bLeftTrigger;
		BYTE            bRightTrigger;
		SHORT           sThumbLX;
		SHORT           sThumbLY;
		SHORT           sThumbRX;
		SHORT           sThumbRY;
	} gamepad;

	TCHAR xinput_dll_path[MAX_PATH];
	HINSTANCE xinput_dll;

	extern bool loaded;
	extern gamepad_codes all_codes[];

    /* Util functions */
	void load();

	void unload();

	button_state pressed(gamepad* pad, gamepad_codes code);

	void free(gamepad* pad);

	int update(int id, gamepad* pad);

	uint16_t to_vc(gamepad_codes code);

	void get_dpad(gamepad* pad, dpad_direction dirs[2]);

	float trigger_l(gamepad* pad);

	float trigger_r(gamepad* pad);

	float stick_l_x(gamepad* pad);

	float stick_l_y(gamepad* pad);

	float stick_r_x(gamepad* pad);

	float stick_r_y(gamepad* pad);
}
#endif