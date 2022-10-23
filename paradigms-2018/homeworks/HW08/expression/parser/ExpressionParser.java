package expression.parser;

import expression.*;
import expression.parser.token.*;
import expression.exceptions.*;
import expression.type.*;
import java.math.BigInteger;

public class ExpressionParser<T extends Number> implements Parser<T> {
    private Tokenizer tokens;
    Type<T> parseType;
    String exprType;

    public Type<T> parseMode() {
        return parseType;
    }

    public TripleExpression<T> parse(String expression, Type<T> p) throws ExpressionException {
        tokens = new Tokenizer(expression);
        parseType = p;
        return expr(false);
    }

    //expr
    private TripleExpression<T> expr(boolean lbOpen) throws ExpressionException {
        TripleExpression<T> temp = sum();
        if (tokens.hasNext()) {
            Token token = tokens.next();
            switch(token.type) {
                case END:
                    if (lbOpen) {
                        throw new NoClosingParenthesisException(token.pos);
                    }
                    break;
                case RB: 
                    if (!lbOpen) {
                        throw new NoOpeningParenthesisException(token.pos);
                    }
                    break;
                default:
                    throw new ParsingException("");
            }
        }
        return temp;
    }

    //sum
    private TripleExpression<T> sum() throws ExpressionException {
        TripleExpression<T> temp = term();
        while (tokens.hasNext()) {
            Token token = tokens.next();
            switch(token.type) {
                case MINUS:
                    temp = new CheckedSubtract<T>(temp, term());
                    break;
                case PLUS:
                    temp = new CheckedAdd<T>(temp, term());
                    break;
                default:
                    tokens.prev();
                    return temp;
            }
        }
        return temp;
    }

    //mul or div
    private TripleExpression<T> term() throws ExpressionException {
        TripleExpression<T> temp = prim();
        while (tokens.hasNext()) {
            Token token = tokens.next();
            switch(token.type) {
                case MUL:
                    temp = new CheckedMultiply<T>(temp, prim());
                    break;
                case DIV:
                    temp = new CheckedDivide<T>(temp, prim());
                    break;
                default:
                    tokens.prev();
                    return temp;
            }
        }
        return temp;
    }

    //primary
    private TripleExpression<T> prim() throws ExpressionException {
        Token token = tokens.next();
        switch(token.type) {
            case NUMBER:
                try {
                    return new Const<T>(parseType.parse(token.value));
                } catch (NumberFormatException e) {
                    throw new OverflowException("overflow");
                }
            case VAR: 
                if (!token.value.equals("x") && !token.value.equals("y") && !token.value.equals("z")) {
                    throw new IncorrectVariableException(token.value, token.pos);
                }
                return new Variable<T>(token.value);
            case MINUS: 
                if (tokens.hasNext()) {
                    Token temp = tokens.next();
                    if (temp.type == Token.Type.NUMBER) {
                        try {
                            return new Const<T>(parseType.parse("-" + temp.value));
                        } catch (NumberFormatException e) {
                            throw new OverflowException("overflow");
                        }
                    } else {
                        tokens.prev();
                    }
                } 
                return new CheckedNegate<T>(prim());
            case LB: 
                return expr(true);
            case RB: 
            case END:
                throw new MissingArgumentException("last", token.pos);
            default:
                Token p = tokens.prev();
                if (p.type == Token.Type.START || p.type == Token.Type.LB) {
                    throw new MissingArgumentException("first", token.pos);
                } else {
                    throw new MissingArgumentException("middle", token.pos);
                }
        }
    }
}
