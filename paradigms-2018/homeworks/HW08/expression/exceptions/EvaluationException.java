package expression.exceptions;

public class EvaluationException extends ExpressionException {
    public EvaluationException(String msg) {
        super("Evaluation error. " + msg);
    }
}
