package ru.ifmo.rain.valeyev.implementor;

import info.kgeorgiy.java.advanced.implementor.Impler;
import info.kgeorgiy.java.advanced.implementor.ImplerException;

import java.nio.file.*;
import java.io.*;
import java.lang.reflect.*;
import java.util.*;
import java.util.function.*;
import java.util.stream.*;

/**
 * Generates Java code for specified class
 */
public class Implementor implements Impler {
    /**
     * Parameter name
     */
    private static final String PARAMETER = " p";

    /**
     * Line separator specified to current OS
     */
    private static final String NEW_LINE = System.lineSeparator();

    /**
     * Defines start of block of code
     */
    private static final String BEGIN_BLOCK = " {" + NEW_LINE;

    /**
     * Defines end of block of code
     */
    private static final String END_BLOCK = "}" + NEW_LINE;

    /**
     * Defines end of line of code
     */
    private static final String END_LINE = ";" + NEW_LINE;

    /**
     * Default comma
     */
    private static final String COMMA = ",";

    /**
     * Default space
     */
    private static final String SPACE = " ";

    /**
     * Empty String
     */
    private static final String EMPTY = "";

    /**
     * TAB: 4 SPACES
     */
    private static final String TAB = "    ";

    /**
     * 2 TABS : 8 SPACES
     */
    private static final String TAB2 = TAB + TAB;

    /**
     * Default prefix that should not be printed
     */
    private static final String DEFAULT_PREFIX = "java.lang.";

    /**
     * Returns type without {@link DEFAULT_PREFIX} of type (if it has)
     * @param type to resolve
     * @return type or type without "java.lang" prefix
     */
    private String resolveType(String type) {
        if (type.startsWith(DEFAULT_PREFIX)) {
            type = type.substring(DEFAULT_PREFIX.length());
        }
        return type;
    }
    
    /**
     * Return name of generated class
     * @param token token of class, which generated name should be returned
     * @return token name with "Impl" suffix
     */
    private String getName(Class<?> token) {
        return token.getSimpleName() + "Impl";
    }

    /**
     * Return modifiers of executable without {@link java.lang.reflect.Modifier.TRANSIENT} and {@link java.lang.reflect.Modifier.ABSTRACT}
     * @param executable executable, which modifiers must be resolved
     * @return string of modifiers of executable without abstract or transient if has
     */
    private String resolveModifiers(Executable executable) {
        return Modifier.toString(executable.getModifiers() & ~Modifier.TRANSIENT & ~Modifier.ABSTRACT);
    }

