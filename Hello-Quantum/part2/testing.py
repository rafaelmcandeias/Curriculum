
from main import *

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
    t0 = tabuleiro_inicial()
    assert tabuleiro_para_str(t0) == '+-------+\n|...x...|\n|..x.x..|\n|.x.0.x.|\n|..0.0..|\n+-------+'
    t2 = str_para_tabuleiro('((-1, -1, -1), (0, 1, -1), (1, -1))')
    assert tabuleiro_para_str(t2) == '+-------+\n|...x...|\n|..x.x..|\n|.x.1.x.|\n|..0.1..|\n+-------+'
    assert celula_para_str(tabuleiro_celula(t0, cria_coordenada(0,0))) == 'x'
    assert celula_para_str(tabuleiro_celula(t0, cria_coordenada(1,1))) == '0'
    assert eh_tabuleiro(t0) == True
    t1 = tabuleiro_inverte_estado(t0, cria_coordenada(1,1))
    assert tabuleiro_para_str(t1) == '+-------+\n|...x...|\n|..x.x..|\n|.x.1.x.|\n|..0.0..|\n+-------+'
    assert tabuleiros_iguais(t0, tabuleiro_inicial()) == False
    assert tabuleiros_iguais(t0, t1) == True


def teste4():
    t1 = tabuleiro_inicial()
    assert tabuleiro_para_str(t1) == '+-------+\n|...x...|\n|..x.x..|\n|.x.0.x.|\n|..0.0..|\n+-------+'
    t2 = porta_h(t1,'D')
    assert tabuleiro_para_str(t2) == '+-------+\n|...x...|\n|..x.0..|\n|.x.x.0.|\n|..0.x..|\n+-------+'
    t3 = porta_h(t2,'E')
    assert tabuleiro_para_str(t3) == '+-------+\n|...0...|\n|..x.x..|\n|.0.x.0.|\n|..x.x..|\n+-------+'
    try:
        t = porta_h(t2,'X')
        raise Exception
    except ValueError as ve:
        print(ve)


if __name__ == "__main__":
    teste1()
    teste2()
    teste3()
    teste4()
