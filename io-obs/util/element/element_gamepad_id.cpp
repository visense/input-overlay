/**
 * This file is part of input-overlay
 * which is licensed under the MPL 2.0 license
 * See LICENSE or mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/input-overlay
 */

#include "../../sources/input_source.hpp"
#include "../../../ccl/ccl.hpp"
#include "element_gamepad_id.hpp"
#include "../util.hpp"

void element_gamepad_id::load(ccl_config* cfg, const std::string& id)
{
    element_texture::load(cfg, id);
    auto i = 1;
    for (auto& map : m_mappings)
    {
        map = m_mapping;
        map.x += i++ * (m_mapping.cx + CFG_INNER_BORDER);
    }
}

void element_gamepad_id::draw(gs_effect_t* effect,
    gs_image_file_t* image, element_data* data, sources::shared_settings* settings)
{
    if (settings->gamepad > 0)
    {
        element_texture::draw(effect, image, &m_mappings[settings->gamepad - 1]);
    }
    else
    {
        element_texture::draw(effect, image, &m_mapping);
    }
}