    /**
     * Returns string, which consists of parameters (example: (SomeClass p1, SomeClass p2) or (p1, p2))
     * @param parameters array of type of parameters of executable
     * @param needType true if type is needed, false otherwise
     * @return string of parameters with type if needed
     */
    private String resolveParameters(Class<?>[] parameters, boolean needType) {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < parameters.length; ++i) {
            if (i != 0) {
                builder.append(COMMA + SPACE);
            }
            builder.append(needType ? resolveType(parameters[i].getCanonicalName()) : EMPTY);
            builder.append(PARAMETER).append(Integer.toString(i + 1));
        }
        return builder.toString();
    }

    /**
     * Return string of exceptions of executable
     * @param executable executable to resolve
     * @return string of exceptions which this executable throws
     */
    private String resolveExceptions(Executable executable) {
        StringBuilder builder = new StringBuilder();
        Class<?>[] exceptions = executable.getExceptionTypes();
        if (exceptions.length != 0) {
            builder.append(" throws ").append(
                    Arrays.stream(exceptions)
                    .map(Class::getCanonicalName)
                    .collect(Collectors.joining(COMMA + SPACE))
                );
        }
        return builder.toString();
    }

    /**
     * Return full signature of executable
     * @param executable executable to resolve
     * @param token token of class executable belongs to
     * @param parameters array of types of parameters of executable
     * @return signature of executable
     */
    private String resolveSignature(Executable executable, Class<?> token, Class<?>[] parameters) {
        StringBuilder builder = new StringBuilder();
        builder.append(resolveModifiers(executable)).append(SPACE);
        if (token == null) {
            Method method = (Method) executable;
            builder.append(resolveType(method.getReturnType().getCanonicalName()))
                .append(SPACE)
                .append(method.getName());
        } else {
            builder.append(getName(token));
        }
        builder.append("(")
            .append(resolveParameters(parameters, true))
            .append(")");
        return builder.toString();
    }

    /**
     * Return full body of method
     * @param method instance of {@link Method}, which body must be resolved
     * @return body with default return type
     */
    private String resolveBody(Method method) {
        Class<?> returnType = method.getReturnType();
        if (returnType.isPrimitive()) {
            String typeName = method.getReturnType().getSimpleName();
            if (typeName.equals("boolean")) {
                return " false";
            } else if (typeName.equals("void")) {
                return EMPTY;
            } else {
                return " 0";
            }
        } else {
            return " null";
        }
    }

    /**
     * Return full definition of executable
     * @param executable executable, that must be resolved
     * @param token name of class method belongs to
     * @return fully resolved string of executable
     */
    private String resolveExecutable(Executable executable, Class<?> token) {
        StringBuilder builder = new StringBuilder();
        Class<?>[] parameters = executable.getParameterTypes();
        builder.append(TAB)
            .append(resolveSignature(executable, token, parameters))
            .append(resolveExceptions(executable))
            .append(BEGIN_BLOCK);
        builder.append(TAB2);
        if (token == null) {
            builder.append("return")
                .append(resolveBody((Method) executable));
        } else {
            builder.append("super(")
                .append(resolveParameters(parameters, false))
                .append(")");
        }
        builder.append(END_LINE)
            .append(TAB)
            .append(END_BLOCK)
            .append(NEW_LINE);
        return builder.toString();
    }

    /**
     * Returns head of generated java class (if class is part of {@link java.lang} package is not printed)
     * @param token token of class, which head must be resolved
     * @return head with package and class definition
     */
    private String resolveHead(Class<?> token) {
        StringBuilder builder = new StringBuilder();
        String packageName = token.getPackageName();
        if (!packageName.isEmpty() && !packageName.startsWith("java")) {
            builder.append("package ")
                .append(packageName)
                .append(END_LINE)
                .append(NEW_LINE);
        }
        builder.append("public class ")
            .append(getName(token))
            .append(SPACE)
            .append(token.isInterface() ? "implements" : "extends")
            .append(SPACE)
            .append(token.getCanonicalName());
        return builder.toString();
    }


    /**
     * Class that encapsultes {@link Method} in it
     * <p>
     * True {@link hashCode} and {@link equals} methods
     */
    private class TrueMethod {
        private final Method method;
        private final String signature;

        public TrueMethod(Method method) {
            this.method = method;
            this.signature = resolveSignature(method, null, method.getParameterTypes());
        }

        /**
         * Returns inner method
         * @return method
         */
        public Method getMethod() {
            return method;
        }

        /**
         * Compares two TrueMethods, based on signature
         * @return boolean
         */
        public boolean equals(Object rhs) {
            if (rhs instanceof TrueMethod) {
                return signature.equals(((TrueMethod) rhs).signature);
            }
            return false;
        }

        /**
         * Returns hashcode of method (based on {@link String} signature)
         * @return hashcode
         */
        public int hashCode() {
            return signature.hashCode();
        }
    }

    /**
     * Adds methods to {@link Set} of TrueMethods
     * @param methods array of methods to add
     * @param collection destination set
     */
    private void addMethods(Method[] methods, Set<TrueMethod> collection) {
        Arrays.stream(methods)
            .filter(method -> Modifier.isAbstract(method.getModifiers()))
            .map(TrueMethod::new)
            .collect(Collectors.toCollection(() -> collection));
    }

    /**
     * Returns all methods of tree of superclasses of token
     * @param token token of class, which methods must be saved to set
     * @return {@link Set} of TrueMethods
     */
    private Set<TrueMethod> getMethods(Class<?> token) {
        Set<TrueMethod> methods = new HashSet<>();
        addMethods(token.getMethods(), methods);
        while (token != null) {
            addMethods(token.getDeclaredMethods(), methods);
            token = token.getSuperclass();
        }
        return methods;
    }

    /**
     * Checks if class can be implemented
     * @param token token of class
     * @param root path to class
     * @throws ImplerException if class cannot be implemented or root path is invalid
     */
    private void check(Class<?> token, Path root) throws ImplerException {
        if (token == null || root == null) {
            throw new ImplerException("Required not null arguments");
        }
        if (token.isPrimitive()) {
            throw new ImplerException("Cannot implement: is primitive");
        }
        if (token.isArray()) {
            throw new ImplerException("Cannot implement: is array");
        }
        if (token == Enum.class) {
            throw new ImplerException("Cannot implement: is enum");
        }
        if (Modifier.isFinal(token.getModifiers())) {
            throw new ImplerException("Cannot implement: is final class");
        }
        if (token.isInterface()) {
            return;
        }
        boolean onlyStaticMethods = true;
        for (Method method : token.getDeclaredMethods()) {
            onlyStaticMethods &= Modifier.isStatic(method.getModifiers());
        }
        boolean onlyPrivateConstructors = true;
        for (Constructor constructor : token.getDeclaredConstructors()) {
            onlyPrivateConstructors &= Modifier.isPrivate(constructor.getModifiers());
        }
        if (onlyStaticMethods && onlyPrivateConstructors) {
            throw new ImplerException("Cannot implement: is utility class");
        }
    }

    /**
     * Returns resolved path of generated stuff
     * @param token token of class
     * @param root path to class
     * @param suff {@link String} of suffix to add in the end
     * @return resolved path
     */
    protected Path resolvePath(Class<?> token, Path root, String suff) {
        return root.toAbsolutePath().resolve(token.getCanonicalName().replace(".", File.separator) + "Impl." + suff);
    }

    /**
     * Implements class and puts generated code to destination
     * @param token token of class
     * @param root path to class
     * @throws ImplerException if some kind of error occured during implementing
     */
    public void implement(Class<?> token, Path root) throws ImplerException {
        check(token, root);
        Path path = resolvePath(token, root, "java");
        try {
            Files.createDirectories(path.getParent());
            try (BufferedWriter writer = Files.newBufferedWriter(path)) {
                writer.write(resolveHead(token));
                writer.write(BEGIN_BLOCK);
                for (Constructor constructor : token.getDeclaredConstructors()) {
                    writer.write(resolveExecutable(constructor, token));
                }
                for (TrueMethod trueMethod : getMethods(token)) {
                    writer.write(resolveExecutable(trueMethod.getMethod(), null));
                }
                writer.write(END_BLOCK);
            } catch (IOException e) {
                throw new ImplerException(e.getMessage());
            }
        } catch (IOException e) {
            throw new ImplerException("Cannot create directories for package");
        }
    }

    /**
     * Main method, arguments should be only length of one (name of class to generate)
     * <br>
     * Usage: <tt>java Implementor [class or interface to implement]<tt>
     * @param args arguments (should be one - name of class to generate)
     */
    public static void main(String[] args) {
        if (args == null || args.length != 1) {
            System.out.println("Usage: java Implementor [class or interface to implement]");
        } else {
            try {
                (new Implementor()).implement(Class.forName(args[0]), Paths.get("."));
            } catch (ClassNotFoundException e) {
                System.out.println("Cannot locate your class");
            } catch (ImplerException e) {
                System.out.println(e.getMessage());
            }
        }
    }
}
