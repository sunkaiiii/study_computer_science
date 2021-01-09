from abc import ABC, abstractclassmethod

# 使用ABC和装饰器来标记方法为抽象的， 子类必须实现方法
class Talker(ABC):
    @abstractclassmethod
    def talk(self):
        pass

class Knigget(Talker):
    def talk(self):
        print("Hi")

# Talker() # 不能实例化
Knigget().talk() # 可以实例化