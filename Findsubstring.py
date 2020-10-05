from itertools import combinations

def ConvertTupletoString(tuple) :
	str = ''.join(tuple)
	return str
		
#derived code
str1 = input("Enter String-1 : ")
str2 = input("Enter String-2 : ")

str1len = len(str1)
str2len = len(str2)

i = 1
y = 0
n = 0
while i <= str1len :
	LIST = combinations(str1, i)
	for j in list(LIST) :
		y += 1
		TempStr = ConvertTupletoString(j)
		x = TempStr.find(str2)
		if(x != -1) :
			n += 1
	i += 1
	
print("number of unmatched string : ", y-n)