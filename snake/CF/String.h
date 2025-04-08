//
// Created by Danylo Shevchenko on 07.04.25.
//

#pragma once

#include <CoreFoundation/CoreFoundation.h>

#include <string>

namespace CF::String {
CF_IMPLICIT_BRIDGING_ENABLED
std::string CopyCPPString(CFStringRef a_string);
char* CopyUTF8String(CFStringRef a_string) CF_RETURNS_NOT_RETAINED;
const char* GetUTF8String(CFStringRef a_string, char** buffer);
CF_IMPLICIT_BRIDGING_DISABLED
}  // namespace CF::String
