import numpy as np
import queue
import math
import itertools

inp = []

with open("test2_input") as f:
    inp = [[c for c in l.strip()] for l in f.readlines() if l != "\n" and l != ""]

maze = np.asarray(inp)

start_pos = np.where(maze == "S")
end_pos = np.where(maze == "E")

pq = queue.PriorityQueue()
counter = itertools.count()
l = "<"
r = ">"
u = "^"
d = "v"

end_pos = (end_pos[0][0], end_pos[1][0])
data = {
    "cost": 0,
    "dir": r,
    "pos": (start_pos[0][0], start_pos[1][0]),
    "seen": set((start_pos[0][0], start_pos[1][0])),
    "rot": set(r),
}

pq.put((0.0, next(counter), data))


def heuristic(pos: tuple, end: tuple) -> float:
    return 0
    return math.sqrt(sum([(pos[0] - end[0]) ** 2, (pos[1] - end[1]) ** 2]))


def move(pos, dir):
    match dir:
        case "<":
            if maze[pos[0], pos[1] - 1] == "#":
                return False, pos
            else:
                return True, (pos[0], pos[1] - 1)
        case ">":
            if maze[pos[0], pos[1] + 1] == "#":
                return False, pos
            else:
                return True, (pos[0], pos[1] + 1)
        case "^":
            if maze[pos[0] - 1, pos[1]] == "#":
                return False, pos
            else:
                return True, (pos[0] - 1, pos[1])
        case "v":
            if maze[pos[0] + 1, pos[1]] == "#":
                return False, pos
            else:
                return True, (pos[0] + 1, pos[1])


def rotate(item):
    r1, r2 = None, None
    if item["dir"] == l or item["dir"] == r:
        newrotu = item["rot"].copy()
        if not u in newrotu:
            newrotu.add(u)
            r1 = {
                "cost": item["cost"] + 1000,
                "dir": u,
                "pos": item["pos"],
                "seen": item["seen"].copy(),
                "rot": newrotu,
            }
        newrotd = item["rot"].copy()
        if not d in newrotd:
            newrotd.add(d)
            r2 = {
                "cost": item["cost"] + 1000,
                "dir": d,
                "pos": item["pos"],
                "seen": item["seen"].copy(),
                "rot": newrotd,
            }
    elif item["dir"] == d or item["dir"] == u:
        newrotr = item["rot"].copy()
        if not r in newrotr:
            newrotr.add(r)
            r1 = {
                "cost": item["cost"] + 1000,
                "dir": r,
                "pos": item["pos"],
                "seen": item["seen"].copy(),
                "rot": newrotr,
            }
        newrotl = item["rot"].copy()
        if not l in newrotl:
            newrotl.add(l)
            r2 = {
                "cost": item["cost"] + 1000,
                "dir": l,
                "pos": item["pos"],
                "seen": item["seen"].copy(),
                "rot": newrotl,
            }
    return r1, r2


result_costs = []
not_pos_counter = 0
while not pq.empty():
    f, _, item = pq.get()
    if item["pos"][0] == end_pos[0] and item["pos"][1] == end_pos[1]:
        result_costs.append(item["cost"])
        break
    h = heuristic(item["pos"], end_pos)
    r1, r2 = rotate(item)
    if not r1 is None:
        pq.put((r1["cost"] + h, next(counter), r1))
    if not r2 is None:
        pq.put((r2["cost"] + h, next(counter), r2))
    # if r1:
    # print("Rotate cost: ", r1["cost"])
    # elif r2:
    # print("Rotate cost: ", r2["cost"])
    possible, pos = move(item["pos"], item["dir"])
    if possible and not pos in item["seen"]:
        item["seen"].add(pos)
        # print("Len of seen: ", len(newseen))
        # print("Move h: ", h, " cost: ", item["cost"])
        pq.put(
            (
                item["cost"] + 1 + h,
                next(counter),
                {
                    "cost": item["cost"] + 1,
                    "dir": item["dir"],
                    "pos": pos,
                    "seen": item["seen"],
                    "rot": set(item["dir"]),
                },
            )
        )


print("Part 1: ", min(result_costs))
print("All costs: ", result_costs)
