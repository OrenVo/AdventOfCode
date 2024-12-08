import numpy as np

inp = []
with open("input") as f:
    inp = [[c for c in l.strip()] for l in f.readlines()]

arr = np.asarray(inp)

res_arr = np.full(arr.shape, 0, np.uint8)
res2_arr = np.full(arr.shape, 0, np.uint8)
unique_chars, inverse, counts = np.unique(arr, return_inverse=True, return_counts=True)


def createAntinodeIndices(
    idx_a: tuple[np.int64, np.int64], idx_b: tuple[np.int64, np.int64]
) -> tuple[tuple[np.int64, np.int64], : tuple[np.int64, np.int64]]:
    x = idx_b[0] - idx_a[0]
    y = idx_b[1] - idx_a[1]
    res_A, res_B = (idx_a[0] - x, idx_a[1] - y), (idx_b[0] + x, idx_b[1] + y)
    return res_A, res_B


for i, c in enumerate(unique_chars):
    if c == ".":
        continue
    indices = np.where(inverse == i)
    for idx_a in zip(indices[0], indices[1]):
        for idx_b in zip(indices[0], indices[1]):
            if idx_a == idx_b:
                continue
            inds = createAntinodeIndices(idx_a, idx_b)

            if (
                inds[0][0] < arr.shape[0]
                and inds[0][0] >= 0
                and inds[0][1] < arr.shape[1]
                and inds[0][1] >= 0
                # and arr[inds[0]] == "."
            ):
                res_arr[inds[0]] = 1
            if (
                inds[1][0] < arr.shape[0]
                and inds[1][0] >= 0
                and inds[1][1] < arr.shape[1]
                and inds[1][1] >= 0
                # and arr[inds[1]] == "."
            ):
                res_arr[inds[1]] = 1


p1 = np.sum(res_arr)
# with open("test_output", "w") as f:
#     for a in arr:
#         for c in a:
#             f.write(c)
#         f.write("\n")


def createAntinodeIndicesPart2(
    idx_a: tuple[np.int64, np.int64],
    idx_b: tuple[np.int64, np.int64],
    shape: any,
) -> list[tuple[tuple[np.int64, np.int64], : tuple[np.int64, np.int64]]]:
    x = idx_b[0] - idx_a[0]
    y = idx_b[1] - idx_a[1]
    res = []
    res.append((idx_a[0] - x, idx_a[1] - y))

    while 0 <= res[-1][0] < shape[0] and 0 <= res[-1][1] < shape[1]:
        res.append((res[-1][0] - x, res[-1][1] - y))

    _ = res.pop()
    res.append((idx_b[0] + x, idx_b[1] + y))
    while 0 <= res[-1][0] < shape[0] and 0 <= res[-1][1] < shape[1]:
        res.append((res[-1][0] + x, res[-1][1] + y))
    res.pop()
    return res


def part2():
    for i, c in enumerate(unique_chars):
        if c == ".":
            continue
        indices = np.where(inverse == i)
        for idx_a in zip(indices[0], indices[1]):
            for idx_b in zip(indices[0], indices[1]):
                if idx_a == idx_b:
                    if counts[i] > 1:
                        res2_arr[idx_a] = 1
                    continue
                indss = createAntinodeIndicesPart2(idx_a, idx_b, arr.shape)
                for inds in indss:
                    if (
                        inds[0] < arr.shape[0]
                        and inds[0] >= 0
                        and inds[1] < arr.shape[1]
                        and inds[1] >= 0
                        # and arr[inds[0]] == "."
                    ):
                        res2_arr[inds] = 1


part2()
p2 = np.sum(res2_arr)

print(f"Part 1: {p1}")
print(f"Part 2: {p2}")
