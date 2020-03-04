import io

class Test:
    def func(self, other = None):
        print("Func: " + str(self.func))
        if (other is not None):
            print("other: " + str(other))

obj = Test()
obj.func()