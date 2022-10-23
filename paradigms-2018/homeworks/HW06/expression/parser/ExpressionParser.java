package expression.parser;

import expression.*;

public class ExpressionParser implements Parser {
    private Tokenizer tokens;
    int isOpen;

    public CommonExpression parse(String expression) {
        tokens = new Tokenizer(expression);
        if (tokens.good()) {
            return expr();
        } else {
            return null;
        }
    }

    //expr
    private CommonExpression expr() {
        CommonExpression temp = or();
        if (tokens.hasNext()) {
            Token token = tokens.next();
            switch(token.type) {
                case END:
                    if (isOpen > 0) {
                        System.out.println("Incorrect input");
                    } 
                    break;
                case RB:
                    if (isOpen > 0) {
                        isOpen--;
                    } else {
                        System.out.println("Incorrect input");
                    }
                    break;
                case LB:
                default:
                    System.out.println("Incorrect input");
                    break;
            }
        }
        return temp;
    }

    //or
    private CommonExpression or() {
        CommonExpression temp = xor();
        while (tokens.hasNext()) {
            Token token = tokens.next();
            switch(token.type) {
                case OR:
                    temp = new Or(temp, xor());
                    break;
                default:
                    tokens.prev();
                    return temp;
            }
        }
        return temp;
    }
    //xor
    private CommonExpression xor() {
        CommonExpression temp = and();
        while (tokens.hasNext()) {
            Token token = tokens.next();
            switch(token.type) {
                case XOR:
                    temp = new Xor(temp, and());
                    break;
                default:
                    tokens.prev();
                    return temp;
            }
        }
        return temp;
    }
    //and
    private CommonExpression and() {
        CommonExpression temp = sum();
        while (tokens.hasNext()) {
            Token token = tokens.next();
            switch(token.type) {
                case AND:
                    temp = new And(temp, sum());
                    break;
                default:
                    tokens.prev();
                    return temp;
            }
        }
        return temp;
    }
    //sum
    private CommonExpression sum() {
        CommonExpression temp = term();
        while (tokens.hasNext()) {
            Token token = tokens.next();
            switch(token.type) {
                case MINUS:
                    temp = new Subtract(temp, term());
                    break;
                case PLUS:
                    temp = new Add(temp, term());
                    break;
                default:
                    tokens.prev();
                    return temp;
            }
        }
        return temp;
    }

    //mul
    private CommonExpression term() {
        CommonExpression temp = prim();
        while (tokens.hasNext()) {
            Token token = tokens.next();
            switch(token.type) {
                case MUL:
                    temp = new Multiply(temp, prim());
                    break;
                case DIV:
                    temp = new Divide(temp, prim());
                    break;
                default:
                    tokens.prev();
                    return temp;
            }
        }
        return temp;
    }

    //pervi
    private CommonExpression prim() {
        Token token = tokens.next();
        switch(token.type) {
            case NUMBER:
                return new Const(Integer.parseInt(token.value));
            case VAR:
                return new Variable(token.value);
            case MINUS:
                if (tokens.hasNext()) {
                    Token temp = tokens.next();
                    if (temp.type == Token.Type.NUMBER) {
                        return new Const(Integer.parseInt("-" + temp.value));
                    } else {
                        tokens.prev();
                    }
                } 
                return new Negate(prim());
            case LB:
                isOpen++;
                return expr();
            case RB:
            case END:
            default:
                return null;
        }
    }
}
