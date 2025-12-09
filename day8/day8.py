class Circuit:
    def __init__(self, id):
        self.id = id
        self.members = set()
    def contains(self, point):
        return point in self.members
    def add(self, point):
        self.members.add(point)
    def size(self):
        return len(self.members)

def value(c):
    return c.size()
def distance(p1,p2):
    return abs(p1[0] - p2[0])**2 + abs(p1[1] - p2[1])**2 + abs(p1[2] - p2[2])**2
lines = []
circuits = []
with open("day8/input.txt", "r") as file:
    lines = file.read().split("\n")
for i, l in enumerate(lines):
    lines[i] = tuple(map(int, l.split(",")))

circuit_id = 0
distances = dict()
connected_pairs = set()

ordered_list = []
for i in range(len(lines)):
        for j in range(i,len(lines)):
            if i == j:
                continue
            ordered_list.append((distance(lines[i], lines[j]),i,j))
ordered_list = sorted(ordered_list, key=lambda x: x[0], reverse=True)
p2 = 0
p1 = 1
connection = 0

connections = 1000
while p2 == 0: 
    _,ni, nj = ordered_list.pop()
    if (ni != -1) and (nj != -1) and (nj != ni):
        connected_pairs.add((ni,nj))
        connected_pairs.add((nj,ni))
        first_connect = 0
        connected = False
        for c in circuits: 
            if c and c.contains(lines[ni]) and not c.contains(lines[nj]):
                c.add(lines[nj])
                if not connected:
                    first_connect = c.id
                else:
                    circuits[first_connect].members.update(c.members)
                    c.members = set()
                    
                connected = True

                
            if c and c.contains(lines[nj]) and not c.contains(lines[ni]):
                c.add(lines[ni])
                if not connected:
                    first_connect = c.id
                else:
                    circuits[first_connect].members.update(c.members)
                    c.members = set()
                    
                connected = True
                # print("Connecting points:", lines[ni], lines[nj], "into:", c.id)
            if c and c.size() == len(lines):
                p2 = lines[nj][0] * lines[ni][0]
            if not connected and c and c.contains(lines[nj]) and c.contains(lines[ni]):
                connected = True
                # print("Points already connected:", lines[ni], lines[nj], "in:", c.id)
                break
                
        if not connected:
            new_circuit = Circuit(circuit_id)
            new_circuit.add(lines[ni])
            new_circuit.add(lines[nj])
            # print("Creating Circuit with:", lines[ni], lines[nj], "into:", new_circuit.id)

            circuits.append(new_circuit)
            circuit_id += 1
    connection += 1
    if connection == connections - 1:
        sorted_circuits = sorted(circuits, key=value, reverse=True)
        for c in sorted_circuits[0:3]:
            p1 *= c.size()
        print("Part 1:", p1)


        

print("Part 2:", p2)