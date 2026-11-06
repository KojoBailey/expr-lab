module;

#include <memory>
#include <variant>

export module parse;

import core;

import tokenize;

using namespace core;

export {
	enum BinaryOperationType {
		Addition,
	};

	class Node;

	struct BinaryOperation {
		BinaryOperationType type;
		UniquePtr<Node> left;
		UniquePtr<Node> right;
	};

	class Node {
	public:
		Variant<BinaryOperation, Number> variant;
	};

	auto parse(Span<Token> tokens) -> Result<Node>
	{
		if (std::holds_alternative<Operator>(tokens[1].variant)) {
			OperatorType operatorType = std::get<Operator>(tokens[1].variant).type;
			if (operatorType == OperatorType::Plus) {
				return Node{BinaryOperation{
					.type = BinaryOperationType::Addition,
					.left = std::make_unique<Node>(Number{
						std::get<Number>(tokens[0].variant).value
					}),
					.right = std::make_unique<Node>(Number{
						std::get<Number>(tokens[2].variant).value
					}),
				}};
			}
		}
		
		return Error{"Invalid"};
	}
}
