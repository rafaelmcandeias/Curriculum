from aux import *
from objects import *

"""
Main code
"""

def cria_celula(value: int) -> Celula:
    """ Creates a celule object

    Args: 1, 0, -1 value of the celule
    Returns: Object celule with that value
    """

    if isinstance(value, int) and value in (-1, 0, 1):
        return Celula(value)

    raise ValueError("cria_celula: argumento invalido")


def obter_valor(celule: Celula) -> int:
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
    return str(t.get_lines()) + ', ' + str(t.get_columns())


def tabuleiro_celula(t, coord):
    """ Returns the cell present in the color coordinate of the t board.
    
    Args: Tabuleiro and Coordinadas
    """
    return t.get_cel(coord)


def tabuleiro_substitui_celula(t, cel, coord):
    """ Returns the board that results from replacing the existing cell in the coor coordinate of the board,
    with the new cell. Your function must verify the correctness of the arguments, generating a
    ValueError with the message: 'tabuleiro_substitui_celula: argumentos invalidos'
    
    Args: Tabuleiro, Celula and Coordinate
    """
    if not eh_tabuleiro(t) or not eh_celula(cel) or not eh_coordenada(coord):
        raise ValueError('tabuleiro_substitui_celula: argumentos invalidos')
    return t.update_cel(cel, coord)


def tabuleiro_inverte_estado(t, coord):
    """ Returns the board that results from inverting the state of the cell present in the coor coordinate of
    the board. Your function must check the correctness of the arguments, generating a
    ValueError with the message: 'tabuleiro_inverte_estado: argumentos invalidos'
    
    Args: Tabuleiro and Coordinada
    """
    if not eh_tabuleiro(t) or not eh_coordenada(coord):
        raise ValueError('tabuleiro_substitui_celula: argumentos invalidos')
    return t.invert_on_coord(coord)


def eh_tabuleiro(arg):
    """ Returns true only in case arg is of type tabuleiro.
    
    Args: Object
    """
    if not isinstance(arg, Tabuleiro):
        return False
    
    return arg.is_tab()


def tabuleiros_iguais(t1, t2):
    """ Returns true only in case t1 and t2 are Tabuleiros that contain
    equal cells in each of the coordinates
    
    Args: Tabuleiro and Tabuleiro
    """
    tab1, tab2 = t1.get_tab(), t2.get_tab()

    for l in range(len(tab1)):
        for c in range(len(tab1[l])):
            if not celulas_iguais(tab1[l][c], tab2[l][c]):
                return False
    return True


def tabuleiro_para_str(t):
    """ Returns the character string that represents its argument.
    The external representation is identical to the one presented in the first project
    
    Args: Tabuleiro
    """
    return '+-------+\n|...{}...|\n|..{}.{}..|\n|.{}.{}.{}.|\n|..{}.{}..|\n+-------+'.format(
        t.get_cel(Coordenada(0, 2)).__str__(),
        t.get_cel(Coordenada(0, 1)).__str__(), t.get_cel(Coordenada(1, 2)).__str__(),
        t.get_cel(Coordenada(0, 0)).__str__(), t.get_cel(Coordenada(1, 1)).__str__(), t.get_cel(Coordenada(2, 1)).__str__(),
        t.get_cel(Coordenada(1, 0)).__str__(), t.get_cel(Coordenada(2, 0)).__str__()
    )


def porta_x(t, p):
    """ Returns the board resulting from applying the X gate to the bottom
    cell of the left or right qubit, depending on whether p is 'E' or 'D', respectively.
    The function must check the validity of its arguments, generating
    a ValueError with the message: 'porta_x: argumentos invalidos.'
    
    Args: Tabuleiro and Porta direction for the operation
    """
    if not eh_tabuleiro(t) or not isinstance(p, str) or p not in ('E', 'D'):
        raise ValueError('porta_x: argumentos invalidos.')
    
    if p == 'E':
        coords = Coordenada(1, 0), Coordenada(1, 1), Coordenada(1, 2)
    else:
        coords = Coordenada(0, 1), Coordenada(1, 1), Coordenada(2, 0)
    
    for c in coords:
        t.invert_on_coord(c)
    
    return t


