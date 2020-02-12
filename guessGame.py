## Make a guess from 1 t0 20 (only numbers no words)
## you have three chances for guess  


import random 
flag = False

#checking if invalid input given
def exception(check):
     try:
         int(check)
     except ValueError:
         print("\nEnter a valid number!!")
         return True
     return False
 
#main function
def _game ():
    # declare flag as global for use
    global flag
    # to generate random no
    rand_num = random.randint(1,20)
    # giving the user 3 chances to guess
    for guess_chance in range(3):
        guess = input("Enter your guess: ")
        
        #until valid input is given
        #ask for valid input again and again
        while(exception(guess)):
                guess = input("Enter your guess again: ")

        if(int(guess)==rand_num):
            flag = True
            break
        else:
            if(guess_chance<2):
                print("Try again!")   ## if you need to check print("Number was {0} Your guess was {1}".format(rand_num,guess))
    return rand_num


number=_game()
if(flag):
        print("\nCongrats You Won!! You guessed Correctly!!")
else:
        print("\nOut of guess chances.\nYou lost! The number was {}.".format(number))

