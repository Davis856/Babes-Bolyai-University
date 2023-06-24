#
# Write the implementation for A2 in this file
#
import math  # for modulus


# UI section
# (write all functions that have input or print statements here). 
# Ideally, this section should not contain any calculations relevant to program functionalities


def print_menu():
    print("Complex number menu.")
    print("1. to show the number list.")
    print("2. to add numbers")
    print("3. to show the longest sequence of numbers which have the same modulus.")
    print("4. to show the longest sequence of consecutive numbers which have a prime number as a modulus difference")
    print("5. to exit")


def start():
    nr_list = init_number()

    while True:
        print_menu()
        option = input("Enter option:")

        if option == '1':
            show_numbers(nr_list)
        elif option == '2':
            add_number_ui(nr_list)
        elif option == '3':
            show_sequence()
        elif option == '4':
            show_sequence_diff()
        elif option == '5':
            break
        else:
            print("Invalid option")


def modulo_ui(nr_list):
    for numbr in nr_list:
        print(modulo(numbr))


def show_numbers(nr_list):
    index = 1
    for number in nr_list:
        print(str(index) + ") " + str(get_real(number)) + "+" + str(get_imaginary(number)) + "i")
        index += 1


def show_sequence():
    numbers = init_number()
    nrr = check_modulo()
    first = nrr[0]
    final = nrr[1]
    index = 1
    print("The longest sequence is:")
    for i in range(first, final + 1):
        print(str(index) + ") " + str(get_real(numbers[i])) + "+" + str(get_imaginary(numbers[i])) + "i")
        index += 1


def show_sequence_diff():
    numbers = init_number()
    num = modulo_difference_check()
    first_diff = num[0]
    final_diff = num[1]
    print("The longest sequence is:")
    index = 1
    for i in range(first_diff, final_diff + 1):
        print(str(index) + ") " + str(get_real(numbers[i])) + "+" + str(get_imaginary(numbers[i])) + "i")
        index += 1


def add_number_ui(number_list):
    # TODO find a better way to ask the user about the number and crash if value can't be converted
    real_part = int(input("Enter real part:"))
    imaginary_part = int(input("Enter imaginary part:"))

    num = create_number(real_part, imaginary_part)
    if num is None:
        print("Invalid number")
        return
    if not add_number(number_list, num):
        print("Number could not be added")


# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values

# print('Hello A2'!) -> prints aren't allowed here!


def create_number(real, imag):
    """
    Create a number
    :param real: Real part of the number
    :param imag: Imaginary part of the number
    :return: A newly created number
    """
    return [real, imag]


# getters and setters
def get_real(number):
    return number[0]


def get_imaginary(number):
    return number[1]


def modulo(nr):
    a = get_real(nr)
    b = get_imaginary(nr)
    mod = math.sqrt(a ** 2 + b ** 2)
    return mod


def check_modulo():
    # We find out the longest sequence and we use 2 variables, start_index and final_index to find out the range of it
    # and what indices to use to print the elements out
    numbr = init_number()

    longest = 0
    streak = 1

    start_index = 0
    final_index = 0

    for i in range(len(numbr) - 1):
        if modulo(numbr[i]) == modulo(numbr[i + 1]):
            streak += 1
            # if this is below is not used, the program will not show the correct results
            if streak > 1:
                longest = streak
                start_index = i - longest + 2  # our i goes up to 8 and we have 10 elements so 9 would be the last one
                final_index = i + 1  # same goes for here
                # which is why we increment it by 1 so that we can also get the last element
        else:
            if longest < streak:
                longest = streak
                start_index = i - longest + 1
                final_index = i
            streak = 1
    return start_index, final_index


def modulo_difference_check():
    # Same logic for exercise 7, but using different algorithm
    num = init_number()

    longest = 0
    streak = 1

    start_index = 0
    final_index = 0

    for i in range(len(num) - 1):
        difference = modulo(num[i]) - modulo(num[i + 1])
        if int(difference) == difference:
            if is_prime(int(difference)):
                streak += 1
                if streak > 1:
                    longest = streak
                    start_index = i - longest + 2
                    final_index = i + 1
            else:
                if longest < streak:
                    longest = streak
                    start_index = i - longest + 1
                    final_index = i
                streak = 1

    return start_index, final_index


def is_prime(nr):
    # function for finding if the numbers are prime

    flag = False  # flag is used to say "is the number not prime?", this is why if the flag is true we return false

    if nr > 1:
        for i in range(2, nr // 2):
            if nr % i == 0:
                flag = True
            break
    else:
        return False

    if flag:
        return False
    else:
        return True


def add_number(number_list, number):
    """
    Adds a new number to the list
    :param number_list: The list of numbers
    :param number: The new number
    :return: Add a number if success, False if number can't be added
    """
    for nr in number_list:
        if type(get_real(nr)) != int or type(get_imaginary(nr)) != int:
            return False
    number_list.append(number)
    return True


def init_number():
    """
    Create 10 numbers to have at the startup
    :return:
    """
    return [create_number(3, 4), create_number(2, 0), create_number(0, 0), create_number(2, 0),
            create_number(3, 1), create_number(2, 2), create_number(3, 4), create_number(3, 4),
            create_number(3, 4), create_number(3, 4)]


start()
