class Sort:
    #constructor for making ek list as common operation of sorting is being performed on the list
    def __init__(self,list1):
        self.list1=list1
        
    def bubble_sort(self):
        swapped=bool()
        temp=0
        for j in range(len(a)):
            for i in range(len(a)-1):
                if self.list1[i]>self.list1[i+1]:
                    temp=a[i]
                    self.list1[i]=self.list1[i+1]
                    self.list1[i+1]=temp
                    swapped=True
            if swapped==False:
                print("already swapped")
                break
        print("Sorted With Bubble Sort")
        return self.list1

    def selection_sort(self):
        for i in range(len(self.list1)):#agar len(a) liya toh last index ke liye run nahi hoga out of bound jYEGA
            min=i
            #this loop finds the index of the smallest number
            for j in range(i+1,len(self.list1)): # jisko min consider kiya uske ge ke elements search hoge
                if self.list1[min]>self.list1[j]:
                    min=j
            #swapp inital considered min with actual min below
            temp=self.list1[i]
            self.list1[i]=self.list1[min]
            self.list1[min]=temp
        print("Sorted With Selection Sort")
        return (self.list1)

    def insertion_sort(self):
        for i in range(len(self.list1)): #this is for movement in list
            for j in range(0,i): #this is to make the partition where we store sorted array
                if self.list1[j]>self.list1[i]: # if the value in sorted array is less greator than value in unsorted group swap them
                    temp=self.list1[i]
                    self.list1[i]=self.list1[j]
                    self.list1[j]=temp
        print("Sorted With Insertion Sort")
        return(self.list1)
    
            

    def shell_sort(self):
        gap=len(self.list1)//2 #declare initial gap
        while gap>0:
            for i in range(len(self.list1)):
                if (((i+gap)<len(self.list1)) and (self.list1[i]>self.list1[i+gap])): #i th index ke baad wale gap index pe ka valuers are compared while keeping in mind thatgap ka indexs stays in bound
                    temp=self.list1[i]
                    self.list1[i]=self.list1[i+gap]
                    self.list1[i+gap]=temp
            gap=gap//2
        print("Sorted With Shell Sort")
        return (self.list1)

def list_maker():
    listout=[]
    term=int(input("Enter the number of terms: "))
    for i in range(term):
        print("Value at index",i+1,"is: ")
        value=int(input())
        listout.append(value)
    return listout

  #obj of calss

repeat=True
while True:
    if repeat==True:
        print("Provide a list: ")
        a=list_maker()
        prem=Sort(a)
        print("Please select a sorting technique form provided the list. \n1. Bubble sort. \n2. Selection sort. \n3.Inserton sort. \n4. Shell Sort.\nENTER ANYTHING ELSE TO EXIT\n")
        choice=int(input("Enter Choice for sorting: "))
        if choice==1:
            print(prem.bubble_sort())
            continue_or_not=int(input("do you Want to continue? 1 for yes, 0 for no"))
            if continue_or_not==0:
                print("thanks")
                repeat=False
        elif choice==2:
            print(prem.selection_sort())
            continue_or_not=int(input("do you Want to continue? 1 for yes, 0 for no"))
            if continue_or_not==0:
                print("thanks")
                repeat=False
        elif choice==3:
            print(prem.insertion_sort())
            continue_or_not=int(input("do you Want to continue? 1 for yes, 0 for no"))
            if continue_or_not==0:
                print("thanks")
                repeat=False
        elif choice==4:
            print(prem.shell_sort())
            continue_or_not=int(input("do you Want to continue? 1 for yes, 0 for no"))
            if continue_or_not==0:
                print("thanks")
                repeat=False
        else:
            print("Thanks, Exit")
            break
    else: 
        break