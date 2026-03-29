#include <rex/ppc/context.h>
#include <rex/ppc/types.h>
#include <rex/logging.h>
#include <filesystem>
#include <system_error>
#include <string_view>

extern "C" void __imp__NewFile(PPCContext& ctx, uint8_t* base);

// handles the .. folders in the ARK
static std::filesystem::path SanitizePath(const char* cc) {
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

extern "C" PPC_FUNC(NewFile) {
    uint32_t cc_addr = ctx.r3.u32;
    uint32_t flags = ctx.r4.u32;

    if (!cc_addr || !base) return;

    const char* cc = reinterpret_cast<const char*>(base + cc_addr);
    if (!cc || !*cc) return;

    std::error_code ec;
    std::filesystem::path sanitized = SanitizePath(cc);

    bool exists = std::filesystem::exists(sanitized, ec);

    if (!exists && sanitized.begin() != sanitized.end() && *sanitized.begin() != "assets") {
        exists = std::filesystem::exists(std::filesystem::path("assets") / sanitized, ec);
    }

    if (exists) {
        REXLOG_INFO("NewFile: {} [flags={:#x}]", cc, flags);
        ctx.r4.u64 = flags | 0x10000;
    } else {
        REXLOG_INFO("NewFile: {} (ARK) [flags={:#x}]", cc, flags);
    }

    __imp__NewFile(ctx, base);
}