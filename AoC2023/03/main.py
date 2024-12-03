import re
import sys

def sum_numbers_from_input(input_lines: list):
    total_sum = 0
    for line in input_lines
        numbers = re.findall(r'\d+', line)
        for number in numbers:
            ...        
    
    return total_sum


input_lines = []

try:
    while(True):
        input_lines.append(input() + "\n")
except EOFError:
    ...
except KeyboardInterrupt:
    print("Program interrupted by user.")
    sys.exit(0)



result = sum_numbers_from_input(input_lines)
print(result)
