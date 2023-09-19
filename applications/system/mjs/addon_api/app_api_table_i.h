#include <assets_icons.h>
/* 
 * A list of app's private functions and objects to expose for plugins.
 * It is used to generate a table of symbols for import resolver to use.
 * TBD: automatically generate this table from app's header files
 */
static constexpr auto app_api_table = sort(create_array_t<sym_entry>(
    API_VARIABLE(I_Certification1_103x56, const Icon),
    API_VARIABLE(I_Certification2_46x33, const Icon)));