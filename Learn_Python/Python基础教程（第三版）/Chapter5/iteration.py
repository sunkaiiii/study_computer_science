names = ['anne', 'beth', 'george', 'damon'] 
ages = [12, 45, 32, 102]

# 合并迭代工具
print(list(zip(names,ages)))

# 迭代时获取索引
for x in enumerate(ages):
    print(x)


# 简单推到
[print(x * x) for x in range(10)]
[print(x*x) for x in range(10) if x%3==0]