/**
 * This file is part of input-overlay
 * which is licensed under the MPL 2.0 license
 * See LICENSE or mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/input-overlay
 */

#include <util/platform.h>
#include "gamepad_hook.hpp"
#include "hook_helper.hpp"
#include "../util/layout_constants.hpp"
#include "../util/element/element_data_holder.hpp"
#include "../util/element/element_trigger.hpp"
#include "../util/element/element_analog_stick.hpp"
#include "../util/element/element_dpad.hpp"
#include "../util/element/element_button.hpp"

namespace gamepad
{
    bool gamepad_hook_state = false;
    bool gamepad_hook_run_flag = true;
    GamepadState pad_states[PAD_COUNT];

#ifdef WINDOWS
    static HANDLE hook_thread;
#else
    static pthread_t game_pad_hook_thread;
#endif

    void start_pad_hook()
    {
        if (gamepad_hook_state)
            return;
#ifdef LINUX
        /* Prevent the hook loop from running if there's no gamepads
         * Prevents infinite loop
         * Hook will be restarted, once users click "reload" button
         * in source properties
         */
        gamepad_hook_state = gamepad_hook_run_flag = init_pad_devices();    
#endif
		
#ifdef WINDOWS
		xinput_fix::load();
        if (xinput_fix::loaded)
        {
			hook_thread = CreateThread(nullptr, 0, static_cast<LPTHREAD_START_ROUTINE>(hook_method),
				nullptr, 0, nullptr);
        }
   
        gamepad_hook_state = hook_thread;
#else
        gamepad_hook_state = pthread_create(&game_pad_hook_thread, nullptr, hook_method, nullptr) == 0;
#endif
		init_pad_devices();
    }

    bool init_pad_devices()
    {
        uint8_t id = 0;
        auto flag = false;
        for (auto& state : pad_states)
        {
            state.init(id++);
            if (state.valid())
                flag = true;
        }
        return flag;
    }

    void end_pad_hook()
    {
        gamepad_hook_run_flag = false;

#ifdef WINDOWS
        CloseHandle(hook_thread);
		xinput_fix::unload();
#endif
    }

    /* Background process for quering game pads */
#ifdef WINDOWS
    DWORD WINAPI hook_method(const LPVOID arg)
#else
    
