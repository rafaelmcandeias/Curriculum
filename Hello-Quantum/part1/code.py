"""
code for testing
"""


def tests():
    """ Function used to test code while being developped."""
    # eh_tabuleiro testing
    print('----eh_tabuleiro testing----')
    t = ((-1, -1, -1), (0, 0, -1), (1, -1))
    assert eh_tabuleiro(t) == True
    t = ((-1, -1, -1), (0, 0, -1), (1, -1, 0))
    assert eh_tabuleiro(
        t) == False, "Last line of puzzle with incorrect dimension"
    t = (3)
    assert eh_tabuleiro(t) == False, "Not a tuple"

    # tabuleiro_str testing
    print('----tabuleiro_str testing----')
    t = ((-1, -1, -1), (1, 1, -1), (0, -1))
    assert tabuleiro_str(
        t) == '+-------+\n|...x...|\n|..x.x..|\n|.x.1.x.|\n|..1.0..|\n+-------+'
    target = ((-1, -1, -1), (0, 0, -1), (0, -1))
    print(tabuleiro_str(target))
    assert tabuleiro_str(
        target) == '+-------+\n|...x...|\n|..x.x..|\n|.x.0.x.|\n|..0.0..|\n+-------+'
    try:
        print(tabuleiro_str(((-1, -1, -1), (0, 0, -1), (-1, -1, -1))))
    except ValueError as ve:
        print(ve)

    # tabuleiros_iguais testing
    print('----tabuleiros_iguais testing----')
    p1 = ((-1, -1, -1), (1, 1, -1), (0, -1))
    print(tabuleiro_str(p1))
    assert tabuleiros_iguais(p1, p1) == True, "Should be equal"
    assert tabuleiros_iguais(p1, target) == False, "They are different"
    p2 = ((-1, -1, -1), (0, 0, -1), (0, -1))
    assert tabuleiros_iguais(p2, target) == True, "Should be equal"
    try:
        tabuleiros_iguais((-1, -1, -1), target)
    except ValueError as ve:
        print(ve)
    try:
        tabuleiros_iguais([-1, -1, -1], target)
    except ValueError as ve:
        print(ve)
    try:
        tabuleiros_iguais(tuple(), target)
    except ValueError as ve:
        print(ve)

    # Porta_x Testing
    print("----porta_x testing----")
    p2 = porta_x(p1, "E")
    print(tabuleiro_str(p2))
    p3 = porta_x(p2, "D")
    print(tabuleiro_str(p3))
    try:
        p = porta_x(p2, "X")
    except ValueError as ve:
        print(ve)

    # Porta_z Testing
    print("----porta_z testing----")
    p7 = ((1, -1, 1), (-1, -1, -1), (-1, 0))
    print(tabuleiro_str(p7))
    p8 = porta_z(p7, "E")
    print(tabuleiro_str(p8))
    p9 = porta_z(p8, "D")
    print(tabuleiro_str(p9))
    try:
        p = porta_z(p9, "X")
    except ValueError as ve:
        print(ve)

    # Porta_h testing
    print("----porta_h testing----")
    p4 = ((-1, -1, -1), (0, -1, 0), (-1, 0))
    print(tabuleiro_str(p4))
    p5 = porta_h(p4, "E")
    print(tabuleiro_str(p5))
    p6 = porta_h(p5, "D")
    print(tabuleiro_str(p6))
    try:
        p = porta_h(p6, "X")
    except ValueError as ve:
        print(ve)


