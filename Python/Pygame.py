'''import pygame

pygame.init()
windowSize=[400,300]
screen=pygame.display.set_mode(windowSize)
pygame.display.set_caption("RectGame")

colour=pygame.color.Color("#0A32F4")
done=False

while not done:
    pygame.draw.rect(screen,colour,[10,20,30,40])
    pygame.display.flip()
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            done=True
pygame.quit()
'''
'''
import pygame
pygame.init()

width=400
height=300
windowSize=[width,height]
screen=pygame.display.set_mode(windowSize)
colour=pygame.color.Color('#646400')
row=0
done=False
while not done:
    increment=255/100
    while row<=height:
        pygame.draw.rect(screen,colour,(0,row,width,row+increment))
        pygame.display.flip()
        if colour[2]+increment<255:
            colour[2]+=increment
        row+=increment
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            done=True

pygame.quit()
'''
'''
import random
import pygame
pygame.init()

width=400
height=300
windowSize=[width,height]
screen=pygame.display.set_mode(windowSize)
clock=pygame.time.Clock()
sqrW=width/10
sqrH=height/10

done=False
while not done:
    red=random.randrange(0,256)
    green=random.randrange(0,256)
    blue=random.randrange(0,256)
    x=random.randrange(0,width,sqrW)
    y=random.randrange(0,height,sqrH)
    pygame.draw.rect(screen,(red,green,blue),(x,y,sqrW,sqrH))

    pygame.display.flip()
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            done=True

    clock.tick(10)
pygame.quit()
'''
'''
import math
import pygame
pygame.init()

windowSize=[400,300]
screen=pygame.display.set_mode(windowSize)
clock=pygame.time.Clock()

width=200
height=200

x=windowSize[0]/2-width/2
y=windowSize[1]/2-height/2

colour=pygame.color.Color('#57B0F6')
black=pygame.color.Color('#000000')

count=0
done=False

while not done:
    screen.fill(black)
    pygame.draw.ellipse(screen,colour,[x,y,width,height])
    width+=math.cos(count)*10
    x-=(math.cos(count)*10)/2
    height+=(math.sin(count)*10)/2
    count+=0.5

    pygame.display.flip()

    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            done=True

    clock.tick(1000)

pygame.quit()
'''
'''
import pygame
pygame.init()
size=[400,300]
screen=pygame.display.set_mode(size)
clock=pygame.time.Clock()
done=False
while not done:
    keys=pygame.key.get_pressed()
    if keys[pygame.K_w]:
        print "hello"

    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            done=True
    clock.tick(32)
pygame.quit()
'''
import random
import pygame
pygame.init()
size=[400,300]
screen=pygame.display.set_mode(size)
clock=pygame.time.Clock()
x=size[0]/2
y=size[1]/2
ballX=random.randrange(0,size[0])
ballY=random.randrange(0,size[1])
goalX=size[0]/2-10
goalY=size[1]/2-10
goalW=20
goalH=20
points=0
red=pygame.color.Color('#FF8080')
blue=pygame.color.Color('#8080FF')
white=pygame.color.Color('#FFFFFF')
black=pygame.color.Color('#000000')


def checkOffScreenX(x):
    if x>size[0]:
        x=0
    elif x<0:
        x=size[0]
    return x

def checkOffScreenY(y):
    if y>size[1]:
        y=0
    elif y<0:
        y=size[1]
    return y
def checkTouching():
    global x
    global ballX
    global y
    global ballY
    if -10<y-ballY<10 and -10<x-ballX<10:
        pygame.draw.circle(screen,white,[x,y],15)

        xDiff=x-ballX
        yDiff=y-ballY
        if ballX==0:
            xDiff-=5
        elif ballX==size[0]:
            xDiff+=5
        if ballY==0:
            yDiff-=5
        elif ballY==size[1]:
            yDiff+=5

        x+=xDiff*3
        ballX-=xDiff*3

        y+=yDiff*3
        ballY-=yDiff*3
        
done=False
while not done:
    screen.fill(black)
    pygame.draw.rect(screen,white,(goalX,goalY,goalW,goalH))

    
    keys=pygame.key.get_pressed()
    if keys[pygame.K_w]:
        y-=1
    if keys[pygame.K_s]:
        y+=1
    if keys[pygame.K_a]:
        x-=1
    if keys[pygame.K_d]:
        x+=1

    x=checkOffScreenX(x)
    y=checkOffScreenY(y)
    ballX=checkOffScreenX(ballX)
    ballY=checkOffScreenY(ballY)
    checkTouching()
    

    for point in range(points):
        pointX=0+point*5
        pygame.draw.rect(screen,white,(pointX,3,4,10))

    pygame.draw.circle(screen,red,[x,y],6)
    pygame.draw.circle(screen,blue,[ballX,ballY],6)

    if goalX<=ballX<=goalX+goalW and goalY<=ballY<=goalY+goalH:
        points+=1
        ballX=random.randrange(0,size[0])
        ballY=random.randrange(0,size[1])
    pygame.display.flip()

    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            done=True
    clock.tick(72)
pygame.quit()
print "Total points:  "+str(points)
