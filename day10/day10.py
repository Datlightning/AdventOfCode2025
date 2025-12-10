from heapq import heappop, heappush
def cmp(target, current, length):
    c = 0
    for i in range(length):
        c += 0 if target[i] == current[i] else 1
    return c 
def cmp2(target, current, length):
    c = 0
    flag = False
    for i in range(length):
        c += target[i] - current[i]
        if target[i] < current[i]:
            flag = True
    return c, flag

def is_int_ascii(s):
    if not s:
        return False
    for c in s:
        code = ord(c)
        if code < 48 or code > 57:
            return False
    return True
lines = []
with open("day10/input.txt", "r") as file:
    lines = file.read().split("\n")
for i, l in enumerate(lines):
    lines[i] = l.split(' ')

p1 = 0
p2 = 0
for input_n, line in enumerate(lines):
    if input_n % 25 == 0:
        print(input_n)
    seen = set()
    seen2 = set()
    target = line[0][1:-1]
    options = line[1:-1]
    length = len(target)
    target = [target[i] == "#" for i in range(length)]
    current = [False for _ in range(length)]
    target2 = line[-1]
    target2 = '(' + target2[1:-1] + ')'
    target2 = eval(target2)
    current2 = [0 for _ in range(length)]
    state = [(0, cmp(target, current, length),  current)]
    state2 = [(0, cmp(target, current, length), current, cmp2(target2, current2, length), current2)]
    p1d = True
    p2d = True
    while p1d or p2d:
        if p2d:
            cs = heappop(state2)
            presses, score, current, score2, current2 = cs
            if presses == 10:
                pass
            if (presses, score, tuple(current), tuple(current2)) in seen2:
                continue
            seen2.add((presses, score, tuple(current), tuple(current2)))
            if (score == 0 and score2 == 0):
                p2 += presses
                p2d = False
            for o in options:
                
                nc = [i for i in current]
                nc2 = [i for i in current2]
                for button in o:
                    if not is_int_ascii(button):
                        continue
                    button = int(button)
                    nc[button] = not nc[button]
                    nc2[button] += 1
                score2, flag = cmp2(target2, nc2, length)
                
                if not flag:
                    new_state = (presses + 1, cmp(target, nc, length), nc, score2, nc2)
                    heappush(state2, new_state)
        if p1d:
            cs = heappop(state)
            presses, score, current = cs
            if (presses, score, tuple(current)) in seen:
                continue
            seen.add((presses, score, tuple(current)))
            if (score == 0):
                p1 += presses
                p1d = False
    
            for o in options:
                nc = [i for i in current]
                for button in o:
                    if not is_int_ascii(button):
                        continue
                    button = int(button)
                    nc[button] = not nc[button]
                new_state = (presses + 1, cmp(target, nc, length), nc)
                heappush(state, new_state)
print(f"Part 1: {p1}")
print(f"Part 2: {p2}")