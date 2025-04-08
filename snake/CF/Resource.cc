//
// Created by Danylo Shevchenko on 07.04.25.
//
#include <string>
#include "String.h"

namespace CF::Resource {
const auto kFilePrefixLength = std::string("file://").length();

std::string CopyURL(const std::string& path) {
  const auto c_path = path.c_str();
  const auto resource_url = CFBundleCopyResourceURL(
      CFBundleGetMainBundle(),
      CFStringCreateWithCString(nullptr, c_path, kCFStringEncodingMacRoman),
      nullptr, nullptr);
  const auto str = String::CopyCPPString(CFURLGetString(resource_url));
  return str.substr(kFilePrefixLength);
}
}  // namespace CF::Resource
