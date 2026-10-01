#include <rex/ppc/context.h>
#include <rex/logging.h>
#include <rex/system/kernel_state.h>

extern "C" void __imp__NewFile(PPCContext& ctx, uint8_t* base);

// handles the .. folders in the ARK
static std::filesystem::path sanitize_path(const char* cc) {
    std::filesystem::path result;
    for (const auto& part : std::filesystem::path(cc)) {
        if (part == "..") {
            result /= "(..)";
        } else {
            result /= part;
        }
    }
    return result;
}

static void replace_og_with_ng_in_path(char* cc) {
    size_t len = std::strlen(cc);

    for (size_t i = 0; (i + 3) < len; i++) {
        // Check if the current 4-character sequence matches "/og/"
        if (!(cc[i] == '/' && cc[i+1] == 'o' && cc[i+2] == 'g' && cc[i+3] == '/')) {
            continue;
        }

        // Replace 'o' with 'n'
        cc[i+1] = 'n';
        break;
    }
}

extern "C" REX_FUNC(NewFile) {
    uint32_t cc_addr = ctx.r3.u32;
    uint32_t flags = ctx.r4.u32;

    if (!cc_addr || !base) return;

    char* cc = reinterpret_cast<char*>(base + cc_addr);
    if (!cc || !*cc) return;

    if (std::string_view(cc).ends_with(".dta")) {
        // Assume always external
        REXLOG_INFO("NewFile: {} [flags={:#x}]", cc, flags);
        ctx.r4.u64 = flags | 0x10000;
        __imp__NewFile(ctx, base);
        return;
    }

    replace_og_with_ng_in_path(cc);
    std::filesystem::path file_path_sanitized = rex::cvar::GetFlagByName("game_data_root") / sanitize_path(cc);

    std::error_code ec;
    bool exists = std::filesystem::exists(file_path_sanitized);

    if (exists) {
        REXLOG_INFO("NewFile: {} [flags={:#x}]", cc, flags);
        ctx.r4.u64 = flags | 0x10000;
    } else {
        REXLOG_INFO("NewFile: {} (ARK) [flags={:#x}]", cc, flags);
    }

    __imp__NewFile(ctx, base);
}

bool SkipReadCachedDTB(PPCRegister& r3) {
    void* dta_path_addr = rex::system::kernel_state()->memory()->TranslateVirtual(r3.u32);
    const char* dta_path = reinterpret_cast<const char*>(dta_path_addr);

    // Check if dta exists
    std::filesystem::path dta_path_sanitized = rex::cvar::GetFlagByName("game_data_root") / sanitize_path(dta_path);
    bool dta_exists = std::filesystem::exists(dta_path_sanitized);

    if (dta_exists) {
        REXLOG_INFO("Loading dta outside ark: {}", dta_path);
        return true;
    }

    return false;
}