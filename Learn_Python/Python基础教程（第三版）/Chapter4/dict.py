from copy import deepcopy

# 函数dict
items = [('name','gumby'),('age',42)]
d = dict(items) # 从list当中映射
print(d)

# 将字符串格式设置功能用于字典
print("The name is {name}".format_map(d))

# 字典的copy是浅复制
# 当替换里面的值时候，原件不受影响。然而，如果是修改副本中值，原件也将发生变化
d['classmate'] = ['bob','dylan']
d2 = d.copy()
d3 = deepcopy(d)
d3['classmate'].append("tom")
d2['classmate'].append('harry')
print(d)
print(d3)

# 按照key 创建字典
print({}.fromkeys(['bob','tom']))
print({}.fromkeys(['bob','tom','jerry'],'noname'))


d = {}.fromkeys(['bob','tom','jerry'],'noname')
d2 = {"bob":"bob","tom":"tom"}
d.update(d2) # 使用一个字典的项来更新字典
print(d)
