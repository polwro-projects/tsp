#pragma once

namespace io::file {
class IParser {
public:
	virtual bool Process() = 0;
};
} // namespace io::file