import matplotlib.pyplot as plt

# 讀取城市路徑
cities = []
with open("best_path.txt", "r") as f:
    for line in f:
        parts = line.strip().split()
        if len(parts) == 3:
            city_id, x, y = map(int, parts)
            cities.append((city_id, x, y))

# 拆成座標序列
x = [c[1] for c in cities]
y = [c[2] for c in cities]
labels = [str(c[0]) for c in cities]

plt.figure(figsize=(10, 8))
plt.plot(x, y, 'r-', linewidth=1.5)   # 路徑線
plt.scatter(x, y, c='blue')           # 城市點

# 顯示編號
for i, txt in enumerate(labels):
    plt.text(x[i] + 0.5, y[i] + 0.5, txt, fontsize=9, color='black')

plt.title("ACO TSP Best Path")
plt.xlabel("X")
plt.ylabel("Y")
plt.grid(True)
plt.axis('equal')
plt.tight_layout()
plt.savefig("result.png", dpi = 480)
plt.show()