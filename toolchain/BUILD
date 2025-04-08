load("@rules_cc//cc:defs.bzl", "cc_toolchain")
load(":cc_toolchain_config.bzl", "cc_toolchain_config")

package(default_visibility = ["//visibility:public"])

filegroup(name = "empty")

cc_toolchain_config(name = "osx_arm_toolchain_config")

cc_toolchain(
    name = "osx_arm_toolchain",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
    toolchain_config = ":osx_arm_toolchain_config",
    toolchain_identifier = "osx_arm-toolchain",
)

toolchain(
    name = "cc_toolchain_for_osx_arm",
    exec_compatible_with = [
        "@platforms//cpu:arm",
        "@platforms//os:osx",
    ],
    target_compatible_with = [
        "@platforms//cpu:arm",
        "@platforms//os:osx",
    ],
    toolchain = ":osx_arm_toolchain",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
)
