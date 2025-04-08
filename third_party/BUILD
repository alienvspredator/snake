load("@rules_cc//cc:defs.bzl", "cc_import", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "entt",
    hdrs = glob([
        "entt/src/**/*.hpp",
        "entt/src/**/*.h",
    ]),
    strip_include_prefix = "entt/src",
)

cc_import(
    name = "SDL3",
    hdrs = glob(["SDL/include/**/*.h"]),
    includes = ["SDL/include"],
    shared_library = "SDL/lib/libSDL3.dylib",
    system_provided = False,
)

cc_import(
    name = "SDL3_image",
    hdrs = glob(["SDL_image/include/**/*.h"]),
    includes = ["SDL_image/include"],
    shared_library = "SDL_image/lib/libSDL3_image.0.dylib",
    system_provided = False,
)

cc_import(
    name = "SDL3_ttf",
    hdrs = glob(["SDL_ttf/include/**/*.h"]),
    includes = ["SDL_ttf/include"],
    shared_library = "SDL_ttf/lib/libSDL3_ttf.0.dylib",
    system_provided = False,
)

cc_library(
    name = "spdlog",
    hdrs = glob(["spdlog/include/spdlog/**/*.h"]),
    strip_include_prefix = "spdlog/include",
)
