import random as r


LENGTH = 4


def printBoard(board):
    for i in range(LENGTH):
        print("-" * (LENGTH * 6 + 1))
        for j in range(LENGTH):
            print("|%5d" % board[i][j], end="")
        print("|")
    print("-" * (LENGTH * 6 + 1))

    s = ''
    for line in board:
        s += ' '.join(str(line[i]) for i in range(LENGTH))
        s += '\n'
    return s


def newPut(board):
    empty = [
        i for i in range(LENGTH ** 2) if board[i // LENGTH][i % LENGTH] == 0]
    if len(empty) <= 0:
        return False
    put = r.choice(empty)
    board[put // LENGTH][put % LENGTH] = r.choice([2, 2, 2, 2, 4])
    return True


def newBoard():
    board = [
        [0 for j in range(LENGTH)] for i in range(LENGTH)]
    newPut(board)
    newPut(board)
    printBoard(board)
    return board


def gravity(board, way):
    if way == 'a':  # 왼쪽
        pass  # 아래 처리 문장은 왼쪽이 기준, 그래서 나머지 방향은 왼쪽 방향 이동에 맞춰 대칭이동
    if way == 'd':  # 오른쪽
        board = [
            [board[i][LENGTH - 1 - j]
                for j in range(LENGTH)]
            for i in range(LENGTH)
        ]
    elif way == 'w':  # 위쪽
        board = [
            [board[j][i] for j in range(LENGTH)]
            for i in range(LENGTH)
        ]
    elif way == 's':  # 아래쪽
        board = [
            [board[LENGTH - 1 - j][LENGTH - 1 - i]
                for j in range(LENGTH)]
            for i in range(LENGTH)
        ]
    else:
        print("Input error!")
        return board

    for i in range(LENGTH):
        zeroCnt = board[i].count(0)
        for z in range(zeroCnt):
            board[i].remove(0)
            board[i].append(0)
        for j in range(LENGTH - 1):
            if board[i][j] > 0 and board[i][j] == board[i][j + 1]:
                board[i][j] *= 2
                board[i].pop(j + 1)
                board[i].append(0)

    if way == 'd':  # 오른쪽
        board = [
            [board[i][LENGTH - 1 - j] for j in range(LENGTH)]
            for i in range(LENGTH)
        ]
    elif way == 'w':  # 위쪽
        board = [
            [board[j][i] for j in range(LENGTH)]
            for i in range(LENGTH)
        ]
    elif way == 's':  # 아래쪽
        board = [
            [board[LENGTH - 1 - j][LENGTH - 1 - i]
                for j in range(LENGTH)]
            for i in range(LENGTH)
        ]
    return board

board = newBoard()
board = gravity(board, 'w')
newPut(board)
printBoard(board)
board = gravity(board, 'a')
newPut(board)
printBoard(board)
board = gravity(board, 'd')
newPut(board)
printBoard(board)
board = gravity(board, 's')
