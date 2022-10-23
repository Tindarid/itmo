package expression.exceptions;

public class NoClosingParenthesisException extends ParsingException {
    public NoClosingParenthesisException(int ind) {
        super("Missing right bracket at " + ind);
    }
}
