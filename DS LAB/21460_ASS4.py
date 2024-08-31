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
        
    def fibo(self,n):
        if(n==1 or n == 0):
            return n
        else:
            return self.fibo(n-1) + self.fibo(n-2)
        
            

s = Search()

list = s.input()
value = int(input("The value to search for is:"))

s.linear_search(list,value)
print(s.binary_search(list,value))

print(s.fibo(3))
