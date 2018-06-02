i = 0
str = ""

for x in map(lambda x: struct.unpack("<B", x), idaapi.get_many_bytes(0x0043F528, 1200 * 2)[::2]):
    str = str + ("0x%02X, " % x[0])

    if i != 0 and ((i + 1) % 16 == 0):
        str = str[:-1] + '\n'

    i = i + 1;

str = str[:-3]
print str

