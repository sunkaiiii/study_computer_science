def print_params(titie, *params):
    print(titie)
    print(params)

# 收集关键字参数
def print_params_3(**params):
    print(params)

# *与**的组合使用
def print_params_4(x,y,z=3,*pospar,**keypar):
    print(x,y,z)
    print(pospar)
    print(keypar)

print_params('Params',2,3,4,5,6,7)

print_params_3(x=1,y=2,z=3)

print_params_4(1,2,3,4,5,6,7,foo=1,bar=2)

def add(x,y):
    return x+y

# 使用分配参数
params = (1,2)
print(add(*params))
# 查看作用域的变量
def see_vars():
    a = 1
    print(vars())
see_vars()
print(vars())