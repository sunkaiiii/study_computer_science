class Secretive:
    def __inaccessible(self):
        print("Bet you can't see me...")
    
    def accessible(self):
        print("The secret message is:")
        self.__inaccessible()
    
class Filter:
    def init(self):
        self.blocked = []
    def filter(self, sequence):
        return [x for x in sequence if x not in self.blocked]

class SPAFilter(Filter): # SPAMFilter是Filter的子类
    def init(self):
        self.blocked = ['SPAM']


class Calculator:
    def calculate(self, expression):
        self.value = eval(expression)
class Talker:
    def talk(self):
        print('Hi, my value is', self.value)

# 多重继承
class TalkingCalculator(Calculator, Talker): pass

s = Secretive()
s.accessible()
# s.__inaccessible() # 不可以直接调用私有方法

print(issubclass(SPAFilter, Filter)) # 判断是否为子类

