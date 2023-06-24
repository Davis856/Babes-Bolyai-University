"""
Implement the solution here. 
You may add other source files.
Make sure you commit & push the source code before the end of the test.

Solutions using user-defined classes will not be graded.
"""
import random


def generate_number():
    """
    Generates random 4 digit secret numbers, the first digit is non-zero and all digits are distinct
    :return: Generated numbers
    """
    first_digit = set(range(10))
    some_digits = random.randint(1, 9)
    digits_3 = random.sample(first_digit - {some_digits}, 3)
    number = str(some_digits) + ''.join(map(str, digits_3))
    return number


def check_number(option):
    """
    Checks if number is correct so that it can play
    :param option:
    :return:
    """
    nr = []
    while option:
        digit = option % 10
        option //= 10
        nr.append(digit)
    for i in range(len(nr) - 1):
        for j in range(i+1, len(nr)):
            if nr[i] == nr[j]:
                return False
    return True


def check_digits(option, generated_number):
    nr = []
    nr2 = []
    while option:
        digit = option % 10
        option //= 10
        nr.append(digit)
    while generated_number:
        digit2 = generated_number % 10
        generated_number //= 10
        nr2.append(digit2)

    nr.reverse()
    nr2.reverse()

    codes = 0
    runners = 0

    for i in range(len(nr)):
        for j in range(len(nr2)):
            if nr[i] == nr2[j] and i == j:
                codes += 1
            elif nr[i] == nr2[j] and i != j:
                runners += 1
    return codes, runners
