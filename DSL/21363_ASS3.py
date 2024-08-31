    
class Matrices:
    
    def __init__(self,matrix,addmat,submat,mulmat,transmat):
        self.matrix=matrix
        self.addmat=addmat
        self.submat=submat
        self.mulmat=mulmat
        self.transmat=transmat

    def matrix():
        nor = int(input("number of rows"))
        noc = int(input("number of columns"))
        superlist=[]
        for i in range(nor):
            list1=[]
            for i in range(noc):
                element=int(input("element:"))
                list1.append(element)
            superlist.append(list1)
        print("The matrix is: ")
        for i in range(len(superlist)):
            print(superlist[i])
        return superlist

    def addmat(m1,m2):
        resultadd=[]
        for i in range(len(m1)):
            l1=[]
            k=0
            for j in range(len(m1[i])):
                k = m1[i][j] + m2[i][j]
                l1.append(k)
            resultadd.append(l1)
        print("The addition Matrices.matrix is:")
        for i in range(len(resultadd)):
            print(resultadd[i])
        # return superlist
        return resultadd

    def submat(m1,m2):
        resultsub=[]
        for i in range(len(m1)):
            l1=[]
            k=0
            for j in range(len(m1[i])):
                k = m1[i][j] - m2[i][j]
                l1.append(k)
            resultsub.append(l1)
        print("The subtraction Matrices.matrix is:")
        for i in range(len(resultsub)):
            print(resultsub[i])
        # return superlist
        return resultsub

    def transmat(m1):
        resulttrans=[]
        if len(m1)>=len(m1[1]):
            for i in range(len(m1)):
                l1=[]
                k=0
                for j in range(len(m1[i])):
                    k = m1[j][i]
                    l1.append(k)
                resulttrans.append(l1)
        else:
            for i in range(len(m1[1])):
                l1=[]
                k=0
                for j in range(len(m1)):
                    k = m1[j][i]
                    l1.append(k)
                resulttrans.append(l1)
        print("The transposed matrix is:")
        for i in range(len(resulttrans)):
            print(resulttrans[i])
        # return superlist
        return resulttrans

    def mulmat(m1,m2):
        resultmul=[]
        for i in range(len(m1)):
            l2=[]
            for j in range(len(m2[0])):
                k1=0
                for k in range(len(m2)):
                    k1 += m1[i][k]*m2[k][j]    
                l2.append(k1)
            resultmul.append(l2)
        print("The multiplication matrix is:")
        for i in range(len(resultmul)):
            print(resultmul[i])

while True:
    print("\n\nGive the First matrix")
    m1=Matrices.matrix()
    print("choose a matrix operations:")
    print("1. add\n2. sub\n3. multiply\n4.transpose")
    choice=int(input())
    if choice == 1:
        print("\ngive second matrix")
        m2 = Matrices.matrix()
        obj1 = Matrices.addmat(m1,m2)
        obj1        
        yon=input("Do you want to continue?('y' for yes, 'n' for no)")
        if yon =='y':
            continue
        else:
            print("Thanks")
            break
    elif choice == 2:
        print("\ngive second matrix")
        m2=Matrices.matrix()
        obj2 = Matrices.submat(m1,m2)         
        obj2
        yon=input("Do you want to continue?('y' for yes, 'n' for no)")
        if yon =='y':
            continue
        else:
            print("Thanks")
            break
    elif choice == 3:
        print("\ngive second matrix")
        m2=Matrices.matrix()
        obj3 = Matrices.mulmat(m1,m2)      
        obj3
        yon=input("Do you want to continue?('y' for yes, 'n' for no)")
        if yon =='y':
            continue
        else:
            print("Thanks")
            break
    elif choice == 4:
        obj4= Matrices.transmat(m1)
        obj4
        yon=input("Do you want to continue?('y' for yes, 'n' for no)")
        if yon =='y':
            continue
        else:
            print("Thanks")
            break
    else:
        (print("provided choice is empty"))