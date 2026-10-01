#include <rex/ppc/context.h>
#include <rex/cvar.h>
#include "constants.h"

REXCVAR_DEFINE_BOOL(force_guitar, false, GAME_SETTINGS_CATEGORY, "Force guitar input");

void GuitarHook(PPCRegister& r11) {
    bool force_guitar = static_cast<bool>(REXCVAR_GET(force_guitar));
    if (force_guitar) {
        r11.u64 = 7;
    }
}