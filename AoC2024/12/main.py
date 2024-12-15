import numpy as np
from scipy.ndimage import label

inp = []
with open("test_input") as f:
    inp = [[c for c in l.strip()] for l in f.readlines()]

arr = np.asarray(inp)


def inbound(idx):
    r, c = idx[0], idx[1]
    return 0 <= r < arr.shape[0] and 0 <= c < arr.shape[1]


def sides(idx, arr):
    # UP, RIGHT, DOWN, LEFT aka North, East, South, West
    dR = [-1, 0, 1, 0]
    dC = [0, 1, 0, -1]
    plant_sides = 0
    row, col = idx[0], idx[1]
    plant = arr[row][col]
    for i in range(4):
        newR = row + dR[i]
        newC = col + dC[i]
        if not inbound((newR, newC)) or arr[newR][newC] != plant:
            newR_90CC = row + dR[(i - 1) % 4]
            newC_90CC = col + dC[(i - 1) % 4]
            isBeginEdge = (
                not inbound((newR_90CC, newC_90CC))
                or arr[newR_90CC][newC_90CC] != plant
            )

            newR_Corner = newR + dR[(i - 1) % 4]
            newC_Corner = newC + dC[(i - 1) % 4]
            isConcaveBeginEdge = (
                inbound((newR_Corner, newC_Corner))
                and arr[newR_Corner][newC_Corner] == plant
            )

            if isBeginEdge or isConcaveBeginEdge:
                plant_sides += 1
    return plant_sides


def find_islands(matrix, value):
    mask = matrix == value
    labeled_array, num_features = label(mask)

    islands = []
    for label_num in range(1, num_features + 1):
        indices = np.argwhere(labeled_array == label_num)
        area = len(indices)  # Area is simply the number of cells

        perimeter = 0
        side_counts = 0
        for index in indices:
            row, col = index
            neighbors = [(row - 1, col), (row + 1, col), (row, col - 1), (row, col + 1)]
            for n_row, n_col in neighbors:
                if (
                    0 <= n_row < matrix.shape[0] and 0 <= n_col < matrix.shape[1]
                ):  # Check bounds
                    if labeled_array[n_row, n_col] != label_num:
                        perimeter += 1
                else:
                    perimeter += 1
            side_counts += sides(indices[0], matrix)
        print("Side counts: ", side_counts)
        print("       Area: ", area, "\n")
        islands.append(
            {
                "indices": [tuple(index) for index in indices],
                "area": area,
                "perimeter": perimeter,
                "result": perimeter * area,
                "result2": side_counts * area,
            }
        )

    return islands


uniques, inverse, counts = np.unique(arr, return_inverse=True, return_counts=True)


res = 0
res2 = 0
print(arr)
for i, c in enumerate(uniques):
    print("Plant: ", c)
    mask_0 = np.where(inverse != i)
    mask_1 = np.where(inverse == i)
    cpy = inverse.copy()
    cpy[mask_0] = 0
    cpy[mask_1] = 1
    idxs = find_islands(cpy, 1)
    for i in idxs:
        res += i["result"]
        res2 += i["result2"]

print("Part 1: ", res)
print("Part 2: ", res2)
