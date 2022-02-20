
# Function that checks if arg is a board.
def eh_tabuleiro(board):
    possible_values = (-1, 0, 1)

    # If is a tuple with size 3.
    if not isinstance(board, tuple) or len(board) != 3:
        return False
    
    # If all elements inside are tuples.
    for e in board:
        if not isinstance(e, tuple):
            return False

    # If 1st and 2nd element of tuple have 3 things.
    for pos in (0, 1):
        if len(board[pos]) != 3:
            return False

    # If 3rd element has 2 things. 
    if len(board[2]) != 2:
        return False
    
    # If every value is int and -1, 0, or 1
    for line in board:
        for value in line:
            if not isinstance(value, int) or value not in possible_values:
                return False
    
    return True


# Function that transforms board into a presentable string
def tabuleiro_str(board):
    if eh_tabuleiro(board):
        return '+-------+\n|...{a}...|\n|..{b}.{c}..|\n|.{d}.{e}.{f}.|\n|..{g}.{h}..|\n+-------+'.format(
            a = board[0][2],
            b = board[0][1],
            c = board[1][2],
            d = board[0][0],
            e = board[1][1],
            f = board[2][1],
            g = board[1][0],
            h = board[2][0],
        )


print("1º")
t = ((-1, -1, -1), (0, 0, -1), (1, -1))
assert eh_tabuleiro(t) == True
t = ((-1, -1, -1), (0, 0, -1), (1, -1, 0))
assert eh_tabuleiro(t) == False
assert eh_tabuleiro(3) == False
print("2º")
