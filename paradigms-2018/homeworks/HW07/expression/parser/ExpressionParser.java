package expression.parser;

import expression.*;
import expression.parser.token.*;
import expression.exceptions.*;

public class ExpressionParser implements Parser {
    private Tokenizer tokens;

    public CommonExpression parse(String expression) throws ExpressionException {
        tokens = new Tokenizer(expression);
        return expr(false);
    }

    //expr
    private CommonExpression expr(boolean lbOpen) throws ExpressionException {
        CommonExpression temp = sum();
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
    private CommonExpression sum() throws ExpressionException {
        CommonExpression temp = term();
        while (tokens.hasNext()) {
            Token token = tokens.next();
            switch(token.type) {
                case MINUS:
                    temp = new CheckedSubtract(temp, term());
                    break;
                case PLUS:
                    temp = new CheckedAdd(temp, term());
                    break;
                default:
                    tokens.prev();
                    return temp;
            }
        }
        return temp;
    }

    //mul or div
    private CommonExpression term() throws ExpressionException {
        CommonExpression temp = prim();
        while (tokens.hasNext()) {
            Token token = tokens.next();
            switch(token.type) {
                case MUL:
                    temp = new CheckedMultiply(temp, prim());
                    break;
                case DIV:
                    temp = new CheckedDivide(temp, prim());
                    break;
                default:
                    tokens.prev();
                    return temp;
            }
        }
        return temp;
    }

    //primary
    private CommonExpression prim() throws ExpressionException {
        Token token = tokens.next();
        switch(token.type) {
            case LOG10:
                Token l = tokens.next();
                if (l.type == Token.Type.LB) {
                    return new CheckedLog10(expr(true));
                } else {
                    tokens.prev();
                    return new CheckedLog10(prim());
                }
            case POW10:
                Token po = tokens.next();
                if (po.type == Token.Type.LB) {
                    return new CheckedPow10(expr(true));
                } else {
                    tokens.prev();
                    return new CheckedPow10(prim());
                }
            case NUMBER:
                try {
                    return new Const(Integer.parseInt(token.value));
                } catch (NumberFormatException e) {
                    throw new OverflowException("overflow");
                }
            case VAR: 
                if (!token.value.equals("x") && !token.value.equals("y") && !token.value.equals("z")) {
                    throw new IncorrectVariableException(token.value, token.pos);
                }
                return new Variable(token.value);
            case MINUS: 
                if (tokens.hasNext()) {
                    Token temp = tokens.next();
                    if (temp.type == Token.Type.NUMBER) {
                        try {
                            return new Const(Integer.parseInt("-" + temp.value));
                        } catch (NumberFormatException e) {
                            throw new OverflowException("overflow");
                        }
                    } else {
                        tokens.prev();
                    }
                } 
                return new CheckedNegate(prim());
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
