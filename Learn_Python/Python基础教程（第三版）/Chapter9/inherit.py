class Bird:
    def __init__(self):
        self.hungry = True
    
    def eat(self):
        if self.hungry:
            print('Aaah...')
            self.hungry = False
        else:
            print("No, thanks")

class SongBird(Bird):
    def __init__(self):
        super().__init__() # 调用父类构造方法
        self.sound = 'Squak!'

    def sing(self):
        print(self.sound)


sb = SongBird()
sb.sing()
sb.eat()
sb.eat()