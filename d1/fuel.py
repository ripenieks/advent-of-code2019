def calcFuel(mass):
    fuel = mass//3-2
    if fuel > 0:
        fuel = fuel+calcFuel(fuel)
    if fuel <= 0:
        fuel = 0;
    return fuel


with open("input.txt", "r") as f:
    data = f.readlines();

def work(data):
    s = 0
    for line in data:
        s = s + calcFuel(int(line))
    return s

print(work(data))
