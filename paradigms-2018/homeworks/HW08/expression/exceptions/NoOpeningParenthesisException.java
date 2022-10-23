package expression.exceptions;

public class NoOpeningParenthesisException extends ParsingException {
    public NoOpeningParenthesisException(int ind) {
        super("Missing left bracket at " + ind);
    }
}