def final_tests():
    """ Function to validate the code.
        Test when code is completed.
    """
    test_counter = 0
    print("----Testing eh_tabuleiro----")
    t = ((-1, -1, -1), (0, 0, -1), (1, -1))
    assert eh_tabuleiro(t) == True
    t = (('-1', '-1', '-1'), ('0', '0', '-1'), ('1', '-1'))
    assert eh_tabuleiro(t) == False
    t = (('2', '-1', '6'), ('0', '2', '-1'), ('1', '-1'))
    assert eh_tabuleiro(t) == False
    t = ((), (), ())
    assert eh_tabuleiro(t) == False
    t = ('()', '()', '()')
    assert eh_tabuleiro(t) == False
    t = ([], [], [])
    assert eh_tabuleiro(t) == False
    t = ((2, -1, 6), (0, 2, -1), (1, -1))
    assert eh_tabuleiro(t) == False
    t = ((-1, -1, -1), (0, 0, -1), (1, -1), ())
    assert eh_tabuleiro(t) == False
    t = ((-1, -1, -1), (1, -1))
    assert eh_tabuleiro(t) == False
    t = ((-1, -1, -1, -1), (0, 0, -1), (1, -1))
    assert eh_tabuleiro(t) == False
    t = ((-1, -1, -1), (0, 0, -1, -1), (1, -1))
    assert eh_tabuleiro(t) == False
    t = ((-1, -1, -1), (0, 0, -1), (1, -1, -1))
    assert eh_tabuleiro(t) == False
    t = [(-1, -1, -1), (0, 0, -1), (1, -1)]
    assert eh_tabuleiro(t) == False
    t = ([-1, -1, -1], [0, 0, -1], [1, -1])
    assert eh_tabuleiro(t) == False
    t = [[-1, -1, -1], [0, 0, -1], [1, -1]]
    assert eh_tabuleiro(t) == False
    t = '((-1,-1,-1),(0,0,-1),(1,-1))'
    assert eh_tabuleiro(t) == False
    t = ()
    assert eh_tabuleiro(t) == False
    t = []
    assert eh_tabuleiro(t) == False
    t = ((1, -1), (0, 0, -1), (-1, -1, -1))
    assert eh_tabuleiro(t) == False
    t = [(-1, -1, -1), (0, 0, -1)]
    assert eh_tabuleiro(t) == False

    print("----Testing tabuleiro_str----")
    assert tabuleiro_str(((-1, -1, -1), (0, -1, 0), (-1, 0))
                         ) == '+-------+\n|...x...|\n|..x.0..|\n|.x.x.0.|\n|..0.x..|\n+-------+'
    assert tabuleiro_str(((-1, -1, -1), (0, -1, 1), (-1, 1))
                         ) == '+-------+\n|...x...|\n|..x.1..|\n|.x.x.1.|\n|..0.x..|\n+-------+'
    assert tabuleiro_str(((-1, -1, -1), (0, 0, -1), (0, -1))
                         ) == '+-------+\n|...x...|\n|..x.x..|\n|.x.0.x.|\n|..0.0..|\n+-------+'
    assert tabuleiro_str(((-1, -1, -1), (0, 1, -1), (1, -1))
                         ) == '+-------+\n|...x...|\n|..x.x..|\n|.x.1.x.|\n|..0.1..|\n+-------+'
    assert tabuleiro_str(((-1, -1, -1), (1, -1, 0), (-1, 1))
                         ) == '+-------+\n|...x...|\n|..x.0..|\n|.x.x.1.|\n|..1.x..|\n+-------+'
    assert tabuleiro_str(((-1, -1, -1), (1, -1, 1), (-1, 0))
                         ) == '+-------+\n|...x...|\n|..x.1..|\n|.x.x.0.|\n|..1.x..|\n+-------+'
    assert tabuleiro_str(((-1, -1, -1), (1, 0, -1), (1, -1))
                         ) == '+-------+\n|...x...|\n|..x.x..|\n|.x.0.x.|\n|..1.1..|\n+-------+'
    assert tabuleiro_str(((-1, -1, -1), (1, 1, -1), (0, -1))
                         ) == '+-------+\n|...x...|\n|..x.x..|\n|.x.1.x.|\n|..1.0..|\n+-------+'
    assert tabuleiro_str(((0, -1, 0), (-1, -1, -1), (-1, 0))
                         ) == '+-------+\n|...0...|\n|..x.x..|\n|.0.x.0.|\n|..x.x..|\n+-------+'
    assert tabuleiro_str(((0, -1, 1), (-1, -1, -1), (-1, 1))
                         ) == '+-------+\n|...1...|\n|..x.x..|\n|.0.x.1.|\n|..x.x..|\n+-------+'
    assert tabuleiro_str(((0, 0, -1), (-1, -1, -1), (0, -1))
                         ) == '+-------+\n|...x...|\n|..0.x..|\n|.0.x.x.|\n|..x.0..|\n+-------+'
    assert tabuleiro_str(((0, 1, -1), (-1, -1, -1), (1, -1))
                         ) == '+-------+\n|...x...|\n|..1.x..|\n|.0.x.x.|\n|..x.1..|\n+-------+'
    assert tabuleiro_str(((1, -1, 0), (-1, -1, -1), (-1, 1))
                         ) == '+-------+\n|...0...|\n|..x.x..|\n|.1.x.1.|\n|..x.x..|\n+-------+'
    assert tabuleiro_str(((1, -1, 1), (-1, -1, -1), (-1, 0))
                         ) == '+-------+\n|...1...|\n|..x.x..|\n|.1.x.0.|\n|..x.x..|\n+-------+'
    assert tabuleiro_str(((1, 0, -1), (-1, -1, -1), (1, -1))
                         ) == '+-------+\n|...x...|\n|..0.x..|\n|.1.x.x.|\n|..x.1..|\n+-------+'
    assert tabuleiro_str(((1, 1, -1), (-1, -1, -1), (0, -1))
                         ) == '+-------+\n|...x...|\n|..1.x..|\n|.1.x.x.|\n|..x.0..|\n+-------+'
    assert tabuleiro_str(((-1, -1, -1), (0, 0, -1), (0, -1))
                         ) != '+-------+\n|...x...|\n|..x.x..|\n|.x.0.x.|\n|..0.0..|\n+-------+\n'
    assert tabuleiro_str(((-1, -1, -1), (0, 1, -1), (1, -1))
                         ) != '+-------+\n|...x...|\n|..x.x..|\n|.x.1.x.|\n|..0.1..|\n+-------+ '
    assert tabuleiro_str(((-1, -1, -1), (0, 1, -1), (1, -1))
                         ) != '+_______+\n|...x...|\n|..x.x..|\n|.x.1.x.|\n|..0.1..|\n+_______+'
    try:
        tabuleiro_str(((1, -1, -1, -1), (-1, -1, -1), (1, 0)))
        raise Exception
    except ValueError as ve:
        print(ve)
    try:
        tabuleiro_str(((1, -1, -1), (-1, -1, -1, -1), (1, 0)))
        raise Exception
    except ValueError as ve:
        print(ve)
    try:
        tabuleiro_str(((1, -1, -1), (-1, -1, -1), (1, 0, 1)))
        raise Exception
    except ValueError as ve:
        print(ve)
    try:
        tabuleiro_str((('1', '-1', '-1'), ('-1', '-1', '-1'), ('1', '0', '1')))
        raise Exception
    except ValueError as ve:
        print(ve)
    try:
        tabuleiro_str((((), (), ()), ((), (), ()), ((), ())))
        raise Exception
    except ValueError as ve:
        print(ve)
    try:
        tabuleiro_str(((2, -1, 6), (0, 2, -1), (1, -1)))
        raise Exception
    except ValueError as ve:
        print(ve)
    try:
        tabuleiro_str(([-1, -1, -1], [0, 0, -1], [1, -1]))
        raise Exception
    except ValueError as ve:
        print(ve)
    try:
        tabuleiro_str([[-1, -1, -1], [0, 0, -1], [1, -1]])
        raise Exception
    except ValueError as ve:
        print(ve)
    try:
        tabuleiro_str([(-1, -1, -1), (0, 0, -1), (1, -1)])
        raise Exception
    except ValueError as ve:
        print(ve)
    try:
        tabuleiro_str([(-1, -1, -1), (0, 0, -1), (1, -1)])
        raise Exception
    except ValueError as ve:
        print(ve)
    try:
        tabuleiro_str('((-1,-1,-1),(0,0,-1),(1,-1))')
        raise Exception
    except ValueError as ve:
        print(ve)
    try:
        tabuleiro_str(((1, -1), (0, 0, -1), (-1, -1, -1)))
        raise Exception
    except ValueError as ve:
        print(ve)

    print("----Testing tabuleiros_iguais----")
    t1 = ((-1, -1, -1), (0, 0, -1), (1, -1))
    t2 = ((-1, -1, -1), (0, 0, -1), (1, -1))
    assert tabuleiros_iguais(t1, t2) == True
    t1 = ((0, -1, -1), (0, 0, -1), (1, -1))
    t2 = ((-1, -1, -1), (0, 0, -1), (1, -1))
    assert tabuleiros_iguais(t1, t2) == False
    t1 = ((-2, -1, -1), (0, 0, -1), (1, -1))
    t2 = ((-1, -1, -1), (0, 0, -1), (1, -1))
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = ((-1, -1, -1), (0, 'x', -1), (1, -1))
    t2 = ((-1, -1, -1), (0, 0, -1), (1, -1))
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = ((-1, -1, -1), (0, 0, -1), (1, -1))
    t2 = ((-2, -1, -1), (0, 0, -1), (1, -1))
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t2 = ((-1, -1, -1), (0, 0, -1), (1, -1))
    t1 = ((-2, -1, -1), (0, 0, -1), (1, -1))
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = ((-1, -1, -1), (0, 0, -1), (1, -1))
    t2 = ((-1, -1, -1), (0, 'x', -1), (1, -1))
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = '((-1,-1,-1),(0,0,-1),(1,-1))'
    t2 = '((-1,-1,-1),(0,0,-1),(1,-1))'
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = [(-1, -1, -1), (0, 0, -1), (1, -1)]
    t2 = [(-1, -1, -1), (0, 0, -1), (1, -1)]
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = ([-1, -1, -1], [0, 0, -1], [1, -1])
    t2 = ([-1, -1, -1], [0, 0, -1], [1, -1])
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = [[-1, -1, -1], [0, 0, -1], [1, -1]]
    t2 = [[-1, -1, -1], [0, 0, -1], [1, -1]]
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = [[-1, -1, -1], [0, 0, -1], [1, -1]]
    t2 = [[-1, -1, -1], [0, 0, -1], [1, -1, 1]]
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = '0'
    t2 = '0'
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = ()
    t2 = ()
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = ((1,), (1,), (1,))
    t2 = ((1,), (1,), (1,))
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = ((2, 3, 4), (4, 5, 6), (7, 8))
    t2 = ((2, 3, 4), (4, 5, 6), (7, 8))
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = ((-1, -1, -1), (0, 0, -1), (1, 1, -1))
    t2 = ((-1, -1, -1), (0, 0, -1), (1, 1, -1))
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = ((-1, -1, -1), (0, -1), (1, -1))
    t2 = ((-1, -1, -1), (0, -1), (1, -1))
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = ((-1, -1, -1), (0, 0, -1), (1,))
    t2 = ((-1, -1, -1), (0, 0, -1), (1,))
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)
    t1 = ((-1, -1), (0, 0, -1), (1, -1))
    t2 = ((-1, -1), (0, 0, -1), (1, -1))
    try:
        tabuleiros_iguais(t1, t2)
        raise Exception
    except ValueError as ve:
        print(ve)

    print("----Testing porta_x----")
    t = ((-1, -1, -1), (0, 0, -1), (1, -1))
    try:
        porta_x(t, 1)
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1), (0, 0, -1), (1, -1))
    try:
        porta_x(t, 'ES')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1), (0, 0, -1), (1, -1))
    try:
        porta_x(t, ())
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1), (0, 0, -1), (1, -1))
    try:
        porta_x(t, [])
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1), (0, 0, -1), (1, -1))
    type(porta_x(t, 'D')) == tuple
    assert porta_x(((-1, -1, -1), (0, -1, 0), (-1, 0)),
                   "D") == ((-1, -1, -1), (0, -1, 0), (-1, 0))
    assert porta_x(((-1, -1, -1), (0, -1, 0), (-1, 0)),
                   "E") == ((-1, -1, -1), (1, -1, 1), (-1, 0))
    assert porta_x(((-1, -1, -1), (0, 0, -1), (0, -1)),
                   "D") == ((-1, -1, -1), (0, 1, -1), (1, -1))
    assert porta_x(((-1, -1, -1), (0, 0, -1), (0, -1)),
                   "E") == ((-1, -1, -1), (1, 1, -1), (0, -1))
    assert porta_x(((-1, -1, -1), (0, 1, -1), (1, -1)),
                   "D") == ((-1, -1, -1), (0, 0, -1), (0, -1))
    assert porta_x(((-1, -1, -1), (0, 1, -1), (1, -1)),
                   "E") == ((-1, -1, -1), (1, 0, -1), (1, -1))
    assert porta_x(((-1, -1, -1), (1, -1, 0), (-1, 1)),
                   "D") == ((-1, -1, -1), (1, -1, 0), (-1, 1))
    assert porta_x(((-1, -1, -1), (1, -1, 0), (-1, 1)),
                   "E") == ((-1, -1, -1), (0, -1, 1), (-1, 1))
    assert porta_x(((-1, -1, -1), (1, 0, -1), (1, -1)),
                   "D") == ((-1, -1, -1), (1, 1, -1), (0, -1))
    assert porta_x(((-1, -1, -1), (1, 0, -1), (1, -1)),
                   "E") == ((-1, -1, -1), (0, 1, -1), (1, -1))
    assert porta_x(((-1, -1, -1), (1, 1, -1), (0, -1)),
                   "D") == ((-1, -1, -1), (1, 0, -1), (1, -1))
    assert porta_x(((-1, -1, -1), (1, 1, -1), (0, -1)),
                   "E") == ((-1, -1, -1), (0, 0, -1), (0, -1))
    assert porta_x(((0, 0, -1), (-1, -1, -1), (0, -1)),
                   "D") == ((0, 1, -1), (-1, -1, -1), (1, -1))
    assert porta_x(((0, 0, -1), (-1, -1, -1), (0, -1)),
                   "E") == ((0, 0, -1), (-1, -1, -1), (0, -1))
    assert porta_x(((0, 1, -1), (-1, -1, -1), (1, -1)),
                   "D") == ((0, 0, -1), (-1, -1, -1), (0, -1))
    assert porta_x(((0, 1, -1), (-1, -1, -1), (1, -1)),
                   "E") == ((0, 1, -1), (-1, -1, -1), (1, -1))
    assert porta_x(((1, 1, -1), (-1, -1, -1), (0, -1)),
                   "D") == ((1, 0, -1), (-1, -1, -1), (1, -1))
    assert porta_x(((1, 1, -1), (-1, -1, -1), (0, -1)),
                   "E") == ((1, 1, -1), (-1, -1, -1), (0, -1))
    t = ((-1, -1, -1), (0, -1), (1, -1))
    try:
        porta_x(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1), (0, -1, 1), (1, -1, 1))
    try:
        porta_x(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = '((-1,-1,-1),(0,0,-1),(1,-1))'
    try:
        porta_x(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = [(-1, -1, -1), (0, 0, -1), (1, -1)]
    try:
        porta_x(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = [[-1, -1, -1], [0, 0, -1], [1, -1]]
    try:
        porta_x(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ([-1, -1, -1], [0, 0, -1], [1, -1])
    try:
        porta_x(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = [(-1, 2, -1), (0, 3, -1), (4, -1)]
    try:
        porta_x(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = [(-1, 2, -1), (0, 3, -1), (1, 3)]
    try:
        porta_x(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, 'x', '-1'), ('0', 3, -1), (1, '-1'))
    try:
        porta_x(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)

    print("----Testing porta_z----")
    t = ((0, -1, 4), (-1, -1, -1), (-1, 0))
    try:
        porta_z(t, 1)
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    try:
        porta_z(t, 'A')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    try:
        porta_z(t, ())
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    try:
        porta_z(t, [])
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    try:
        porta_z(t, 'h')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'E')
    assert t2[0][2] == 1
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'E')
    assert t2[0][1] == -1
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'E')
    assert t2[0][0] == 1
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'E')
    assert t2[0][1] == -1
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'E')
    assert t2[1][2] == -1
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'E')
    assert t2[2][1] == 0
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'D')
    assert t2[0][2] == 1
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'D')
    assert t2[1][2] == -1
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'D')
    assert t2[2][1] == 1
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'D')
    assert t2[0][1] == -1
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'D')
    assert t2[0][0] == 0
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'D')
    assert t2[0][1] != 'x'
    assert porta_z(((-1, -1, -1), (0, 1, -1), (1, -1)),
                   "D") == ((-1, -1, -1), (0, 1, -1), (1, -1))
    assert porta_z(((-1, -1, -1), (0, 1, -1), (1, -1)),
                   "E") == ((-1, -1, -1), (0, 1, -1), (1, -1))
    assert porta_z(((-1, -1, -1), (1, -1, 1), (-1, 0)),
                   "D") == ((-1, -1, -1), (1, -1, 0), (-1, 1))
    assert porta_z(((-1, -1, -1), (1, -1, 1), (-1, 0)),
                   "E") == ((-1, -1, -1), (1, -1, 1), (-1, 0))
    assert porta_z(((-1, -1, -1), (1, 0, -1), (1, -1)),
                   "D") == ((-1, -1, -1), (1, 0, -1), (1, -1))
    assert porta_z(((-1, -1, -1), (1, 0, -1), (1, -1)),
                   "E") == ((-1, -1, -1), (1, 0, -1), (1, -1))
    assert porta_z(((0, -1, 0), (-1, -1, -1), (-1, 0)),
                   "D") == ((0, -1, 1), (-1, -1, -1), (-1, 1))
    assert porta_z(((0, -1, 0), (-1, -1, -1), (-1, 0)),
                   "E") == ((1, -1, 1), (-1, -1, -1), (-1, 0))
    assert porta_z(((0, -1, 1), (-1, -1, -1), (-1, 1)),
                   "D") == ((0, -1, 0), (-1, -1, -1), (-1, 0))
    assert porta_z(((0, -1, 1), (-1, -1, -1), (-1, 1)),
                   "E") == ((1, -1, 0), (-1, -1, -1), (-1, 1))
    assert porta_z(((0, 0, -1), (-1, -1, -1), (0, -1)),
                   "D") == ((0, 0, -1), (-1, -1, -1), (0, -1))
    assert porta_z(((0, 0, -1), (-1, -1, -1), (0, -1)),
                   "E") == ((1, 1, -1), (-1, -1, -1), (0, -1))
    assert porta_z(((1, -1, 0), (-1, -1, -1), (-1, 1)),
                   "D") == ((1, -1, 1), (-1, -1, -1), (-1, 0))
    assert porta_z(((1, -1, 0), (-1, -1, -1), (-1, 1)),
                   "E") == ((0, -1, 1), (-1, -1, -1), (-1, 1))
    assert porta_z(((1, -1, 1), (-1, -1, -1), (-1, 0)),
                   "D") == ((1, -1, 0), (-1, -1, -1), (-1, 1))
    assert porta_z(((1, 1, -1), (-1, -1, -1), (0, -1)),
                   "E") == ((0, 0, -1), (-1, -1, -1), (0, -1))
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    assert type(porta_z(t, 'D')) == tuple
    t = ((0, -1, 0), (-1, -1, -1), (-1, 0))
    t2 = porta_z(t, 'D')
    t3 = porta_z(t, 'E')
    assert t2[0][2] == t3[0][2]
    t = ((-1, -1, -1), (0, -1), (1, -1))
    try:
        porta_z(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1), (0, -1, 1), (1, -1, 1))
    try:
        porta_z(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1, -1), (0, -1, 1), (1, -1))
    try:
        porta_z(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = '((-1,-1,-1),(0,0,-1),(1,-1))'
    try:
        t2 = porta_z(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = [(-1, -1, -1), (0, 0, -1), (1, -1)]
    try:
        t2 = porta_z(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = [[-1, -1, -1], [0, 0, -1], [1, -1]]
    try:
        t2 = porta_z(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ([-1, -1, -1], [0, 0, -1], [1, -1])
    try:
        t2 = porta_z(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = [(-1, 2, -1), (0, 3, -1), (4, -1)]
    try:
        t2 = porta_z(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = [(-1, 2, -1), (0, 3, -1), (1, 3)]
    try:
        t2 = porta_z(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, '-1', -1), (0, 2, 'x'), (1, 'a'))
    try:
        t2 = porta_z(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)

    print("----Testing porta_h----")
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    try:
        porta_h(t, 1)
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    try:
        porta_h(t, 'A')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    try:
        porta_h(t, ())
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    try:
        porta_h(t, [])
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    try:
        porta_h(t, 'z')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'E')
    assert t2[1][1] == -1
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'E')
    assert t2[1][0] == -1
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'E')
    assert t2[2][0] == 0
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'E')
    assert t2[0][0] == 0
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'E')
    assert t2[0][1] == 0
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'E')
    assert t2[0][2] == -1
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'E')
    assert t2[0][2] != 'x'
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'E')
    assert t2[2][1] == -1
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'D')
    assert t2[1][1] == -1
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'D')
    assert t2[2][0] == -1
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'D')
    assert t2[2][1] == 0
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'D')
    assert t2[1][2] == 0
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'D')
    assert t2[0][2] == -1
    assert porta_h(((-1, -1, -1), (0, -1, 1), (-1, 1)),
                   "D") == ((-1, -1, -1), (0, 1, -1), (1, -1))
    assert porta_h(((-1, -1, -1), (0, -1, 1), (-1, 1)),
                   "E") == ((0, -1, 1), (-1, -1, -1), (-1, 1))
    assert porta_h(((-1, -1, -1), (0, 0, -1), (0, -1)),
                   "D") == ((-1, -1, -1), (0, -1, 0), (-1, 0))
    assert porta_h(((-1, -1, -1), (0, 0, -1), (0, -1)),
                   "E") == ((0, 0, -1), (-1, -1, -1), (0, -1))
    assert porta_h(((-1, -1, -1), (1, 1, -1), (0, -1)),
                   "D") == ((-1, -1, -1), (1, -1, 1), (-1, 0))
    assert porta_h(((-1, -1, -1), (1, 1, -1), (0, -1)),
                   "E") == ((1, 1, -1), (-1, -1, -1), (0, -1))
    assert porta_h(((0, -1, 0), (-1, -1, -1), (-1, 0)),
                   "D") == ((0, 0, -1), (-1, -1, -1), (0, -1))
    assert porta_h(((0, -1, 0), (-1, -1, -1), (-1, 0)),
                   "E") == ((-1, -1, -1), (0, -1, 0), (-1, 0))
    assert porta_h(((0, -1, 1), (-1, -1, -1), (-1, 1)),
                   "D") == ((0, 1, -1), (-1, -1, -1), (1, -1))
    assert porta_h(((0, -1, 1), (-1, -1, -1), (-1, 1)),
                   "E") == ((-1, -1, -1), (0, -1, 1), (-1, 1))
    assert porta_h(((0, 0, -1), (-1, -1, -1), (0, -1)),
                   "D") == ((0, -1, 0), (-1, -1, -1), (-1, 0))
    assert porta_h(((0, 0, -1), (-1, -1, -1), (0, -1)),
                   "E") == ((-1, -1, -1), (0, 0, -1), (0, -1))
    assert porta_h(((0, 1, -1), (-1, -1, -1), (1, -1)),
                   "D") == ((0, -1, 1), (-1, -1, -1), (-1, 1))
    assert porta_h(((0, 1, -1), (-1, -1, -1), (1, -1)),
                   "E") == ((-1, -1, -1), (0, 1, -1), (1, -1))
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    assert type(porta_h(t, 'D')) == tuple
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'D')
    t3 = porta_h(t, 'E')
    assert t2[1][2] == t3[0][1]
    t = ((-1, -1, -1), (0, 0, -1), (0, -1))
    t2 = porta_h(t, 'D')
    t3 = porta_h(t, 'E')
    assert t2[1][1] == t3[1][1]
    t = ((-1, -1, -1), (0, -1), (1, -1))
    try:
        porta_h(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, -1, -1), (0, -1, 1), (1, -1, 1))
    try:
        porta_h(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = '((-1,-1,-1),(0,0,-1),(1,-1))'
    try:
        t2 = porta_h(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = [(-1, -1, -1), (0, 0, -1), (1, -1)]
    try:
        t2 = porta_h(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = [[-1, -1, -1], [0, 0, -1], [1, -1]]
    try:
        t2 = porta_h(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ([-1, -1, -1], [0, 0, -1], [1, -1])
    try:
        t2 = porta_h(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = [(-1, 2, -1), (0, 3, -1), (4, -1)]
    try:
        t2 = porta_h(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = [(-1, 2, -1), (0, 3, -1), (1, 3)]
    try:
        t2 = porta_h(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, '-1', -1), (0, 2, 'x'), (1, 'a'))
    try:
        t2 = porta_h(t, 'D')
        raise Exception
    except ValueError as ve:
        print(ve)
    t = ((-1, 'x', '-1'), ('0', 3, -1), (1, '-1'))
    try:
        t2 = porta_h(t, 'E')
        raise Exception
    except ValueError as ve:
        print(ve)


"""
Main code
"""
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



if __name__ == "__main__":
    tests()
    #final_tests()