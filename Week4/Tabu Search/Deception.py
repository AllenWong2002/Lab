import matplotlib.pyplot as plt

# 讀取 result.txt
iterations = []
values = []

with open("DeceptionResult.txt", "r") as file:
    for line in file:
        if line.strip() == "":
            continue
        it, val = line.strip().split()
        iterations.append(int(it))
        values.append(float(val))

# 繪圖
plt.figure(figsize=(10, 6))
plt.plot(iterations, values, label="The average value of each iteration across all runs", color="purple")

# 設定圖表格式
plt.xlabel("Iteration")
plt.ylabel("Objective Value")
plt.title("Deception Problem 10bits")
plt.xlim(0, 60)
plt.ylim(0, 800)
plt.grid(True)
plt.legend()

# 儲存圖檔
plt.savefig("DeceptionResult_10bits.png")
plt.show()
