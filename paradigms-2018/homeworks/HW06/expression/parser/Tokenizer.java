package expression.parser;

import java.util.ArrayList;
import java.util.List;

public class Tokenizer {
    private List<Token> tokens;
    private String expr;
    int length;
    private int cur;
    private boolean isGood;

    Tokenizer(String expression) {
        tokens = new ArrayList<>();
        cur = -1;
        expr = expression;
        length = expr.length();
        isGood = tokenize();
        tokens.add(new Token("", Token.Type.END));
    }

    public boolean good() {
        return isGood;
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

    private boolean tokenize() {
        for (int i = 0; i < length; i++) {
            char c = expr.charAt(i);
            if (Character.isWhitespace(c)) {
                continue;
            }
            switch(c) {
                case '^':
                    tokens.add(new Token("^", Token.Type.XOR));
                    break;
                case '&':
                    tokens.add(new Token("&", Token.Type.AND));
                    break;
                case '|':
                    tokens.add(new Token("|", Token.Type.OR));
                    break;
                case '*':
                    tokens.add(new Token("*", Token.Type.MUL));
                    break;
                case '/':
                    tokens.add(new Token("/", Token.Type.DIV));
                    break;
                case '+':
                    tokens.add(new Token("+", Token.Type.PLUS));
                    break;
                case '-':
                    tokens.add(new Token("-", Token.Type.MINUS));
                    break;
                case '(':
                    tokens.add(new Token("(", Token.Type.LB));
                    break;
                case ')':
                    tokens.add(new Token(")", Token.Type.RB));
                    break;
                default:
                    if (Character.isDigit(c)) {
                        int j = parseInt(i);
                        tokens.add(new Token(expr.substring(i, j + 1), Token.Type.NUMBER));
                        i = j;
                    } else {
                        int j = parseStr(i);
                        tokens.add(new Token(expr.substring(i, j + 1), Token.Type.VAR));
                        i = j;
                    }
                    break;
            }
        }
        return true;
    }
}
