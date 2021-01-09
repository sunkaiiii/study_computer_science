class Fibs:
    def __init__(self):
        self.a = 0 
        self.b = 1
    
    # next方法
    def __next__(self):
        self.a,self.b=self.b,self.a+self.b
        return self.a
    # 迭代器
    def __iter__(self):
        return self

# 带有终止的迭代器
class Fibs2:
    def __init__(self):
        self.a = 0 
        self.b = 1
    
    # next方法
    def __next__(self):
        self.a,self.b=self.b,self.a+self.b
        if self.a > 1000:
            raise StopIteration
        return self.a
    # 迭代器
    def __iter__(self):
        return self


fibs = Fibs()
for f in fibs:
    if f > 1000:
        print(f)
        break
fibs = Fibs2()
for f in fibs:
    print(f)