import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt(), m = scanner.nextInt(), q = scanner.nextInt();

        ArrayList<ArrayList<Integer>> constraints = new ArrayList<>();
        for (int i = 0; i < q; i++) {
            int a = scanner.nextInt(), b = scanner.nextInt(), c = scanner.nextInt(), d = scanner.nextInt();
            constraints.add(new ArrayList<>(Arrays.asList(a, b, c, d)));
        }

        ArrayList<ArrayList<Integer>> allNonDescendantSequences = generateNonDescendantSequence(n, m);

        int maxValue = 0;
        for (ArrayList<Integer> sequence : allNonDescendantSequences) {
            int value = 0;
            for (ArrayList<Integer> constraint : constraints) {
                if(sequence.get(constraint.get(1) - 1) - sequence.get(constraint.get(0) - 1) == constraint.get(2))
                    value += constraint.get(3);
            }
            if (value > maxValue) maxValue = value;
        }

        System.out.println(maxValue);


    }

    static ArrayList<ArrayList<Integer>> generateNonDescendantSequence (int length, int bound) {
        if (length == 1) {
            ArrayList<ArrayList<Integer>> baseSequence = new ArrayList<>();
            for (int i = 1; i < bound+1; i++) {
                baseSequence.add(new ArrayList<>(Collections.singletonList(i)));
            }
            return baseSequence;
        }

        ArrayList<ArrayList<Integer>> prevSequence = generateNonDescendantSequence(length-1, bound);
        ArrayList<ArrayList<Integer>> finalSequence = new ArrayList<>();

        for(ArrayList<Integer> sequence : prevSequence) {
            for (int i = sequence.get(length-2); i <= bound; i++) {
                ArrayList<Integer> newSequence = new ArrayList<>(sequence);
                newSequence.add(i);
                finalSequence.add(new ArrayList<>(newSequence));
            }
        }

        return finalSequence;
    }
}
