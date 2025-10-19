import pygame # It loads pygame library in your sytem or we can say add it to your system . It consist of tools for making a pygame.
import sys # It loads sys library in our system . It is used for manipulating OS.
pygame.init() # It starts all the pygame module which are needed for a making a game .
screen = pygame.display.set_mode((800,400)) # here screen  acts as a variable for manipulating display . here pygame.display creates a window . here set_mode creates a window of width 800 and height 400
while True : # It creates a loop which keeps window on and True is as until  condition is true
    for event in pygame.event.get(): # here event is instruction given by user so for check all this events onde by one 
       if event.type==pygame.QUIT: # Every event have a type here pygame.Quit is an event  and Quit is type of that event for closing the window 
           pygame.quit() # It quits all the pygame modules .
           exit() # It completely quits the program.
    pygame.display.update() # It continuously update whatever you do on the screen.



    