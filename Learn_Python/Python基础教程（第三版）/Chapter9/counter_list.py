class CounterList(list):
    def __init__(self, *args):
        super().__init__(*args)
        self.counter = 0
    def __getitem__(self,index):
        self.counter += 1
        return super(CounterList, self).__getitem__(index)

cl = CounterList(range(10))
print(cl)
cl.reverse()
print(cl)
del cl[3:6]
print(cl)
print(cl.counter)
cl[2]
cl[4]
print(cl.counter)