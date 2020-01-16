str = input("str=")

check = input("check=")

ans = "No"

for i in range(len(str)):
    if str[i] == check:
        ans = "Yes"

print(ans)
