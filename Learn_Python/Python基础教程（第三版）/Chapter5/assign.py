# 序列解包
values = 1,2,3
print(values)
x,y,z = values
print(x)

a,b,*rest = [1,2,3,4] # 使用星号运算符来收集多余的值
print(rest)

a,*rest,b = [1,2,3,4] # 还可以将星号放在别的位置
print(rest)