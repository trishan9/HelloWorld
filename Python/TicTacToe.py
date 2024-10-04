from tkinter import *
import json

game = Tk()

game.geometry("518x613+100+100")
game.resizable(False, False)
game.title("Tic Tac Toe")

board = {1: ' ', 2: ' ', 3: ' ', 4: ' ', 5: ' ', 6: ' ', 7: ' ', 8: ' ', 9: ' '}

person = 'X'
bot = 'O'
check = 0
player = True
winstreak = 0

with open('score.json', 'r') as file:
    winstreak = json.load(file)   


def disableBoard():
    for x in buttons:
        x["state"] = DISABLED
    restart_menu.entryconfig('Restart Game', state='normal')


def restart():
    global board, check, player
    
    board = {1: ' ', 2: ' ', 3: ' ', 4: ' ', 5: ' ', 6: ' ', 7: ' ', 8: ' ', 9: ' '}
    check = 0
    player = True
    
    for button in buttons:
        button.configure(text = ' ', bg='#dcdcdc', state = 'normal')
        
        
def resetScore():
    global winstreak
    with open('score.json', 'w') as file:
        json.dump(0, file)        
    winstreak = 0
    score.config(text=f'Highest Winstreak: {winstreak // 2}')

def winCondition():
    if board[1] == board[2] and board[1] == board[3] and board[1] != ' ':
        winner(1, 2, 3)
    elif board[4] == board[5] and board[4] == board[6] and board[4] != ' ':
        winner(4, 5, 6)
    elif board[7] == board[8] and board[7] == board[9] and board[7] != ' ':
        winner(7, 8, 9)
    elif board[1] == board[4] and board[1] == board[7] and board[1] != ' ':
        winner(1, 4, 7)
    elif board[2] == board[5] and board[2] == board[8] and board[2] != ' ':
        winner(2, 5, 8)
    elif board[3] == board[6] and board[3] == board[9] and board[3] != ' ':
        winner(3, 6, 9)
    elif board[1] == board[5] and board[1] == board[9] and board[1] != ' ':
        winner(1, 5, 9)
    elif board[3] == board[5] and board[3] == board[7] and board[3] != ' ':
        winner(3, 5, 7)
    else:
        pass


def checkWinner(theWinner):
    if board[1] == board[2] and board[1] == board[3] and board[1] == theWinner:
        return True
    elif board[4] == board[5] and board[4] == board[6] and board[4] == theWinner:
        return True
    elif board[7] == board[8] and board[7] == board[9] and board[7] == theWinner:
        return True
    elif board[1] == board[4] and board[1] == board[7] and board[1] == theWinner:
        return True
    elif board[2] == board[5] and board[2] == board[8] and board[2] == theWinner:
        return True
    elif board[3] == board[6] and board[3] == board[9] and board[3] == theWinner:
        return True
    elif board[1] == board[5] and board[1] == board[9] and board[1] == theWinner:
        return True
    elif board[3] == board[5] and board[3] == board[7] and board[3] == theWinner:
        return True
    else:
        return False


def winner(p1, p2, p3):
    buttons[p1 - 1].configure(bg='green')
    buttons[p2 - 1].configure(bg='green')
    buttons[p3 - 1].configure(bg='green')
    disableBoard()
    updateScore()


def checkDraw():
    global check
    if check == 9:
        disableBoard()


def updateScore():
    global winstreak, player
            
    with open('score.json', 'r') as file:
        winstreak = json.load(file)
    
    score.config(text=f'Highest Winstreak: {winstreak // 2}')
    
    if player:
        winstreak += 1
    else:
        winstreak = 0
    
    with open('score.json', 'w') as file:
        json.dump(winstreak, file)    

    score.config(text=f'Highest Winstreak: {winstreak // 2}')
        
        
def click(position):
    global check, person
    if board[position] == ' ' and board[position] != bot:
        board[position] = person
        buttons[position - 1].configure(text=person)
        check += 1
        play()


def botMove(turn, position):
    board[position] = turn
    buttons[position - 1].configure(text=turn)


def computerMove():
    global bot, player, person
    if checkWinner(person):
        return
    bestScore = -100
    bestMove = 0
    for key in board.keys():
        if board[key] == ' ':
            board[key] = bot
            score = minimax(board, 0, False)
            board[key] = ' '
            if score > bestScore:
                bestScore = score
                bestMove = key

    board[bestMove] = bot
    botMove(bot, bestMove)
    
    if checkWinner(bot):
        player = not player
        
    return


def print_board():
    print("Current Board:")
    for i in range(3):
        for j in range(3):
            position = i * 3 + j + 1
            print(board[position], end=" ")
        print()

def minimax(board, depth, isMax):
    if checkWinner(bot):
        return 100 - depth
    elif checkWinner(person):
        return -100 + depth
    elif checkDraw():
        return 0

    if isMax:
        bestScore = -100
        for key in board.keys():
            if board[key] == ' ':
                board[key] = bot
                score = minimax(board, depth + 1, False)
                board[key] = ' '
                bestScore = max(score, bestScore)
        return bestScore
    else:
        bestScore = 100
        for key in board.keys():
            if board[key] == ' ':
                board[key] = person
                score = minimax(board, depth + 1, True)
                board[key] = ' '
                bestScore = min(score, bestScore)
        return bestScore


def play():
    winCondition()
    checkDraw()
    computerMove()
    winCondition()
    checkDraw()


buttons = []

for x in range(3):
    for y in range(3):
        position = x * 3 + y + 1
        button = Button(game, text=' ', font=('Helvetica', 15), bg='#dcdcdc', width=15, height=7, bd=0.5,
                        command=lambda pos=position: click(pos))
        button.grid(row=x + 1, column=y, sticky='NESW')
        buttons.append(button)

menu_bar = Menu(game)
game.config(menu=menu_bar)

restart_menu = Menu(menu_bar, tearoff=0)
menu_bar.add_cascade(label='Menu', menu=restart_menu)
restart_menu_index = restart_menu.index("end")
restart_menu.add_command(label='Restart Game', command=restart)
restart_menu.add_command(label='Reset Score', command=resetScore)


score = Label(game, text = f"Highest Winstreak: {winstreak // 2}", font=('Helvetica', 15))
score.grid(row=0, column=0, columnspan=10, ipady = 30, sticky='NESW')

game.mainloop()