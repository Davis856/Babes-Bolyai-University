"""
  Write non-UI functions below
"""

import re


def create_contestant(p1, p2, p3):
    """
    Creates a new contestant
    :param p1: first mark of the problem
    :param p2: second mark of the problem
    :param p3: third mark of the problem
    :return: A newly created contestant, error if the contestant cannot be created.
    """
    return [p1, p2, p3]


def test_create_contestant():
    assert (create_contestant(1, 2, 3))
    assert (create_contestant(10, 20, 30))
    assert (create_contestant(20, 'a', 10))


test_create_contestant()


def add_contestant(cont_list, cont):
    """
    Adds a new contestant to the list
    :param cont_list: The list of contestants
    :param cont: The new contestant to add
    :return: Adds a contestant if success, False if contestant can't be added
    """
    cont_list.append(cont)


"""
def test_add_contestant():
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 3, 2),
                 create_contestant(10, 5, 3), create_contestant(7, 3, 6), create_contestant(1, 2, 5),
                 create_contestant(9, 6, 5), create_contestant(5, 8, 10), create_contestant(9, 6, 10),
                 create_contestant(1, 1, 1)]
    assert(add_contestant(test_list, [3, 3, 3]))
    assert(add_contestant(test_list, (2, 2, 2)))
"""


def insert_contestant(cont_list, cont, index):
    """
    Adds a new contestant to a chosen position in the list
    :param cont_list: The list of contestants
    :param cont: The new contestant to add
    :param index: Position
    :return: Inserts the contestant to the desired position if the position is empty
                or if the other contestant is removed (marks are all 0)
    """
    # for contestant in cont_list:
    # if not (get_mark1(contestant) or get_mark2(contestant) or get_mark3(contestant)):
    # raise ValueError("Unable to insert, make sure all of the marks are added or the index is mentioned")
    cont_list.insert(index, cont)


"""
def test_insert_contestant():
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 3, 2),
                 create_contestant(10, 5, 3), create_contestant(7, 3, 6), create_contestant(1, 2, 5),
                 create_contestant(9, 6, 5), create_contestant(5, 8, 10), create_contestant(9, 6, 10),
                 create_contestant(1, 1, 1)]

    assert(insert_contestant(test_list, [3, 3, 3], 5))
    assert(insert_contestant(test_list, [5, 3, 3], 7))


test_insert_contestant()
"""


def remove_contestants(conts_list, index):
    """
    "Removes" a contestant by switching all marks to 0
    :param conts_list: The list of contestants
    :param index: The position of the contestant
    :return: Sets all the marks of the <>contestant to 0
    """
    if conts_list[index] == [0, 0, 0]:
        raise ValueError("Unable to remove contestant, make sure it is not already removed")
    else:
        conts_list[index] = [0, 0, 0]


"""
def test_remove_contestants():
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 3, 2),
                 create_contestant(10, 5, 3), create_contestant(7, 3, 6), create_contestant(1, 2, 5),
                 create_contestant(9, 6, 5), create_contestant(5, 8, 10), create_contestant(9, 6, 10),
                 create_contestant(1, 1, 1)]
    assert (remove_contestants(test_list, 2))
    assert (remove_contestants(test_list, 5))


test_remove_contestants()
"""


def remove_more_contestants(conts_list, first_index, last_index):
    """
    Removes a contestant from a given position to another one
    :param conts_list: The list of contestants
    :param first_index: First position from which to remove
    :param last_index: Last position to remove
    :return:
    """
    for i in range(first_index, last_index):
        conts_list[i] = [0, 0, 0]


"""
def test_remove_more_contestants():
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 3, 2),
                 create_contestant(10, 5, 3), create_contestant(7, 3, 6), create_contestant(1, 2, 5),
                 create_contestant(9, 6, 5), create_contestant(5, 8, 10), create_contestant(9, 6, 10),
                 create_contestant(1, 1, 1)]
    assert (remove_more_contestants(test_list, 2, 5))
    assert (remove_more_contestants(test_list, 3, 8))


test_remove_more_contestants()
"""


def replace_marks(conts_list, index, prob, marks):
    """
    Replaces a contestant's marks by changing the old ones with the new input ones
    :param conts_list: The list of contestants
    :param index: The position of the contestant
    :param prob: The problem (P1, P2, P3)
    :param marks: The new mark
    :return: Sets all marks of the contestant to new ones
    """
    if conts_list[index]:
        if prob == 'P1':
            m2 = get_mark2(conts_list[index])
            m3 = get_mark3(conts_list[index])
            conts_list[index] = [marks, m2, m3]
        elif prob == 'P2':
            m1 = get_mark1(conts_list[index])
            m3 = get_mark3(conts_list[index])
            conts_list[index] = [m1, marks, m3]
        elif prob == 'P3':
            m1 = get_mark1(conts_list[index])
            m2 = get_mark2(conts_list[index])
            conts_list[index] = [m1, m2, marks]
        else:
            raise ValueError("Problem doesn't exist!")
    else:
        raise ValueError("Could not replace given contestant's marks, make sure the contestant exists")


