import pygame # It loads pygame library in your sytem or we can say add it to your system . It consist of tools for making a pygame.
import sys # It loads sys library in our system . It is used for manipulating OS.
pygame.init() # It starts all the pygame module which are needed for a making a game .
screen = pygame.display.set_mode((700,400)) # here screen  acts as a variable for manipulating display . here pygame.display creates a window . here set_mode creates a window of width 800 and height 400
pygame.display.set_caption('first game') # It sets the caption of the window to 'first game'
clock=pygame.time.Clock()
sky_surface= pygame.image.load('/home/lavesh/DSA/Games/sky-background-video-conferencing_23-2148623067.jpg').convert_alpha() # It loads an image from the specified file path and converts it for optimal display with per-pixel alpha transparency.
scaled_image=pygame.transform.scale(sky_surface,(2000,1800)) # It scales the image to the specified width and height (300x200 pixels in this case).
ground_surface=pygame.image.load('/home/lavesh/DSA/Games/4d47cf9d991b73ed537f452748f539c6.jpg')
scaled_ground=pygame.transform.scale(ground_surface,(905,100))
character_surface=pygame.image.load('/home/lavesh/DSA/Games/—Pngtree—chameleon on white background_9137688.png') 
character_x_pos=3
while True: 
    for event in pygame.event.get(): # here event is instruction given by user so for check all this events onde by one 
       if event.type==pygame.QUIT: # Every event have a type here pygame.Quit is an event  and Quit is type of that event for closing the window 
           pygame.quit() # It quits all the pygame modules .
           exit() # It completely quits the program.
    screen.blit(sky_surface,(0,0))
    screen.blit(scaled_ground,(0,360))
    character_x_pos+=1
    if character_x_pos>700:
        character_x_pos=0   
    screen.blit(character_surface,(character_x_pos,250))

    pygame.display.update() # It continuously update whatever you do on the screen.
    clock.tick(60)
