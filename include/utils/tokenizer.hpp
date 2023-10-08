#pragma once

#include <deque>
#include <string>

namespace utils {
	class Tokenizer {
	public:
		using Tokens = std::deque< std::string >;

	public:
		static Tokens tokenize(std::string line, char delimiter);
	};
}