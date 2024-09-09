class SortingOpr:
    def insertionSort(self, elements, n):
        for i in range(1, n):
            anchor = elements[i]
            j = i-1
            while j >= 0 and anchor < elements[j]:
                elements[j+1] = elements[j]
                j -= 1
            elements[j+1] = anchor
            # Print the array after each pass
            print(f"Pass {i}: {elements}")
        return elements

    def shellSort(arr, n):
    gap=n//2
    while gap>0:
        j=gap
        while j<n:
            i=j-gap 
            
            while i>=0:
                if arr[i+gap]>arr[i]:
                    break
                else:
                    arr[i+gap],arr[i]=arr[i],arr[i+gap]
                i=i-gap
            j+=1
        gap=gap//2 

# Input data
n = int(input("Enter no. of students: "))
data = []
for i in range(n):
    name = input(f"Enter Name of student {i+1}: ")
    marks = float(input(f"Enter marks of student {i+1}: "))
    data.append((marks, name))

# Sorting and result
obj = SortingOpr()
print("\nPerforming Insertion Sort:")
insertionResult = obj.insertionSort(data.copy(), n)

print("\nPerforming Shell Sort:")
shellResult = obj.shellSort(data.copy(), n)

# Printing top 5 students
print("\nTop 5 students (using insertion sort): ")
for n, m in insertionResult[:-6:-1]:
    print(m, ": ", n)

print("\nTop 5 students (using shell sort): ")
for n, m in shellResult[:-6:-1]:
    print(n, ": ", m)
