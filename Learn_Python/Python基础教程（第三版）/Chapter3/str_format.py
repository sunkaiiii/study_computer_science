from string import Template

format = "Hello, %s. %s enough for ya?"
values = ('world', 'Hot')
print(format % values)

# 模板字符串
tmpl = Template("Hello, $who! $what enough for ya?")
print(tmpl.substitute(who="Mars", what="Dusty"))

# 替换风格的
print("{}, {} and {}".format("first", "second", "third"))
print("{3} {0} {2} {1} {3} {0}".format("be", "not", "or", "to"))

# 替换字段名
print("{foo} {} {bar} {}".format(1,2,bar=4,foo=3))

# 基本转换
print("The number is {num:f}".format(num=42))
print("The number is {num:b}".format(num=42))
print("The number is {num:x}".format(num=42))
print("The number is {num:,}".format(num=1000000)) # 千位分隔符