"""
  User interface module
"""

import re
from functions import *


def add_contestant_command(cont_list, param, undo_list, index):
    """
    Adds a new contestant to the list
    :param cont_list: The list of contestants
    :param param: The new contestant to add
    :param undo_list: List which contains the new elements for undo function
    :param index: Index of the command to be undone.
    :return: Adds a contestant if success, False if contestant can't be added
    """
    if not param:
        raise ValueError("error: usage: add <p1 score> <p2 score> <p3 score>")
    new_contestant = param.split("; ")
    for conts in new_contestant:
        m1, m2, m3 = conts.split(" ")
        list_index = len(cont_list) + 1
        if int(m1) and int(m2) and int(m3):
            if int(m1) < 0 or int(m2) < 0 or int(m3) < 0:
                raise ValueError("One of the marks or more are lower than 0")
            elif int(m1) > 10 or int(m2) > 10 or int(m3) > 10:
                raise ValueError("One of the marks or more are higher than 10")
            try:
                undo_list.append([index, 'remove', list_index])
                add_contestant(cont_list, create_contestant(int(m1), int(m2), int(m3)))
                print("Contestant added successfully")
            except ValueError as ve:
                print("Contestant could not be added: " + m1, m2, m3 + ". Make sure all of the marks are integers"
                                                                       " smaller than 0 or higher than 10")
        else:
            raise ValueError("Cannot add contestant: one of the marks is missing.")


def add_contestant_command_no_trace(cont_list, param):
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
        list_index = len(cont_list) + 1
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


def insert_contestant_command(cont_list, param, undo_list, index):
    """
    Inserts a new contestant to the list in a given position
    :param cont_list: The list of contestants
    :param param: The new contestant to insert
    :param undo_list: List which contains the new elements for undo function
    :param index: Index of the command to be undone.
    :return: Inserts a contestant if success, False is contestant can't be inserted
    """
    if not param:
        raise ValueError("error: usage: insert <p1 score> <p2 score> <p3 score> at <position>")
    new_contestant = param.split("; ")
    for contest in new_contestant:
        m1, m2, m3, index_cont = re.findall(r'\d+', contest)
        if int(m1) and int(m2) and int(m3) and int(index_cont) < len(cont_list):
            try:
                undo_list.append([index, 'revert_insert', index_cont])
                insert_contestant(cont_list, create_contestant(m1, m2, m3), int(index_cont) - 1)
                print("Contestant has been inserted successfully")
            except ValueError as ve:
                print("Contestant could not be inserted " + m1, m2, m3 + " at position: " + str(index_cont) +
                      ". Make sure all of the marks are added or the index is mentioned")
        else:
            raise ValueError(
                "Cannot add contestant: one of the marks is missing or the position is not specified correctly")


def insert_contestant_command_no_trace(cont_list, param):
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


def remove_contestant_command(cont_list, param, undo_list, index, mark1_list, mark2_list, mark3_list):
    """
    Removes a contestant by switching his marks to 0
    :param cont_list: The list of contestants
    :param param: params to configure the command
    :param undo_list: List which contains the new elements for undo function
    :param index: Index of the command to be undone.
    :param mark1_list: List of P1 marks
    :param mark2_list: List of P2 marks
    :param mark3_list: List of P3 marks
    :return: Removes a contestant if success, raises ve if crash
    """
    if not param:
        raise ValueError(
            "error: usage: remove <position> or remove <start position> to <end position> "
            "or remove [ < or > or = ] <average>")
    else:
        number = param.split(" ")
        if len(number) == 1:
            index_cont = int(number[0])
            if index_cont <= len(cont_list):
                try:
                    undo_list.append(
                        [index, "replace", index_cont, get_mark1(cont_list[index_cont - 1]),
                         get_mark2(cont_list[index_cont - 1]),
                         get_mark3(cont_list[index_cont - 1])])
                    remove_contestants(cont_list, index_cont - 1)
                    print("Contestant removed successfully!")
                    show_contestants(cont_list)
                except ValueError as ve:
                    print("Could not remove contestant at " + str(index_cont) + ". Make sure it is not already removed")
            else:
                print("Error: contestant does not exist!")
        elif len(number) == 3:
            first_index = int(number[0])
            last_index = int(number[2])
            if first_index <= len(cont_list) and last_index <= len(cont_list):
                try:
                    undo_list.append([index, "replace_more", first_index, last_index])
                    for i in range(len(cont_list)):
                        mark1_list.append(get_mark1(cont_list[i]))
                        mark2_list.append(get_mark2(cont_list[i]))
                        mark3_list.append(get_mark3(cont_list[i]))
                    remove_more_contestants(cont_list, first_index - 1, last_index)
                    print("Contestants removed successfully!")
                    show_contestants(cont_list)
                except ValueError as ve:
                    print("Could not remove contestants.")
            elif first_index <= len(cont_list) <= last_index:
                print("Make sure all the contestants exist first!")
            elif first_index >= len(cont_list) and last_index >= len(cont_list):
                print("The first contestant doesn't exist, therefore nothing can be removed!")
        elif len(number) == 2:
            prop = number[0]
            average = number[1]
            if prop == '<' or prop == '>' or prop == '=':
                try:
                    undo_list.append([index, 'replace_prop', prop])
                    for i in range(len(cont_list)):
                        mark1_list.append(get_mark1(cont_list[i]))
                        mark2_list.append(get_mark2(cont_list[i]))
                        mark3_list.append(get_mark3(cont_list[i]))
                    remove_average_prop(cont_list, average, prop)
                    print("Here is your list")
                    show_contestants(cont_list)
                except ValueError:
                    print("Error occurred")
            else:
                print("Error: make sure the command is used correctly")


