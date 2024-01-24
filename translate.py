import sys
#pip install googletrans
from googletrans import Translator

#https://www.youtube.com/watch?v=P1uHDPpe_04&ab_channel=codebasics

tr = Translator()

userText = ""

for x in sys.argv:
    userText += x
    userText += " "

#Getting our arguments in order, it's pretty crap code but it works so whatever ¯\_(ツ)_/¯

#Remove ../translate.py
userText = userText[16:]

#Creating dest from last 2 chars of userText
length = len(userText)
dest = userText[length - 3:]
dest = dest[:-1]

#Remove dest
userText = userText[:-3]

out = tr.translate(userText, dest=dest)

with open('../translation.txt', 'w') as file:
    file.write(out.text)
    
print(out.text)