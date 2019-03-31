/*
    How to Java:
    - install JDK (for javac)
    - set JAVA_HOME (F:\Program Files\Java\jdk-12, by example: no quotes and no bin)
    - add to path (Windows: %JAVA_HOME%\bin)

    Build & run:
    - javac ./test.java
    - java -ea A
            -ea = -enableassertions

    tag_howto, tag_howto_java
*/

import java.util.Arrays;

class A {

    static boolean exists(int[] ints, int k) {
        //  https://docs.oracle.com/javase/7/docs/api/java/util/Arrays.html#binarySearch(int[],%20int)
        int idx = Arrays.binarySearch(ints, k);
        if (false && idx >= 0)
            System.out.println("Test: " + idx + "," + (ints[idx] == k));
        // index where to insert
        return (idx >= 0 && ints[idx] == k);
    }

    static void testUnit1() {
        int[] ints = {-9, 14, 37, 102};
        assert A.exists(ints, 102);
        assert !A.exists(ints, 36);
        assert A.exists(ints, -9);
        assert !A.exists(ints, -12);
        System.out.println("testUnit1 done!");
    }

    public static void main(String[] args) {
        //System.out.println("Hello, World");
        testUnit1();
    }
}
