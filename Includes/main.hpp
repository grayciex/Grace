#ifndef MAIN_H
#define MAIN_H

#include <CTRPluginFramework.hpp>
#include "Game.hpp"
#include "Plugin.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;
    struct U32_NAME_VALUE {const char *name; const u32 value;};
}
#endif
