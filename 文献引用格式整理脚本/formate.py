num = 46
of = open('2.txt', 'w')
for line in open('1.txt'):
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
                print '\n*1*\n'
                print output
                # raw_input()
            elif c == '(':
                output = output[:len(output) - 1] + '.'
                nameing = False
                titleing = True
                year = line[i + 1 : i + 5]
                print '\n*2.1*\n'
                print year
                # raw_input()
                print '\n*2.2*\n'
                print output
                # raw_input()
                i = i + 7
                print '\n*2.3*\n'
                print line[i:]
                # raw_input()
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
                print '\n*3*\n'
                print output
                # raw_input()
            else:
                i += 1
                output += c
            continue
        if journaling:
            if c == ',' and is_first:
                i += 1
                is_first = False
                output += ', ' + year + c
                print '\n*5*\n'
                print output
                # raw_input()
            else:
                i += 1
                output += c
                print '\n*6*\n'
                print output
                # raw_input()
    print output
    of.write(output + '\n')
of.close()
