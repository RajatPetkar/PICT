class Sports:
    def input(self, arr):
        nos = int(input())
        print("Please provide the roll numbers of these students:")
        for var1 in range(nos):
            while True:
                print("Enter roll number of student number ", var1 + 1)
                roll = int(input())
                if roll in arr:
                    print("THIS ROLL NUMBER ALREADY EXISTS, Try something else")
                else:
                    arr.append(roll)
                    break

    def union(self, set1, set2):
        result = list(set1)
        for element in set2:
            if element not in result:
                result.append(element)
        return result

    def intersection(self, set1, set2):
        result = []
        for element in set1:
            if element in set2:
                result.append(element)
        return result

    def difference(self, set1, set2):
        result = []
        for element in set1:
            if element not in set2:
                result.append(element)
        return result

    def symmetric_difference(self, set1, set2):
        result = []
        for element in set1:
            if element not in set2:
                result.append(element)
        for element in set2:
            if element not in set1:
                result.append(element)
        return result

    def choice1(self):
        print("Students who play both cricket and badminton are:")
        print(cr)
        print(bd)
        print(self.intersection(cr, bd))

    def choice2(self):
        print("Students who play either cricket or badminton but not both are:")
        print(cr)
        print(bd)
        print(self.symmetric_difference(cr, bd))

    def choice3(self):
        print("Number of students who play neither cricket nor badminton:")
        all_students = list(set(cr + bd + fb))
        neither_cricket_nor_badminton = self.difference(all_students, self.union(cr, bd))
        print(all_students)
        print(neither_cricket_nor_badminton)

    def choice4(self):
        print("Number of students who play cricket and football but not badminton:")
        cricket_and_football = self.intersection(cr, fb)
        cricket_football_not_badminton = self.difference(cricket_and_football, bd)
        print(cr)
        print(bd)
        print(cricket_football_not_badminton)

    def choice5(self):
        print("List of students who play either cricket or badminton:")
        print(self.union(cr, bd))


cr = []
bd = []
fb = []

s = Sports()

print("The number of students in the class playing football is:")
s.input(fb)

print("The number of students in the class playing badminton is:")
s.input(bd)

print("The number of students in the class playing cricket is:")
s.input(cr)

print("CHOICES:")
print("1. List of students who play both cricket and badminton")
print("2. List of students who play either cricket or badminton but not both")
print("3. Number of students who play neither cricket nor badminton")
print("4. Number of students who play cricket and football but not badminton")
print("5. List of students who play either cricket or badminton")

while True:
    print("Should computing start? (1 for yes, 0 for no)")
    bool1 = int(input())
    if bool1 == 0:
        break

    print("Enter selected choice:")
    var = int(input())
    if var == 1:
        s.choice1()
    elif var == 2:
        s.choice2()
    elif var == 3:
        s.choice3()
    elif var == 4:
        s.choice4()
    elif var == 5:
        s.choice5()

    print("Do you want to continue? 1 for yes, 0 for no")
    again = int(input())
    if again == 0:
        break