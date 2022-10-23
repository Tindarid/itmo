package expression.exceptions;

public class TooBigConstException extends ParsingException {
    public TooBigConstException(int ind) {
        super("Not an integer at " + ind);
    }
}
