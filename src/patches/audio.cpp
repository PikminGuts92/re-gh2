#include <rex/ppc/context.h>
#include <rex/cvar.h>
#include "constants.h"

REXCVAR_DEFINE_DOUBLE(audio_offset, 0.0, GAME_SETTINGS_CATEGORY, "Offset song audio to sync with notes");

void AudioOffsetHook(PPCRegister& f1) {
    double offset = static_cast<double>(REXCVAR_GET(audio_offset));
    f1.f64 += offset;
}

void AudioOffsetHookPractice(PPCRegister& f1) {
    double offset = static_cast<double>(REXCVAR_GET(audio_offset));
    double newpos = f1.f64 + offset;
    if (newpos < 0) return;
    else f1.f64 = newpos;
}