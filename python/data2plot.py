import matplotlib.pyplot as plt

import matplotlib.pyplot as plt

# 读取文件内容
data = []
with open('doc/PerformanceResult.txt', 'r') as file:
    for line in file:
        value = float(line.strip())  # 假设每行的数据是浮点数，需要根据实际情况进行适配
        data.append(value)

# 绘制图形
x = range(1, len(data) + 1)
y = data

plt.plot(x, y)
plt.xlabel('thread number')
plt.ylabel('time')
plt.title('performance')

# 保存图像
plt.savefig('doc/performance')

# 显示图形
plt.show()