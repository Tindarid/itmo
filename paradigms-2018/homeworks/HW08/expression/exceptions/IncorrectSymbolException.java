package expression.exceptions;

public class IncorrectSymbolException extends ParsingException {
    public IncorrectSymbolException(int ind) {
        super("Incorrect symbol at " + ind);
    }
}
