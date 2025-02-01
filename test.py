p1 = (3.0, 4.0)
p2 = (6.0, 8.0)
center = (40.0, 30.0)


def distance(p1, p2):
    return ((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)**0.5

def area(a, b, c):
    return abs((a[0] * (b[1] - c[1]) + b[0] * (c[1] - a[1]) + c[0] * (a[1] - b[1])) / 2.0)

def perimeter(a, b, c):
    return distance(a, b) + distance(b, c) + distance(c, a)

print(area(p1, p2, center))
print(perimeter(p1, p2, center))