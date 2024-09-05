class Sorter:
    def length(self, elements):
        count = 0
        for _ in elements:
            count += 1
        return count

    def swap(self, a, b, arr):
        arr[a], arr[b] = arr[b], arr[a]

    def partition(self, elements, start, end):
        pivot_index = start
        pivot = elements[pivot_index][0]

        while start < end:
            while start < self.length(elements) and elements[start][0] <= pivot:
                start += 1

            while elements[end][0] > pivot:
                end -= 1

            if start < end:
                self.swap(start, end, elements)

        self.swap(pivot_index, end, elements)

        return end

    def quickSort(self, elements, start, end, pass_num=1):
        if start < end:
            pi = self.partition(elements, start, end)
            print(f"Pass {pass_num}: {elements}")  # Print each pass
            pass_num += 1  # Increment pass number
            self.quickSort(elements, start, pi-1, pass_num)
            self.quickSort(elements, pi+1, end, pass_num)
        return elements


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
