inp = ""
rules = dict()
sequences = []
with open("input", "r") as f:
    inp = f.read()

lines = inp.splitlines()
for l in lines:
    if len(r := l.split("|")) > 1:
        if (k := int(r[0])) in rules:
            rules[k].append(int(r[1]))
        else:
            rules[int(r[0])] = [int(r[1])]
    elif l == "":
        continue
    else:
        sequences.append([int(x) for x in l.split(",")])


def checkIfValid(seen: set, x: int, rules: dict) -> bool:
    for v in rules[x]:
        if v in seen:
            return False
    else:
        return True


def filterSequences(rules: dict, sequences: list) -> tuple[list, list]:
    res = []
    bad = []
    for s in sequences:
        seen = set()
        valid = True
        for x in s:
            if x in rules:
                if not (valid := checkIfValid(seen, x, rules)):
                    break
            seen.add(x)
        if valid:
            res.append(s)
        else:
            bad.append(s)

    return res, bad


def fixWrongSequences(rules: dict, sequences: list) -> list:
    res = []
    for s in sequences:
        valid = False
        fixed = s.copy()
        while not valid:
            valid = True
            seen = set()
            print("")
            for i, x in enumerate(fixed.copy()):
                print(x)
                if x in rules:
                    if not checkIfValid(seen, x, rules):
                        if i >= 1:
                            fixed[i], fixed[i - 1] = fixed[i - 1], fixed[i]
                            valid = False
                            break
                        else:
                            raise f"Error i: {i} is < 0 cannot swap with previous element."
                    else:
                        seen.add(x)
        res.append(fixed.copy())
    return res


valid, bad = filterSequences(rules, sequences)

part1 = sum(map(lambda x: x[int((len(x) - 1) / 2)], valid))
fixed = fixWrongSequences(rules, bad)
print(f"Part 1: {part1}")
print(f"Part 2: {sum(map(lambda x: x[int((len(x) - 1) / 2)], fixed))}")
