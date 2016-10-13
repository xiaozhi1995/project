'''import Tkinter as tk
window=tk.Tk()

def buttonClick():
#    print "Beep!"
    button.config(text="Clicked!")
button=tk.Button(window,text="Click me!",command=buttonClick)
button.pack()
window.mainloop()
'''

'''import Tkinter as tk
window=tk.Tk()

count=0

def buttonCount():
    global count
    count+=1
    button.config(text=str(count))

button=tk.Button(window,text="count",command=buttonCount)
button.pack()
window.mainloop()
'''

'''import Tkinter as tk
window=tk.Tk()

def changeStr():
    stringCopy=entry.get()
    stringCopy=stringCopy[::-1]
    entry.delete(0,tk.END)
    entry.insert(0,stringCopy)

entry=tk.Entry(window)
button=tk.Button(window,text="StrChange",command=changeStr)

entry.pack()
button.pack()
window.mainloop()
'''

'''
import Tkinter as tk
window=tk.Tk()

def checkPassword():
    password="Apple"
    enterPass=passwordEntry.get()
    if enterPass == password:
        confirmLabel.config(text="Correct")
    else:
        confirmLabel.config(text="Incorrect")


passwordLabel=tk.Label(window,text="Password")
passwordEntry=tk.Entry(window,show="*")

button=tk.Button(window,text="Enter",command=checkPassword)
confirmLabel=tk.Label(window)

passwordLabel.pack()
passwordEntry.pack()
button.pack()
confirmLabel.pack()

window.mainloop()
'''

'''import Tkinter as tk
import random
window=tk.Tk()

def randomNoun():
    nouns=["cats","hippos","cakes"]
    noun=random.choice(nouns)
    return noun

def randomVerb():
    verbs=["eats","likes","hates","has"]
    verb=random.choice(verbs)
    return verb

def  buttonClick():
    name=nameEntry.get()
    verb=randomVerb()
    noun=randomNoun()
    sentence=name+" "+verb+" "+noun
    result.delete(0,tk.END)
    result.insert(0,sentence)

nameLabel=tk.Label(window,text="Name:")
nameEntry=tk.Entry(window)
button=tk.Button(window,text="Generate",command=buttonClick)
result=tk.Entry(window)

nameLabel.pack()
nameEntry.pack()
button.pack()
result.pack()
window.mainloop()
'''

'''
import random
import Tkinter as tk
window=tk.Tk()

maxNo=10
score=0
rounds=0

def buttonClick():
    global score
    global rounds
    try:
        guess=int(guessBox.get())
        if 0<guess<=maxNo:
            result=random.randrange(1,maxNo+1)
            if guess==result:
                score=score+1
            rounds+=1
        else:
            result="Entry not valid"
    except:
        result="Entry not valid"

    resultLabel.config(text=result)
    scoreLabel.config(text=str(score)+"/"+str(rounds))
    guessBox.delete(0,tk.END)

guessLabel=tk.Label(window,text="Enter a number from 1 to"+str(maxNo))
guessBox=tk.Entry(window)
resultLabel=tk.Label(window)
scoreLabel=tk.Label(window)
button=tk.Button(window,text="guess",command=buttonClick)

guessLabel.pack()
guessBox.pack()
resultLabel.pack()
scoreLabel.pack()
button.pack()

window.mainloop()'''


'''import Tkinter as tk
window=tk.Tk()

slider=tk.Scale(window,from_=0,to=100)
slider.pack()
tk.mainloop()
'''

'''import Tkinter as tk
window=tk.Tk()

colour="#FF0000"
canvas=tk.Canvas(window,height=300,width=300,bg=colour)
canvas.pack()
window.mainloop()
'''
'''
import Tkinter as tk
window=tk.Tk()

def sliderUpdate(source):
    red=redSlider.get()
    green=greenSlider.get()
    blue=blueSlider.get()
    
    colour="#%02x%02x%02x"%(red,green,blue)
    canvas.config(bg=colour)
    hexText.delete(0,tk.END)
    hexText.insert(0,colour)

redSlider=tk.Scale(window,from_=0,to=255,command=sliderUpdate)
greenSlider=tk.Scale(window,from_=0,to=255,command=sliderUpdate)
blueSlider=tk.Scale(window,from_=0,to=255,command=sliderUpdate)
canvas=tk.Canvas(window,width=200,height=200)
hexText=tk.Entry(window)

redSlider.grid(row=1,column=1)
greenSlider.grid(row=1,column=2)
blueSlider.grid(row=1,column=3)
canvas.grid(row=2,column=1,columnspan=3)
hexText.grid(row=3,column=1,columnspan=3)

tk.mainloop()  
'''

'''import Tkinter as tk
import time
window=tk.Tk()

clicks=0
start=0
goal=10

def buttonClick():
    global clicks
    global start

    if clicks==0:
        start=time.time()
        clicks=clicks+1
    elif clicks+1>=goal:
        score=time.time()-start
        label.config(text="Time: "+str(score))
        clicks=0
    else:
        clicks=clicks+1
    slider.set(clicks)

button=tk.Button(window,text="Click me",command=buttonClick)
slider=tk.Scale(window,from_=0,to=goal)
label=tk.Label(window)
button.pack()
slider.pack()
label.pack()
window.mainloop()
'''
