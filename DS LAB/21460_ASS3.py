class Matrices:
    
    def create_matrix(self):
        nor = int(input("Enter number of rows: "))
        noc = int(input("Enter number of columns: "))
        matrix = []
        for i in range(nor):
            row = []
            for j in range(noc):
                element = int(input(f"Enter element [{i+1}][{j+1}]: "))
                row.append(element)
            matrix.append(row)
        print("The matrix is: ")
        for row in matrix:
            print(row)
        return matrix

    def add_matrices(self, m1, m2):
        result = []
        for i in range(len(m1)):
            row = []
            for j in range(len(m1[i])):
                row.append(m1[i][j] + m2[i][j])
            result.append(row)
        print("The resulting matrix after addition is:")
        for row in result:
            print(row)
        return result

    def subtract_matrices(self, m1, m2):
        result = []
        for i in range(len(m1)):
            row = []
            for j in range(len(m1[i])):
                row.append(m1[i][j] - m2[i][j])
            result.append(row)
        print("The resulting matrix after subtraction is:")
        for row in result:
            print(row)
        return result

    def transpose_matrix(self, m):
        result = []
        for i in range(len(m[0])):
            row = []
            for j in range(len(m)):
                row.append(m[j][i])
            result.append(row)
        print("The transposed matrix is:")
        for row in result:
            print(row)
        return result

    def multiply_matrices(self, m1, m2):
        result = []
        for i in range(len(m1)):
            row = []
            for j in range(len(m2[0])):
                element = 0
                for k in range(len(m2)):
                    element += m1[i][k] * m2[k][j]
                row.append(element)
            result.append(row)
        print("The resulting matrix after multiplication is:")
        for row in result:
            print(row)
        return result

mat = Matrices()

while True:
    print("\n\nGive the first matrix")
    m1 = mat.create_matrix()

    print("Choose a matrix operation:")
    print("1. Add\n2. Subtract\n3. Multiply\n4. Transpose")
    choice = int(input())

    if choice in [1, 2, 3]:
        print("\nGive the second matrix")
        m2 = mat.create_matrix()

    if choice == 1:
        mat.add_matrices(m1, m2)
    elif choice == 2:
        mat.subtract_matrices(m1, m2)
    elif choice == 3:
        mat.multiply_matrices(m1, m2)
    elif choice == 4:
        mat.transpose_matrix(m1)
    else:
        print("Invalid choice. Please try again.")

    yon = input("Do you want to continue? ('y' for yes, 'n' for no): ")
    if yon.lower() != 'y':
        break