def remove_contestant_command_no_trace(cont_list, param):
    """
    Removes a contestant by switching his marks to 0
    :param cont_list: The list of contestants
    :param param: params to configure the command
    :return: Removes a contestant if success, raises ve if crash
    """
    if not param:
        raise ValueError(
            "error: usage: remove <position> or remove <start position> to <end position> "
            "or remove [ < or > or = ] <average>")
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
        elif len(number) == 2:
            prop = number[0]
            average = number[1]
            print(prop, average)
            if prop == '<' or prop == '>' or prop == '=':
                try:
                    remove_average_prop(cont_list, average, prop)
                    print("Here is your list")
                    show_contestants(cont_list)
                except ValueError:
                    print("Error occurred")
            else:
                print("Error: make sure the command is used correctly")


def replace_contestant_command(cont_list, param, undo_list, index):
    """
    Replaces a contestant's marks with the new input
    :param cont_list: The list of contestants
    :param param: params to configure the command
    :param undo_list: List which contains the new elements for undo function
    :param index: Index of the command to be undone.
    :return:Replaces a contestant if success, raises ve if crash
    """
    if not param:
        raise ValueError("usage: replace <position> <problem_no> with <new_mark>")
    else:
        params = param.split(" ")
        if len(params) == 4:
            index_cont = int(params[0])
            if index_cont <= len(cont_list):
                problem = params[1]
                new_mark = int(params[3])
                if new_mark < 0:
                    raise ValueError("New mark is lower than 0, insert another one")
                elif new_mark > 10:
                    raise ValueError("New mark is higher than 10, insert another one")
                try:
                    undo_list.append([index, 'replace_func', index_cont, problem, get_mark1(cont_list[index_cont - 1]),
                                      get_mark2(cont_list[index_cont - 1]), get_mark3(cont_list[index_cont - 1])])
                    replace_marks(cont_list, index_cont - 1, problem, new_mark)
                    print("Contestant's marks replaced successfully.")
                    show_contestants(cont_list)
                except ValueError as ve:
                    print("Could not replace given contestant's marks, make sure the contestant or the problem exists")
            else:
                print("Error: the contestant does not exist!")
        else:
            print("Error: could not get problem number or new mark, make sure everything is written")
            print("usage: replace <position> <problem_no> with <new_mark>")


def replace_contestant_command_no_trace(cont_list, param):
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


def contestant_average_positions_command(conts_list, param):
    """
    Command to display the average of the average of the contestants marks.
    :param conts_list: The list of contestants
    :param param: Parameters
    :return: Average
    """
    if not param:
        raise ValueError("usage: avg <first_position> to <last_position>")
    else:
        params = param.split(" ")
        if len(params) == 3:
            first_index = int(params[0])
            last_index = int(params[2])
            if first_index <= len(conts_list) and last_index <= len(conts_list):
                try:
                    result = contestant_average_positions(conts_list, first_index, last_index)
                    print("Average of the average: " + str(result))
                except ValueError:
                    print("Error: make sure the average can be calculated")
            elif first_index <= len(conts_list) <= last_index:
                print("Make sure all the contestants exist first!")
            elif first_index >= len(conts_list) and last_index >= len(conts_list):
                print("The first contestant doesn't exist, therefore nothing can be calculated!")


def minimum_average_command(conts_list, param):
    """
    Displays the minimum of the average of the contestants
    :param conts_list: The list of contestants
    :param param: Params of the commands
    :return: Minimum of the average
    """
    if not param:
        raise ValueError("usage: min <first_position> to <last_position>")
    else:
        params = param.split(" ")
        if len(params) == 3:
            first_index = int(params[0])
            last_index = int(params[2])
            if first_index <= len(conts_list) and last_index <= len(conts_list):
                try:
                    result = minimum_average(conts_list, first_index, last_index)
                    print("Minimum of the average: " + str(result))
                except ValueError:
                    print("Error: make sure the minimum exists")
            elif first_index <= len(conts_list) <= last_index:
                print("Make sure all the contestants exist first!")
            elif first_index >= len(conts_list) and last_index >= len(conts_list):
                print("The first contestant doesn't exist, therefore nothing can be shown!")


