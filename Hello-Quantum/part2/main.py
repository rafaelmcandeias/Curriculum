from aux import *
from objects import *

"""
Main code
"""

def cria_celula(value):
    """ Creates a celule object

    Args: 1, 0, -1 value of the celule
    Returns: Object celule with that value
    """

    if isinstance(value, int) and value in (-1, 0, 1):
        return Celula(value)

    raise ValueError("cria_celula: argumento invalido")


def obter_valor(celule):
    """ Gets the value from the celule
    
    Args: The celule
    Returns: The value of the celule
    """

    return celule.get_value()


def inverte_estado(celule):
    """ Inverts the celule's state

    Args: The celule
    Returns: the celule with changed state
    """

    if celule.get_value() == 0:
        celule.set_value(1)
    
    elif celule.get_value() == 1:
        celule.set_value(0)

    return celule


def eh_celula(celule):
    """ Checks if the argument is a celule

    Args: celule
    Returns: Boolean
    """

    return isinstance(celule, Celula)


def celulas_iguais(c1, c2):
    """ Checks if the two cells are the same
    
    Args: Celules to compare
    Returns: Boolean
    """

    return eh_celula(c1) and eh_celula(c2) and c1.get_value() == c2.get_value()


def celula_para_str(celule):
    """ Returns a string that represents the cell
    
    Args: The cell
    """

    return celule.__str__()


def cria_coordenada(l, c):
    """ Returns the coordinate corresponding to line l and column c.
    If the arguments are not natural numbers or one of the arguments does not belong to the set {0, 1, 2},
    the function is undefined, on implementation it returns a ValueError with the message
    ’create_coordinate: invalid arguments’.
    
    Args: line number, column number
    """
    return Coordenada(l, c)


def coordenada_linha(coord):
    """ Returns the natural corresponding to the c coordinate line

    Args: Coordenada object
    """
    return coord.get_line()


def coordenada_coluna(coord):
    """ Returns the natural corresponding to the l coordinate line

    Args: Coordenada object
    """
    return coord.get_column()


def eh_coordenada(obj):
    """ Returns true only in case its argument is of Coordenada type
    
    Args: Any object
    """
    return isinstance(obj, Coordenada)


def coordenadas_iguais(coord1, coord2):
    """ Returns true only if c1 and c2 represent equal coordinates,
    that is, they represent the same position

    Args: two coordenada objects
    """
    return coord1.get_column() == coord2.get_column() and coord1.get_line() == coord2.get_line()


def coordenada_para_str(coord):
    return coord.__str__()


def tabuleiro_inicial():
    """ Returns the board that represents your initial game state, that is, the one represented in Figure 1.
    Note that the coordinate (2, 0) does not exist.
    """
    return Tabuleiro()


def str_para_tabuleiro(string):
    """ Returns the board corresponding to the string that is its argument.
    The string s corresponds to the internal representation of the board as used in the first project,
    that is, a string corresponding to a tuple of 3 tuples, the first two with 3 elements and the last with
    2 elements. The elements of these tuples are taken from the set {0,1,-1}.
    For example, '((-1, -1, -1), (0, 1, -1), (1, -1))'.
    Your function must guarantee the correctness of the argument,
    generating a ValueError with the message 'str_para_tabuleiro: argumentos invalidos'

    Args: String representation of the tabuleiro
    """
    tabuleiro = Tabuleiro()
    return tabuleiro.cpy_str(string)


def tabuleiro_dimensao(t):
    """ Returns the natural corresponding to the number of lines (and, consequently,
    also the number of columns) existing in t.
    """


"""
Code for testing
"""
def teste1():
    c0 = cria_celula(0)
    c1 = cria_celula(1)
    cx = cria_celula(-1)
    assert celula_para_str(c1) == '1'
    assert celula_para_str(c0) == '0'
    assert celula_para_str(cx) == 'x'
    assert celulas_iguais(c1,c0) == False
    c2 = cria_celula(1)
    assert celulas_iguais(c1,c2) == True
    assert eh_celula(c0) == True
    assert eh_celula(-2) == False
    assert eh_celula(2) == False
    assert celula_para_str(inverte_estado(c0)) == '1'
    assert celula_para_str(inverte_estado(c1)) == '0'
    assert celula_para_str(inverte_estado(cx)) == 'x'


def teste2():
    cd = cria_coordenada(0, 2)
    try:
        cria_coordenada(0, 'a')
        raise Exception
    except ValueError as ve:
        print(ve)
    assert coordenada_linha(cd) == 0
    assert coordenada_coluna(cd) == 2
    assert eh_coordenada(cd) == True
    assert eh_coordenada(('a',0)) == False
    assert coordenada_para_str(cd) == '(0, 2)'
    assert coordenadas_iguais(cd, cria_coordenada(0,2)) == True
    assert coordenadas_iguais(cd, cria_coordenada(2,0)) == False


def teste3():
    pass


if __name__ == "__main__":
    #teste1()
    #teste2()
    teste3()