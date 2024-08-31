# def quick_sort(a):
#     if len(a) <= 1:
#         return a
#     pivot = a[len(a) // 2]
#     lessorSide = []
#greatorSide = []
#     for i in range(len(a)):
#         if a[i] > pivot:
#        greatorSide.append(a[i])
#         elif a[i] < pivot:
#             lessorSide.append(a[i])
#     return quick_sort(lessorSide) + [pivot] + quick_greatorSide)

class Sort:  
    def __init__(self,l1):
        self.l1=l1

    def quick_sort(self):
        if len(self.l1) <= 1:
            return self.l1
        pivot = self.l1[len(self.l1) // 2]
        lessorSide = []
        greatorSide = []
        for i in range(len(self.l1)):
            if self.l1[i] > pivot:
                greatorSide.append(self.l1[i])
            elif self.l1[i] < pivot:
                lessorSide.append(self.l1[i])
        
        return Sort(lessorSide).quick_sort() + [pivot] + Sort(greatorSide).quick_sort()
    
a=[1,-1,2,3,4,89,9,65,5]
prem=Sort(a)
print(prem.quick_sort())