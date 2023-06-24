# Solve the problem from the second set here


# Problem 2

def start():
    n = int(input("Enter a number for which you want to find out:"))

    return n


def find_twin():
    number = start()

    # the idea here is that we create the first number so that it is odd, because the only even prime number is 2
    # it's true that our input can be 1 so the first prime number checked is 2
    # but 3-2 is 1 and 5-2 is 3 which is already over 2
    # so it's impossible for 2 to be twin with any other prime number

    # if the input is odd, the p1 is gonna be even, so this is why the +1
    # if the input is even, p1 is even in any case

    p1 = number + number % 2 + 1

    # since we use natural numbers, we can assume that p2 is bigger than p1
    # so the immediately larger number is p1+2 in order to make it odd.

    p2 = p1 + 2

    # variable to store if the numbers are found or not
    found = False

    if number < 1:
        print("The number must be bigger than 1.")
        return None
    else:
        while found == False:
            if is_prime(p1) and is_prime(p2):
                if p2 - p1 == 2:
                    found = True
                    return p1, p2
            else:
                p1 = p2
                p2 = p1 + 2


def is_prime(nr):
    # function for finding if the numbers are prime

    prime = True

    if nr > 1:
        for i in range(2, nr):
            if nr % i == 0:
                prime = False
                break

    return prime


def print_result():
    result = find_twin()
    print("The numbers are: " + str(result))

print_result()