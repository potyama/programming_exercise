import random

word = []
r = random.randint(1,1500)
f = open('toeic1500.dat')
word = f.read().splitlines()
print(word[r])
