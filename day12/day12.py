sizes = {}
boundaries = []
with open("day12/input.txt", "r") as file:
    lines = file.read().split("\n\n")
    for i,line in enumerate(lines):
        split = line.splitlines()
        boundary = False
        for nline in split:
            if "x" in nline:
                boundary = True
            if not boundary:
                if ":" in nline:
                    continue
                if i in sizes:
                    sizes[i] += nline.count("#")
                else:
                    sizes[i] = nline.count("#")
            else:
                size, counts = nline.split(":")
                x,y = size.split("x")
                area = int(x) * int(y)
                counts = tuple(map(int, counts.strip().split(" ")))
                boundaries.append((area, counts))

p1 = 0
for area, counts in boundaries:
    current = 0
    for i, value in enumerate(counts):
        current += value * sizes[i]
    p1 += 1 if current <= area else 0
print(f"Part 1: {p1}")