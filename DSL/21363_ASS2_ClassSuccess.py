class Strings():
    # No need to define a constructor, pyhto anyways doesvit for you
    
    #defined constructor for 2 input vale functions
    def __init__(self, str1,str_req):
        self.str1=str1
        self.str_req=str_req
        
    #TO make a split of the string
    def splitter(self):
        string1 = self.str1.lower()
        string1 = string1+" " 
        string2 = str()
        l3=[]
        for i in string1:
            if i != " ":
                string2=string2+i
            elif i == " ":
                l3.append(string2)
                string2=""
        return l3

    #LONGEST WORD OF STRING
    def longest(self):
        string1 = Strings.splitter()
        long = str()
        list1=[]
        for var in string1:
            if len(var) >= len(long):
                long = var  
                list1.append(long)
            else:
                continue
        print("Longest elemnt of the string are:")
        return(list1)

    #TO CHECK PALINDROME
    def palindrome(self):
        string2 = self.str1
        l1=[]
        for i in range(0,len(string2)):
            if string2[i] == string2[-1-i]:
                l1.append(1)
            else:
                l1.append(0)
        if 0 in l1:
            return("Given string is not palindrome")
        else:
            return("Given string is a palindrome")

    #TO GET NUMBER OF TIMES CHARACTER OCCURS
    def freq(self):
        str1=self.str1
        str2=self.str_req
        var=0
        for i in range(0,len(str1)):
            if str1[i] == str2:
                var+=1
            else:
                continue
        return("The occurance of this character in string is",var,"times")

    #TO GET NUMBER OF TIMES WORD OCCURS
    def freq2(self):
        str1=Strings.splitter()
        str2=self.str_req
        var=0
        for i in str1:
            if i == str2:
                var+=1
        return "The occurance of this WORD in string is",var,"times"

    #TO check for first occcurence of given character in string
    def firstapp(self):
        str1=self.str1
        str2=self.str_req
        var=0
        for i in range(0,len(str1)):
            if str1[i] == str2:
                return"The first appearance of the character is at postion",i+1,"from the start of the string"
        return 0    
print("Give a string")
strin=str(input())
print("KYA CHAHIYE AAPKO:")
print("1. TO check for first occcurence of given character in string")
print("2. TO GET NUMBER OF TIMES CHARACTER OCCURS")
print("3. TO GET NUMBER OF TIMES WORD OCCURS")
print("4. TO CHECK PALINDROME")
print("5. LONGEST WORD OF STRING")
choice=int(input())
if choice == 1:
    search_val=str(input("Searching for which character: "))
    obj=Strings(strin,search_val)
    print(obj.firstapp())
elif choice == 2:
    search_val=str(input("Searching for which character: "))
    obj=Strings(strin,search_val)
    print(obj.freq())
elif choice == 3:
    search_val=str(input("Searching for which character: "))
    obj=Strings(strin,search_val)
    print(obj.freq2())
elif choice == 4:
    obj=Strings(strin,"no_use")
    print(obj.palindrome())
elif choice == 5:
    obj=Strings(strin,"no_use")
    print(obj.longest())
else:
    print("wrong input, retry")
