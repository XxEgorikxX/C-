import time
import matplotlib.pyplot as plt
import random

def insert_into_vector(massiv, index, value):
    if index < 0 or index > len(massiv):
        return massiv.copy()
    result = massiv.copy()
    result.insert(index, value)
    return result

ns = [10, 100, 1000, 10000, 100000, 500000, 1000000, 2000000, 5000000]
insert_times = []

for n in ns:
    my_vector = list(range(n))
    index = random.randint(0, n)
    value = 123
    start = time.perf_counter()
    insert_into_vector(my_vector, index, value)
    insert_times.append(time.perf_counter() - start)


plt.figure(figsize=(10, 6))
plt.plot(ns, insert_times, marker='o', label='Вставка в произвольное место')

plt.xlabel('Размер массива (n)', fontsize=12)
plt.ylabel('Время работы (секунды)', fontsize=12)
plt.title('Время вставки элемента в произвольное место массива', fontsize=14)
plt.legend()
plt.grid(True)
plt.xscale('log')
plt.yscale('log')
plt.tight_layout()
plt.show()