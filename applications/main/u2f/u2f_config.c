#include "u2f_config.h"
#include <storage/storage.h>

#define U2F_CONFIG_FOLDER INT_PATH("u2f/")
#define U2F_SETTINGS_PATH U2F_CONFIG_FOLDER ".u2f.settings"
#define U2F_SETTINGS_FILE_SIZE sizeof(U2fConfig)

#define TAG "U2f"

static const struct U2fConfig default_config = {.resident_keys = false};

static bool u2f_config_load(U2fConfig* config) {
    bool state = false;

    Storage* fs_api = furi_record_open(RECORD_STORAGE);
    File* settings_file = storage_file_alloc(fs_api);
    if(storage_file_open(settings_file, U2F_SETTINGS_PATH, FSAM_READ, FSOM_OPEN_EXISTING)) {
        // Read config file
        size_t read = storage_file_read(settings_file, config, U2F_SETTINGS_FILE_SIZE);

        state = (read == U2F_SETTINGS_FILE_SIZE); // Will not pass if the file is too small
    }

    storage_file_close(settings_file);
    storage_file_free(settings_file);
    furi_record_close(RECORD_STORAGE);

    if(!state) {
        FURI_LOG_W(TAG, "Settings load error, generating new");

        // Write default config file
        state = u2f_config_write(&default_config);
    }

    if(!state) config = &default_config;
    return state;
}

static bool u2f_config_write(U2fConfig* config) {
    bool state = false;

    Storage* fs_api = furi_record_open(RECORD_STORAGE);
    File* settings_file = storage_file_alloc(fs_api);

    if(storage_file_open(settings_file, U2F_SETTINGS_PATH, FSAM_WRITE, FSOM_OPEN_ALWAYS)) {
        size_t wrote = storage_file_write(settings_file, config, U2F_SETTINGS_FILE_SIZE);

        state = (wrote == U2F_SETTINGS_FILE_SIZE); // Will not pass if file was not wrote entirely.
    }

    storage_file_close(settings_file);
    storage_file_free(settings_file);
    furi_record_close(RECORD_STORAGE);

    return state;
}
