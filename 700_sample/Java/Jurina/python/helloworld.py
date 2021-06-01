file = open('helloworld', 'r')
no = None
while no != file.tell():
    no = file.tell()
    print file.readline()

