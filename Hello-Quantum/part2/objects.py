
class Celula:
    """
    Type Celula is used to represent the color of each of the circles of a qubit,
    It can assume three values, one for each possible state: active, inactive and uncertain.
    """
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


class Coordenada:
    """
    Type Coordenada is utilized to represent the position
    of a celula in a group of celulas organized in 3x3 matrix
    """

    def __init__(self, l, c) -> None:
        if not isinstance(l, int) or not isinstance(c, int) or l not in (0, 1, 2) or c not in (0, 1, 2):
            raise ValueError('cria_coordenada: argumentos invalidos')
        self.l = l
        self.c = c
    
    def get_line(self) -> int:
        return self.l
    
    def get_column(self) -> int:
        return self.c
    
    def __str__(self):
        return '(' + str(self.l) + ', ' + str(self.c) + ')'
    

class Tabuleiro:
    """
    The Tabuleiro type is used to store a pair of qubits and observation cells to query their values.
    A board corresponds to a matrix with 3 rows and 3 columns
    """
    def __init__(self) -> None:
        self.tab = [[-1, -1, -1], [-1, -1, -1], [None, -1]]
    
    def cpy_str(self, string) -> None:
        parts = string[1:-1].split(', ')
        for i in (0, 3, 6):
            parts[i] = parts[0][1:]
        for i in (2, 5, 7):
            parts[i] = parts[0][:-1]

        for index in range(len(parts)):
            if parts[index] not in ('-1', '0', '1'):
                raise ValueError('str_para_tabuleiro: argumentos invalidos')
            parts[index] = eval(parts[index])

        self.tab[0] = parts[:3]
        self.tab[1] = parts[3:6]
        self.tab[2] = parts[6:]