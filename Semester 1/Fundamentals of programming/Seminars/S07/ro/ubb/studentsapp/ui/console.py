"""

@author: radu

 
"""
from ro.ubb.studentsapp.domain import operations


def read_command():
    # todo : return cmd, args
    command = input("Command = ")
    pos = command.find(" ")

    if pos == -1:
        return command, []

    cmd = command[:pos]
    args = command[pos:]
    args = args.split(",")
    args = [s.strip() for s in args]
    return cmd, args

def add_student(all_students: list, id, name, grade):
    id = int(id)
    grade = int(grade)
    # todo : check for exceptions

    operations.add_student(all_students, id, name, grade)


def print_commands(commands: dict):
    print(commands)


def run_console():
    all_students = []
    commands = {"add": add_student}
    while True:
        print_commands(commands)
        cmd, args = read_command()

        if cmd == "exit":
            break
        try:
            commands[cmd](all_students, *args)
        except KeyError as ke:
            print("Option not yet implemented!", ke)

