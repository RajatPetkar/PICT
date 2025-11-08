public class MemoryAllocation {
    public static void main(String[] args) {
        int blocks[] = {100, 500, 200, 300, 600};
        int process[] = {212, 417, 112, 426};

        firstFit(blocks.clone(), process);
        bestFit(blocks.clone(), process);
        worstFit(blocks.clone(), process);
        nextFit(blocks.clone(), process);
    }

    static void firstFit(int b[], int p[]) {
        System.out.println("\nFirst Fit:");
        for (int x : p) {
            boolean placed = false;
            for (int i = 0; i < b.length; i++) {
                if (b[i] >= x) {
                    System.out.println("Process " + x + " in Block " + b[i]);
                    b[i] -= x;
                    placed = true; break;
                }
            }
            if (!placed) System.out.println("Process " + x + " Not Allocated");
        }
    }

    static void bestFit(int b[], int p[]) {
        System.out.println("\nBest Fit:");
        for (int x : p) {
            int idx = -1;
            for (int i = 0; i < b.length; i++)
                if (b[i] >= x && (idx == -1 || b[i] < b[idx])) idx = i;
            if (idx != -1) {
                System.out.println("Process " + x + " in Block " + b[idx]);
                b[idx] -= x;
            } else System.out.println("Process " + x + " Not Allocated");
        }
    }

    static void worstFit(int b[], int p[]) {
        System.out.println("\nWorst Fit:");
        for (int x : p) {
            int idx = -1;
            for (int i = 0; i < b.length; i++)
                if (b[i] >= x && (idx == -1 || b[i] > b[idx])) idx = i;
            if (idx != -1) {
                System.out.println("Process " + x + " in Block " + b[idx]);
                b[idx] -= x;
            } else System.out.println("Process " + x + " Not Allocated");
        }
    }

    static void nextFit(int b[], int p[]) {
        System.out.println("\nNext Fit:");
        int pos = 0;
        for (int x : p) {
            boolean placed = false;
            for (int i = 0; i < b.length; i++) {
                int idx = (pos + i) % b.length;
                if (b[idx] >= x) {
                    System.out.println("Process " + x + " in Block " + b[idx]);
                    b[idx] -= x;
                    pos = idx;
                    placed = true; break;
                }
            }
            if (!placed) System.out.println("Process " + x + " Not Allocated");
        }
    }
}
