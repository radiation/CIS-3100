class Sample (object):
    def __init__(self, val):
        self.__secret = val
    def get_secret(self):
        return self.__secret
    
s = Sample(42)
print(s.get_secret())