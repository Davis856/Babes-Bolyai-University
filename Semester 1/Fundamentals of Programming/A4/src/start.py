"""
  Start the program by running this module
"""
from ui import *


def print_commands():
    print("\nCommand-driven menu to administrate contestants")
    print("Commands are as following:")
    print("add - to add a new contestant")
    print("insert - to add a new contestant at a given position")
    print("list - to show the list of contestants")
    print("remove - to remove a contestant from the list")
    print("replace - to replace a contestant's marks")
    print("avg - to display the average of the average")
    print("min - to display the minimum average")
    print("top - to display the top of the contestants")
    print("undo - to undo")
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

    undo_list = []

    mark1_list = []
    mark2_list = []
    mark3_list = []

    index = 1

    while True:
        print_commands()

        command = input("command: ")
        command_word, command_params = split_command(command)

        try:
            if command_word == 'add':
                add_contestant_command(contestant_list, command_params, undo_list, index)
                index += 1
            elif command_word == 'insert':
                insert_contestant_command(contestant_list, command_params, undo_list, index)
                index += 1
            elif command_word == 'list':
                show_contestants_command(contestant_list, command_params)
            elif command_word == 'remove':
                remove_contestant_command(contestant_list, command_params, undo_list, index, mark1_list,
                                          mark2_list, mark3_list)
                index += 1
            elif command_word == 'replace':
                replace_contestant_command(contestant_list, command_params, undo_list, index)
                index += 1
            elif command_word == 'avg':
                contestant_average_positions_command(contestant_list, command_params)
            elif command_word == 'min':
                minimum_average_command(contestant_list, command_params)
            elif command_word == 'top':
                top_contestants_command(contestant_list, command_params)
            elif command_word == 'undo':
                undo_command(contestant_list, undo_list, index, mark1_list, mark2_list, mark3_list)
                index -= 1
            elif command_word == 'exit':
                return
            else:
                print("Unknown command!")
        except ValueError as ve:
            print(str(ve))


start_menu()
