import java.util.Scanner;

class Semaphore
{
    public int value;

    public Semaphore(int i) // To initialize the semaphore object with initial value.
    {
        this.value = i;
    }

    public boolean Wait()   // It checks the access or status of the buffer.
    {
        if(this.value > 0)
        {
            this.value--;
            return true;
        }
        else
            return false;
    }

    public void Signal()    // It releases the resources.
    {
        this.value++;
    }
}
    
public class ProducerConsumer
{
    public static void main(String args[])
    {
        final int buffer_size = 10;    // size of the buffer.
        int count = 0;      // The number of elements in the buffer.
        int in = 0;     //It moves to the next available slot.
        int out = 0;    //It moves the slot to consume.
        int[] buffer = new int[buffer_size];

        // Creating the Semaphore variables.
        Semaphore mutex = new Semaphore(1);
        Semaphore empty = new Semaphore(buffer_size);
        Semaphore full = new Semaphore(0);

        while(true)
        {
            System.out.println("\n<--------------MENU--------------->");
            System.out.println("1. Produce");
            System.out.println("2. Consume");
            System.out.println("3. Show Semaphore values");
            System.out.println("4. Exit");
            System.out.println("\nEnter choice: ");
            Scanner sc = new Scanner(System.in);
            int choice = sc.nextInt();

            switch(choice)
            {
                // Produce
                case 1:
                    {
                        if(!empty.Wait())
                        {
                            System.out.println("The Buffer is full.");
                            break;
                        }
                        if(!mutex.Wait())
                        {
                            System.out.println("The resource is busy.");
                            empty.Signal();
                            break;
                        }

                        // Defining the Critical Section
                        System.out.println("Enter product: ");
                        int temp = sc.nextInt();
                        buffer[in] = temp;
                        in = (in + 1) % buffer_size;
                        count++;
                        System.out.println("The produced item is : " + temp);

                        mutex.Signal();
                        full.Signal();
                        break;

                    }

                // Consume
                case 2:
                    {
                        if(!full.Wait())
                        {
                            System.out.println("The Buffer is empty.");
                            break;
                        }
                        if(!mutex.Wait())
                        {
                            System.out.println("The resource is busy.");
                            full.Signal();
                            break;
                        }

                        // Critical Section
                        int temp = buffer[out];
                        out = (out + 1) % buffer_size;
                        count--;
                        System.out.println("The item consumed is : " + temp);

                        mutex.Signal();
                        empty.Signal();
                        break;
                    }

                case 3:
                    {
                        System.out.println("Items in buffer: " + count + "/" + buffer_size);
                        System.out.println("Mutex: " + mutex.value + ", Empty: " + empty.value + ", Full: " + full.value);
                        break;
                    }
                
                case 4:
                    return;
            }
        }    
    }
}