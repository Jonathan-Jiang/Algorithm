import re
num = 0
of = open('2.txt', 'w')
for line in open('1.txt'):
    line = line.strip()
    num += 1
    nameing = True
    titleing = False 
    journaling = False
    year = ''
    output = '[' + str(num) + '] '
    is_in_name = True
    is_first = True
    i = 0
    while i < len(line):
        c = line[i]
        if nameing:
            if c == ',' and is_in_name:
                is_in_name = not is_in_name
                i += 1
                continue
            elif c == '.' or c == '&':
                i += 1
                continue
            elif c == ',' and not is_in_name:
                i += 1
                is_in_name = not is_in_name
                output += c
            elif c == '(':
                output = output[:len(output) - 1] + '.'
                nameing = False
                titleing = True
                year = line[i + 1 : i + 5]
                i = i + 7
            else:
                i += 1
                output += c
            continue
        if titleing:
            if c == '.':
                i += 1
                output += '[J].'
                titleing = False
                journaling = True
            else:
                i += 1
                output += c
            continue
        if journaling:
            if c == ',' and is_first:
                i += 1
                is_first = False
                output += ', ' + year + c
            else:
                i += 1
                output += c
    p = re.compile(r'(\s)+')
    output = p.sub(r' ', output)
    of.write(output + '\n')
of.close()
