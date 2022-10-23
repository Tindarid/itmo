package expression.parser;

import expression.TripleExpression;
import expression.exceptions.ExpressionException;
import expression.type.Type;

public interface Parser<T extends Number> {
    TripleExpression<T> parse(String expression, Type<T> parseType) throws ExpressionException;
}
