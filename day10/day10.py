from heapq import heappop, heappush
from collections import deque


def cmp(target, current, length):
    c = 0
    for i in range(length):
        c += 0 if target[i] == current[i] else 1
    return c 

def cmp2(target, current,):
    c = sum(t - c for t, c in zip(target, current))
    flag = any(c > t for c, t in zip(current, target))
    return c, flag


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
    for i, o in enumerate(options):
        temp = eval(o)
        if isinstance(temp, int):
            temp = (temp,)
        options[i] = temp
    
    length = len(target)
    target = [target[i] == "#" for i in range(length)]
    current = [False for _ in range(length)]

    target2 = line[-1]
    target2 = '(' + target2[1:-1] + ')'
    target2 = eval(target2)

    current2 = tuple([0 for _ in range(length)])
    
    state = [(0, cmp(target, current, length),  current)]
    state2 = [(0, cmp2(target2, current2), current2)]
    p1d = True
    p2d = True
    while p1d or p2d:
        if p2d:
            presses, score2, current2 = heappop(state2)   # current2 is a TUPLE!

            if current2 in seen2:
                continue
            seen2.add(current2)

            if score2 == 0:
                p2 += presses
                p2d = False
                continue

            for option in options:
                
                nc2 = list(current2)   

                for button in option:
                    nc2[button] += 1

                score2, flag = cmp2(target2, nc2)

                if not flag:
                    heappush(state2, (presses + 1, score2, tuple(nc2)))
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
                    nc[button] = not nc[button]
                new_state = (presses + 1, cmp(target, nc, length), nc)
                heappush(state, new_state)
print(f"Part 1: {p1}")
print(f"Part 2: {p2}")