import core;

#include <format>
#include <print>
#include <variant>

using namespace core;

struct Number {
	F64 value;
};

enum class OperatorType {
	Plus,
	Minus,
	Asterisk,
	ForwardSlash,
	ParenOpen,
	ParenClose,
	Comma,
};

struct Operator {
	OperatorType type;
};

struct Token {
	Variant<Number, Operator> variant;
};

template <>
struct std::formatter<Number> : std::formatter<String> {
	auto format(const Number& obj, std::format_context& ctx) const {
		return std::formatter<String>::format(std::format("{}", obj.value), ctx);
	}
};

template <>
struct std::formatter<Operator> : std::formatter<String> {
	auto format(const Operator& obj, std::format_context& ctx) const {
		String str = "";
		switch (obj.type) {
		case OperatorType::Plus:
			str = "Plus";
			break;
		default:
			str = "Unknown Operator";
		}
		return std::formatter<String>::format(str, ctx);
	}
};

template <>
struct std::formatter<Token> : std::formatter<String> {
	auto format(const Token& obj, std::format_context& ctx) const {
		String str = "";
		if (std::holds_alternative<Number>(obj.variant)) {
			auto number = std::get<Number>(obj.variant);
			str = std::format("Number( {} )", number);
		}
		if (std::holds_alternative<Operator>(obj.variant)) {
			auto op = std::get<Operator>(obj.variant);
			str = std::format("Operator( {} )", op);
		}

		return std::formatter<String>::format(str, ctx);
	}
};

auto tokenize(StringView rawInput) -> Result<Vector<Token>>
{
	Vector<Token> result;

	result.emplace_back(Number{5});
	result.emplace_back(Operator{OperatorType::Plus});
	result.emplace_back(Number{3});

	return result;
}

auto main() -> CInt
{
	Result<Vector<Token>> tokenResult = tokenize("5 + 3");
	if (not tokenResult.has_value()) {
		std::println("Tokenize Error: {}", tokenResult.error());
	}
	Vector<Token> tokens = std::move(*tokenResult);

	std::println("[");
	for (const auto& token : tokens) {
		std::println("\t{},", token);
	}
	std::println("]");
	// print the tokens
}
