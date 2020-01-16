import random

word =[]
f = open('toeic1500.dat').readlines()
r = random.choice(f).split()
print(r[1])
