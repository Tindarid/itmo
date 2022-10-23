package expression.exceptions;

public class ExpressionException extends Exception {
    public ExpressionException(String msg) {
        super("An error occured. " + msg);
    }
}
