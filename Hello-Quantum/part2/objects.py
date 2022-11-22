
class Celula:

    def __init__(self, value):
        self.value = value
    
    def get_value(self):
        return self.value
    
    def set_value(self, value):
        self.value = value
    
    def __str__(self):
        if self.value == -1:
            return 'x'
        return str(self.value)
