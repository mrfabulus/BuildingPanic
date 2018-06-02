def FindNextLabeledAddress(ea, limit = None):
    while Name(ea) == "" and (limit == None or (limit < ea)):
        ea += 1

    return ea

def getSignBit(imm):
    return (imm & 0x80000000) == 0x80000000

def toSigned(imm):
    if(getSignBit(imm)):
        return -0x100000000 + imm
    else:
        return imm

def fn(addr):
    num = Dword(addr)
    if getSignBit(num) == 1:
        return "%d" % toSigned(num)
    else:
        return "0x%02x" % num

def dumpTileInfo(addr):
    i = 0
    str = ""

    for x in map(lambda x: struct.unpack("<B", x), idaapi.get_many_bytes(addr, 1200 * 2)[::2]):
        str = str + ("0x%02X, " % x[0])

        if i != 0 and ((i + 1) % 16 == 0):
            str = str[:-1] + '\n'

        i = i + 1;

    str = str[:-3]
    print str

def dumpP1(addr, index):
    # print "dumpP1 %x %d" % (addr, index)
    end = FindNextLabeledAddress(addr + 2)
    cursor = addr
    
    result = ("static const uint16_t RenderMeta_1_%d[] =\n{\n" % index)
    
    while cursor < end:
        create_word(cursor)
        cData = Word(cursor)
        cursor += 2
        result += "    %d,\n" % cData
    
    result += "};\n\n"
    return result

def dumpP2(addr):
    end = FindNextLabeledAddress(addr + 4)
    result = "static const MSRect RenderMeta_2[] =\n{\n"
    cursor = addr

    while cursor < end:
        line = ("    { %s, %s, %s, %s },\n" % (fn(cursor), fn(cursor + 4), fn(cursor + 8), fn(cursor + 12)))
        result += line
        cursor += 16

    result += "};\n"

    return result

def dumpP3(addr):
    end = FindNextLabeledAddress(addr + 4)
    result = "static const MSRect RenderMeta_3[] =\n{\n"
    cursor = addr

    while cursor < end:
        line = ("    { %s, %s, %s, %s },\n" % (fn(cursor), fn(cursor + 4), fn(cursor + 8), fn(cursor + 12)))
        result += line
        cursor += 16

    result += "};\n"

    return result

def dumpRenderMeta(addr):
    ptr1 = Dword(addr)
    ptr2 = Dword(addr + 4)
    ptr3 = Dword(addr + 8)

    ptr1_end = FindNextLabeledAddress(ptr1 + 4)
    # print "%X -> %X" % (ptr1, ptr1_end)

    output = "// ------ PlaceHolderEntity RenderMeta START ------\n"
    
    cursor = ptr1
    linkerStructStr = "static const uint16_t* RenderMeta_1[] =\n{\n"

    while cursor < ptr1_end:
        if Dword(cursor) == 0:
            linkerStructStr += "    0\n"
            break

        index = ((cursor - ptr1) / 4) + 1
        output += dumpP1(Dword(cursor), index)
        linkerStructStr += ("    &RenderMeta_1_%d[0],\n" % index)
        cursor += 4

    linkerStructStr += "};\n"
    output += linkerStructStr

    output += "\n"
    output += dumpP2(ptr2)
    output += "\n"
    output += dumpP3(ptr3)
    output += "\n"

    output += "const RenderMeta SomeStruct_Meta::PlaceHolderEntity_RenderMeta =\n"
    output += "{\n"
    output += "    &RenderMeta_1[0],\n"
    output += "    &RenderMeta_2[0],\n"
    output += "    &RenderMeta_3[0],\n"
    output += "    gConsts::RenderMetaTerminatorPtr\n"
    output += "};\n"

    output += "// ------ PlaceHolderEntity RenderMeta END ------"
    print output

