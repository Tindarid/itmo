package expression.parser;

import expression.TripleExpression;
import expression.exceptions.ExpressionException;

public interface Parser {
    TripleExpression parse(String expression) throws ExpressionException;
}
