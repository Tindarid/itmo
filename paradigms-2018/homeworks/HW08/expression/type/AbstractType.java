package expression.type;

import expression.exceptions.EvaluationException;

public abstract class AbstractType<T extends Number> implements Type<T> {
    protected T value;

    public Type<T> parse(int a) {
        return parseImpl(a);
    }

    public Type<T> parse(String expr) {
        return parseImpl(expr);
    }

    protected abstract Type<T> parseImpl(String expr);
    protected abstract Type<T> parseImpl(int a);

    public T value() {
        return value;
    }

    public Type<T> add(Type<T> a) throws EvaluationException {
        return valueOf(addImpl(a.value()));
    }

    public Type<T> sub(Type<T> a) throws EvaluationException {
        return valueOf(subImpl(a.value()));
    }

    public Type<T> div(Type<T> a) throws EvaluationException {
        return valueOf(divImpl(a.value()));
    }

    public Type<T> mul(Type<T> a) throws EvaluationException {
        return valueOf(mulImpl(a.value()));
    }

    public Type<T> neg() throws EvaluationException {
        return valueOf(negImpl());
    }

    protected abstract T addImpl(T a) throws EvaluationException;
    protected abstract T subImpl(T a) throws EvaluationException;
    protected abstract T divImpl(T a) throws EvaluationException;
    protected abstract T mulImpl(T a) throws EvaluationException;
    protected abstract T negImpl() throws EvaluationException;
    protected abstract Type<T> valueOf(T a) throws EvaluationException;
}
