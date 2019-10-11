import random

game_on = True  # keeps track of whether or not there is a winner
player = 'X'
winner = None
board = ['-', '-', '-',
         '-', '-', '-',
         '-', '-', '-']


def play_game():
	global ans
	print('Welcome to TicTacToe!')
	
	while (True):
  		ans = input("Would you like to play against a bot? (y/n) ")
  		if(ans == 'y' or ans == 'n'): break
  		print("Invalid input, try again.")
	
	while game_on:
 		display_board()
 		turn()
 		check_game()
    
	display_board()
	
	if winner == 'X' or winner == 'O':
		print('The winner is ' + winner)
	elif winner == None:
		print('Tie!')




def display_board(): # prints board
    print(board[0] + ' | ' + board[1] + ' | ' + board[2])
    print(board[3] + ' | ' + board[4] + ' | ' + board[5])
    print(board[6] + ' | ' + board[7] + ' | ' + board[8])

def compTurn():
	print("Computer's turn: ")
	while(True):
		mark = random.randint(1,9)
		if board[mark-1] == '-': break
	board[mark-1] = player
	switch_turns()

def turn():
	global mark
	if ans == 'y' and player == 'O':
		return compTurn()
	while(True):
		mark = input('Select a position from 1-9: ')
		if(isValid(mark)):
			mark = int(mark) - 1
			if(board[mark] == '-'):
				break
		print('Invalid input, try again.')
	board[mark] = player
	
	switch_turns()


def isValid(mark):
	return(mark == '1' or mark == '2' or mark == '3' or mark == '4' or mark == '5' or mark == '6' or mark == '7' or mark == '8' or mark == '9')

def switch_turns():
    global player
    if player == 'X':
        player = 'O'
    else:
        player = 'X'


def check_game():
    check_winner()
    check_tie()


def check_winner():
    global winner
    row_winner = check_row()
    col_winner = check_col()
    diag_winner = check_diagonal()
    if row_winner:
        winner = row_winner
    elif col_winner:
        winner = col_winner
    elif diag_winner:
        winner = diag_winner
    else:
        winner = None


def check_tie():
    global game_on
    if game_on:
        if '-' not in board:
            game_on = False
            return True
        else:
            return False


def check_row():
    global game_on
    row1 = board[0] == board[1] == board[2] != '-'
    row2 = board[3] == board[4] == board[5] != '-'
    row3 = board[6] == board[7] == board[8] != '-'
    if row1 or row2 or row3:
        game_on = False
    if row1:
        return board[0]
    elif row2:
        return board[3]
    elif row3:
        return board[6]
    return


def check_col():
    global game_on
    col1 = board[0] == board[3] == board[6] != '-'
    col2 = board[1] == board[4] == board[7] != '-'
    col3 = board[2] == board[5] == board[8] != '-'
    if col1 or col2 or col3:
        game_on = False
    if col1:
        return board[0]
    elif col2:
        return board[1]
    elif col3:
        return board[2]
    return

def check_diagonal():
    global game_on
    diag1 = board[0] == board[4] == board[8] != '-'
    diag2 = board[2] == board[4] == board[6] != '-'
    if diag1 or diag2:
        game_on = False
    if diag1:
        return board[0]
    elif diag2:
        return board[2]
    return


play_game()
