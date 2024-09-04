class SortingOpr:
    def insertionSort(self, elements, n):
        for i in range(1, n):
            anchor = elements[i]
            j = i-1
            while j>=0 and anchor<elements[j]:
                elements[j+1] = elements[j]
                j-=1
            elements[j+1] = anchor
        return elements


    def shellSort(self, elements, n):
        gap = n//2
        while gap > 0:
            for i in range(gap, n):
                anchor = elements[i]
                j = i
                while j>=gap and elements[i-gap][0]>anchor[0]:
                    elements[j] = elements[j-gap]
                    j -=gap
                elements[j] = anchor
            gap = gap//2
        return elements 


n = int(input("Enter no. of students: "))
data = []
for i in range(n):
    name = input(f"Enter Name of student {i+1}: ")
    marks = float(input(f"Enter marks of student {i+1}: "))
    data.append((marks, name))
obj = SortingOpr()
insertionResult = obj.insertionSort(data, n)
shellResult = obj.shellSort(data, n)

print("\nTop 5 students(using insertion sort): ")
for n, m in insertionResult[:-6:-1]:
    print(m, ": ", n)

print("\nTop 5 students(using shell sort): ")
for n, m in shellResult[:-6:-1]:
    print(n, ": ", m)


