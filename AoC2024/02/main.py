def check_safety(l: list):
    isIncreasing = (l[0] - l[1]) > 0
    for i, x in enumerate(l):
        if i < len(l) - 1:
            if (1 > abs(l[i] - l[i + 1]) or abs(l[i] - l[i + 1]) > 3) or (
                (isIncreasing and (l[i] - l[i + 1]) < 0)
                or (not isIncreasing and (l[i] - l[i + 1]) > 0)
            ):
                return False
    return True


def check_safety_with_dampener(l: list):
    ls = []
    for i, y in enumerate(l):
        lc = l.copy()
        lc = lc[:i] + lc[i + 1 :]
        ls.append(lc)
    ls.append(l)

    for z in ls:
        if check_safety(z):
            return True
    return False


a = []

total = 0
total2 = 0


def check(a):
    diff = [a[i + 1] - a[i] for i in range(len(a) - 1)]
    if all(d > 0 and d <= 3 for d in diff) or all(d < 0 and d >= -3 for d in diff):
        return True
    return False


def checkrem(a):
    for i in range(len(a)):
        if check(a[:i] + a[i + 1 :]):
            return True
    return False


with open("00input", "r") as f:
    a = [[int(x) for x in l.split(" ")] for l in f.readlines()]

safe = [x for x in a if check_safety(x)]

not_safe = [x for x in a if not check_safety(x)]

print(len(safe))

print(len(safe) + len([x for x in not_safe if check_safety_with_dampener(x)]))

for i in a:
    if check(i):
        total += 1
    elif checkrem(i):
        total2 += 1
