import java.util.*;

public class CPU_Scheduling {

    static class Process {
        String pid;
        int at, bt, pt; // arrival, burst, priority
        Process(String p, int a, int b, int pr) {
            pid = p; at = a; bt = b; pt = pr;
        }
    }

    public static void main(String[] args) {
        Process p[] = {
            new Process("P1", 0, 7, 2),
            new Process("P2", 2, 4, 1),
            new Process("P3", 4, 1, 3),
            new Process("P4", 5, 4, 2)
        };

        System.out.println("\n--- FCFS ---");
        fcfs(p);

        System.out.println("\n--- SJF (Preemptive) / SRTF ---");
        sjf(p);

        System.out.println("\n--- Priority (Non-Preemptive) ---");
        priority(p);

        System.out.println("\n--- Round Robin ---");
        roundRobin(p, 2);
    }

    // ---------- FCFS ----------
    static void fcfs(Process p[]) {
        int time = 0;
        int wt = 0, tat = 0;
        for (Process x : p) {
            if (time < x.at) time = x.at;
            int start = time;
            time += x.bt;
            int finish = time;
            wt += (start - x.at);
            tat += (finish - x.at);
            System.out.println(x.pid + " Start:" + start + " Finish:" + finish);
        }
        System.out.println("Avg WT = " + wt / 4.0 + "  Avg TAT = " + tat / 4.0);
    }

    // ---------- SJF PREEMPTIVE (SRTF) ----------
    static void sjf(Process p[]) {
        int n = p.length;
        int rt[] = new int[n];
        for (int i = 0; i < n; i++) rt[i] = p[i].bt;
        int completed = 0, time = 0;
        int wt = 0, tat = 0;

        while (completed != n) {
            int idx = -1, min = 999;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && rt[i] > 0 && rt[i] < min) {
                    min = rt[i];
                    idx = i;
                }
            }
            if (idx == -1) { time++; continue; }
            rt[idx]--;
            if (rt[idx] == 0) {
                completed++;
                int finish = time + 1;
                wt += finish - p[idx].at - p[idx].bt;
                tat += finish - p[idx].at;
            }
            time++;
        }
        System.out.println("Avg WT = " + wt / 4.0 + "  Avg TAT = " + tat / 4.0);
    }

    // ---------- PRIORITY NON-PREEMPTIVE ----------
    static void priority(Process p[]) {
        Process arr[] = p.clone();
        Arrays.sort(arr, (a, b) -> a.at - b.at);
        int time = 0, wt = 0, tat = 0;
        boolean done[] = new boolean[p.length];
        int completed = 0;

        while (completed != p.length) {
            int idx = -1, best = 999;
            for (int i = 0; i < p.length; i++) {
                if (!done[i] && p[i].at <= time && p[i].pt < best) {
                    best = p[i].pt; idx = i;
                }
            }
            if (idx == -1) { time++; continue; }
            int start = time;
            time += p[idx].bt;
            int finish = time;
            done[idx] = true;
            completed++;
            wt += start - p[idx].at;
            tat += finish - p[idx].at;
            System.out.println(p[idx].pid + " Start:" + start + " Finish:" + finish);
        }
        System.out.println("Avg WT = " + wt / 4.0 + "  Avg TAT = " + tat / 4.0);
    }

    // ---------- ROUND ROBIN ----------
    static void roundRobin(Process p[], int q) {
        int n = p.length;
        int rt[] = new int[n];
        for (int i = 0; i < n; i++) rt[i] = p[i].bt;
        int time = 0, completed = 0, wt = 0, tat = 0;

        while (completed != n) {
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && rt[i] > 0) {
                    int exec = Math.min(q, rt[i]);
                    rt[i] -= exec;
                    time += exec;
                    if (rt[i] == 0) {
                        completed++;
                        wt += time - p[i].at - p[i].bt;
                        tat += time - p[i].at;
                    }
                } else time++;
            }
        }
        System.out.println("Avg WT = " + wt / 4.0 + "  Avg TAT = " + tat / 4.0);
    }
}
