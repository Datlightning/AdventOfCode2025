from shapely import Polygon, box

points = []
with open("day9/input.txt", "r") as file:
    lines = file.read().split("\n")
for p1, p2 in [l.split(",") for l in lines]:
    points.append((int(p1.strip()), int(p2.strip())))
p = Polygon(points)
p2 = 0
p1 = 0
for i in range(len(points)):
    for j in range(i+1, len(points)):
        x,y = points[i]
        px,py = points[j]
        r = box(min(px,x), min(py,y), max(px,x), max(py,y))
        area = (1 + abs(x - px)) * (1 + abs(y - py))
        if p.contains(r) and area > p2:
            p2 = area
        p1 = max(area, p1)
print(f"Part 1: {p1}")
print(f"Part 2: {p2}")