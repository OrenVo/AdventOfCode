import re

num_reg = re.compile(r"\d+")
inp = []

with open("input") as f:
    inp = f.readlines()

parsed = []
i = 0
while i < len(inp):
    if "Button A" in inp[i]:
        A = num_reg.findall(inp[i])
        B = num_reg.findall(inp[i + 1])
        prize = num_reg.findall(inp[i + 2])
        parsed.append(
            {
                "A": {"X": int(A[0]), "Y": int(A[1])},
                "B": {"X": int(B[0]), "Y": int(B[1])},
                "P": {"X": int(prize[0]), "Y": int(prize[1])},
            }
        )
        i += 3
    else:
        i += 1

#
#
#
#
#
#


def solve(x):
    x1 = x["A"]["X"]
    x2 = x["A"]["Y"]
    y1 = x["B"]["X"]
    y2 = x["B"]["Y"]
    p1 = x["P"]["X"]
    p2 = x["P"]["Y"]
    # print(x1, x2, y1, y2, p1, p2)
    b = (p2 * x1 - p1 * x2) // (y2 * x1 - y1 * x2)
    a = (p1 - b * y1) // x1
    # print(b, a, "\n")
    # print((int(x1 * a + y1 * b), int(x2 * a + y2 * b)) == (p1, p2))
    if (x1 * a + y1 * b, x2 * a + y2 * b) != (p1, p2):
        return 0
    else:
        return a * 3 + b


def solve2(x):
    x1 = x["A"]["X"]
    x2 = x["A"]["Y"]
    y1 = x["B"]["X"]
    y2 = x["B"]["Y"]
    p1 = x["P"]["X"] + 10000000000000
    p2 = x["P"]["Y"] + 10000000000000
    # print(x1, x2, y1, y2, p1, p2)
    b = (p2 * x1 - p1 * x2) // (y2 * x1 - y1 * x2)
    a = (p1 - b * y1) // x1
    # print(b, a, "\n")
    # print((int(x1 * a + y1 * b), int(x2 * a + y2 * b)) == (p1, p2))
    if (x1 * a + y1 * b, x2 * a + y2 * b) != (p1, p2):
        return 0
    else:
        return a * 3 + b


print("Part 1: ", sum([solve(x) for x in parsed]))
print("Part 2: ", sum([solve2(x) for x in parsed]))
