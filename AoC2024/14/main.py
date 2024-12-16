import numpy as np
from PIL import Image


def parse_line(l: str):
    splited = l.split(" ")
    p, v = splited[0], splited[1]
    p = p.split(",")
    v = v.split(",")

    return {
        "P": (int(p[0][2:]), int(p[1])),
        "V": (int(v[0][2:]), int(v[1])),
    }


width, height = 101, 103  # 7, 11


def move(pos: tuple, velocity: tuple) -> tuple:
    global width, height
    x = pos[0]
    y = pos[1]
    x += velocity[0]
    y += velocity[1]
    if x < 0:
        x += width
    if y < 0:
        y += height
    if x >= width:
        x -= width
    if y >= height:
        y -= height
    return x, y


inp = []

with open("input") as f:
    inp = [parse_line(l) for l in f.readlines()]


arr = np.zeros((width, height))

for robot in inp:
    pos = robot["P"]
    for i in range(100):
        pos = move(pos, robot["V"])
    arr[pos] += 1
row_mid = width // 2
col_mid = height // 2
arr[row_mid, :] = 0
arr[:, col_mid] = 0

q0 = np.sum(arr[:row_mid, :col_mid])
q0 *= np.sum(arr[:row_mid, col_mid:])
q0 *= np.sum(arr[row_mid:, :col_mid])
q0 *= np.sum(arr[row_mid:, col_mid:])

print("Part 1: ", int(q0))

for i in range(10_000):
    pic = np.zeros((width, height), np.uint8)
    for robot in inp:
        pos = robot["P"]
        robot["P"] = move(pos, robot["V"])
        pic[pos] += 1
    un = np.unique(pic)
    nz = np.where(pic != 0)
    z = np.where(pic == 0)
    pic[nz] = 255
    pic[z] = 0
    if len(un) == 2:
        print(f"Possible solution: {i}")
    if len(un) == len(inp) + 1:
        print(f"Possible solution: {i}")
    img = Image.fromarray(pic, mode="L").save(
        f"imgs/pic_{i}.png"
    )  # for visual confirmation
