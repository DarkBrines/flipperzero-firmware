
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct U2fConfig {
    _Bool resident_keys;
};

typedef struct U2fConfig U2fConfig;

_Bool u2f_config_load(U2fConfig* config);

_Bool u2f_config_write(U2fConfig* config);

#ifdef __cplusplus
}
#endif
