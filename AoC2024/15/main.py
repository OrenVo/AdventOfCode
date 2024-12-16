import numpy as np

up = "^"
down = "v"
left = "<"
right = ">"

ops = []
mat = []

with open("input") as f:
    lines = f.readlines()
    parse_map = True
    for l in lines:
        if l == "\n":
            parse_map = False
            continue
        if parse_map:
            mat.append([c for c in l.strip()])
        else:
            for c in l:
                ops.append(c)
map = np.asarray(mat)


def doOperation(pos: tuple, vec: tuple) -> list:
    move_ops = []
    new_pos = (pos[0] + vec[0], pos[1] + vec[1])
    if map[new_pos[0], new_pos[1]] == "#":
        return []
    elif map[new_pos[0], new_pos[1]] == ".":
        move_ops.append({"C": "@", "NP": (new_pos[0], new_pos[1])})
    elif map[new_pos[0], new_pos[1]] == "O":
        move_ops.append({"C": "@", "NP": (new_pos[0], new_pos[1])})
        new_pos2 = (new_pos[0], new_pos[1])
        while True:
            new_pos2 = (new_pos2[0] + vec[0], new_pos2[1] + vec[1])
            move_ops.append({"C": "O", "NP": (new_pos2[0], new_pos2[1])})
            if map[new_pos2[0], new_pos2[1]] == ".":
                break
            elif map[new_pos2[0], new_pos2[1]] == "#":
                move_ops = []
                break
    return move_ops


map2 = []
for row in map:
    new_row = []
    for col in row:
        match col:
            case "#":
                new_row.append("##")
            case "@":
                new_row.append("@.")
            case "O":
                new_row.append("[]")
            case ".":
                new_row.append("..")
    map2.append(new_row)

map2 = np.asarray(map2)

while ops:
    pos = np.where(map == "@")
    op = ops.pop(0)
    move_ops = []
    if op == "^":
        move_ops = doOperation((pos[0], pos[1]), (-1, 0))
    elif op == "v":
        move_ops = doOperation((pos[0], pos[1]), (1, 0))
    elif op == "<":
        move_ops = doOperation((pos[0], pos[1]), (0, -1))
    elif op == ">":
        move_ops = doOperation((pos[0], pos[1]), (0, 1))
    while move_ops:
        o = move_ops.pop()
        if o["C"] == "@":
            map[np.where(map == "@")] = "."
        map[o["NP"]] = o["C"]


indices = np.where(map == "O")

res = 0

for x, y in zip(indices[0], indices[1]):
    res += (100 * x) + y

print(map2)

print(f"Part 1: {res}")
