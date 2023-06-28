import os
import sys
import random
if __name__ == "__main__":
    print("This is a directory test generator for blk-rn")
    if len(sys.argv) != 2:
        print("Error: incorrect number of arguments")
        print("Usage: python3 generate_tests.py <test_mode>")
        exit(-1)
    if sys.argv[1] == "-h" or sys.argv[1] == "--help":
        print("This script is used to help the development of blk-rn")
        print("Usage: python3 generate_tests.py <test_mode>")
        print("test_mode can be one of the following:")
        print("-1: 10 random files with random names")
        print("-2: 100 random files with random names")
        print("-3: 10 random files with random names and 10 random files with random names and .txt1 or .txt2 extensions")
        exit(0)
    test_mode = sys.argv[1]
    if test_mode not in ["-1", "-2", "-3"]:
        print("Error: invalid test mode")
        print("Usage: python3 generate_tests.py <test_mode>")
        exit(-1)
    if not os.path.exists("tests"):
        os.makedirs("tests")
    else:
        print("Warning: tests directory already exists")
        print("Do you want to overwrite the files? (y/n)")
        overwrite = input()
        if overwrite != "y":
            exit(0)
        else:
            print("Overwriting files...")
            for file in os.listdir("tests"):
                os.remove(os.path.join("tests", file))
    if test_mode == "-1":
        for i in range(10):
            random_number = random.randint(1, 100)
            file = open("tests/"+str(random_number)+".txt", "w")
            file.close()
    elif test_mode == "-2":
        for i in range(100):
            random_number = random.randint(1, 100)
            file = open("tests/"+str(random_number)+".txt", "w")
            file.close()
    elif test_mode == "-3":
        for i in range(10):
            random_number = random.randint(1, 100)
            file = open("tests/"+str(random_number)+".txt1", "w")
            file.close()
            file = open("tests/"+str(random_number)+".txt2", "w")
            file.close()    
    print("Done")