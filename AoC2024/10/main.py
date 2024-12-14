import numpy as np


inp = []
with open("input") as f:
    inp = [[int(c) for c in l.strip()] for l in f.readlines()]

arr = np.asarray(inp, dtype=np.int8)


def findTrailScores(arr, startIdx) -> int:
    res_indexes = set()
    stack = [startIdx]
    while len(stack) > 0:
        curr = stack.pop()
        if arr[curr] == 9:
            res_indexes.add(curr)
        else:
            if curr[0] - 1 >= 0 and arr[curr[0] - 1, curr[1]] - 1 == arr[curr]:
                stack.append((curr[0] - 1, curr[1]))
            if curr[1] - 1 >= 0 and arr[curr[0], curr[1] - 1] - 1 == arr[curr]:
                stack.append((curr[0], curr[1] - 1))
            if (
                curr[0] + 1 < arr.shape[0]
                and arr[curr[0] + 1, curr[1]] - 1 == arr[curr]
            ):
                stack.append((curr[0] + 1, curr[1]))
            if (
                curr[1] + 1 < arr.shape[1]
                and arr[curr[0], curr[1] + 1] - 1 == arr[curr]
            ):
                stack.append((curr[0], curr[1] + 1))
    return len(res_indexes)


def findTrailScores2(arr, startIdx) -> int:
    res = 0
    stack = [startIdx]
    while len(stack) > 0:
        curr = stack.pop()
        if arr[curr] == 9:
            res += 1
        else:
            if curr[0] - 1 >= 0 and arr[curr[0] - 1, curr[1]] - 1 == arr[curr]:
                stack.append((curr[0] - 1, curr[1]))
            if curr[1] - 1 >= 0 and arr[curr[0], curr[1] - 1] - 1 == arr[curr]:
                stack.append((curr[0], curr[1] - 1))
            if (
                curr[0] + 1 < arr.shape[0]
                and arr[curr[0] + 1, curr[1]] - 1 == arr[curr]
            ):
                stack.append((curr[0] + 1, curr[1]))
            if (
                curr[1] + 1 < arr.shape[1]
                and arr[curr[0], curr[1] + 1] - 1 == arr[curr]
            ):
                stack.append((curr[0], curr[1] + 1))
    return res


res = 0

starting_points = np.where(arr == 0)

for idx in zip(starting_points[0], starting_points[1]):
    res += findTrailScores(arr, idx)

res2 = 0
for idx in zip(starting_points[0], starting_points[1]):
    res2 += findTrailScores2(arr, idx)

print(f"Part 1: {res}")

print(f"Part 1: {res2}")
