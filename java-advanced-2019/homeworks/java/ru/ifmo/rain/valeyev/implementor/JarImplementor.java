package ru.ifmo.rain.valeyev.implementor;

import info.kgeorgiy.java.advanced.implementor.JarImpler;
import info.kgeorgiy.java.advanced.implementor.ImplerException;

import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.io.IOException;
import java.io.File;
import javax.tools.JavaCompiler;
import javax.tools.ToolProvider;
import java.util.zip.ZipEntry;
import java.util.jar.Manifest;
import java.util.jar.Attributes;
import java.util.jar.JarOutputStream;
import java.net.URISyntaxException;
import java.security.CodeSource;

/**
 * Generates Java code for specified class, compiles it and packs in jar
 */
public class JarImplementor extends Implementor implements JarImpler {
    /**
     * Creates jar of class
     * @param token class, which jar file is needed
     * @param root source files folder
     * @param jarFile destination jar
     * @throws ImplerException if IO Error occured during creating
     */
    private void createJar(Class<?> token, Path root, Path jarFile) throws ImplerException {
        Manifest manifest = new Manifest();
        Attributes attributes = manifest.getMainAttributes();
        attributes.put(Attributes.Name.MANIFEST_VERSION, "1.0");
        attributes.put(Attributes.Name.IMPLEMENTATION_VENDOR, "Jar Implementor");
        try (JarOutputStream writer = new JarOutputStream(Files.newOutputStream(jarFile), manifest)) {
            writer.putNextEntry(new ZipEntry(token.getCanonicalName().replace('.', File.separatorChar) + "Impl.class"));
            Files.copy(resolvePath(token, root, "class"), writer);
        } catch (IOException e) {
            throw new ImplerException("Error while writing jar file:" + e.getMessage());
        }
    }

    /**
     * Gets class path of specified class
     * @param token - class, which class path is needed
     * @throws ImplerException if class path cannot be resolved
     * @return specified class path of class
     */
    private static String getClassPath(Class<?> token) throws ImplerException {
        try {
            CodeSource source = token.getProtectionDomain().getCodeSource();
            if (source == null) {
                return ".";
            }
            return Path.of(source.getLocation().toURI()).toString();
        } catch (final URISyntaxException e) {
            throw new ImplerException("Cannot resolve classpath" + e.getMessage());
        }
    }

    /**
     * Compiles file using specified classpath
     * @param classPath path to class folder
     * @param filename path of file to compile
     * @throws ImplerException if no compiler found or compiler exits with code not equal to 0
     */
    private void compile(String classPath, String filename) throws ImplerException {
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        if (compiler == null) {
            throw new ImplerException("Could not find java compiler");
        }
        String[] args = {"-cp", classPath, filename};
        if (compiler.run(null, null, null, args) != 0) {
            throw new ImplerException("Could not compile generated files");
        }
    }

    /**
     * Implements jar of class name, creates temp directory, compiles files and then cleans temp directory
     * @param token class to implement
     * @param jarFile path of destination jar
     * @throws ImplerException if some kind of error occured during implementing
     */
    public void implementJar(Class<?> token, Path jarFile) throws ImplerException {
        if (token == null || jarFile == null) {
            throw new ImplerException("Null arguments passed to implementJar");
        }
        try {
            Files.createDirectories(jarFile.getParent());
        } catch (IOException e) {
            throw new ImplerException("Cannot create directory for jar file" + e.getMessage());
        }
        Path temp;
        try {
            temp = Files.createTempDirectory(jarFile.toAbsolutePath().getParent(), "temp");
        } catch (IOException e) {
            throw new ImplerException("Cannot create temp directory" + e.getMessage());
        }
        try {
            implement(token, temp);
            Path generatedFile = resolvePath(token, temp, "java");
            compile(getClassPath(token), generatedFile.toString());
            createJar(token, temp, jarFile);
        } finally {
            try {
                Files.walkFileTree(temp, new SimpleFileVisitor<Path>() {
                    public FileVisitResult visitFile(Path file, BasicFileAttributes attrs)
                        throws IOException
                    {
                        Files.delete(file);
                        return FileVisitResult.CONTINUE;
                    }

                    public FileVisitResult postVisitDirectory(Path dir, IOException e) 
                        throws IOException 
                    {
                        Files.delete(dir);
                        return FileVisitResult.CONTINUE;
                    }
                });
            } catch (IOException e) {
                System.out.println("Cannot delete temp directory");
            }
        }
    }

    /**
     * Main method
     * <p>
     * First argument should be <tt>-class<tt> or <tt>-jar<tt>
     * <p>
     * Second argument must be classname
     * <p>
     * Third argument in case of "-jar" option should be name of jar file to generate
     * @param args arguments
     */
    public static void main(String[] args) {
        if (args == null || !(args.length == 2 || args.length == 3)) {
            printUsage();
            return;
        }
        for (String arg : args) {
            if (arg == null) {
                System.out.println("Passed null parameters");
                return;
            }
        }
        try {
            String key = args[0];
            JarImpler implementor = new JarImplementor();
            if ("-class".equals(key) && args.length == 2) {
                implementor.implement(Class.forName(args[1]), Paths.get("."));
            } else if ("-jar".equals(key) && args.length == 3) {
                implementor.implementJar(Class.forName(args[1]), Paths.get(".").resolve(args[2]));
            } else {
                printUsage();
            }
        } catch (ClassNotFoundException e) {
            System.out.println("Cannot locate your class");
        } catch (InvalidPathException e) {
            System.out.println("Invalid path");
        } catch (ImplerException e) {
            System.out.println(e.getMessage());
        }
    }

    /**
     * Prints usage of JarImplementor via {@link System.out}
     */
    public static void printUsage() {
        System.out.println("Usage:");
        System.out.println("java Implementor -class [class or interface to implement]");
        System.out.println("or");
        System.out.println("java Implementor -jar [class or interface to implement] [name of jar file]");
    }
}
