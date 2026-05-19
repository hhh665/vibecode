public class LcmCalculatorTest {

    private static int passed;
    private static int failed;

    public static void main(String[] args) {
        test_lcm_12_18();
        test_lcm_coprime();
        test_lcm_same_number();
        test_lcm_one_is_multiple();
        test_lcm_large_numbers();
        test_lcm_throws_on_zero();
        test_lcm_throws_on_negative();

        System.out.println("\n---");
        System.out.println("Passed: " + passed + ", Failed: " + failed);
        if (failed > 0) {
            System.exit(1);
        }
    }

    private static void check(String name, long expected, long actual) {
        if (expected == actual) {
            passed++;
            System.out.println("PASS " + name);
        } else {
            failed++;
            System.out.println("FAIL " + name + " - expected " + expected + " but got " + actual);
        }
    }

    static void test_lcm_12_18() {
        check("lcm(12,18)", 36, LcmCalculator.lcm(12, 18));
    }

    static void test_lcm_coprime() {
        check("lcm(7,13)", 91, LcmCalculator.lcm(7, 13));
    }

    static void test_lcm_same_number() {
        check("lcm(5,5)", 5, LcmCalculator.lcm(5, 5));
    }

    static void test_lcm_one_is_multiple() {
        check("lcm(6,18)", 18, LcmCalculator.lcm(6, 18));
    }

    static void test_lcm_large_numbers() {
        check("lcm(12345,67890)", 55873470, LcmCalculator.lcm(12345, 67890));
    }

    static void test_lcm_throws_on_zero() {
        try {
            LcmCalculator.lcm(0, 5);
            failed++;
            System.out.println("FAIL lcm(0,5) should have thrown");
        } catch (IllegalArgumentException e) {
            passed++;
            System.out.println("PASS lcm(0,5) throws");
        }
    }

    static void test_lcm_throws_on_negative() {
        try {
            LcmCalculator.lcm(-3, 5);
            failed++;
            System.out.println("FAIL lcm(-3,5) should have thrown");
        } catch (IllegalArgumentException e) {
            passed++;
            System.out.println("PASS lcm(-3,5) throws");
        }
    }
}