def porta_z(t, p):
    """ Returns the board resulting from applying the Z gate to the top cell
    of the left or right qubit, depending on whether p is 'E' or 'D', respectively.
    The function must check the validity of its arguments,
    generating a ValueError with the message: 'porta_z: argumentos invalidos.'
    
    Args: Tabuleiro and Porta direction for the operation
    """
    if not eh_tabuleiro(t) or not isinstance(p, str) or p not in ('E', 'D'):
        raise ValueError('porta_x: argumentos invalidos.')

    if p == 'E':
        coords = Coordenada(0, 0), Coordenada(0, 1), Coordenada(0, 2)
    else:
        coords = Coordenada(0, 2), Coordenada(1, 2), Coordenada(2, 1)

    for c in coords:
        t.invert_on_coord(c)

    return t


def porta_h(t, p):
    """ Returns the board resulting from applying the H gate to the left or right qubit,
    depending on whether p is 'E' or 'D', respectively. The function must check
    the validity of its arguments, generating a ValueError with the
    message: 'porta_h: argumentos invalidos.'
    
    Args: Tabuleiro and Porta direction for the operation
    """
    if not eh_tabuleiro(t) or not isinstance(p, str) or p not in ('E', 'D'):
        raise ValueError('porta_x: argumentos invalidos.')
    
    new_tabuleiro = t.cpy()

    if p == 'E':
        top_coords = ((0, 0), (0, 1), (0, 2))
        bottom_coords = ((1, 0), (1, 1), (1, 2))
    
    else:
        top_coords = ((0, 2), (1, 2), (2, 1))
        bottom_coords = ((0, 1), (1, 1), (2, 0))
    
    # update top line
    for index in range(len(top_coords)):
        top_coord = Coordenada(top_coords[index][0], top_coords[index][1])
        bottom_coord = Coordenada(bottom_coords[index][0], bottom_coords[index][1])
        bottom_cel = t.get_cel(bottom_coord)
        new_tabuleiro.cpy_cel(top_coord, bottom_cel)
    
    # update bottom line
    for index in range(len(bottom_coords)):
        bottom_coord = Coordenada(bottom_coords[index][0], bottom_coords[index][1])
        top_coord = Coordenada(top_coords[index][0], top_coords[index][1])
        top_cel = t.get_cel(top_coord)
        new_tabuleiro.cpy_cel(bottom_coord, top_cel)

    return new_tabuleiro


def hello_quantum(string):
    """ Main game function that allows you to play a complete game of Hello Quantum.
    The hello_quantum function receives a character string containing the description
    of the objective board and the maximum number of moves. The function returns true if
    the player manages to transform the initial board into the objective board, not
    exceeding the indicated number of moves, and returns false otherwise.
    The maximum number of moves is displayed immediately after the objective board
    description, separated by ':'.
    For example, hello_quantum('((-1, -1, -1), (0, 1, -1), (1, -1)):1').
    """
    print('Bem-vindo ao Hello Quantum!')
    print('O seu objetivo e chegar ao tabuleiro:')
    
    game_str, max_plays = string.split(':')
    final_tab = str_para_tabuleiro(game_str)
    
    print(tabuleiro_para_str(final_tab))
    print('Comecando com o tabuleiro que se segue:')
    tab = tabuleiro_inicial()
    print(tabuleiro_para_str(tab))

    plays = 0
    while plays < eval(max_plays):
        port = input('Escolha uma porta para aplicar (X, Z ou H): ')
        direc = input('Escolha um qubit para analisar (E ou D): ')
        if port == 'X':
            tab = porta_x(tab, direc)
        elif port == 'Z':
            tab = porta_z(tab, direc)
        else:
            tab = porta_h(tab, direc)
        
        plays += 1
        print(tabuleiro_para_str(tab))
        
        if tabuleiros_iguais(tab, final_tab):
            print('Parabens, conseguiu converter o tabuleiro em ' + str(plays) + ' jogadas!')
            return True
    return False