with open("day1/input.txt") as f:
    lines = f.read().split("\n")

dial = 50
p1 = 0
p2 = 0
for line in lines:
    if line[0] == "L":
        move = line[1:].strip()
        move = int(move)
        for _ in range(move):
            if dial == 0:
                p2 += 1
            dial -= 1
            dial %= 100
    elif line[0] == "R":
        move = line[1:].strip()
        move = int(move)
        for _ in range(move):
            if dial == 0:
                p2 += 1
            dial += 1
            dial %= 100
    # print(dial)
    if dial == 0:
        p1 += 1
    
print(p1)
print(p2)