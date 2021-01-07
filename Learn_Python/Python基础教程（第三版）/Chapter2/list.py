names = ['Alice', 'Beth', 'Cecil', 'Dee-Dee', 'Earl']

del names[2] # 删除列表的元素

print(names)

names2 = ["bob","alen"]

names3 = names[2:] + names2 # 给切片赋值

print(names3)

names3[2:] = names

print(names3)

names3[1:4] = [] # 删除元素

print(names3)

names3[2:2] = names2

sorted_names = sorted(names3) #为列表排序
print(sorted_names)
print(names3)
names3.sort()
print(names3)

names3.sort(key=len) # 按照元素的长度排序
print(names3)