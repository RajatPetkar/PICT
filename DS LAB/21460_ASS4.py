class Search:
    
    def input(self):
        list = []
        print("Enter no. of elements of list :-")
        no = int(input())
        
        for i in range(0,no):
            n = int(input("Enter the number of elements in the list: "))
            list.append(n)
        return list
    
    def linear_search(self,list,value):
        ispresent = 0
        for i in range(0,len(list)):
            if list[i] == value:
                ispresent = i
    
        if(ispresent):
            print(f"element is present at index {ispresent+1}")
        else:
            print("element is not present")
    
    def binary_search(self,list,value):
        list.sort()
        left = 0
        right = len(list)-1
        
        while left <= right:
            mid = 0
            while list[mid] < (right - left + 1):
                mid += 1
            mid = left + list[mid - 1]
            
            if list[mid] == value:
                return f"The value {value} is found at index {mid + 1}"
            elif list[mid] < value:
                left = mid + 1
            else:
                right = mid - 1
        return "The value does not exist in the list"
        
    def sentinelSearch(self, arr, item):
        n = self.getLength(arr)
        last = arr[-1]
        arr[-1] = item
        i=0
        while arr[i] != item:
            i+=1
        arr[-1] = last
        if i<n-1 or arr[-1]==item:
            return i
        else:
            return -1

    def fibonacciSearch(self, arr, item):
        n = self.getLength(arr)

        fib2 = 0
        fib1 = 1
        fib = fib2 + fib1

        while fib < n:
            fib2 = fib1
            fib1 = fib
            fib = fib2 + fib1

        offset = -1

        while fib > 1:
            temp = offset + fib2
            
            i = temp if temp<n-1 else n-1

            if arr[i] == item:
                return i
            elif arr[i]<item:
                fib = fib1
                fib1 = fib2
                fib2 = fib - fib1
                offset = i
            else:
                fib = fib2
                fib1 = fib1 - fib2
                fib2 = fib - fib1

        if fib1 and offset + 1 < n and arr[offset + 1] == item:
            return offset + 1
        
        return -1
        
            

s = Search()

list = s.input()
value = int(input("The value to search for is:"))

s.linear_search(list,value)
print(s.binary_search(list,value))
