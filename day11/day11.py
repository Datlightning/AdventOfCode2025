from collections import deque
from functools import lru_cache


lines = []
directions = dict()
with open("day11/input.txt", "r") as file:
    lines = file.read().split("\n")
for l in lines:
    start, end = l.split(":")
    end = end.strip().split(" ")
    directions[start.strip()] = end
# print(directions)
p1 = True
p2 = True
if p1:
    start = 'you'
    queue = [start]
    p1 = 0
    while queue:
        current = queue.pop()
        if current == "out":
            p1 += 1
            continue
        for new in directions[current]:
            queue.append(new)
    print(f"Part 1: {p1}")
if p2:
    
    @lru_cache(None)
    def count_paths(current, s1, s2):
        # Base case: finished
        if current == 'out':
            return 1 if (s1 == 1 and s2 == 1) else 0

        # Update flags
        if current == 'fft':
            s1 = 1
        if current == 'dac':
            s2 = 1

        # Sum over all children
        total = 0
        for nxt in directions[current]:
            total += count_paths(nxt, s1, s2)

        return total
    
    p2 = count_paths('svr', 0,0)
    print(f"Part 2: {p2}")
