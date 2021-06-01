file = open('helloworld.py', 'r')
no = None
while no != file.tell():
    no = file.tell()
    print file.readline()