def top_contestants_command(conts_list, param):
    """
    Displays the top of the contestants
    :param conts_list: The list of contestants
    :param param: The parameters
    :return:
    """
    if not param:
        raise ValueError("usage: top <number> or top <number> <p1> or <p2> or <p3>")
    else:
        params = param.split()
        new_conts_list = sort_marks(conts_list)
        new_conts_list_format = ['%.2f' % elem for elem in new_conts_list]
        if len(params) == 1:
            try:
                number = int(params[0])
                index = 1
                for i in range(number):
                    print("Contestant " + str(index) + " with an average of: " + str((new_conts_list_format[i])))
                    index += 1
            except ValueError:
                print("Top could not be shown.")
        elif len(params) == 2:
            number = int(params[0])
            mark = params[1]
            if mark == 'P1':
                try:
                    new_list = top_contestants_marks(conts_list, mark)
                    index = 1
                    print("Here is your top: ")
                    for i in range(number):
                        print("Contestant " + str(index) + " : " + str(new_list[i]))
                        index += 1
                except ValueError:
                    print("Top could not be shown.")
            elif mark == 'P2':
                try:
                    new_list = top_contestants_marks(conts_list, mark)
                    index = 1
                    print("Here is your top: ")
                    for i in range(number):
                        print("Contestant " + str(index) + " : " + str(new_list[i]))
                        index += 1
                except ValueError:
                    print("Top could not be shown.")
            elif mark == 'P3':
                try:
                    new_list = top_contestants_marks(conts_list, mark)
                    index = 1
                    print("Here is your top: ")
                    for i in range(number):
                        print("Contestant " + str(index) + " : " + str(new_list[i]))
                        index += 1
                except ValueError:
                    print("Top could not be shown.")
            else:
                print("Error: make sure the problem number is correct")


def undo_command(cont_list, undo_list, index, mark1_list, mark2_list, mark3_list):
    """
    Command that does undo function for all the functions that modify the list
    :param cont_list: The list of contestants
    :param undo_list: The list which stores commands to be undone
    :param index: A basic variable to organize commands order in undo_list
    :param mark1_list: List of P1 marks
    :param mark2_list: List of P2 marks
    :param mark3_list: List of P3 marks
    :return: Undo different commands
    """
    command_list = len(undo_list)
    if command_list != 0:
        small_list = undo_list[index - 2]
        if small_list[1] == 'remove':
            cont_list.pop()
            command_list -= 1
            undo_list.pop()
            print("Undo done!")
            show_contestants(cont_list)
        elif small_list[1] == 'replace':
            set_mark1(cont_list[small_list[2] - 1], small_list[3])
            set_mark2(cont_list[small_list[2] - 1], small_list[4])
            set_mark3(cont_list[small_list[2] - 1], small_list[5])
            print("Undo done!")
            show_contestants(cont_list)
            command_list -= 1
            undo_list.pop()
        elif small_list[1] == 'replace_more':
            for i in range(small_list[2] - 1, small_list[3]):
                set_mark1(cont_list[i], mark1_list[i])
                set_mark2(cont_list[i], mark2_list[i])
                set_mark3(cont_list[i], mark3_list[i])
            print("Undo done!")
            show_contestants(cont_list)
            command_list -= 1
            undo_list.pop()
        elif small_list[1] == 'replace_prop':
            for i in range(len(cont_list)):
                set_mark1(cont_list[i], mark1_list[i])
                set_mark2(cont_list[i], mark2_list[i])
                set_mark3(cont_list[i], mark3_list[i])
            print("Undo done!")
            show_contestants(cont_list)
            command_list -= 1
            undo_list.pop()
        elif small_list[1] == 'revert_insert':
            cont_list.pop(int(small_list[2]) - 1)
            print("Undo done!")
            show_contestants(cont_list)
            command_list -= 1
            undo_list.pop()
        elif small_list[1] == 'replace_func':
            if small_list[3] == 'P1':
                set_mark1(cont_list[small_list[2] - 1], small_list[4])
            elif small_list[3] == 'P2':
                set_mark2(cont_list[small_list[2] - 1], small_list[5])
            elif small_list[3] == 'P3':
                set_mark2(cont_list[small_list[2] - 1], small_list[6])
            print("Undo done!")
            show_contestants(cont_list)
            command_list -= 1
            undo_list.pop()
    else:
        print("Nothing to undo!")


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
