str_list = ['ad','sad','gvsdfh','qwdqwrt']
print(str_list[-1]) # 当使用负数索引时，Python将从右开始往左数。因此-1是最后一个元素的位置

print(str_list[1:3]) # 切片
print(str_list[-3:])

print(str_list[::2]) # 指定步长

print(str_list * 5) # 重复创建序列
