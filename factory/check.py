import numpy as np

def exp(x, a, b, c, x0):
    return a + b * np.exp(c * (x - x0))

if __name__ == '__main__':
    x = np.arange(0, 10.25, 0.25)
    print(x)
    print(*exp(x, 1, 2, 0.5, 0))