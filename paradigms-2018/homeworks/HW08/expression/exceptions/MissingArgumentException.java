package expression.exceptions;

public class MissingArgumentException extends ParsingException {
    public MissingArgumentException(String msg, int ind) {
        super("Missing " + msg + " argument at " + ind);
    }
}
