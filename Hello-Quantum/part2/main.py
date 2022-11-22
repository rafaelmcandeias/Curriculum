from aux import *
from objects import *


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

    return c1.get_value() == c2.get_value()


def celula_para_str(celule):
    """ Returns a string that represents the cell
    
    Args: The cell
    """

    return celule.__str__()


# TESTE
def teste2_1():
    c0 = cria_celula(0)
    c1 = cria_celula(1)
    cx = cria_celula(-1)
    print(celula_para_str(c1))
    print(celula_para_str(cx))
    print(celula_para_str(c0))
    print(celulas_iguais(c1,c0))
    c2 = cria_celula(1)
    print(celulas_iguais(c1,c2))
    print(eh_celula(c0))
    print(eh_celula(-2))
    print(eh_celula(2))
    print(celula_para_str(inverte_estado(c0)))
    print(celula_para_str(inverte_estado(c1)))
    print(celula_para_str(inverte_estado(cx)))


