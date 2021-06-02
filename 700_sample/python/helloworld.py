file = open('helloworld.py', 'r')
line = file.readline()
while line:
    print line.rstrip()
    line = file.readline()

