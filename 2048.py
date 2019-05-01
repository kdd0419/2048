import random as r

# 2048판(배열)의 행과 열의 길이
LENGTH = 4


def emptyCell(board):  # 2048 판에서 빈 칸 반환

    return [
        i for i in range(LENGTH ** 2) if board[i // LENGTH][i % LENGTH] == 0
    ]


def hasEmptyCell(board):  # 2048 판이 빈 칸을 가지고 있는지

    return len(emptyCell(board)) > 0


def newBoard():  # 새로운 2048 판을 만들기

    board = [
        [0 for j in range(LENGTH)] for i in range(LENGTH)]

    newPut(board)
    newPut(board)

    score = 0

    return board, score


def newPut(board):  # 2048 판에 새 블럭(숫자)을 넣기

    if not hasEmptyCell(board):
        return

    put = r.choice(emptyCell(board))
    board[put // LENGTH][put % LENGTH] = r.choice([2, 2, 2, 2, 4])

    return board


def printBoard(board, score):  # 2048 판 출력

    print(("\n" + "-" * (LENGTH * 6) + "\n").join('|'.join(
        "%5d" % board[i][j] for j in range(LENGTH)) for i in range(LENGTH)))

    print("score :", score)

    return '\n'.join(' '.join(
                "%5d" % board[i][j] for j in range(LENGTH)
            ) for i in range(LENGTH)) + '\n' + str(score)


def wayMove(board, way):  # 2048 판을 왼쪽 방향에 맞춰 대칭이동을 시켜준다.

    if way == 'd':  # 오른쪽 ( 좌우 대칭 이동 )
        board = [
            [board[i][LENGTH - 1 - j]
                for j in range(LENGTH)]
            for i in range(LENGTH)
        ]
    elif way == 'w':  # 위쪽 ( y = -x 대칭 이동 )
        board = [
            [board[j][i] for j in range(LENGTH)]
            for i in range(LENGTH)
        ]
    elif way == 's':  # 아래쪽 ( y = x 대칭 이동 )
        board = [
            [board[LENGTH - 1 - j][LENGTH - 1 - i]
                for j in range(LENGTH)]
            for i in range(LENGTH)
        ]

    return board


def gravity(board, way, score):  # 2048 판을 한 쪽으로 민다

    if way not in ['a', 'w', 's', 'd']:  # 네 방향이 아닌 입력 에러
        print("Input error!")
        return board

    if way != 'a':
        board = wayMove(board, way)  # 왼쪽이 아닌 방향을 왼쪽에 맞춤

    for i in range(LENGTH):
        zeroCnt = board[i].count(0)
        for z in range(zeroCnt):  # 왼쪽의 0 삭제하고 오른쪽으로 0 넣기
            board[i].remove(0)
            board[i].append(0)

        for j in range(LENGTH - 1):
            if board[i][j] > 0 and board[i][j] == board[i][j + 1]:
                # 같은 숫자가 만났을 때 합치기
                board[i][j] *= 2
                board[i].pop(j + 1)
                board[i].append(0)
                score += board[i][j]

    if way != 'a':
        board = wayMove(board, way)  # 원래 방향에 다시 맞춤

    return board, score


def noMerge(board):  # 2048 판이 하나도 합칠 수 없을 시 게임 종료

    for i in range(LENGTH):
        for j in range(LENGTH):
            if i + 1 < LENGTH and board[i][j] == board[i + 1][j]:
                return False

            if j + 1 < LENGTH and board[i][j] == board[i][j + 1]:
                return False

    return True


def moved(board, g_board):

    return len(
        [board[i // LENGTH][i % LENGTH] != g_board[i // LENGTH][i % LENGTH]
            for i in range(LENGTH ** 2)]
        ) > 0


def play_2048():

    board, score = newBoard()
    printBoard(board=board, score=score)

    while hasEmptyCell(board) or not noMerge(board):
        g_board, score = gravity(board=board, way=input(), score=score)

        if moved(board, g_board):
            g_board = newPut(g_board)

        board = g_board

        printBoard(board, score)

    print("Game Over!")


while True:
    play_2048()
    while True:
        re = input("Retry? (y/n) > ")
        if re in ['Y', 'y']:
            break
        elif re in ['N', 'n']:
            exit()
        else:
            print("Input error!")
