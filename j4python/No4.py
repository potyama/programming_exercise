str = ""
flag = 0
count = int(input("count = "))
for i in range(count):
    a = input()

    if str.find(a) == -1:
        str += a
    flag = 0
    print("str = "+ str)

