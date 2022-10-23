package expression.parser.token;

public class Token {
    public enum Type {
        START, PLUS, MINUS, LB, RB, NUMBER, DIV, MUL, END, VAR, LOG10, POW10
    }

    public String value;
    public Type type;
    public int pos;

    Token(String v, Type t, int p) {
        value = v;
        type = t;
        pos = p;
    }
}
