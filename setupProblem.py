import os
import sys


def create(problemName):
    if os.path.exists(f"./{problemName}.cpp"):
        print("Problem already exists")
    open(f"./{problemName}.cpp", "w").close()
    open(f"./{problemName}.test", "w").close()
    return


def remove(problemName):
    if not os.path.exists(f"./{problemName}.cpp"):
        print("Problem does NOT exists")
    os.remove(f"./{problemName}.cpp")
    os.remove(f"./{problemName}.test")
    return


if __name__ == "__main__":
    action = sys.argv[1]
    problemName = sys.argv[2]
    if action == "create":
        create(problemName)
    else:
        remove(problemName)
