#include <u2f_app_i.h>
#include <gui/modules/variable_item_list.h>
#include "../u2f_config.h"

enum U2fVariableItemToggle {
    U2fVariableItemToggleOff,
    U2fVariableItemToggleOn,
    U2fVariableItemToggleSettingsNum,
};

const char* const gpio_otg_text[U2fVariableItemToggleSettingsNum] = {
    "OFF",
    "ON",
};

static void u2f_scene_config_resident_keys_change_callback(VariableItem* item) {
    U2fApp* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);

    variable_item_set_current_value_text(item, gpio_otg_text[index]);

    if(index == U2fVariableItemToggleOff) {
        app->config->resident_keys = false;
    } else if(index == U2fVariableItemToggleOn) {
        app->config->resident_keys = true;
    }

    // Save config
    u2f_config_write(app->config);
}

void u2f_scene_config_on_enter(void* context) {
    U2fApp* app = context;

    // Load config
    u2f_config_load(app->config);

    VariableItemList* var_item_list = app->config_view;

    VariableItem* item = variable_item_list_add(
        var_item_list, "Resident keys", 2, u2f_scene_config_resident_keys_change_callback, app);

    if(false /* TODO implement config */) {
        variable_item_set_current_value_index(item, U2fVariableItemToggleOn);
        variable_item_set_current_value_text(item, gpio_otg_text[U2fVariableItemToggleOn]);
    } else {
        variable_item_set_current_value_index(item, U2fVariableItemToggleOff);
        variable_item_set_current_value_text(item, gpio_otg_text[U2fVariableItemToggleOff]);
    }
}

// void u2f_scene_config_on_event(void* context, SceneManagerEvent event) {
//     furi_assert(context);
//     U2fApp* app = context;

//     if(event.type == SceneManagerEventTypeBack) {
//         scene_manager_previous_scene(app->scene_manager);
//         return true;
//     }
// }

void u2f_scene_config_on_exit(void* context) {
    U2fApp* app = context;
    variable_item_list_reset(app->config_view);
}
