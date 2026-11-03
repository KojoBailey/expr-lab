module;

#include <bit>
#include <cstddef>
#include <cstring>
#include <concepts>
#include <exception>
#include <expected>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <variant>

export module core;

export namespace core {
	using Nothing = void;

	using Byte = std::byte;
	using Char = char;
	using USize = std::size_t;
	using CInt = int;
	using Bool = bool;
	using F32 = float;
	using F64 = double;

	using String = std::string;
	using StringView = std::string_view;
	using Path = std::filesystem::path;

	template<typename A, typename B>
	using Pair = std::pair<A, B>;

	template<typename... As>
	using Variant = std::variant<As...>;

	template<typename A>
	using Maybe = std::optional<A>;

	template<typename V>
	using Result = std::expected<V, String>;

	template<typename T>
	using Error = std::unexpected<T>;

	using Exception = std::exception;

	template<typename A>
	using Vector = std::vector<A>;

	template<typename A>
	using Span = std::span<A>;

	template<typename Key, typename Value>
	using Map = std::map<Key, Value>;

	template<typename Key, typename Value>
	using HashMap = std::unordered_map<Key, Value>;

	using IFStream = std::ifstream;
	using OFStream = std::ofstream;

	using Endian = std::endian;

	template<typename A>
	concept Integral = std::integral<A>;
}