    void* hook_method(void *)
#endif
    {
        while (gamepad_hook_run_flag)
        {
            if (!hook::input_data)
                break;
            for (auto& pad : pad_states)
            {
                if (!pad.valid())
                    continue;

#ifdef WINDOWS
				dpad_direction d;

                for (const auto& button : all_codes)
                {
                    const auto state = xinput_fix::pressed(pad.ptr(), button);
                    hook::input_data->add_gamepad_data(pad.get_id(), xinput_to_vc(button),
                        new element_data_button(state));
                }

                /* Dpad direction */
				xinput_fix::get_dpad(pad.ptr(), dir);
                hook::input_data->add_gamepad_data(pad.get_id(), VC_DPAD_DATA,
                    new element_data_dpad(dir[0], dir[1]));

                /* Analog sticks */
                hook::input_data->add_gamepad_data(pad.get_id(), VC_STICK_DATA,
                    new element_data_analog_stick(
                        xinput_fix::pressed(pad.ptr(), xinput_fix::CODE_LEFT_THUMB),
						xinput_fix::pressed(pad.ptr(), xinput_fix::CODE_RIGHT_THUMB),
						xinput_fix::stick_l_x(pad.ptr()),
						xinput_fix::stick_l_y(pad.ptr()),
						xinput_fix::stick_r_x(pad.ptr()),
						xinput_fix::stick_r_y(pad.ptr())
                    ));

                /* Trigger buttons */
                hook::input_data->add_gamepad_data(pad.get_id(), VC_TRIGGER_DATA,
                    new element_data_trigger(
						xinput_fix::trigger_l(pad.ptr()),
						xinput_fix::trigger_r(pad.ptr())
                    ));
#else
                unsigned char m_packet[8];
                fread(m_packet, sizeof(char) * 8, 1, pad.dev());
                
                if (m_packet[ID_TYPE] == ID_BUTTON) {
                    switch(m_packet[ID_KEY_CODE])
                    {
                        case PAD_L_ANALOG:
                            hook::input_data->add_gamepad_data(pad.get_id(), VC_STICK_DATA,
                                new element_data_analog_stick(m_packet[ID_STATE_1] == ID_PRESSED ?
                                STATE_PRESSED : STATE_RELEASED, SIDE_LEFT));
                            break;
                        case PAD_R_ANALOG:
                            hook::input_data->add_gamepad_data(pad.get_id(), VC_STICK_DATA,
                                new element_data_analog_stick(m_packet[ID_STATE_1] == ID_PRESSED ?
                                STATE_PRESSED : STATE_RELEASED, SIDE_RIGHT));
                            break;
                        default:
                            switch(m_packet[ID_KEY_CODE])
                            {
                                case PAD_DPAD_DOWN:
                                    hook::input_data->add_gamepad_data(pad.get_id(),
                                        VC_DPAD_DATA, new element_data_dpad(
                                            DPAD_DOWN, m_packet[ID_STATE_1] == ID_PRESSED ?
                                                       STATE_PRESSED : STATE_RELEASED
                                            ));
                                break;
                                case PAD_DPAD_UP:
                                    hook::input_data->add_gamepad_data(pad.get_id(),
                                                                       VC_DPAD_DATA, new element_data_dpad(
                                            DPAD_UP, m_packet[ID_STATE_1] == ID_PRESSED ?
                                                       STATE_PRESSED : STATE_RELEASED
                                        ));
                                    break;
                                case PAD_DPAD_LEFT:
                                    hook::input_data->add_gamepad_data(pad.get_id(),
                                        VC_DPAD_DATA, new element_data_dpad(
                                            DPAD_LEFT, m_packet[ID_STATE_1] == ID_PRESSED ?
                                                       STATE_PRESSED : STATE_RELEASED
                                        ));
                                    break;
                                case PAD_DPAD_RIGHT:
                                    hook::input_data->add_gamepad_data(pad.get_id(),
                                        VC_DPAD_DATA, new element_data_dpad(
                                            DPAD_RIGHT, m_packet[ID_STATE_1] == ID_PRESSED ?
                                                       STATE_PRESSED : STATE_RELEASED
                                        ));
                                    break;
                                default: ;
                            }
                            hook::input_data->add_gamepad_data(pad.get_id(),
                                PAD_TO_VC(m_packet[ID_KEY_CODE]),
                                new element_data_button(m_packet[ID_STATE_1] == ID_PRESSED ?
                                STATE_PRESSED : STATE_RELEASED));
                    }
                } else {
                    float axis;
                    switch (m_packet[ID_KEY_CODE]) {
                        case ID_L_TRIGGER:
                            hook::input_data->add_gamepad_data(pad.get_id(), VC_TRIGGER_DATA,
                                new element_data_trigger(T_DATA_LEFT,
                                    m_packet[ID_STATE_1] / 255.f));
                            break;
                        case ID_R_TRIGGER:
                            hook::input_data->add_gamepad_data(pad.get_id(), VC_TRIGGER_DATA,
                                new element_data_trigger(T_DATA_RIGHT,
                                m_packet[ID_STATE_1] / 255.f));
                            break;
                        case ID_R_ANALOG_X:
                            if (m_packet[ID_STATE_2] < 128)
                                axis = UTIL_CLAMP(-1.f, (m_packet[ID_STATE_2]) / STICK_MAX_VAL, 1.f);
                            else
                                axis = UTIL_CLAMP(-1.f,
                                    (m_packet[ID_STATE_2] - 255) / STICK_MAX_VAL, 1.f);
                            
                            hook::input_data->add_gamepad_data(pad.get_id(), VC_STICK_DATA, new element_data_analog_stick(axis,
                                STICK_STATE_RIGHT_X));
                            break;
                        case ID_R_ANALOG_Y:
                            if (m_packet[ID_STATE_2] < 128)
                                axis = UTIL_CLAMP(-1.f, (m_packet[ID_STATE_2]) / STICK_MAX_VAL, 1.f);
                            else
                                axis = UTIL_CLAMP(-1.f, (m_packet[ID_STATE_2] - 255) /
                                STICK_MAX_VAL, 1.f);
                            hook::input_data->add_gamepad_data(pad.get_id(), VC_STICK_DATA, new element_data_analog_stick(axis,
                                STICK_STATE_RIGHT_Y));
                            break;
                        case ID_L_ANALOG_X:
                            if (m_packet[ID_STATE_2] < 128)
                                axis = UTIL_CLAMP(-1.f, (m_packet[ID_STATE_2]) / STICK_MAX_VAL, 1.f);
                            else
                                axis = UTIL_CLAMP(-1.f, (m_packet[ID_STATE_2] - 255) / STICK_MAX_VAL, 1.f);
        
                            hook::input_data->add_gamepad_data(pad.get_id(), VC_STICK_DATA, new element_data_analog_stick(axis,
                                STICK_STATE_LEFT_X));
                            break;
                        case ID_L_ANALOG_Y:
                            if (m_packet[ID_STATE_2] < 128)
                                axis = UTIL_CLAMP(-1.f, ((float) m_packet[ID_STATE_2]) / STICK_MAX_VAL, 1.f);
                            else
                                axis = UTIL_CLAMP(-1.f, ((float) m_packet[ID_STATE_2] - 255) / STICK_MAX_VAL, 1.f);
        
                            hook::input_data->add_gamepad_data(pad.get_id(), VC_STICK_DATA, new element_data_analog_stick(axis,
                                STICK_STATE_LEFT_Y));
                            break;
                        default: ;
                    }
                }

#endif /* LINUX */
            }
#ifdef  WINDOWS /* Delay on linux results in buffered input */
            os_sleep_ms(25);
#endif
        }

        for (auto& state : pad_states)
            state.unload();
#ifdef WINDOWS
        return UIOHOOK_SUCCESS;
#else
        pthread_exit(nullptr);
#endif
    }
}
