import matplotlib.pyplot as plt
import numpy as np
import math
import sys


a = float(sys.argv[1])
b = float(sys.argv[2])
N = int(sys.argv[3])
dots = sys.argv[4:2*N+4]  # узлы аппроксимации
data = sys.argv[2*N+4:]  # данный о x, многочлене и функции в этих точках

x = np.array([float(data[i]) for i in range(0, len(data), 3)])

y_lagrange = np.array([float(data[i]) for i in range(1, len(data), 3)])
y_true = np.array([float(data[i]) for i in range(2, len(data), 3)])

x_dots = np.array([float(dots[i]) for i in range(0, len(dots), 2)])
y_dots = np.array([float(dots[i]) for i in range(1, len(dots), 2)])

# дальше только графика
fig, ax = plt.subplots()

y_max = math.ceil(max(y_lagrange.max(), y_true.max()))
y_min = min(y_lagrange.min(), y_true.min()) // 1

ax.plot(x, y_lagrange, "k:", linewidth=2.0, label="L(x)")
ax.plot(x, y_true, "k", linewidth=2.0, label="f(x)")
ax.plot(x_dots, y_dots, "o")
ax.legend()
ax.set(xlim=(a//1, math.ceil(b)), xticks=np.arange(a//1, math.ceil(b)+1),
       ylim=(y_min, y_max), yticks=np.arange(y_min, y_max+1))

plt.show()