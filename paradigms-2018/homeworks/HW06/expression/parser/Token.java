package expression.parser;

public class Token {
    public enum Type {
        PLUS, MINUS, LB, RB, NUMBER, DIV, MUL, END, VAR, XOR, OR, AND
    }

    public String value;
    public Type type;

    Token(String v, Type t) {
        value = v;
        type = t;
    }
}
