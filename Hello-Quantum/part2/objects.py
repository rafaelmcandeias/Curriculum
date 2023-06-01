
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
    
    def invert(self):
        if self.value != 1:
            self.value = 1 - self.value
        return self.value


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
        self.tab = ((Celula(-1), Celula(-1), Celula(-1)),
                    (Celula(0), Celula(0), Celula(-1)),
                    (Celula(0), Celula(-1)))
    
    def cpy_str(self, string) -> None:
        parts = string[1:-1].split(', ')
        for i in (0, 3, 6):
            parts[i] = parts[i][1:]
        for i in (2, 5, 7):
            parts[i] = parts[i][:-1]

        for index in range(len(parts)):
            if parts[index] not in ('-1', '0', '1'):
                raise ValueError('str_para_tabuleiro: argumentos invalidos')
            parts[index] = Celula(eval(parts[index]))

        # convert from tuple to list for easier manipulation
        list_tab = list(list(sub) for sub in self.tab)

        list_tab[0] = parts[:3]
        list_tab[1] = parts[3:6]
        list_tab[2] = parts[6:]

        # store again as a tuple
        self.tab = tuple(tuple(sub) for sub in list_tab)
        return self
    
    def get_lines(self):
        return 3
    
    def get_columns(self):
        return 3

    def get_tab(self):
        return self.tab
    
    def get_celula(self, coord):
        return self.tab[coord.get_line()][coord.get_column()]
    
    def update_cel(self, cel, coord):
        self.tab[coord.get_line()][coord.get_column()] = cel
        return self
    
    def invert_on_coord(self, coord):
        self.tab[coord.get_line()][coord.get_column()].invert()
        return self
    
    def is_tab(self):
        if not isinstance(self.tab, tuple):
            return False

        for coll in self.tab:
            if not isinstance(coll, tuple):
                return False
        for val in coll:
            if not isinstance(val, Celula):
                return False
        return True
