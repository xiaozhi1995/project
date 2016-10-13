#import turtle
#length=20
#angle=45
#count=0
#while count<5:
#    turtle.forward(length)
#    turtle.right(angle)
#    turtle.forward(length)
#    turtle.left(angle)
#    count+=1

#print("a:best b:good c:normal d:bad e:worst,Enter your option")
#s=input("Please input ")
#if s=="a":
#    print("you're best")
#elif s=="b":
#    print("you're good")
#elif s=="c":
#    print("you're normal")
#elif s=="d":
#    print("you're bad")
#elif s=="e":
#    print("you're worst")
#else:
#    print("your input isn't exist")

#import turtle
#turtle.color("red")
#turtle.penup()
#turtle.goto(0,50)
#turtle.pendown()
#turtle.circle(45)

#count=0
#while count<360:
#    turtle.forward(1)
#    turtle.right(1)
#    count+=1

import turtle
sides=6
angle=360.0/sides
length=400.0/sides

for side in range(sides):
    turtle.forward(length)
    turtle.right(angle)
turtle.done()
