#pragma once

#include <fstream>
#include <list>
#include <stdexcept>
#include <string>

namespace io {
	class BaseReader {
	public:
		BaseReader(const std::string& file);
		~BaseReader();

	protected:
		using Content = std::list< std::string >;

	protected:
		Content ReadRaw() const;

	private:
		mutable std::ifstream stream_;
	};
}