"""
def test_replace_marks():
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 3, 2),
                 create_contestant(10, 5, 3), create_contestant(7, 3, 6), create_contestant(1, 2, 5),
                 create_contestant(9, 6, 5), create_contestant(5, 8, 10), create_contestant(9, 6, 10),
                 create_contestant(1, 1, 1)]
    assert (replace_marks(test_list, 4, 'P1', 3))
    assert (replace_marks(test_list, 2, 'P2', 5))


test_replace_marks()
"""


def contestant_init():
    """
    Creates some marks to be used at startup
    :return: A list of marks
    """
    return [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 3, 2),
            create_contestant(10, 5, 3), create_contestant(7, 3, 6), create_contestant(1, 2, 5),
            create_contestant(9, 6, 5), create_contestant(5, 8, 10), create_contestant(9, 6, 10),
            create_contestant(1, 1, 1)]


def test_contestant_init():
    assert (contestant_init())


test_contestant_init()


def contestant_average(cont):
    """
    Gets average of a contestant's marks
    :return: Average
    """
    m1 = get_mark1(cont)
    m2 = get_mark2(cont)
    m3 = get_mark3(cont)
    average = (m1 + m2 + m3) / 3

    return average


"""
def test_contestant_average():
    assert(contestant_average([3, 3, 3]))

test_contestant_average()
"""


# getters and setters zone
def get_mark1(mark):
    return int(mark[0])


def get_mark2(mark):
    return int(mark[1])


def get_mark3(mark):
    return int(mark[2])


##############################


# command related
def split_command(command):
    """
    Divide user input into command word and command parameters
    :param command: User command
    :return: Tuple of (<command word>,<command parameters>)
    """
    command = command.strip()
    splits = command.split(" ", maxsplit=1)
    command_word = splits[0]
    command_param = splits[1] if len(splits) == 2 else None
    return command_word, command_param


def test_split_command():
    assert split_command('add 1 2 1') == ('add', '1 2 1')
    assert split_command('add 1 2 1; 2 2 1') == ('add', '1 2 1; 2 2 1')
    assert split_command('insert 2 2 2 at 5') == ('insert', '2 2 2 at 5')
    assert split_command('remove 1') == ('remove', '1')
    assert split_command('remove 2 to 3') == ('remove', '2 to 3')
    assert split_command('replace 2 P1 with 5') == ('replace', '2 P1 with 5')
    assert split_command('list') == ('list', None)
    assert split_command('exit') == ('exit', None)


test_split_command()


############################

def show_contestants_property_smaller(conts_list, prop):
    """
    Sorts the marks of the contestants by a property given (<)
    :param conts_list: The list of contestants with an average smaller than asked
    :param prop: Property
    :return: Sorted list by the property
    """
    new_conts_list = []
    contestants = 0
    for conts in conts_list:
        average = contestant_average(conts)
        if average < float(prop):
            new_conts_list.append(conts)
            contestants += 1
    if contestants > 0:
        return new_conts_list
    else:
        raise ValueError("List cannot be shown: there is no contestant with an average smaller than asked for.")


def show_contestants_property_bigger(conts_list, prop):
    """
    Sorts the marks of the contestants by a property given (>)
    :param conts_list: The list of contestants with an average bigger than asked for
    :param prop: Property
    :return: Sorted list by the property
    """
    new_conts_list = []
    contestants = 0
    for conts in conts_list:
        average = contestant_average(conts)
        if average > float(prop):
            new_conts_list.append(conts)
            contestants += 1
    if contestants > 0:
        return new_conts_list
    else:
        raise ValueError("List cannot be shown: there is no contestant with an average bigger than asked for.")


def show_contestants_property_equal(conts_list, prop):
    """
    Sorts the marks of the contestants by a property given (=)
    :param conts_list: The list of contestants with an average equal to what is asked for
    :param prop: Property
    :return: Sorted list by the property
    """
    new_conts_list = []
    contestants = 0
    for conts in conts_list:
        average = contestant_average(conts)
        if average == float(prop):
            new_conts_list.append(conts)
            contestants += 1
    if contestants > 0:
        return new_conts_list
    else:
        raise ValueError("List cannot be shown: there is no contestant with an average equal to what asked for.")


"""
  Write the command-driven UI below
"""


