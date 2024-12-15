import numpy as np
from scipy.ndimage import label

inp = []
with open("test_input") as f:
    inp = [[c for c in l.strip()] for l in f.readlines()]

arr = np.asarray(inp)


def find_islands(matrix, value):
    mask = matrix == value
    labeled_array, num_features = label(mask)

    islands = []
    for label_num in range(1, num_features + 1):
        indices = np.argwhere(labeled_array == label_num)
        area = len(indices)  # Area is simply the number of cells

        perimeter = 0
        for index in indices:
            row, col = index
            neighbors = [(row - 1, col), (row + 1, col), (row, col - 1), (row, col + 1)]
            sides = set()
            for n_row, n_col in neighbors:
                if (
                    0 <= n_row < matrix.shape[0] and 0 <= n_col < matrix.shape[1]
                ):  # Check bounds
                    if labeled_array[n_row, n_col] != label_num:
                        perimeter += 1
                else:
                    perimeter += 1
        print(sides)
        islands.append(
            {
                "indices": [tuple(index) for index in indices],
                "area": area,
                "perimeter": perimeter,
                "result": perimeter * area,
                "result2": len(sides) * area,
            }
        )

    return islands


uniques, inverse, counts = np.unique(arr, return_inverse=True, return_counts=True)


res = 0
res2 = 0

for i, c in enumerate(uniques):
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
