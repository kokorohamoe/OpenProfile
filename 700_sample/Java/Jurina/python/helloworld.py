file = open('helloworld', 'r')
no = None
while no != file.tell():
    print file.readline()
    no = file.tell()

