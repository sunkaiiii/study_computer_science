class Rectangle:
    def __init__(self):
        self.width = 0
        self.heigh = 0
    
    def set_size(self,size):
        self.width, self.heigh = size
    
    def get_size(self):
        return self.width,self.heigh

    size = property(get_size,set_size) # 函数property

r = Rectangle()
r.width = 10
r.heigh = 5
print(r.size)
r.size = 150,50
print(r.size)
print(r.heigh,r.width)

