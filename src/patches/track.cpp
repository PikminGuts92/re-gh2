#include <rex/ppc/context.h>
#include <rex/cvar.h>
#include "constants.h"

REXCVAR_DEFINE_BOOL(force_hyperspeed, false, GAME_SETTINGS_CATEGORY, "Force hyperspeed");
REXCVAR_DEFINE_DOUBLE(hyperspeed_scale, 1.5, GAME_SETTINGS_CATEGORY, "Hyperspeed scale (1x = 1.5)");

void ForceHyperspeed(PPCRegister& r3) {
    bool force = static_cast<bool>(REXCVAR_GET(force_hyperspeed));
    if (force) {
        r3.u32 = 1;
    }
}

void HyperspeedScale(PPCRegister& f0, PPCRegister& f31) {
    double scale = static_cast<double>(REXCVAR_GET(hyperspeed_scale));
    f31.f64 = f0.f64 * scale;
}