def print_commands():
    print("\nCommand-driven menu to administrate contestants")
    print("Commands are as following:")
    print("add - to add a new contestant")
    print("insert - to add a new contestant at a given position")
    print("list - to show the list of contestants")
    print("remove - to remove a contestant from the list")
    print("replace - to replace a contestant's marks")
    print("exit - to exit the menu")


def start_menu():
    """
    add 5, 7, 10 - adds the score of the 3 problems
    insert 5 1 9 at 3 - inserts the given scores at the 3rd element of the list
    remove <index> - removes the scores of the participant at position <index>
    remove <start_index> to <end_index> - removes each participant's score from the start to the end of the positions
    replace <old score> at <score> with <new score> - replaces the score obtained by the participant for a given prob
    list - displays the list of participants and their scores
    list sorted - displays the list of participants in decreasing order of average score
    list [ < | = | > ] <score> - lists the participants which have < mark or = mark or > mark
    """
    contestant_list = contestant_init()

    while True:
        print_commands()

        command = input("command: ")
        command_word, command_params = split_command(command)

        try:
            if command_word == 'add':
                add_contestant_command(contestant_list, command_params)
            elif command_word == 'insert':
                insert_contestant_command(contestant_list, command_params)
            elif command_word == 'list':
                show_contestants_command(contestant_list, command_params)
            elif command_word == 'remove':
                remove_contestant_command(contestant_list, command_params)
            elif command_word == 'replace':
                replace_contestant_command(contestant_list, command_params)
            elif command_word == 'exit':
                return
            else:
                print("Unknown command!")
        except ValueError as ve:
            print(str(ve))


# commands-related
def add_contestant_command(cont_list, param):
    """
    Adds a new contestant to the list
    :param cont_list: The list of contestants
    :param param: The new contestant to add
    :return: Adds a contestant if success, False if contestant can't be added
    """
    if not param:
        raise ValueError("error: usage: add <p1 score> <p2 score> <p3 score>")
    new_contestant = param.split("; ")
    for conts in new_contestant:
        m1, m2, m3 = conts.split(" ")
        if int(m1) and int(m2) and int(m3):
            if int(m1) < 0 or int(m2) < 0 or int(m3) < 0:
                raise ValueError("One of the marks or more are lower than 0")
            elif int(m1) > 10 or int(m2) > 10 or int(m3) > 10:
                raise ValueError("One of the marks or more are higher than 10")
            try:
                add_contestant(cont_list, create_contestant(int(m1), int(m2), int(m3)))
                print("Contestant added successfully")
            except ValueError as ve:
                print("Contestant could not be added: " + m1, m2, m3 + ". Make sure all of the marks are integers"
                                                                       " smaller than 0 or higher than 10")
        else:
            raise ValueError("Cannot add contestant: one of the marks is missing.")


def insert_contestant_command(cont_list, param):
    """
    Inserts a new contestant to the list in a given position
    :param cont_list: The list of contestants
    :param param: The new contestant to insert
    :return: Inserts a contestant if success, False is contestant can't be inserted
    """
    if not param:
        raise ValueError("error: usage: insert <p1 score> <p2 score> <p3 score> at <position>")
    new_contestant = param.split("; ")
    for contest in new_contestant:
        m1, m2, m3, index = re.findall(r'\d+', contest)
        if int(m1) and int(m2) and int(m3) and int(index):
            try:
                insert_contestant(cont_list, create_contestant(m1, m2, m3), int(index) - 1)
                print("Contestant has been inserted successfully")
            except ValueError as ve:
                print("Contestant could not be inserted " + m1, m2, m3 + " at position: " + str(index) +
                      ". Make sure all of the marks are added or the index is mentioned")
        else:
            raise ValueError("Cannot add contestant: one of the marks is missing or the position is not specified")


