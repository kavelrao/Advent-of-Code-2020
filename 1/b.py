target = 2020
result = 0
numbers = []
with open("input.txt") as f:
    numbers = f.read().splitlines()

for i in range(len(numbers)):
    for j in range(len(numbers)):
        for k in range(len(numbers)):
            if int(numbers[i]) + int(numbers[j]) + int(numbers[k])== target:
                result = int(numbers[i]) * int(numbers[j]) * int(numbers[k])

print(result)
