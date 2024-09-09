class Sorter:
    def length(self, elements):
        count = 0
        for _ in elements:
            count += 1
        return count

    def swap(self, a, b, arr):
        arr[a], arr[b] = arr[b], arr[a]

    def partition(arr, low, high):
    pivot = arr[high]
    
    i = low - 1

    for j in range(low, high):
        if arr[j] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]

    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

def quick_sort(arr, low, high):
    if low < high:
        pi = partition(arr, low, high)
        print(f"{} Pass :- ")
        quick_sort(arr, low, pi - 1)
        quick_sort(arr, pi + 1, high)


n = int(input("Enter no. of students: "))
data = []
for i in range(n):
    name = input(f"Enter Name of student {i+1}: ")
    marks = float(input(f"Enter marks of student {i+1}: "))
    data.append((marks, name))

obj = Sorter()
quickResult = obj.quickSort(data, 0, n-1)

print("\nTop 5 students (using quick sort): ")
for n, m in quickResult[:-6:-1]:
    print(m, ": ", n)
