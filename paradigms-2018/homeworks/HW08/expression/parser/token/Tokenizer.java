package expression.parser.token;

import java.util.ArrayList;
import java.util.List;
import expression.exceptions.IncorrectSymbolException;

public class Tokenizer {
    private List<Token> tokens;
    private String expr;
    private int length;
    private int cur = 0;

    public Tokenizer(String expression) throws IncorrectSymbolException {
        tokens = new ArrayList<>();
        expr = expression;
        length = expr.length();
        tokens.add(new Token("", Token.Type.START, 0));
        tokenize();
        tokens.add(new Token("", Token.Type.END, length + 1));
    }

    public boolean hasNext() {
        return (cur + 1 < tokens.size());
    }

    public Token next() {
        return tokens.get(++cur);
    }

    public Token prev() {
        return tokens.get(--cur);
    }

    private int parseInt(int j) {
        while (j < length && Character.isDigit(expr.charAt(j))) {
            j++;
        }
        return j - 1;
    }

    private int parseStr(int j) {
        while (j < length && Character.isLetter(expr.charAt(j))) {
            j++;
        }
        return j - 1;
    }

    private void tokenize() throws IncorrectSymbolException {
        for (int i = 0; i < length; i++) {
            char c = expr.charAt(i);
            if (Character.isWhitespace(c)) {
                continue;
            }
            switch(c) {
                case '*':
                    tokens.add(new Token("*", Token.Type.MUL, i + 1));
                    break;
                case '/':
                    tokens.add(new Token("/", Token.Type.DIV, i + 1));
                    break;
                case '+':
                    tokens.add(new Token("+", Token.Type.PLUS, i + 1));
                    break;
                case '-':
                    tokens.add(new Token("-", Token.Type.MINUS, i + 1));
                    break;
                case '(':
                    tokens.add(new Token("(", Token.Type.LB, i + 1));
                    break;
                case ')':
                    tokens.add(new Token(")", Token.Type.RB, i + 1));
                    break;
                default:
                    if (Character.isDigit(c)) {
                        int j = parseInt(i);
                        tokens.add(new Token(expr.substring(i, j + 1), Token.Type.NUMBER, i));
                        i = j;
                    } else if (Character.isLetter(c)) {
                        int j = parseStr(i);
                        tokens.add(new Token(expr.substring(i, j + 1), Token.Type.VAR, i));
                        i = j;
                    } else {
                        throw new IncorrectSymbolException(i + 1);
                    }
                    break;
            }
        }
    }
}
