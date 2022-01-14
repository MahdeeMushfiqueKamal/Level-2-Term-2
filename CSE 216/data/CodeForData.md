# Generate SUbject names 
```python
from os import sep


fhand1 = open('sub.txt')
for line in fhand1.readlines():
    line = line.split(',')
    #print('cur.execute(\'\'\'INSERT INTO SUBJECT(SUB_ID,NAME) VALUES(\'',line[0],'\',\'',line[1].strip(),'\');\'\'\')',sep='')
    print('INSERT INTO SUBJECT(SUB_ID,NAME) VALUES(\'',line[0],'\',\'',line[1].strip(),'\');',sep='')
fhand1.close()
```

# Generate Uni-Sub
```python
from os import sep


fhand1 = open('uni_sub.csv')
for line in fhand1.readlines():
    line = line.split(',')
    #print('cur.execute(\'\'\'INSERT INTO UNI_SUB(UNI_ID,SUB_ID,CAPASITY,QUOTA_CAPASITY) VALUES(\'',line[0],'\',\'',line[1],'\',\'',line[2],'\',\'',line[3].strip(),'\');\'\'\')',sep='')
    print('INSERT INTO UNI_SUB(UNI_ID,SUB_ID,CAPASITY,QUOTA_CAPASITY) VALUES(\'',line[0],'\',\'',line[1],'\',\'',line[2],'\',\'',line[3].strip(),'\');',sep='')
fhand1.close()
```

# Generate random names
```python
import random

fhand1 = open('Full_Names.txt','w')
bfn = open('BoyFirstName.txt')
gfn = open('GirlFirstName.txt')
bln = open('BoyLastName.txt')
gln =open('GirlLastName.txt')

BFN = bfn.readlines()
GFN = gfn.readlines()
BLN = bln.read().split(',')
GLN = gln.read().split(',')

for i in range(20000):
    name = str(random.choice(BFN)).strip() + ' '+ str(random.choice(BLN)).strip() + '\n'
    fhand1.write(name)

for i in range(12000):
    name = str(random.choice(GFN)).strip() + ' '+ str(random.choice(GLN)).strip() + '\n'
    fhand1.write(name)

```