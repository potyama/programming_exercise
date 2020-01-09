st = input("str = ")
check = input("check = ")
ans = ""
flag = 0
for i in range(len(st)):
    if st[i] == check:
        flag = 1
        ans += str(i)
        ans += ' '

if flag == 0:
    print(-1)
else:
    print(ans)


#関数使うと

st2 = list(st)

ans = [i for i, x in enumerate(st2) if x == check]
if ans == [] :
    print(-1)
else :
    print(ans)
