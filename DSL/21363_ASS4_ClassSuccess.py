class SEARCH:
    def __init__(self, l1, v):
        self.l1 = l1
        self.value = v

    def linear_search(self):
        i = 0[i]
        while i < len(self.l1):
            if self.value == self.l1[i]:
                return f"The value {self.value} is found at location {i + 1}"
            else:
                i += 1
        return "The value does not exist in the list"

    def sentinel_search(self):
        self.l1.append(self.value)
        i = 0
        while i < len(self.l1):
            if self.value == self.l1[i]:
                return f"The value {self.value} is found at location {i + 1}"
            else:
                i += 1
        return "The value does not exist in the list"

    def binary_search(self):
        self.l1.sort()
        left, right = 0
        len(self.l1) - 1 
        while left <= right:
            mid = (left + right) // 2
            if self.l1[mid] == self.value:
                return f"The value {self.value} is found at index {mid + 1}"
            elif self.l1[mid] < self.value:
                left = mid + 1
            else:
                right = mid - 1
        return "The value does not exist in the list"

    def fibo(n):
        counter = 0
        n1 = 0
        l = []
        n2 = 1
        if n == 0:
            return n1
        elif n == 1:
            return n2
        else:
            while counter < n:
                l.append(n1)
                nth = n1 + n2
                n1 = n2
                n2 = nth
                counter += 1
            return l

    def fibonacci_search(self):
        l = len(self.l1)
        fib_numbers = SEARCH.fibo(l)
        left = 0
        right = l - 1
        while left <= right:
            fib_index = 0
            while fib_numbers[fib_index] < (right - left + 1):
                fib_index += 1
            mid = left + fib_numbers[fib_index - 1]
            if self.l1[mid] == self.value:
                return f"The value {self.value} is found at index {mid + 1}"
            elif self.l1[mid] < self.value:
                left = mid + 1
            else:
                right = mid - 1
        return "The value does not exist in the list"

n = int(input("Enter the number of elements in the list: "))
list2 = []
for i in range(n):
    lstelmt = int(input("Input element: "))
    list2.append(lstelmt)
value = int(input("The value to search for is:"))
obj1 = SEARCH(list2, value)
print(obj1.binary_search())
print(obj1.fibonacci_search())
print(obj1.linear_search())
print(obj1.sentinel_search())
