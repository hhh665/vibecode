public class LcmCalculator {

    /**
     * Returns the least common multiple (LCM) of two positive integers.
     */
    public static long lcm(int a, int b) {
        if (a <= 0 || b <= 0) {
            throw new IllegalArgumentException("Arguments must be positive");
        }
        return (long) a / gcd(a, b) * b;
    }

    private static int gcd(int a, int b) {
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    public static void main(String[] args) {
        System.out.println("lcm(12, 18) = " + lcm(12, 18));
        System.out.println("lcm(7, 13)  = " + lcm(7, 13));
    }
}
