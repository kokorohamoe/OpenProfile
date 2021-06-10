file = open(__file__, 'r')
no = None
while no != file.tell():
    no = file.tell()
    print file.readline().rstrip()

