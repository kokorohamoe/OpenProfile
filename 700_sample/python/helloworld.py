file = open('helloworld.py', 'r')
while True:
    line =  file.readline()
    if not line:
        break
    print line

