str1=input()
str2=input()

def compararStrings(str1,str2):
    if(str1==str2):
        return True
    elif len(str1)<=1:
         return str1==str2
    elif len(str1)!=len(str2):
            return False
    elif len(str1)%2==1:
        return False

    mid= len(str1)//2 

    return (compararStrings(str1[:mid], str2[mid:]) and compararStrings(str1[mid:], str2[:mid])) or (compararStrings(str1[:mid], str2[:mid])and compararStrings(str1[mid:], str2[mid:]))  

if compararStrings(str1,str2):
     print("YES")
else:
     print("NO")