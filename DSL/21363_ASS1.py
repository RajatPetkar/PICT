cr=[]
bd=[]
fb=[]

print("the number of students in the class playing football is:")
nos=int(input())
print("please provide the roll numbers of these students:")
for var1 in range(0,nos):
    while True:
        print("enter roll number of student number ",var1+1)
        roll=int(input())
        if roll in fb:
            print("THIS ROLL NUMBER ALREADY EXIST, Try something else")
        else:
            fb.append(roll)
            break

print("the number of students in the class playing badminton is:")
nos=int(input())
print("please provide the roll numbers of these students:")
for var1 in range(0,nos):
    while True:
        print("enter roll number of student number ",var1+1)
        roll=int(input())
        if roll in bd:
            print("THIS ROLL NUMBER ALREADY EXIST, Try something else")
        else:
            bd.append(roll)
            break

print("the number of students in the class playing cricket is:")
nos=int(input())
print("please provide the roll numbers of these students:")
for var1 in range(0,nos):
    while True:
        print("enter roll number of student number ",var1+1)
        roll=int(input())
        if roll in cr:
            print("THIS ROLL NUMBER ALREADY EXIST, Try something else")
        else:
            cr.append(roll)
            break

class Sports:
    def union(*arg):
        l3=[]
        l4=[]
        uni=[]
        li=list()
        for li in arg:
            uni = uni+li
        for i in uni:
            if uni.count(i) > 1:
                if i in l3:
                    continue
                else:
                    l3.append(i)
            else:
                if i in l4:
                    continue
                else:
                    l4.append(i)
        return l3+l4

    def intersection(*arg):
        noa= len(arg)
        l3=[]
        inte=[]
        li=list()
        for li in arg:
            inte = inte+li
        for i in inte:
            if inte.count(i) == noa:
                if i in l3:
                    continue
                else:
                    l3.append(i)    
            else:
                continue
        return l3
    

    def choice1():
        print("students who play cricket are:")
        print(cr)
        print("students who play badminton are:")
        print(bd)
        print("students who play both cricket and badminton are:")
        print((Sports.union(cr,bd)))

    def choice2():
        print("students who play cricket are:")
        print(cr)
        print("students who play badminton are:")
        print(bd)
        print("students who play either cricket or badminton but not both are:")
        l4=[]
        i = (Sports.union(cr,bd))
        j = (Sports.intersection(cr,bd))
        l3=i+j
        for var1 in l3:
            if l3.count(var1) > 1:
                continue
            else:
                l4.append(var1)
        return l4
        # for var2 in j:
        #     for var1 in i:
        #         if var2 != var1:
        #             if var2 in l3:
        #                 continue
        #             else:
        #                 l3.append(var2)
        #         else:
        #             continue

    def choice3():
        print("students who play cricket are:")
        print(cr)
        print("students who play badminton are:")
        print(bd)
        print("students who play football are:")
        print(fb)
        print("Number of students who play neither cricket nor badminton")
        l4=[]
        i = (Sports.union(cr,bd,fb))
        j = (Sports.union(cr,bd))
        l3=i+j
        for var1 in l3:
            if l3.count(var1) > 1:
                continue
            else:
                l4.append(var1)
        return len(l4)

    def choice4():
        print("students who play cricket are:")
        print(cr)
        print("students who play badminton are:")
        print(bd)
        print("students who play football are:")
        print(fb)
        print("Number of students who play cricket and football but not badminton:")
        l4=[]
        i=(Sports.union(cr,bd,fb))
        j=bd
        l3=i+j
        for var1 in l3:
            if l3.count(var1) > 1:
                continue
            else:
                l4.append(var1)
        print(l4)
        return len(l4)
    
    def choice5():
        print("students who play cricket are:")
        print(cr)
        print("students who play badminton are:")
        print(bd)
        # print("students who play football are:")
        # print(fb)
        print("List of students who play either cricket or badminton is:")
        print(Sports.union(cr,bd))



print("CHOICES:")
print("1. List of students who play both cricket and badminton")
print("2. List of students who play either cricket or badminton but not both")
print("3. Number of students who play neither cricket nor badminton")
print("4. Number of students who play cricket and football but not badminton")
print("5. List of students who play either cricket or badminton")
bool1=1
while bool1 == 1:
    print("should computing start:(1 for yes, 0 for  no)")
    bool1=int(input())
    print("enter selected choice:")
    var=int(input())
    if var == 1:
        print(Sports.choice1())
        print("Do you want to continue: 1 for yes, 0 for no")
        again=int(input())
        if again==1:
            continue
        else:
            break
    elif var == 2:
        print(Sports.choice2())
        print("Do you want to continue: 1 for yes, 0 for no")
        again=int(input())
        if again==1:
            continue
        else:
            break
    elif var == 3:
        print(Sports.choice3())
        print("Do you want to continue: 1 for yes, 0 for no")
        again=int(input())
        if again==1:
            continue
        else:
            break
    elif var == 4:
        print(Sports.choice4())
        print("Do you want to continue: 1 for yes, 0 for no")
        again=int(input())
        if again==1:
            continue
        else:
            break
    elif var == 5:
        print(Sports.choice5())
        print("Do you want to continue: 1 for yes, 0 for no")
        again=int(input())
        if again==1:
            continue
        else:
            break
    else:
        print ("thanks")