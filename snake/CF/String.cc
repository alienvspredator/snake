//
// Created by Danylo Shevchenko on 07.04.25.
//

#include "String.h"
#include <CoreFoundation/CoreFoundation.h>
#include <malloc/malloc.h>
#include <string>

namespace CF::String {
std::string CopyCPPString(const CFStringRef a_string) {
  const auto c_str = CopyUTF8String(a_string);
  const auto str = std::string(c_str);
  free(c_str);
  return str;
}

char* CopyUTF8String(const CFStringRef a_string) {
  if (a_string == nullptr) {
    return nullptr;
  }

  const CFIndex length = CFStringGetLength(a_string);
  const CFIndex max_size =
      CFStringGetMaximumSizeForEncoding(length,
                                        kCFStringEncodingUTF8) +
      1;  // + 1 for \0
  const auto buffer = static_cast<char*>(malloc(max_size));
  if (CFStringGetCString(a_string, buffer, max_size, kCFStringEncodingUTF8)) {
    return buffer;
  }
  free(buffer);
  return nullptr;
}

const char* GetUTF8String(const CFStringRef a_string, char** buffer) {
  if (a_string == nullptr) {
    return nullptr;
  }

  const char* cstr = CFStringGetCStringPtr(a_string, kCFStringEncodingUTF8);
  if (cstr == nullptr) {
    const CFIndex length = CFStringGetLength(a_string);
    const CFIndex max_size =
        CFStringGetMaximumSizeForEncoding(length,
                                          kCFStringEncodingUTF8) +
        1;  // +1 for \0
    if (max_size > malloc_size(buffer)) {
      *buffer = static_cast<char*>(realloc(*buffer, max_size));
    }
    if (CFStringGetCString(a_string, *buffer, max_size,
                           kCFStringEncodingUTF8)) {
      cstr = *buffer;
    }
  }
  return cstr;
}
}  // namespace CF::String
