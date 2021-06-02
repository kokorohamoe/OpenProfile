file = open('helloworld.py', 'r')
line = file.readline
while line:
    print line
    line = file.readline()

