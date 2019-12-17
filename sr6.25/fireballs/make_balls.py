import random

randnum = list()
for i in range(0, 99):
    randnum.append(random.randrange(-10, 10))

sum = 0
for i in range(0, 99):
    sum += randnum[i]
  
print (sum)
for i in range(0, 99):
    print(f'{randnum[i]}, ', end = '')