def show_contestants_command(cont_list, param):
    """
    Shows the contestants, either as they are or ordered or by a property(see start_menu)
    :param cont_list: The list of contestants
    :param param: params to configure the command list
    :return: Shows the list in the chosen manner, raises ve if crash
    """
    if not param:
        show_contestants(cont_list)
    else:
        if param == "sorted":
            print("Your ordered list is:")
            show_contestants_sorted(cont_list)
        else:
            new_contest = param.split("; ")
            for contest in new_contest:
                split = contest.split(" ")
                if len(split) == 2:
                    param = split[0]
                    prop = split[1]
                else:
                    raise ValueError("There is no number set or the property is not accepted")
                if param == "<":
                    index = 1
                    try:
                        print("Here is the list")
                        new_list = show_contestants_property_smaller(cont_list, prop)
                        for i in range(len(new_list)):
                            print("Contestant " + str(index) + " : " + str(new_list[i]))
                            index += 1
                    except ValueError as ve:
                        print("List cannot be shown: there is no contestant with an average smaller than asked for")
                elif param == ">":
                    index = 1
                    try:
                        print("Here is the list")
                        new_list = show_contestants_property_bigger(cont_list, prop)
                        for i in range(len(new_list)):
                            print("Contestant " + str(index) + " : " + str(new_list[i]))
                            index += 1
                    except ValueError as ve:
                        print("List cannot be shown: there is no contestant with an average bigger than asked for")
                elif param == "=":
                    index = 1
                    try:
                        print("Here is the list")
                        new_list = show_contestants_property_equal(cont_list, prop)
                        for i in range(len(new_list)):
                            print("Contestant " + str(index) + " : " + str(new_list[i]))
                            index += 1
                    except ValueError as ve:
                        print("List cannot be shown: there is no contestant with average equal to what was asked for")
                else:
                    raise ValueError("There is no number set or the property is not accepted.")


def remove_contestant_command(cont_list, param):
    """
    Removes a contestant by switching his marks to 0
    :param cont_list: The list of contestants
    :param param: params to configure the command
    :return: Removes a contestant if success, raises ve if crash
    """
    if not param:
        raise ValueError("error: usage: remove <position> or remove <start position> to <end position>")
    else:
        number = param.split(" ")
        if len(number) == 1:
            index = int(number[0])
            if index <= len(cont_list):
                try:
                    remove_contestants(cont_list, index - 1)
                    print("Contestant removed successfully!")
                    show_contestants(cont_list)
                except ValueError as ve:
                    print("Could not remove contestant at " + str(index) + ". Make sure it is not already removed")
            else:
                print("Error: contestant does not exist!")
        elif len(number) == 3:
            first_index = int(number[0])
            last_index = int(number[2])
            if first_index <= len(cont_list) and last_index <= len(cont_list):
                try:
                    remove_more_contestants(cont_list, first_index - 1, last_index)
                    print("Contestants removed successfully!")
                    show_contestants(cont_list)
                except ValueError as ve:
                    print("Could not remove contestants.")
            elif first_index <= len(cont_list) <= last_index:
                print("Make sure all the contestants exist first!")
            elif first_index >= len(cont_list) and last_index >= len(cont_list):
                print("The first contestant doesn't exist, therefore nothing can be removed!")


def replace_contestant_command(cont_list, param):
    """
    Replaces a contestant's marks with the new input
    :param cont_list: The list of contestants
    :param param: params to configure the command
    :return:Replaces a contestant if success, raises ve if crash
    """
    if not param:
        raise ValueError("usage: replace <position> <problem_no> with <new_mark>")
    else:
        params = param.split(" ")
        if len(params) == 4:
            index = int(params[0])
            if index <= len(cont_list):
                problem = params[1]
                new_mark = int(params[3])
                if new_mark < 0:
                    raise ValueError("New mark is lower than 0, insert another one")
                elif new_mark > 10:
                    raise ValueError("New mark is higher than 10, insert another one")
                try:
                    replace_marks(cont_list, index - 1, problem, new_mark)
                    print("Contestant's marks replaced successfully.")
                    show_contestants(cont_list)
                except ValueError as ve:
                    print("Could not replace given contestant's marks, make sure the contestant or the problem exists")
            else:
                print("Error: the contestant does not exist!")
        else:
            print("Error: could not get problem number or new mark, make sure everything is written")
            print("usage: replace <position> <problem_no> with <new_mark>")


#############################


def show_contestants(conts_list):
    """
    Shows the list of the contestants
    :return: A list of contestants
    """
    index = 1
    for conts in conts_list:
        print("Contestant " + str(index) + " marks: " + str(get_mark1(conts)) + " " + str(get_mark2(conts))
              + " " + str(get_mark3(conts)))
        index += 1


def show_contestants_sorted(conts_list):
    """
    Displays the list of the contestants in a decreasing order
    :param conts_list: The list of contestants
    :return:
    """
    new_conts_list = sort_marks(conts_list)
    new_conts_list_format = ['%.2f' % elem for elem in new_conts_list]
    index = 1
    for i in range(len(conts_list)):
        print("Contestant " + str(index) + " with an average of: " + str((new_conts_list_format[i])))
        index += 1


def sort_marks(conts_list):
    """
    Sorts the marks of the contestants to be shown in show_contestants_sorted
    :return: Sorted list
    """
    average_mark = []
    for conts in conts_list:
        average = contestant_average(conts)
        average_mark.append(average)

    new_conts_list = sorted(average_mark, reverse=True)

    return new_conts_list


start_menu()
