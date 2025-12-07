def display(lines):
    for l in lines:
        print("".join(str(c) for c in l))
lines = []

with open("day7/input.txt") as f:
    lines = f.read().split("\n")
    
x = len(lines[0])
y = len(lines)
for i, l in enumerate(lines):
    lines[i] = list(l)
p1 = 0
seen = set()
current_path = []
for y, line in enumerate(lines):
    for x, c in enumerate(line):
        if c == "S":
            current_path.append((y,x))
            lines[y][x] = 1
        if c == ".":
            lines[y][x] = 0

p2 = 0
seen_splits = set()
seen = set()
while current_path:

    print()
    y,x = current_path.pop(0)
    if (y,x) in seen:
        continue
    lx = x-1
    rx = x+1
    count = 0
    if (y > 0):
        if (lx >= 0) and (lines[y][lx] == "^"):
            lines[y][x] += lines[y-1][lx]
            count +=1 
        if (rx < len(lines[0])) and (lines[y][rx] == "^"):
            lines[y][x] += lines[y-1][rx]
            count += 1
        lines[y][x] += lines[y-1][x]

    
    seen.add((y,x))
    y+=1
    if y >= len(lines):
        continue
    c = lines[y][x]
    if c == "^":
        nx1 = x - 1
        nx2 = x + 1
        if (nx1 >= 0):
            current_path.append((y,nx1))
        if (nx2 < len(lines[0])):
            current_path.append((y,nx2))

        if (y,x) not in seen_splits:
            seen_splits.add((y,x))
            p1 += 1
    else:
        current_path.append((y,x))


y = len(lines) - 1
for x in range(len(lines[0])):
    p2 += lines[y][x]


print(f"Part 1: {p1}")
print(f"Part 2: {p2}")