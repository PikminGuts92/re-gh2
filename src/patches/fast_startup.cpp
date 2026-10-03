#include <rex/ppc/context.h>
#include <rex/cvar.h>
#include <rex/system/kernel_state.h>
#include "constants.h"


REXCVAR_DEFINE_BOOL(fast_startup, false, GAME_SETTINGS_CATEGORY, "Skip startup logos and intro video");
void SetSplashWaitTime(PPCRegister& f30) {
    bool fast = static_cast<bool>(REXCVAR_GET(fast_startup));
    if (fast) {
        f30.f64 = 0.0f;
    }
}

bool SkipRedOctaneLogo() {
    return static_cast<bool>(REXCVAR_GET(fast_startup));
}

bool SkipActivisionLogo() {
    return static_cast<bool>(REXCVAR_GET(fast_startup));
}

bool SkipHarmonixLogo() {
    return static_cast<bool>(REXCVAR_GET(fast_startup));
}

bool MetaPanelOnPlayMovie(PPCRegister& r3) {
    bool fast_startup = static_cast<bool>(REXCVAR_GET(fast_startup));
    if (!fast_startup) {
        return false;
    }

    void* movie_path_addr = rex::system::kernel_state()->memory()->TranslateVirtual(r3.u32);
    const char* movie_path = reinterpret_cast<const char*>(movie_path_addr);

    // Skip if intro video
    return std::string_view(movie_path).compare("intro.wmv") == 0;
}