// gh2test - ReXGlue Recompiled Project
//
// This file is yours to edit. 'rexglue migrate' will NOT overwrite it.

#include "generated/gh2test_init.h"

#include "gh2test_app.h"

REX_DEFINE_APP(gh2test, Gh2testApp::Create)
REX_HOOK(rex_sub_8239CA70, memset)
REX_HOOK(rex_sub_8239CB70, memcpy)
REX_HOOK(rex_sub_8239D4F0, memmove)