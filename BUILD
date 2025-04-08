load("@rules_apple//apple:macos.bzl", "macos_application")
load("@rules_apple//apple:versioning.bzl", "apple_bundle_version")
load("@rules_cc//cc:defs.bzl", "cc_binary")

apple_bundle_version(
    name = "SnakeVersion",
    build_version = "1.0.0",
)

macos_application(
    name = "mac-app",
    app_icons = glob(["Icon.xcassets/**"]),
    bundle_id = "com.danyloshevchenko.snake",
    infoplists = [":Info.plist"],
    minimum_os_version = "10.13",
    version = ":SnakeVersion",
    deps = [":libAppBundleSnake"],
)

cc_library(
    name = "libAppBundleSnake",
    srcs = glob([
        "snake/**/*.cc",
        "snake/**/*.h",
    ]),
    data = glob(["assets/**"]),
    includes = [
        "third_party/SDL/include",
        "third_party/SDL_image/include",
        "third_party/SDL_ttf/include",
    ],
    local_defines = ["MACOS_APP_BUNDLE"],
    deps = [
        "//third_party:SDL3",
        "//third_party:SDL3_image",
        "//third_party:SDL3_ttf",
        "//third_party:entt",
        "//third_party:spdlog",
    ],
)

cc_binary(
    name = "snake",
    srcs = glob([
        "snake/**/*.cc",
        "snake/**/*.h",
    ]),
    data = glob(["assets/**"]),
    includes = [
        "third_party/SDL/include",
        "third_party/SDL_image/include",
        "third_party/SDL_ttf/include",
    ],
    deps = [
        "//third_party:SDL3",
        "//third_party:SDL3_image",
        "//third_party:SDL3_ttf",
        "//third_party:entt",
        "//third_party:spdlog",
    ],
)
