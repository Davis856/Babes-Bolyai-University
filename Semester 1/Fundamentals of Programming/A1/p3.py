# Solve the problem from the third set here

def solve(n):
    i = 1
    numbers = 0

    # we create the main function in order to find out the number requested

    while numbers < n:
        if i == 1:
            numbers += 1
            number = i

            if numbers == n:
                return number

        elif i == 2:
            numbers += 1
            number = i

            if numbers == n:
                return number
        # function to find out the prime divisors
        else:
            copy_i = i
            for j in range(2, copy_i // 2 + 1):
                if copy_i % j == 0:

                    while copy_i % j == 0:
                        copy_i = copy_i // j

                    number = j
                    for q in range(0, j):
                        numbers += 1
                        if numbers == n:
                            return number

            if copy_i != 1:
                numbers += 1
                number = i
                if numbers == n:
                    return number

        i += 1


def read_input():
    return int(input("Enter a number:"))


def print_result(n):
    result = solve(n)
    print(result)


n = read_input()
print_result(n)
