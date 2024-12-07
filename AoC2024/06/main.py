import numpy as np
import multiprocessing

up = "^"
down = "v"
right = ">"
left = "<"
obstacle = "#"

mark = "X"

inp = []
with open("input") as f:
    inp = [[c for c in l.strip()] for l in f.readlines()]

arr = np.asarray(inp)
arr_part2 = arr.copy()

rot = np.rot90(arr, axes=(1, 0))

idx = np.where(rot == up)
starting_row = int(idx[0][0])
starting_col = int(idx[1][0])

# part 1
while True:
    idx = np.where(rot == up)
    row = int(idx[0][0])
    col = int(idx[1][0])
    ob_idx = np.where(rot[row, col::] == obstacle)
    if ob_idx[0].size == 0:  # no obstacles in path (going out of map)
        rot[row, col:] = mark
        break
    else:
        ob_idx = col + int(ob_idx[0][0]) - 1
        rot[row, col:ob_idx] = mark
        rot[row, ob_idx] = up
    rot = np.rot90(rot)


infinite_loops_count = multiprocessing.Value("i", 0)
# part 2 brute force


def isInfinite(arr):
    count = 0
    rot = np.rot90(arr, axes=(1, 0))
    while True:
        if count >= 100_000:
            return 1
        idx = np.where(rot == up)
        row = int(idx[0][0])
        col = int(idx[1][0])
        ob_idx = np.where(rot[row, col::] == obstacle)
        if ob_idx[0].size == 0:  # no obstacles in path (going out of map)
            # rot[row, col:] = mark
            return 0
        else:
            ob_idx = col + int(ob_idx[0][0]) - 1
            rot[row, col:ob_idx] = mark
            rot[row, ob_idx] = up
        rot = np.rot90(rot)
        count += 1


# processes = []
def update_counter(result, counter):
    with counter.get_lock():
        counter.value += result


pool = multiprocessing.Pool(processes=12)

for i in range(arr_part2.shape[0]):
    for j in range(arr_part2.shape[1]):
        arr_cpy = arr_part2.copy()
        if arr_cpy[i, j] == up:
            continue
        else:
            arr_cpy[i, j] = obstacle
        pool.apply_async(
            isInfinite,
            args=(arr_cpy,),
            callback=lambda result: update_counter(result, infinite_loops_count),
        )
        # processes.append(
        # multiprocessing.Process(
        # target=isInfinite, args=(arr_cpy, infinite_loops_count)
        # )
        # )

# running_processe = 0
# running = []
# while len(processes) != 0 or len(running) != 0:
# if len(processes) != 0:
# p = processes.pop(0)
# p.start()
# running.append(p)
# running_processe += 1
# if running_processe == 12:
# while len(running) > 0:
# r = running.pop(0)
# r.join()
# running_processe -= 1
#
# for r in running:
# r.join()
pool.close()
pool.join()

print(f"Part 1: {np.sum(arr == mark)}")
print(f"Part 2: {infinite_loops_count.value}")
