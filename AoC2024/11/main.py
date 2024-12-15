from functools import lru_cache

inp = []
with open("input") as f:
    inp = [int(num) for num in f.read().split(" ")]


def count_digits(x):
    count = 0
    while x > 0:
        x //= 10
        count += 1
    return count


@lru_cache(maxsize=None)
def blinkXTimes(stone, depth=25):
    while depth > 0:
        if stone == 0:
            stone = 1
            depth -= 1
            continue
        d_count = count_digits(stone)
        if d_count % 2 == 0:
            mask = 10 ** (d_count // 2)
            l = stone // mask
            r = stone % mask
            return blinkXTimes(l, depth - 1) + blinkXTimes(r, depth - 1)

        stone *= 2024
        depth -= 1
    return 1


print("Part 1: ", sum([blinkXTimes(x) for x in inp]))
print("Part 2: ", sum([blinkXTimes(x, 75) for x in inp]))
