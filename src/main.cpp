import core;

import tokenize;
import parse;

#include <print>
#include <variant>

using namespace core;

auto evaluate(const Node& ast) -> Result<F64>
{
	if (std::holds_alternative<BinaryOperation>(ast.variant)) {
		auto& binaryOperation = std::get<BinaryOperation>(ast.variant);
		if (binaryOperation.type == BinaryOperationType::Addition) {
			return std::get<Number>(binaryOperation.left->variant).value
				+ std::get<Number>(binaryOperation.right->variant).value;
		} else {
			return Error{"Invalid"};
		}
	}
	return Error{"Invalid"};
}

auto main() -> CInt
{
	Result<Vector<Token>> maybeTokens = tokenize("21 + 3");
	if (not maybeTokens.has_value()) {
		std::println("Tokenize Error: {}", maybeTokens.error());
	}
	Vector<Token> tokens = std::move(*maybeTokens);

	std::println("[");
	for (const auto& token : tokens) {
		std::println("\t{},", token);
	}
	std::println("]");

	Result<Node> maybeAst = parse(tokens);
	if (not maybeAst.has_value()) {
		std::println("AST Error: {}", maybeAst.error());
	}
	Node ast = std::move(*maybeAst);

	Result<F64> maybeResult = evaluate(ast);
	if (not maybeResult.has_value()) {
		std::println("Evaluation Error: {}", maybeResult.error());
	}
	F64 result = std::move(*maybeResult);

	std::println("Result: {}", result);
}
