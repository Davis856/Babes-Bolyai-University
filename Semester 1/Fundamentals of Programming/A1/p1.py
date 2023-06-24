# Solve the problem from the first set here

# Problem 4

def start():
    n = int(input("Enter a number: "))

    return n

# We create a function to search each apparition of the digit so that we can store them in a list
def search_digits():
    number = start()
    digits = [0, 0, 0, 0, 0, 0, 0, 0, 0,
              0]  # we create a list for digits so that we can see which one is present in the given number
    while number:
        digits[number % 10] = digits[number % 10] + 1  # we increment by 1 each apparition of the digit
        number = (number // 10)

    return digits


def max_number():
    digit_list = search_digits()
    m = 0  # variable used to find the requested number
    p = 1
    # variable used to be able to place each digit in the front of the number in for
    # we increment it by 10 so we can form the number

    for i in range(len(digit_list)):
        if digit_list[i]:
            while digit_list[i]:
                m = m + p * i
                p = p * 10
                digit_list[i] = digit_list[i] - 1

    return m


# We're printing the result of the program using a function
def result():
    number = max_number()
    print("The biggest number you can get from your input is " + str(number))


result()
