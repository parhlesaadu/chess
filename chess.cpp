#include<iostream>
using namespace std;

void DisplayBoard(char chessboard[][8]) {
	cout << "ROWS\n";
	for (int i = 0; i < 8; i++) {
		cout << i << "      ";
		for (int j = 0; j < 8; j++) {
			cout << chessboard[i][j] << ' ';
		}
		cout << endl;
	}
	cout << "\nCOLS   0 1 2 3 4 5 6 7\n\n";
}

void InputValidation(int* validOptions, int* movePTR, int max) {
	cout << "Enter your option here: ";
	cin >> *movePTR;
	bool validity = false;
	for (int i = 0; i < 45 && !validity; i++) {
		if (*(validOptions + i) == *movePTR) validity = true;
	}
	while (!validity || *movePTR > max || *movePTR <= 0) {
		cout << "INVALID ENTRY! Kindly reenter: ";
		cin >> *movePTR;
		validity = false;
		for (int i = 1; i < 45 && !validity; i++) {
			if (*(validOptions + i) == *movePTR) validity = true;
		}
	}
}

void YourNextMove(char chessboard[][8], int player) {
	player %= 2; 
	if (!player) player = 2;
	int b1, b2;	// store the ASCII codes for the first and last UPPERCASE/lowercase letter
	player == 1? b1 = 65 : b1 = 97;
	b2 = b1 + 25;
// UPPERCASE (ASCII 65-90) FOR PLAYER 1 / lowercase (ASCII 97-122) for player 2
	DisplayBoard(chessboard);
	char option, piece;
	cout << "1 (K/k - King)\n"
		<< "2 (Q/q - Queen)\n"
		<< "3 (R/r - Rook)\n"
		<< "4 (B/b - Bishop)\n"
		<< "5 (N/n - Knight)\n"
		<< "0 (Finish Game)\n";
	bool availability = false;
	while (!availability) {
		askagain:
		cout << "\nPlayer " << player << " your pieces are in ";
		if (player == 1) cout << "UPPERCASE.\n";
		else cout << "lowercase.\n";
		cout << "Enter the number corresponding to the piece you wish to move: ";
		cin >> option;
		while (option < '0' || option > '5') {
			cout << "INVALID OPTION! Kindly reenter: ";
			cin >> option;
		}
		switch (option) {
		case '1': { if (player % 2) piece = 'K'; else piece = 'k'; } break;
		case '2': { if (player % 2) piece = 'Q'; else piece = 'q'; } break;
		case '3': { if (player % 2) piece = 'R'; else piece = 'r'; } break;
		case '4': { if (player % 2) piece = 'B'; else piece = 'b'; } break;
		case '5': { if (player % 2) piece = 'N'; else piece = 'n'; } break;
		default: { 
			char confirm;
			do {
				cout << "\nConfirm game termination (Y/N): "; cin >> confirm;
				if (confirm != 'Y' && confirm != 'N' && confirm != 'y' && confirm != 'n') cout << "INVALID OPTION!";
			} while (confirm != 'Y' && confirm != 'N' && confirm != 'y' && confirm != 'n');
			if (confirm == 'Y' || confirm == 'y') {
				cout << "\nGAME TERMINATED\n"; exit(0);
			}
			else goto askagain;
		}
		}
		
		for (int i = 0; i < 8 && !availability; i++) {
			for (int j = 0; j < 8 && !availability; j++) {
				if (chessboard[i][j] == piece) availability = true;
			}
		}
		if (!availability) cout << "SORRY, THIS PIECE IS UNAVAILABLE!\n";
	}

	char R, C;
	cout << "Enter the current row/column (separated by a space) of the piece you wish to move: ";
	cin >> R >> C;
	while (R < '0' || R > '7' || C < '0' || C > '7' || chessboard[R - 48][C - 48] != piece) {
		cout << "INVALID POSITION! Kindly reenter: ";
		cin >> R >> C;
	}

	int move, validOptions[45], index = 0, * movePTR = &move, r = R - 48, c = C - 48;

	switch (option) {
	case '1': {
		cout << "\nPossible moves for selected piece in rows and columns are given below:\n";
		if (r >= 1 && c >= 1 && chessboard[r - 1][c - 1] == '.') {
			cout << "Enter 1 for [" << r - 1 << "][" << c - 1 << "]\n";
			validOptions[0] = 1;
		}

		if (r >= 1 && chessboard[r - 1][c] == '.') {
			cout << "Enter 2 for [" << r - 1 << "][" << c << "]\n";
			validOptions[1] = 2;
		}

		if (r >= 1 && c < 7 && chessboard[r - 1][c + 1] == '.') {
			cout << "Enter 3 for [" << r - 1 << "][" << c + 1 << "]\n";
			validOptions[2] = 3;
		}

		if (c >= 1 && chessboard[r][c - 1] == '.') {
			cout << "Enter 4 for [" << r << "][" << c - 1 << "]\n";
			validOptions[3] = 4;
		}

		if (c < 7 && chessboard[r][c + 1] == '.') {
			cout << "Enter 5 for [" << r << "][" << c + 1 << "]\n";
			validOptions[4] = 5;
		}

		if (r < 7 && c >= 1 && chessboard[r + 1][c - 1] == '.') {
			cout << "Enter 6 for [" << r + 1 << "][" << c - 1 << "]\n";
			validOptions[5] = 6;
		}

		if (r < 7 && chessboard[r + 1][c] == '.') {
			cout << "Enter 7 for [" << r + 1 << "][" << c << "]\n";
			validOptions[6] = 7;
		}

		if (r < 7 && c < 7 && chessboard[r + 1][c + 1] == '.') {
			cout << "Enter 8 for [" << r + 1 << "][" << c + 1 << "]\n";
			validOptions[7] = 8;
		}

		InputValidation(validOptions, movePTR, 8);

		switch (move) {
		case 1: {
			chessboard[r - 1][c - 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 2: {
			chessboard[r - 1][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 3: {
			chessboard[r - 1][c + 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 4: {
			chessboard[r][c - 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 5: {
			chessboard[r][c + 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 6: {
			chessboard[r + 1][c - 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 7: {
			chessboard[r + 1][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 8: {
			chessboard[r + 1][c + 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		}
		}
	} break;
	case '2': {
		cout << "\nPossible moves for selected piece in rows and columns are given below:\n";
		for (int i = 1; i <= 7; i++) {
			if (r + i < 8 && c + i < 8 && (chessboard[r + i][c + i] < b1 || chessboard[r + i][c + i] > b2)) {
				cout << "Enter " << i << " for [" << r + i << "][" << c + i << "]\n";
				validOptions[index] = i; index++;
			}
		}
		for (int i = 1; i <= 7; i++) {
			if (r - i > -1 && c + i < 8 && (chessboard[r - i][c + i] < b1 || chessboard[r - i][c + i] > b2)) {
				cout << "Enter " << i + 7 << " for [" << r - i << "][" << c + i << "]\n";
				validOptions[index] = i + 7; index++;
			}
		}
		for (int i = 1; i <= 7; i++) {
			if (r - i > -1 && c - i > -1 && (chessboard[r - i][c - i] < b1 || chessboard[r - i][c - i] > b2)) {
				cout << "Enter " << i + 14 << " for [" << r - i << "][" << c - i << "]\n";
				validOptions[index] = i + 14; index++;
			}

		}
		for (int i = 1; i <= 7; i++) {
			if (r + i < 8 && c - i > -1 && (chessboard[r + i][c - i] < b1 || chessboard[r + i][c - i] > b2)) {
				cout << "Enter " << i + 21 << " for [" << r + i << "][" << c - i << "]\n";
				validOptions[index] = i + 21; index++;
			}
		}
		for (int i = 1; i <= 8; i++) {
			if (c != i - 1 && (chessboard[r][i - 1] < b1 || chessboard[r][i - 1] > b2)) {
				cout << "Enter " << i + 28 << " for [" << r << "][" << i - 1 << "]\n";
				validOptions[index] = i + 28; index++;
			}
		}
		for (int i = 1; i <= 8; i++) {
			if (r != i - 1 && (chessboard[i - 1][c] < b1 || chessboard[i - 1][c] > b2)) {
				cout << "Enter " << i + 36 << " for [" << i - 1 << "][" << c << "]\n";
				validOptions[index] = i + 36; index++;
			}
		}

		InputValidation(validOptions, movePTR, 44);

		switch (move) {
		case 1: {
			chessboard[r + 1][c + 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 2: {
			chessboard[r + 2][c + 2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 3: {
			chessboard[r + 3][c + 3] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 4: {
			chessboard[r + 4][c + 4] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 5: {
			chessboard[r + 5][c + 5] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 6: {
			chessboard[r + 6][c + 6] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 7: {
			chessboard[r + 7][c + 7] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 8: {
			chessboard[r - 1][c + 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 9: {
			chessboard[r - 2][c + 2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 10: {
			chessboard[r - 3][c + 3] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 11: {
			chessboard[r - 4][c + 4] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 12: {
			chessboard[r - 5][c + 5] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 13: {
			chessboard[r - 6][c + 6] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 14: {
			chessboard[r - 7][c + 7] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 15: {
			chessboard[r - 1][c - 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 16: {
			chessboard[r - 2][c - 2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 17: {
			chessboard[r - 3][c - 3] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 18: {
			chessboard[r - 4][c - 4] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 19: {
			chessboard[r - 5][c - 5] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 20: {
			chessboard[r - 6][c - 6] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 21: {
			chessboard[r - 7][c - 7] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 22: {
			chessboard[r + 1][c - 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 23: {
			chessboard[r + 2][c - 2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 24: {
			chessboard[r + 3][c - 3] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 25: {
			chessboard[r + 4][c - 4] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 26: {
			chessboard[r + 5][c - 5] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 27: {
			chessboard[r + 6][c - 6] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 28: {
			chessboard[r + 7][c - 7] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 29: {
			chessboard[r][0] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 30: {
			chessboard[r][1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 31: {
			chessboard[r][2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 32: {
			chessboard[r][3] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 33: {
			chessboard[r][4] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 34: {
			chessboard[r][5] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 35: {
			chessboard[r][6] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 36: {
			chessboard[r][7] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 37: {
			chessboard[0][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 38: {
			chessboard[1][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 39: {
			chessboard[2][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 40: {
			chessboard[3][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 41: {
			chessboard[4][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 42: {
			chessboard[5][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 43: {
			chessboard[6][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 44: {
			chessboard[7][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		}
		}
	} break;
	case '3': {
		cout << "\nPossible moves for selected piece in rows and columns are given below:\n";
		for (int i = 1; i <= 8; i++) {
			if (c != i - 1 && (chessboard[r][i - 1] < b1 || chessboard[r][i - 1] > b2)) {
				cout << "Enter " << i << " for [" << r << "][" << i - 1 << "]\n";
				validOptions[index] = i; index++;
			}
		}
		for (int i = 1; i <= 8; i++) {
			if (r != i - 1 && (chessboard[i - 1][c] < b1 || chessboard[i - 1][c] > b2)) {
				cout << "Enter " << i + 8 << " for [" << i - 1 << "][" << c << "]\n";
				validOptions[index] = i + 8; index++;
			}
		}

		InputValidation(validOptions, movePTR, 16);

		switch (move) {
		case 1: {
			chessboard[r][0] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 2: {
			chessboard[r][1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 3: {
			chessboard[r][2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 4: {
			chessboard[r][3] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 5: {
			chessboard[r][4] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 6: {
			chessboard[r][5] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 7: {
			chessboard[r][6] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 8: {
			chessboard[r][7] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 9: {
			chessboard[0][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 10: {
			chessboard[1][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 11: {
			chessboard[2][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 12: {
			chessboard[3][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 13: {
			chessboard[4][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 14: {
			chessboard[5][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 15: {
			chessboard[6][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 16: {
			chessboard[7][c] = chessboard[r][c];
			chessboard[r][c] = '.';
		}
		}
	} break;
	case '4': {
		cout << "\nPossible moves for selected piece in rows and columns are given below:\n";
		for (int i = 1; i <= 7; i++) {
			if (r + i < 8 && c + i < 8 && (chessboard[r + i][c + i] < b1 || chessboard[r + i][c + i] > b2)) {
				cout << "Enter " << i << " for [" << r + i << "][" << c + i << "]\n";
				validOptions[index] = i; index++;
			}
		}
		for (int i = 1; i <= 7; i++) {
			if (r - i > -1 && c + i < 8 && (chessboard[r - i][c + i] < b1 || chessboard[r - i][c + i] > b2)) {
				cout << "Enter " << i + 7 << " for [" << r - i << "][" << c + i << "]\n";
				validOptions[index] = i + 7; index++;
			}
		}
		for (int i = 1; i <= 7; i++) {
			if (r - i > -1 && c - i > -1 && (chessboard[r - i][c - i] < b1 || chessboard[r - i][c - i] > b2)) {
				cout << "Enter " << i + 14 << " for [" << r - i << "][" << c - i << "]\n";
				validOptions[index] = i + 14; index++;
			}

		}
		for (int i = 1; i <= 7; i++) {
			if (r + i < 8 && c - i > -1 && (chessboard[r + i][c - i] < b1 || chessboard[r + i][c - i] > b2)) {
				cout << "Enter " << i + 21 << " for [" << r + i << "][" << c - i << "]\n";
				validOptions[index] = i + 21; index++;
			}
		}

		InputValidation(validOptions, movePTR, 28);

		switch (move) {
		case 1: {
			chessboard[r + 1][c + 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 2: {
			chessboard[r + 2][c + 2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 3: {
			chessboard[r + 3][c + 3] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 4: {
			chessboard[r + 4][c + 4] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 5: {
			chessboard[r + 5][c + 5] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 6: {
			chessboard[r + 6][c + 6] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 7: {
			chessboard[r + 7][c + 7] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 8: {
			chessboard[r - 1][c + 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 9: {
			chessboard[r - 2][c + 2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 10: {
			chessboard[r - 3][c + 3] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 11: {
			chessboard[r - 4][c + 4] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 12: {
			chessboard[r - 5][c + 5] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 13: {
			chessboard[r - 6][c + 6] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 14: {
			chessboard[r - 7][c + 7] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 15: {
			chessboard[r - 1][c - 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 16: {
			chessboard[r - 2][c - 2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 17: {
			chessboard[r - 3][c - 3] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 18: {
			chessboard[r - 4][c - 4] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 19: {
			chessboard[r - 5][c - 5] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 20: {
			chessboard[r - 6][c - 6] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 21: {
			chessboard[r - 7][c - 7] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 22: {
			chessboard[r + 1][c - 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 23: {
			chessboard[r + 2][c - 2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 24: {
			chessboard[r + 3][c - 3] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 25: {
			chessboard[r + 4][c - 4] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 26: {
			chessboard[r + 5][c - 5] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 27: {
			chessboard[r + 6][c - 6] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 28: {
			chessboard[r + 7][c - 7] = chessboard[r][c];
			chessboard[r][c] = '.';
		}
		}
	} break;
	case '5': {
		cout << "\nPossible moves for selected piece in rows and columns are given below:\n";
		if (r + 2 <= 7 && c - 1 >= 0 && (chessboard[r + 2][c - 1] < b1 || chessboard[r + 2][c - 1] > b2)) {
			cout << "Enter 1 for [" << r + 2 << "][" << c - 1 << "]\n";
			validOptions[0] = 1;
		}

		if (r + 2 <= 7 && c + 1 <= 7 && (chessboard[r + 2][c + 1] < b1 || chessboard[r + 2][c + 1] > b2)) {
			cout << "Enter 2 for [" << r + 2 << "][" << c + 1 << "]\n";
			validOptions[1] = 2;
		}

		if (r - 2 >= 0 && c - 1 >= 0 && (chessboard[r - 2][c - 1] < b1 || chessboard[r - 2][c - 1] > b2)) {
			cout << "Enter 3 for [" << r - 2 << "][" << c - 1 << "]\n";
			validOptions[2] = 3;
		}

		if (r - 2 >= 0 && c + 1 <= 7 && (chessboard[r - 2][c + 1] < b1 || chessboard[r - 2][c + 1] > b2)) {
			cout << "Enter 4 for [" << r - 2 << "][" << c + 1 << "]\n";
			validOptions[3] = 4;
		}

		if (c + 2 <= 7 && r - 1 >= 0 && (chessboard[r - 1][c + 2] < b1 || chessboard[r - 1][c + 2] > b2)) {
			cout << "Enter 5 for [" << r - 1 << "][" << c + 2 << "]\n";
			validOptions[4] = 5;
		}

		if (c + 2 <= 7 && r + 1 <= 7 && (chessboard[r + 1][c + 2] < b1 || chessboard[r - 1][c + 2] > b2)) {
			cout << "Enter 6 for [" << r + 1 << "][" << c + 2 << "]\n";
			validOptions[5] = 6;
		}

		if (c - 2 >= 0 && r - 1 >= 0 && (chessboard[r - 1][c - 2] < b1 || chessboard[r - 1][c - 2] > b2)) {
			cout << "Enter 7 for [" << r - 1 << "][" << c - 2 << "]\n";
			validOptions[6] = 7;
		}

		if (c - 2 >= 0 && r + 1 <= 7 && (chessboard[r + 1][c - 2] < b1 || chessboard[r + 1][c - 2] > b2)) {
			cout << "Enter 8 for [" << r + 1 << "][" << c - 2 << "]\n";
			validOptions[7] = 8;
		}

		InputValidation(validOptions, movePTR, 8);

		switch (move) {
		case 1: {
			chessboard[r + 2][c - 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 2: {
			chessboard[r + 2][c + 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 3: {
			chessboard[r - 2][c - 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 4: {
			chessboard[r - 2][c + 1] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 5: {
			chessboard[r - 1][c + 2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 6: {
			chessboard[r + 1][c + 2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 7: {
			chessboard[r - 1][c - 2] = chessboard[r][c];
			chessboard[r][c] = '.';
		} break;
		case 8: {
			chessboard[r + 1][c - 2] = chessboard[r][c];
			chessboard[r][c] = '.';
		}
		}
	}
	}
	cout << endl;

}

void SaveTheKing(char chessboard[][8]) {
	bool K1 = true, k2 = true;
	for (int player = 1; K1 && k2; player++) {
		K1 = false; k2 = false;
		YourNextMove(chessboard, player);
		// the loops below check the presence of both kings in the game
		for (int i = 0; i < 8 && !(K1 && k2); i++) {
			for (int j = 0; j < 8 && !(K1 && k2); j++) {
				if (chessboard[i][j] == 'K') K1 = true;
				if (chessboard[i][j] == 'k') k2 = true;
			}
		}
	}
	if (k2 && !K1) cout << "PLAYER 2 WINS!\n";
	if (K1 && !k2) cout << "PLAYER 1 WINS!\n";
}

void start() {
	int player = 1;
	char chessboard[8][8] = {
		{'R','N','B','Q','K','B','N','R'},
		{'.','.','.','.','.','.','.','.'},
		{'.','.','.','.','.','.','.','.'},
		{'.','.','.','.','.','.','.','.'},
		{'.','.','.','.','.','.','.','.'},
		{'.','.','.','.','.','.','.','.'},
		{'.','.','.','.','.','.','.','.'},
		{'r','n','b','q','k','b','n','r'}
	};

	SaveTheKing(chessboard);
}

int main() {
	start();
	return 0;
}
