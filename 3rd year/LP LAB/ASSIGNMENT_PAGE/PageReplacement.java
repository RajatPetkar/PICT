package ASSIGNMENT_PAGE;
import java.util.*;

public class PageReplacement {
    public static void main(String[] args) {
        int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3};
        int frames = 3;

        fifo(pages, frames);
        lru(pages, frames);
        mru(pages, frames);
        optimal(pages, frames);
    }

    static void fifo(int pages[], int f) {
        Queue<Integer> q = new LinkedList<>();
        int faults = 0;
        for (int p : pages) {
            if (!q.contains(p)) {
                if (q.size() == f) q.poll();
                q.add(p);
                faults++;
            }
        }
        System.out.println("FIFO Faults = " + faults);
    }

    static void lru(int pages[], int f) {
        ArrayList<Integer> list = new ArrayList<>();
        int faults = 0;
        for (int p : pages) {
            if (!list.contains(p)) {
                if (list.size() == f) list.remove(0);
                list.add(p);
                faults++;
            } else {
                list.remove((Integer)p);
                list.add(p);
            }
        }
        System.out.println("LRU Faults = " + faults);
    }

    // ✅ MRU (Most Recently Used)
    static void mru(int pages[], int f) {
        ArrayList<Integer> list = new ArrayList<>();
        int faults = 0;
        for (int p : pages) {
            if (!list.contains(p)) {
                if (list.size() == f) list.remove(list.size() - 1); // remove MOST RECENTLY used
                list.add(p);
                faults++;
            } else {
                list.remove((Integer)p);
                list.add(p); // this becomes most recent
            }
        }
        System.out.println("MRU Faults = " + faults);
    }

    static void optimal(int pages[], int f) {
        ArrayList<Integer> list = new ArrayList<>();
        int faults = 0;
        for (int i = 0; i < pages.length; i++) {
            int p = pages[i];
            if (!list.contains(p)) {
                if (list.size() == f) {
                    int idx = -1, far = -1;
                    for (int x : list) {
                        int j;
                        for (j = i; j < pages.length; j++)
                            if (pages[j] == x) break;
                        if (j > far) { far = j; idx = x; }
                    }
                    list.remove((Integer)idx);
                }
                list.add(p);
                faults++;
            }
        }
        System.out.println("Optimal Faults = " + faults);
    }
}
