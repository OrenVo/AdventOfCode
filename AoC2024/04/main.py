import numpy as np
import re

regex = re.compile(r"XMAS")
regex2 = re.compile(r"SAMX")
inp = []
cum_sum = 0
with open("input", "r") as f:
    for line in f.readlines():
        cum_sum = sum([len(regex.findall(line)), len(regex2.findall(line)), cum_sum])
        inp.append([c for c in line.strip()])


matrix = np.asarray(inp)
for r in matrix.T:
    line = "".join(c for c in r)
    cum_sum = sum([len(regex.findall(line)), len(regex2.findall(line)), cum_sum])


for i in range(-matrix.shape[0] + 1, matrix.shape[1]):
    diagonal1 = np.diagonal(matrix, offset=i)
    diagonal2 = np.diagonal(np.fliplr(matrix), offset=i)
    diagonal_string = "".join(c for c in diagonal1)
    cum_sum = sum(
        [
            len(regex.findall(diagonal_string)),
            len(regex2.findall(diagonal_string)),
            cum_sum,
        ]
    )
    diagonal_string2 = "".join(c for c in diagonal2)
    cum_sum = sum(
        [
            len(regex.findall(diagonal_string2)),
            len(regex2.findall(diagonal_string2)),
            cum_sum,
        ]
    )

print(f"Part 1: {cum_sum}")

# Part 2

pattern1 = np.array([["M", "_", "S"], ["_", "A", "_"], ["M", "_", "S"]])
pattern2 = np.rot90(pattern1)
pattern3 = np.rot90(pattern2)
pattern4 = np.rot90(pattern3)

mask = np.array([[True, False, True], [False, True, False], [True, False, True]])

window = np.lib.stride_tricks.sliding_window_view(matrix, (3, 3))
masked_window = np.where(mask, window, "_")
masked_pattern1 = np.where(mask, pattern1, "_")
masked_pattern2 = np.where(mask, pattern2, "_")
masked_pattern3 = np.where(mask, pattern3, "_")
masked_pattern4 = np.where(mask, pattern4, "_")

count2 = sum(
    [
        np.sum(np.all(masked_window == masked_pattern1, axis=(2, 3))),
        np.sum(np.all(masked_window == masked_pattern2, axis=(2, 3))),
        np.sum(np.all(masked_window == masked_pattern3, axis=(2, 3))),
        np.sum(np.all(masked_window == masked_pattern4, axis=(2, 3))),
    ]
)
print(f"Part 2: {count2}")
