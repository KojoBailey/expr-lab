module;

#include <format>
#include <print>
#include <variant>

export module tokenize;

import core;

using namespace core;

export {
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

	auto isDigit(Char chr) -> Bool
	{
		return chr >= '0' and chr <= '9';
	}

	auto parseDigit(Char chr) -> F64
	{
		return chr - '0';
	}

	auto parseNumber(StringView string) -> Pair<F64, USize>
	{
		F64 result = 0;
		USize i;
		for (i = 0; i < string.size(); ++i) {
			Char currentChar = string[i];
			if (isDigit(currentChar)) {
				result *= 10;
				result += parseDigit(currentChar);
			} else break;
		}

		return Pair(result, ++i);
	}

	auto tokenize(StringView rawInput) -> Result<Vector<Token>>
	{
		Vector<Token> result;

		for (USize i = 0; i < rawInput.size(); ++i) {
			const Char currentChar = rawInput[i];

			switch (currentChar) {
			case ' ':
				continue;
			case '+':
				result.emplace_back(Operator{OperatorType::Plus});
				break;
			default:
				if (isDigit(currentChar)) {
					auto [number, length] = parseNumber(rawInput.substr(i));
					result.emplace_back(Number{number});
					i += length - 1;
				}
			}
		}

		return result;
	}
}
