#pragma once

#include <regex>

namespace io::file::ini {
const std::regex kSectionHeaderPattern("\\[([a-zA-Z0-9]{1,25})\\]");
}