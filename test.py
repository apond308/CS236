import glob
import os

os.system("rm *.txt")
os.system("g++ ../lab2/*.cpp -o ../lab2/lab2")

files = glob.glob("/home/apond/Desktop/Winter_2019/235/test/**/*.txt", recursive=True)

for file in files:
    if ("test_case" in file):
        filename = os.path.basename(file)
        print("\n\nTesting: " + filename + "...")
        os.system("../lab2/lab2 " + file + " > process" + filename)
        os.system("diff process" + filename + " 80/answer" + file[-5:])

