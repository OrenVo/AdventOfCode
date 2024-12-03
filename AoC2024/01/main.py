a = []

with open("00input", "r") as f:
    a = f.readlines()

l1 = [int(l.split("   ")[0]) for l in a]
l2 = [int(l.split("   ")[1]) for l in a]
l1copy = l1.copy()
l2copy = l2.copy()
pairs = []
while True:
    if len(l1) == len(l2) == 0:
        break
    else:
        m1 = min(l1)
        m2 = min(l2)
        pairs.append((m1, m2))
        l1.remove(m1)
        l2.remove(m2)


res = 0


def reduce(x):
    global res
    res = res + abs(x[0] - x[1])
    return x


for b in pairs:
    res = res + abs(b[0] - b[1])

print(res)
# part 2
l2dic = {}
for x in l2copy:
    if x in l2dic:
        l2dic[x] = l2dic[x] + 1
    else:
        l2dic[x] = 1
res2 = 0
for x in l1copy:
    if x in l2dic:
        res2 = res2 + (x * l2dic[x])
    else:
        ...
print(res2)
