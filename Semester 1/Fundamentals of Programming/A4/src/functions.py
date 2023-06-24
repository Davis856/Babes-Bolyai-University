"""
  Program functionalities module
"""


# getters and setters zone
def get_mark1(mark):
    return int(mark[0])


def get_mark2(mark):
    return int(mark[1])


def get_mark3(mark):
    return int(mark[2])


def set_mark1(mark, value):
    mark[0] = value
    return mark[0]


def set_mark2(mark, value):
    mark[1] = value
    return mark[1]


def set_mark3(mark, value):
    mark[2] = value
    return mark[2]


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


def test_add_contestant():
    test_list = []
    l = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 3, 2)]
    add_contestant(test_list, [4, 5, 6])
    add_contestant(test_list, [10, 10, 10])
    add_contestant(test_list, [5, 3, 2])
    assert test_list == l


test_add_contestant()


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


def test_insert_contestant():
    test_list = []
    l = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 3, 2)]

    insert_contestant(test_list, [4, 5, 6], 1)
    insert_contestant(test_list, [10, 10, 10], 2)
    insert_contestant(test_list, [5, 3, 2], 3)

    assert test_list == l


test_insert_contestant()


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


def test_remove_contestants():
    l = [create_contestant(3, 3, 3), create_contestant(3, 5, 5), create_contestant(0, 0, 0), create_contestant(0, 0, 0)]
    test_list = [create_contestant(3, 3, 3), create_contestant(3, 5, 5), create_contestant(5, 3, 2),
                 create_contestant(10, 5, 3)]
    remove_contestants(test_list, 2)
    remove_contestants(test_list, 3)

    assert test_list == l


test_remove_contestants()


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


def test_remove_more_contestants():
    l = [create_contestant(3, 3, 3), create_contestant(3, 5, 5), create_contestant(0, 0, 0), create_contestant(0, 0, 0)]
    test_list = [create_contestant(3, 3, 3), create_contestant(3, 5, 5), create_contestant(5, 3, 2),
                 create_contestant(10, 5, 3)]

    remove_more_contestants(test_list, 2, 4)

    assert test_list == l


test_remove_more_contestants()


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
            set_mark1(conts_list[index], marks)
        elif prob == 'P2':
            set_mark2(conts_list[index], marks)
        elif prob == 'P3':
            set_mark3(conts_list[index], marks)
        else:
            raise ValueError("Problem doesn't exist!")
    else:
        raise ValueError("Could not replace given contestant's marks, make sure the contestant exists")


def test_replace_marks():
    l = [create_contestant(4, 5, 6), create_contestant(10, 5, 10), create_contestant(5, 3, 2),
         create_contestant(3, 5, 3)]
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 3, 2),
                 create_contestant(10, 5, 3)]
    replace_marks(test_list, 3, 'P1', 3)
    replace_marks(test_list, 1, 'P2', 5)

    assert test_list == l


test_replace_marks()


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


def test_contestant_average():
    contestant = create_contestant(1, 2, 3)
    assert (contestant_average(contestant))


test_contestant_average()


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


def test_show_contestants_ps():
    l = [create_contestant(5, 3, 2)]
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 3, 2),
                 create_contestant(10, 5, 3)]

    new_test_list = show_contestants_property_smaller(test_list, 5)

    assert new_test_list == l


test_show_contestants_ps()


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


def test_show_contestants_pb():
    l = [create_contestant(10, 10, 10), create_contestant(10, 5, 3)]
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 3, 2),
                 create_contestant(10, 5, 3)]

    new_test_list = show_contestants_property_bigger(test_list, 5)

    assert new_test_list == l


test_show_contestants_pb()


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


def test_show_contestants_pe():
    l = [create_contestant(4, 5, 6)]
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 3, 2),
                 create_contestant(10, 5, 3)]

    new_test_list = show_contestants_property_equal(test_list, 5)

    assert new_test_list == l


test_show_contestants_pe()


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


def test_sort_marks():
    l = [10, 6, 5, 4]
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 5, 2),
                 create_contestant(10, 5, 3)]

    new_test_list = sort_marks(test_list)

    assert new_test_list == l


test_sort_marks()


def contestant_average_positions(conts_list, first_index, last_index):
    """
    Gets the average of the average of the contestants from a given position <first_index> to <last_index>
    :param conts_list: The list of contestants
    :param first_index: The first position
    :param last_index: The last position
    :return: Average of the average of the contestants
    """
    sums = 0
    for i in range(first_index - 1, last_index):
        sums += contestant_average(conts_list[i])
    divider = last_index - first_index + 1
    average = sums / divider

    return average


