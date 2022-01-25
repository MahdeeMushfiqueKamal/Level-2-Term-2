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


Add students
```python
import random
fhand = open('Full_Names.txt')
NAMES = list()

for line in fhand.readlines():
    line = line.strip()
    NAMES.append(line)
fhand.close()

fhand = open('StudentQueries.sql','w')
DAY = range(1,29)
MONTH = range(1,13)
YEAR = [2000,2001]
LOCATION = ['BUET','RUET','CUET','SUST']
HSC_ROLL_pool = range(1234567,9999999)
HSC_REG_pool = range(123456789, 400000000)

HSC_ROLL = list()
HSC_REG = list()

for i in range(40000):
    HSC_ROLL.append(random.choice(HSC_ROLL_pool))
    HSC_REG.append(random.choice(HSC_REG_pool))

HSC_ROLL = list(set(HSC_ROLL))
HSC_REG = list(set(HSC_REG))


for i in range(7000):
    birthday = str(random.choice(DAY))+'/'+str(random.choice(MONTH))+'/'+str(random.choice(YEAR))
    quota_status ='\'Y\'' if 'Chakma' in NAMES[i] or 'Marma' in NAMES[i] else '\'N\''
    center_id = 'KUET'

    querystr = 'INSERT INTO STUDENT(HSC_ROLL,HSC_REG,NAME,BIRTHDATE,QUOTA_STATUS,CENTER_ID) VALUES('+ str(HSC_ROLL[i])+','+ str(HSC_REG[i])+',\''+NAMES[i].strip()+'\',\''+birthday+'\','+quota_status+',\''+center_id+'\');\n'
    fhand.write(querystr)
    querystr = 'UPDATE EXAM_CENTER SET FILLED = (SELECT FILLED FROM EXAM_CENTER WHERE CENTER_ID=\''+ center_id +'\' ) + 1 WHERE CENTER_ID=\''+center_id+'\';\n' 
    fhand.write(querystr)

for i in range(7001,len(NAMES)):
    birthday = str(random.choice(DAY))+'/'+str(random.choice(MONTH))+'/'+str(random.choice(YEAR))
    quota_status ='\'Y\'' if 'Chakma' in NAMES[i] or 'Marma' in NAMES[i] else '\'N\''
    center_id = random.choice(LOCATION)
    
    querystr = 'INSERT INTO STUDENT(HSC_ROLL,HSC_REG,NAME,BIRTHDATE,QUOTA_STATUS,CENTER_ID) VALUES('+ str(HSC_ROLL[i])+','+ str(HSC_REG[i])+',\''+NAMES[i].strip()+'\',\''+birthday+'\','+quota_status+',\''+center_id+'\');\n'
    fhand.write(querystr)
    querystr = 'UPDATE EXAM_CENTER SET FILLED = (SELECT FILLED FROM EXAM_CENTER WHERE CENTER_ID=\''+ center_id +'\' ) + 1 WHERE CENTER_ID=\''+center_id+'\';\n' 
    fhand.write(querystr)

```