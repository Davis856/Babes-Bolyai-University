import code_runners
import datetime


def start():
    print("Guess the number game!")
    print("Please, pick a number!")
    print("You have 60 seconds!")
    print("Or press 1 to exit!")


def start_menu():
    start()
    opt = input()
    result = code_runners.generate_number()
    if opt == '8086':
        print("Congratulations, you found the cheat code!")
        print("Here is the number!")
        print(result)
        start_menu()
    elif len(opt) == 4:
        if code_runners.check_number(int(opt)):
            choices = code_runners.check_digits(int(opt), int(result))
            codes = choices[0]
            runners = choices[1]
            print("Your number is " + opt + " and it has " + str(codes) + " codes" + " and " + str(runners) + " runners")
            start_menu()
        else:
            print("Wrong number, please choose another one which has 4 digits and all the digits are different")
            start_menu()
    elif 5 <= len(opt) or len(opt) <= 3:
        print("Wrong number, please choose another one which has 4 digits and all the digits are different!")
        print("Computer wins!")
        start_menu()
    elif opt == '1':
        return


start_menu()