def test_contestant_average_positions():
    l = 25 / 4
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 4, 3),
                 create_contestant(10, 5, 3)]

    average = contestant_average_positions(test_list, 1, 4)

    assert average == l


test_contestant_average_positions()


def minimum_average(conts_list, first_index, last_index):
    """
    Gets the minimum of the average of the contestants from a given position <first_index> to <last_index>
    :param conts_list: The list of contestants
    :param first_index: The first position
    :param last_index: The last position
    :return: Average of the average of the contestants if success
    """
    if first_index and last_index:
        minimum = contestant_average(conts_list[first_index - 1])
        for i in range(first_index, last_index):
            minimum = min(minimum, contestant_average(conts_list[i]))
    else:
        raise ValueError("Something went wrong, check if the command is used correctly.")

    return minimum


def test_minimum_average():
    l = 4
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 4, 3),
                 create_contestant(10, 5, 3)]

    minimum = minimum_average(test_list, 1, 4)

    assert minimum == l


test_minimum_average()


def top_contestants_marks(conts_list, marks):
    """
    Gets the top <number> based on problem number.
    :param conts_list: The list of contestants
    :param marks: The problem number
    :return: Top <number> <p1> || <p2> || <p3>
    """
    if marks == 'P1':
        mark1_list = []
        for conts in conts_list:
            mark1_list.append(get_mark1(conts))

        new_mark1_list = sorted(mark1_list, reverse=True)
        return new_mark1_list
    elif marks == 'P2':
        mark2_list = []
        for conts in conts_list:
            mark2_list.append(get_mark2(conts))

        new_mark2_list = sorted(mark2_list, reverse=True)
        return new_mark2_list
    elif marks == 'P3':
        mark3_list = []
        for conts in conts_list:
            mark3_list.append(get_mark3(conts))

        new_mark3_list = sorted(mark3_list, reverse=True)
        return new_mark3_list
    else:
        raise ValueError("Incorrect problem number!")


def test_top_contestants_marks():
    list1 = [10, 10, 5, 4]
    list2 = [10, 5, 5, 4]
    list3 = [10, 6, 3, 3]
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 4, 3),
                 create_contestant(10, 5, 3)]

    top_list = top_contestants_marks(test_list, 'P1')
    top_list2 = top_contestants_marks(test_list, 'P2')
    top_list3 = top_contestants_marks(test_list, 'P3')

    assert top_list == list1
    assert top_list2 == list2
    assert top_list3 == list3


test_top_contestants_marks()


def remove_average_prop(cont_list, average, prop):
    """
    Removes contestants which have < or > or = to the average specified by the user
    :param cont_list: The list of contestants
    :param average: Average specified
    :param prop: Property
    :return: Marks set to 0 for the contestants which have that property
    """
    if prop == '<':
        for conts in cont_list:
            if int(contestant_average(conts)) < (int(average) / 10):
                set_mark1(conts, 0)
                set_mark2(conts, 0)
                set_mark3(conts, 0)
        return cont_list
    elif prop == '=':
        for conts in cont_list:
            if int(contestant_average(conts)) == (int(average) / 10):
                set_mark1(conts, 0)
                set_mark2(conts, 0)
                set_mark3(conts, 0)
        return cont_list
    elif prop == '>':
        for conts in cont_list:
            if int(contestant_average(conts)) > (int(average) / 10):
                set_mark1(conts, 0)
                set_mark2(conts, 0)
                set_mark3(conts, 0)
        return cont_list
    else:
        raise ValueError("Wrong parameter!")


def test_remove_average_prop():
    list1 = [[4, 5, 6], [10, 10, 10], [0, 0, 0], [10, 5, 3]]
    list2 = [[4, 5, 6], [0, 0, 0], [0, 0, 0], [10, 5, 3]]
    list3 = [[0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]]
    test_list = [create_contestant(4, 5, 6), create_contestant(10, 10, 10), create_contestant(5, 4, 3),
                 create_contestant(10, 5, 3)]

    test_list1 = remove_average_prop(test_list, 50, '<')
    assert test_list1 == list1
    test_list2 = remove_average_prop(test_list, 100, '=')
    assert test_list2 == list2
    test_list3 = remove_average_prop(test_list, 10, '>')
    assert test_list3 == list3


test_remove_average_prop()
