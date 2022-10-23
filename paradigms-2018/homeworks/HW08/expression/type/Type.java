package expression.type;

import expression.exceptions.EvaluationException;

public interface Type<T extends Number> {
    public T value();
    public Type<T> add(Type<T> a) throws EvaluationException;
    public Type<T> sub(Type<T> a) throws EvaluationException;
    public Type<T> div(Type<T> a) throws EvaluationException;
    public Type<T> mul(Type<T> a) throws EvaluationException;
    public Type<T> neg() throws EvaluationException;
    public Type<T> parse(String expr);
    public Type<T> parse(int a);
}
