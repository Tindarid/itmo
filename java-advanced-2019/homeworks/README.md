# Homeworks
[Скрипт для запуска тестов](scripts/hw_test.sh)

## HW1
Тема: `Input and Output`

Класс [RecursiveWalk](java/ru/ifmo/rain/valeyev/walk/RecursiveWalk.java), осуществляющий подсчет хеш-сумм файлов в директориях.

Формат запуска: `java RecursiveWalk <входной файл> <выходной файл>`

Формат строки в выходном файле: `<шестнадцатеричная хеш-сумма> <путь к файлу>`

Используется алгоритм [FNV](https://ru.wikipedia.org/wiki/FNV.html).

Кодировка входного и выходного файлов — UTF-8.

## HW2 (Collections Framework)
Тема: `Collections Framework`

Класс [ArraySet](java/ru/ifmo/rain/valeyev/arrayset/ArraySet.java), реализующий неизменяемое упорядоченное множество (интерфейс [NavigableSet](https://docs.oracle.com/en/java/javase/11/docs/api/java.base/java/util/NavigableSet.html)).

Все операции над множествами производятся с максимально возможной асимптотической эффективностью.

## HW3
Тема: `Streams and Lambda expressions`

Класс [StudentDB](java/ru/ifmo/rain/valeyev/student/StudentDB.java), осуществляющий поиск по базе студентов (реализует интерфейс [StudentGroupQuery](../modules/info.kgeorgiy.java.advanced.student/info/kgeorgiy/java/advanced/student/StudentGroupQuery.java)).

Каждый метод состоит из одного оператора.

## HW4
Тема: `Java Reflection`

Класс [Implementor](java/ru/ifmo/rain/valeyev/implementor/Implementor.java), который генерирует реализации классов и интерфейсов (реализует интерфейс [Impler](../modules/info.kgeorgiy.java.advanced.implementor/info/kgeorgiy/java/advanced/implementor/Impler.java)).

Формат запуска: `java Implementor <class to implement>`

В результате работы будет сгенерирован Java-код класса с суффиксом "Impl", расширяющий (реализующий) указанный класс (интерфейс).

Методы сгенерированного класса игнорируют свои аргументы и возвращают значения по умолчанию.

## HW5
Тема: `Jar`

Класс [JarImplementor](java/ru/ifmo/rain/valeyev/implementor/JarImplementor.java), который генерирует реализации классов и интерфейсов, а также может запаковать реализацию в .jar файл (реализует интерфейс [JarImpler](../modules/info.kgeorgiy.java.advanced.implementor/info/kgeorgiy/java/advanced/implementor/JarImpler.java)).

* Формат запуска №1: `java JarImplementor -class <class to implement>`
  * В результате работы будет сгенерирован Java-код класса с суффиксом "Impl", расширяющий (реализующий) указанный класс (интерфейс).
  * Методы сгенерированного класса игнорируют свои аргументы и возвращают значения по умолчанию.
* Формат запуска №2: `java JarImplementor -jar <class to implement> <name of jar file>`
  * В результате работы будет сгенерирован Java-код класса с суффиксом "Impl", расширяющий (реализующий) указанный класс (интерфейс) и запакованный в указанный .jar файл.

[Модуляризованное решение](java-modules/ru.ifmo.rain.valeyev.implementor/)

[Скрипты для сборки и запуска(префикс "hw5")](scripts/)

## HW6
Тема: `Javadoc`

[Скрипт](scripts/hw6_javadoc.sh) для генерации документации класса [JarImplementor](java/ru/ifmo/rain/valeyev/implementor/JarImplementor.java)

## HW7
Тема: `Итеративный параллелизм`

Класс [IterativeParallelism](java/ru/ifmo/rain/valeyev/concurrent/IterativeParallelism.java), который обрабатывает списки в несколько потоков.

Реализованы следующие функции:

* `minimum(threads, list, comparator)` — первый минимум;
* `maximum(threads, list, comparator)` — первый максимум;
* `all(threads, list, predicate)` — проверка, что все элементы списка удовлетворяют предикату;
* `any(threads, list, predicate)` — проверка, что существует элемент списка, удовлетворяющий предикату.
* `filter(threads, list, predicate)` — вернуть список, содержащий элементы удовлетворяющие предикату;
* `map(threads, list, function)` — вернуть список, содержащий результаты применения функции;
* `join(threads, list)` — конкатенация строковых представлений элементов списка.

Во все функции передается параметр `threads` — сколько потоков надо использовать при вычислении.

## HW8
Тема: `Параллельный запуск`

Класс [ParallelMapperImpl](/java/ru/ifmo/rain/valeyev/mapper/ParallelMapperImpl), реализующий интерфейс [ParallelMapper](../modules/info.kgeorgiy.java.advanced.mapper/info/kgeorgiy/java/advanced/mapper/ParallelMapper.java);

Задания на исполнения накапливаются в очереди и обрабатываются по мере поступления.

К одному ParallelMapper могут одновременно обращаться несколько клиентов.

IterativeParallelism теперь может использовать ParallelMapper
