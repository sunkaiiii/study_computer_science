from math import sqrt
# 将字符串作为代码执行
exec("print('Hello world')")

scope = {}
exec('sqrt = 1', scope)# 为代码字符串提供命名空间
print(scope['sqrt'])