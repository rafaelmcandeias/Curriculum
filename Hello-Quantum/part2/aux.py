

def add_x(tabuleiro):
    """ Function that returns a tuple equal to the given one but with x's instead of -1. """
    tab_to_print = ()
    for line in tabuleiro:
        for state in line:
            if state == -1:
                tab_to_print += ('x', )
            else:
                tab_to_print += (state, )
    return tab_to_print


def switch_bit(bit):
    """ Function that replaces a bit 0 to 1 and bit 1 to 0. """
    if bit != -1:
        return 1 - bit
    
    return bit


def switch_line(line):
    """ Function that switches all bits in a line. """
    new_line = ()
    for bit in line:
        new_line += (switch_bit(bit), )
    return new_line


def eh_tabuleiro(tabuleiro):
    """ Function that receives any type of variable.
        Checks if it is a tabuleiro.
    """
    if not isinstance(tabuleiro, tuple) or len(tabuleiro) != 3:
        return False

    if not all(isinstance(line, tuple) for line in tabuleiro):
        return False
    
    if (len(tabuleiro[0]), len(tabuleiro[1])) != (3, 3) or len(tabuleiro[2]) != 2:
        return False
    
    for line in tabuleiro:
        for state in line:
            if not isinstance(state, int) or state not in (-1, 0, 1):
                return False
    
    return True


def tabuleiro_str(tabuleiro):
    """ Function that prints into terminal the given tabuleiro.
        Raises ValueError exception if tabuleiro is not valid.
    """
    if eh_tabuleiro(tabuleiro):
        tab_to_print = add_x(tabuleiro)
        return '+-------+\n|...{}...|\n|..{}.{}..|\n|.{}.{}.{}.|\n|..{}.{}..|\n+-------+'.format(
            tab_to_print[2], 
            tab_to_print[1], tab_to_print[5], 
            tab_to_print[0], tab_to_print[4], tab_to_print[-1], 
            tab_to_print[3], tab_to_print[-2]
        )
    else:
        raise ValueError("tabuleiro_str: argumento invalido")


def tabuleiros_iguais(t1, t2):
    """ Function that returns true if booth tabuleiros are exactly the same. """
    if not eh_tabuleiro(t1) or not eh_tabuleiro(t2):
        raise ValueError('tabuleiros_iguais: um dos argumentos nao e tabuleiro')
    
    for line1, line2 in zip(t1, t2):
        if not all(x == y for x, y in zip(line1, line2)):
            return False
    return True


def porta_x(tabuleiro, local):
    """ Function that switches bits in port x of the board.
        X port can be the 2nd line or 2nd element of the first 2 lines plus the 1st element of the 3rd line.
        A switch consist on replacing every bit 0 to 1 and 1 to 0.
    """
    if not eh_tabuleiro(tabuleiro) or local not in ("E", "D") or not isinstance(local, str):
        raise ValueError('porta_x: um dos argumentos e invalido')
    
    if local == 'E':
        return (tabuleiro[0], switch_line(tabuleiro[1]), tabuleiro[2])
    
    return ((tabuleiro[0][0], switch_bit(tabuleiro[0][1]), tabuleiro[0][2]),
            (tabuleiro[1][0], switch_bit(tabuleiro[1][1]), tabuleiro[1][2]),
            (switch_bit(tabuleiro[2][0]), tabuleiro[2][1]))


def porta_z(tabuleiro, local):
    """ Function that switches bits in port z of the board.
        Z port can be the 1st line or 2nd element of the last bit in all lines.
        A switch consist on replacing every bit 0 to 1 and 1 to 0.
    """
    if not eh_tabuleiro(tabuleiro) or local not in ("E", "D") or not isinstance(local, str):
        raise ValueError('porta_z: um dos argumentos e invalido')

    if local == 'E':
        return (switch_line(tabuleiro[0]), tabuleiro[1], tabuleiro[2])

    return ((tabuleiro[0][0], tabuleiro[0][1], switch_bit(tabuleiro[0][2])),
            (tabuleiro[1][0], tabuleiro[1][1], switch_bit(tabuleiro[1][2])),
            (tabuleiro[2][0], switch_bit(tabuleiro[2][1])))


def porta_h(tabuleiro, local):
    """ Function that switches lines in port h of the board.
        H port can switch the 1st line with the 2nd line of the board
            or the last bit in all lines with the 2nd bit in the 1st and 2nd line and the 1st bit of the last line.
        The bit values are unchanged. But the lines are swapped.
    """
    if not eh_tabuleiro(tabuleiro) or local not in ("E", "D") or not isinstance(local, str):
        raise ValueError('porta_h: um dos argumentos e invalido')

    if local == 'E':
        return (tabuleiro[1], tabuleiro[0], tabuleiro[2])

    return ((tabuleiro[0][0], tabuleiro[0][2], tabuleiro[0][1]),
            (tabuleiro[1][0], tabuleiro[1][2], tabuleiro[1][1]),
            (tabuleiro[2][1], tabuleiro[2][0]))
