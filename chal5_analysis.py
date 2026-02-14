import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# ===========================
# 1. Load the CSV
# ===========================
df = pd.read_csv("outputs/benchmark.csv")

# ===========================
# 2. Plot row-major vs column-major
# ===========================
plt.figure(figsize=(12,7))

# Plot each line with markers
plt.plot(df['Size'], df['Row_Static'], marker='o', label='Row-Major Static')
plt.plot(df['Size'], df['Col_Static'], marker='o', label='Column-Major Static')
plt.plot(df['Size'], df['Row_Dynamic'], marker='s', label='Row-Major Dynamic')
plt.plot(df['Size'], df['Col_Dynamic'], marker='s', label='Column-Major Dynamic')

plt.xlabel("Array Size (n)", fontsize=14)
plt.ylabel("Time (seconds)", fontsize=14)
plt.title("Row-Major vs Column-Major Performance (Static vs Dynamic Arrays)", fontsize=16)

plt.xscale('log')
plt.yscale('log')

# x_min = df['Size'].min()
# x_max = df['Size'].max()
# x_ticks = np.linspace(np.log10(x_min + 1), np.log10(x_max + 1), 8)
# plt.xticks(10**x_ticks, labels=[str(int(10**t)) for t in x_ticks])
x_ticks = (df['Size'])
plt.xticks(x_ticks, labels=[str(int(t)) for t in x_ticks])

y_min = df[['Row_Static','Col_Static','Row_Dynamic','Col_Dynamic']].min().min()
y_max = df[['Row_Static','Col_Static','Row_Dynamic','Col_Dynamic']].max().max()
y_ticks = np.linspace(np.log10(y_min), np.log10(y_max), 10)
plt.yticks(10**y_ticks, labels=[f"{10**t:.1e}" for t in y_ticks])

plt.grid(linestyle='--', linewidth=0.5, alpha=0.7)
plt.legend(fontsize=12)

plt.tight_layout()
plt.savefig("outputs/benchmark_plot.png")

# ===========================
# 5. Print analysis summary
# ===========================
print("\n=== Data Analysis Summary ===")
for idx, row in df.iterrows():
    size = row['Size']
    times = {
        'Row Static': row['Row_Static'],
        'Column Static': row['Col_Static'],
        'Row Dynamic': row['Row_Dynamic'],
        'Column Dynamic': row['Col_Dynamic']
    }
    fastest = min(times, key=times.get)
    slowest = max(times, key=times.get)
    speedup = times[slowest] / times[fastest]
    
    print(f"Size {size:.0f}: fastest = {fastest} ({times[fastest]:.6f}s), "
          f"slowest = {slowest} ({times[slowest]:.6f}s), "
          f"speedup factor = {speedup:.2f}x")
