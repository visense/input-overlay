/**
 * This file is part of input-overlay
 * which is licensed under the MPL 2.0 license
 * See LICENSE or mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/input-overlay
 */

#include "input_source.hpp"
#include "../hook/hook_helper.hpp"
#include "../hook/gamepad_hook.hpp"
#include "../util/element/element_data_holder.hpp"
#include "../util/util.hpp"
#include "../../ccl/ccl.hpp"
#include <clocale>

namespace sources
{
    inline void input_source::update(obs_data_t* settings)
    {
        m_settings.image_file = obs_data_get_string(settings, S_OVERLAY_FILE);
        m_settings.layout_file = obs_data_get_string(settings, S_LAYOUT_FILE);
        m_overlay->load();

        m_settings.gamepad = obs_data_get_int(settings, S_CONTROLLER_ID);
#ifdef HAVE_XINPUT
        m_settings.left_dz = obs_data_get_int(settings, S_CONTROLLER_L_DEAD_ZONE) / STICK_MAX_VAL;
        m_settings.right_dz = obs_data_get_int(settings, S_CONTROLLER_R_DEAD_ZONE) / STICK_MAX_VAL;
#endif
    }

    inline void input_source::tick(float seconds)
    {
        /* NO-OP */
    }

    inline void input_source::render(gs_effect_t* effect) const
    {
        if (!m_overlay->get_texture() || !m_overlay->get_texture()->texture)
            return;
        
        if (m_settings.layout_file.empty() || !m_overlay->is_loaded())
        {
            gs_effect_set_texture(gs_effect_get_param_by_name(effect, "image"),
                m_overlay->get_texture()->texture);
            gs_draw_sprite(m_overlay->get_texture()->texture, 0, cx, cy);
        }
        else
        {
            m_overlay->draw(effect);
        }
    }

    bool path_changed(obs_properties_t* props, obs_property_t* p,
        obs_data_t* s)
    {
        const std::string cfg = obs_data_get_string(s, S_LAYOUT_FILE);
        auto temp = ccl_config(cfg, "");

        const auto flags = temp.get_int(CFG_FLAGS, true);

        obs_property_set_visible(GET_PROPS(S_CONTROLLER_L_DEAD_ZONE), flags & FLAG_LEFT_STICK);
        obs_property_set_visible(GET_PROPS(S_CONTROLLER_R_DEAD_ZONE), flags & FLAG_RIGHT_STICK);
        obs_property_set_visible(GET_PROPS(S_CONTROLLER_ID), flags & FLAG_GAMEPAD
            || (flags & FLAG_LEFT_STICK || flags & FLAG_RIGHT_STICK));
        obs_property_set_visible(GET_PROPS(S_MOUSE_SENS), flags & FLAG_MOUSE);
        obs_property_set_visible(GET_PROPS(S_MONITOR_USE_CENTER), flags & FLAG_MOUSE);
        obs_property_set_visible(GET_PROPS(S_MOUSE_DEAD_ZONE), flags & FLAG_MOUSE);

        return true;
    }

    bool use_monitor_center_changed(obs_properties_t* props, obs_property_t* p,
        obs_data_t* s)
    {
        const auto use_center = obs_data_get_bool(s, S_MONITOR_USE_CENTER);
        obs_property_set_visible(GET_PROPS(S_MONITOR_H_CENTER), use_center);
        obs_property_set_visible(GET_PROPS(S_MONITOR_V_CENTER), use_center);

        return true;
    }
    
    bool reload_pads(obs_properties_t* props, obs_property_t* property,
        void* data)
    {
        gamepad::init_pad_devices();
        return true;
    }

