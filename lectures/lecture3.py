# Lecture 3, 20240205

from math import sqrt


def all_the_math(x):
    numerator = ((4 * x**3) - (12*x**2) - (9 * x) + 27)
    denominator = (sqrt(5 * x**2 + 2) + (3 * abs(x - 2.5)))
    return numerator/denominator

def main():
    x = -3
    while x <= 4:
        decorator = "POSITIVE"
        y = all_the_math(x)
        if y == 0:
            decorator = "ZERO"
        elif y < 0:
            decorator = "NEGATIVE"
        print(f"x={x}, y={y} Y IS {decorator}")
        x += .5

main()