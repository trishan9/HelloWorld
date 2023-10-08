def palind(s):
    s=s.lower().replace(" ","")
    return s==s[::-1]

s=input("Enter string: ")
if palind(s):
    print("palindrom-->  Yes")
else:
    print("palindrom--> No")