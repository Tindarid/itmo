package expression.exceptions;

public class IncorrectVariableException extends ParsingException {
    public IncorrectVariableException(String msg, int ind) {
        super("Incorrect variable " + msg + " at " + ind);
    }
}