    obs_properties_t* get_properties_for_overlay(void* data)
    {
        const auto s = static_cast<input_source*>(data);
        const auto props = obs_properties_create();
        std::string img_path;
        std::string layout_path;

        auto filter_img = util_file_filter(
            T_FILTER_IMAGE_FILES, "*.jpg *.png *.bmp");
        auto filter_text = util_file_filter(T_FILTER_TEXT_FILES, "*.ini");

        obs_properties_add_path(props, S_OVERLAY_FILE, T_OVERLAY_FILE,
            OBS_PATH_FILE,
            filter_img.c_str(), img_path.c_str());

        const auto cfg = obs_properties_add_path(props, S_LAYOUT_FILE, T_LAYOUT_FILE,
            OBS_PATH_FILE,
            filter_text.c_str(), layout_path.c_str());

        obs_property_set_modified_callback(cfg, path_changed);

        /* Mouse stuff */
        obs_property_set_visible(obs_properties_add_int_slider(props,
            S_MOUSE_SENS, T_MOUSE_SENS, 1, 500, 1), false);

        auto use_center = obs_properties_add_bool(
            props, S_MONITOR_USE_CENTER, T_MONITOR_USE_CENTER);
        obs_property_set_modified_callback(use_center,
                                           use_monitor_center_changed);

        obs_property_set_visible(obs_properties_add_int(props, S_MONITOR_H_CENTER, T_MONITOR_H_CENTER,
                               -9999, 9999, 1), false);
        obs_property_set_visible(obs_properties_add_int(props, S_MONITOR_V_CENTER, T_MONITOR_V_CENTER,
                               -9999, 9999, 1), false);
        obs_property_set_visible(obs_properties_add_int_slider(props, S_MOUSE_DEAD_ZONE, T_MOUSE_DEAD_ZONE,
                                      0, 50, 1), false);

        /* Gamepad stuff */
        obs_property_set_visible(obs_properties_add_int(props, S_CONTROLLER_ID,
            T_CONTROLLER_ID, 0, 3, 1), false);

#if HAVE_XINPUT /* Linux only allows values 0 - 127 */
        obs_property_set_visible(obs_properties_add_int_slider(props, S_CONTROLLER_L_DEAD_ZONE,
                                      T_CONROLLER_L_DEADZONE, 1,
                                      STICK_MAX_VAL - 1, 1), false);
        obs_property_set_visible(obs_properties_add_int_slider(props, S_CONTROLLER_R_DEAD_ZONE,
                                      T_CONROLLER_R_DEADZONE, 1,
                                      STICK_MAX_VAL - 1, 1), false);
#else
        obs_properties_add_button(props, S_RELOAD_PAD_DEVICES, T_RELOAD_PAD_DEVICES, reload_pads);
#endif
        return props;
    }

    void register_overlay_source()
    {
        /* Input Overlay */
        obs_source_info si = {};
        si.id = "input-overlay";
        si.type = OBS_SOURCE_TYPE_INPUT;
        si.output_flags = OBS_SOURCE_VIDEO;
        si.get_properties = get_properties_for_overlay;

        si.get_name = [](void*) { return obs_module_text("InputOverlay"); };
        si.create = [](obs_data_t* settings, obs_source_t* source)
        {
            return (void*)new input_source(source, settings);
        };
        si.destroy = [](void* data)
        {
            delete reinterpret_cast<input_source*>(data);
        };
        si.get_width = [](void* data)
        {
            return reinterpret_cast<input_source*>(data)->m_settings.cx;
        };
        si.get_height = [](void* data)
        {
            return reinterpret_cast<input_source*>(data)->m_settings.cy;
        };

        si.get_defaults = [](obs_data_t* settings)
        {
            /* NO-OP */
        };

        si.update = [](void* data, obs_data_t* settings)
        {
            reinterpret_cast<input_source*>(data)->update(settings);
        };
        si.video_tick = [](void* data, float seconds)
        {
            reinterpret_cast<input_source*>(data)->tick(seconds);
        };
        si.video_render = [](void* data, gs_effect_t* effect)
        {
            reinterpret_cast<input_source*>(data)->render(effect);
        };
        obs_register_source(&si);
    }
}
