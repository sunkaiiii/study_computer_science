import shelve

s = shelve.open('test.dat')
s['x'] = ['a','b','c']
temp = s['x'] # 使用临时对象
temp.append('d')
s['x'] = temp # 重新写入，以此来刷新文件
print(s['x'])