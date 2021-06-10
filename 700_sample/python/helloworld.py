#!//usr/bin/python

file = open( __file__ , 'r')
line = file.readline
while line:
    line = line.rstrip()
    print line
    line = file.readline()

