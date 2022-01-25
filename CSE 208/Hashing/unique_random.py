import random

random_words = list()
letters = list()

for i in range(26):
    letters.append(chr(i+ord('a')))


for i in range(20000):
    new_word = ''
    for j in range(7):
        new_word = new_word + random.choice(letters)
    random_words.append(new_word)

random_words = set(random_words)
random_words = list(random_words)
random_words = random_words[:10000]

print(len(random_words))

fhand = open('random_10000.txt','w')
for i in range(10000):
    fhand.write(random_words[i])
    fhand.write('\n')
fhand.close()


random.shuffle(random_words)

fhand = open('random_1000.txt','w')

for i in range(1000):
    fhand.write(random_words[i])
    fhand.write('\n')
fhand.close()
