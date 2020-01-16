# coding: utf-8

str = input()
ans = ""

for i in range(len(str)):
	if str[i].islower():
		ans += str[i]

print(ans)
