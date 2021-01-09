def flatten(nested):
    for sublist in nested:
        for element in sublist:
            yield element # 生成器

def flatten2(nested):
    try:
        try: nested + '' #不迭代类似于字符串对象
        except TypeError: pass
        else: raise TypeError
        for sublist in nested:
            for element in flatten2(sublist):
                yield element
    except TypeError:
        yield nested

nested = [[1, 2], [3, 4], [5]]
for num in flatten(nested):
    print(num)

for num in flatten2(nested):
    print(num)