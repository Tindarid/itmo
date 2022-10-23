package expression.exceptions;

public class ParsingException extends ExpressionException {
    public ParsingException(String msg) {
        super("Parsing error. " + msg);
    }
}
