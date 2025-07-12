import java.util.LinkedList;
import java.util.Queue;

class ProducerConsumer {
    private final int bufferSize;
    private final Queue<Integer> buffer;
    private int emptySlots;
    private int fullSlots;

    public ProducerConsumer(int size) {
        this.bufferSize = size;
        this.buffer = new LinkedList<>();
        this.emptySlots = size;
        this.fullSlots = 0;
    }

    public synchronized void produce(int item) throws InterruptedException {
        while (emptySlots <= 0) {
            wait(); // Wait for space in buffer
        }

        buffer.add(item);
        System.out.println("Produced: " + item);

        emptySlots--;
        fullSlots++;
        notifyAll(); // Notify consumers
    }

    public synchronized void consume() throws InterruptedException {
        while (fullSlots <= 0) {
            wait(); // Wait for items in buffer
        }

        int item = buffer.poll();
        System.out.println("Consumed: " + item);

        fullSlots--;
        emptySlots++;
        notifyAll(); // Notify producers
    }
}

class Producer extends Thread {
    private final ProducerConsumer pc;
    private final int totalItems;

    public Producer(ProducerConsumer pc, int totalItems) {
        this.pc = pc;
        this.totalItems = totalItems;
    }

    public void run() {
        for (int i = 1; i <= totalItems; i++) {
            try {
                pc.produce(i);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

class Consumer extends Thread {
    private final ProducerConsumer pc;
    private final int totalItems;

    public Consumer(ProducerConsumer pc, int totalItems) {
        this.pc = pc;
        this.totalItems = totalItems;
    }

    public void run() {
        for (int i = 0; i < totalItems; i++) {
            try {
                pc.consume();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

public class Main {
    public static void main(String[] args) throws Exception {
        int bufferSize = 5;
        int totalItems = 5;

        ProducerConsumer pc = new ProducerConsumer(bufferSize);

        Producer producer = new Producer(pc, totalItems);
        Consumer consumer = new Consumer(pc, totalItems);

        producer.start();
        consumer.start();

        producer.join();
        consumer.join();
    }
}
