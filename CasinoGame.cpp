// Created in 10/13/22 by Carlos Berreteaga
#include <iostream>
#include <string>

using namespace std;

class Player {
public:
	string PName;
	int Difficulty = 0; // Determines the starting cash of the player
	int CurrentCash = 1000 ; // Total cash Player has
	int StartingCash[3] = { 1000, 500, 100 }; // Cash player enters casino with
	int Chips[4][2] = { 1, 0, 20, 0, 50, 0, 100, 0 }; // First array is type of chip, second arrays is amount of chip type; Types of chips are $1, $20, $50, $100
	int ChipsValue = 0; // Total value of all the chips player has
};

class Casino {
public:
	void Intro(); // Intro to casino game
	void ChooseDifficulty(); // Enables player to choose dificulty at start of game, changes total cash that player has at beggining 
	void ChooseGame(); // Function that allows player to choose what game or table to play
	void BlackJack(); // Card Game Instructions
	void Craps(); // Dice Game Instructions
	void ChipExchange(int Cash); // Exchanges cash to chips
	void CashExchange(int Cash); // Exchanges chips to cash
	void Lobby(); // Lobby of casino, where player can choose where to go
	void GiveNewChips(int Bet); // Reset count of Chips when player wins or loses at table
};

class Game {
public:
	int Deck[52] = { 1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11 }; // Deck of all the cards in a casino deck
	int Dice[6] = { 1, 2, 3, 4, 5, 6 }; // Six sided dice
	void PlayBJ(); // Plays the game of blackjack, must run function MyCasino.Blackjack() before hand
	void PlayCraps(); // Plays the game of craps, must run function MyCasino.Craps() before hand
	int DrawCard(); // Generates a random card to be drawn by player or dealer
	int RollDice(); // // Generates a random number between 1 - 6 for dice roll
	int OriginalTotalOfDice = 0; // Original total of dice throw for when player plays Craps
};

Player MyPlayer; // Object of class Player
Casino MyCasino; // Object of class Casino
Game MyGame; // Object of class Game

int main() {

	MyCasino.Intro();

	return 0;
}

void Casino::Intro() {

	cout << "Welcome to the Virtual Casino!\n\n"
		<< "What is your name? ";

	getline(cin, MyPlayer.PName); // Gets name of player, can have spaces
	cin.clear();

	MyCasino.ChooseDifficulty();
}

void Casino::ChooseDifficulty() {
	
	bool bContinue = false;

	cout << "\n\nChoose Difficulty:\n"
		<< "[1] Easy; Starting Cash = $1,000\n"
		<< "[2] Normal; Starting Cash = $500\n"
		<< "[3] Hard; Starting Cash = $100\n\n";

	do {
		cout << "Enter digit 1-3: ";
		cin.clear();
		cin >> MyPlayer.Difficulty;


		if (MyPlayer.Difficulty != 1 && MyPlayer.Difficulty != 2 && MyPlayer.Difficulty != 3) {
			cout << "\nInvalid Input. Try again\n";
			cin.clear();
			cin.ignore();
		}
		else {
			bContinue = true;
		}
	} while (!bContinue);

	switch (MyPlayer.Difficulty) {
		case 1:
			cout << "\nChoosen Difficulty: Easy\n";
			MyPlayer.CurrentCash = MyPlayer.StartingCash[0];
			break;
		case 2:
			cout << "\nChoosen Difficulty: Normal\n";
			MyPlayer.CurrentCash = MyPlayer.StartingCash[1];

			break;
		case 3:
			cout << "\nChoosen Difficulty: Hard\n";
			MyPlayer.CurrentCash = MyPlayer.StartingCash[2];
			break;
		default:
			break;
	}

	MyCasino.Lobby();
}

void Casino::Lobby() {

	int Choice = 0;
	bool bContinue = false;
	
	system("cls");

	// Shows on screen player name, current cash, and all current chips
	cout << "Name: " << MyPlayer.PName << "                      " << "Cash: $" << MyPlayer.CurrentCash << "\n\n";
	cout << "Chips $1: " << MyPlayer.Chips[0][1] << "   "
		<< "Chips $20: " << MyPlayer.Chips[1][1] << "   "
		<< "Chips $50: " << MyPlayer.Chips[2][1] << "   "
		<< "Chips $100: " << MyPlayer.Chips[3][1] << "\n\n";

	cout << "You are now in the lobby of the Virtual Casino\n"
		<< "There are various things to do...\n\n";

	cout << "Things to do:\n"
		<< "[1] Exchange Cash to Chips\n"
		<< "[2] Exchange Chips to Cash\n"
		<< "[3] Choose Table/Game\n"
		<< "[4] Exit\n";
	do {
		cout << "Enter digit 1-4: ";
		cin >> Choice;

		if (Choice == 1 || Choice == 2 || Choice == 3 || Choice == 4)
		{
			bContinue = true;
		}
		else {
			cin.clear();
			cin.ignore();
		}

	} while (!bContinue);

	switch (Choice)
	{
	case 1:
		MyCasino.ChipExchange(MyPlayer.CurrentCash);
		break;
	case 2: 
		MyCasino.CashExchange(MyPlayer.CurrentCash);
		break;
	case 3:
		MyCasino.ChooseGame();
		break;
	case 4:
		cout << "\nThank you for playing, hope to see you again soon!\n\n";
		break;
	default:
		break;
	}

}

void Casino::ChipExchange(int Cash) {


	int CashToChips = 0;
	bool bContinue = false;
	int AnotherExchange = 0;
	int Chips1 = 0;
	int Chips20 = 0;
	int Chips50 = 0;
	int Chips100 = 0;

	system("cls");

	// Prints to screen total CurrentCash from Player class
	cout << "Total Available Cash: $" << Cash << "\n";

	// If player has no cash then no exchange is possible
	if (Cash <= 0)
	{
		cout << "\nYou don't have enough cash for the exchange\n\n";
		system("pause");
		MyCasino.Lobby();
		return;
	}

	// Will loop until player enters valid amount for exchange, nothing above current cash, 0, or below 0
	while (!bContinue)
	{
		cout << "\nHow much cash do you want to change to chips?\n"
			<< "Cash to exchange: ";

		cin >> CashToChips;

		if (CashToChips > Cash || CashToChips == 0)
		{
			cin.clear();
			cin.ignore();
			cout << "\nInvalid Amount. Try again\n";
		}
		else
		{
			bContinue = true;
		}
	}

	MyPlayer.ChipsValue += CashToChips;
	Cash -= CashToChips;

	// Divides Cash into seperate Chips
	while (CashToChips >= 100)
	{	
		Chips100++;
		CashToChips -= 100;
	}
	while (CashToChips >= 50) {
		Chips50++;
		CashToChips -= 50;
	}
	while (CashToChips >= 20)
	{
		Chips20++;
		CashToChips -= 20;
	}
	while (CashToChips >= 1)
	{
		Chips1++;
		CashToChips -= 1;
	}
	
	// Prints out total NEW chips player gets from the exchange
	cout << "\nHere are your chips:\n"
		<< "Chips of $1: " << Chips1 << "\n"
		<< "Chips of $20: " << Chips20 << "\n"
		<< "Chips of $50: " << Chips50 << "\n"
		<< "Chips of $100: " <<Chips100 << "\n\n";

	// Places Total Chips of each type into Two-Dimensional Array
	for (int i = 4; i >= 0; --i)
	{
		if (i == 0)
		{
			Chips1 += MyPlayer.Chips[i][1];
			MyPlayer.Chips[i][1] = Chips1;
		}
		if (i == 1)
		{
			Chips20 += MyPlayer.Chips[i][1];
			MyPlayer.Chips[i][1] = Chips20;
		}
		if (i == 2)
		{
			Chips50 += MyPlayer.Chips[i][1];
			MyPlayer.Chips[i][1] = Chips50;
		}
		if (i == 3)
		{
			Chips100 += MyPlayer.Chips[i][1];
			MyPlayer.Chips[i][1] = Chips100;
		}
	}

	// Prints Table of Two-Dimmensional Array
	/*for (int i = 0; i < 4; ++i) {
		cout << MyPlayer.Chips[i][0] << "   " << MyPlayer.Chips[i][1] << endl;
	}*/

	cout << "Your new total cash is $" << Cash << "\n\n";



	bContinue = false;

	do {

		cout << "Would you like to to do another exchange? [1] Yes, [2] No\n";
		cin >> AnotherExchange;

		if (AnotherExchange == 1 || AnotherExchange == 2)
		{
			bContinue = true;
		}
		else
		{
			cout << "\nInvalid Input. Try again\n";
			cin.clear();
			cin.ignore();
		}

	} while (!bContinue);

	if (AnotherExchange == 1) {
		MyCasino.ChipExchange(Cash);
		return;
	}
	else if (AnotherExchange == 2) {
		MyPlayer.CurrentCash = Cash;
		MyCasino.Lobby();
		return;
	}
}

void Casino::CashExchange(int Cash) {

	int ChipsToCash = 0;
	int AnotherExchange = 0;
	bool bContinue = false;
	int Chips1 = MyPlayer.Chips[0][1];
	int Chips20 = MyPlayer.Chips[1][1];
	int Chips50 = MyPlayer.Chips[2][1];
	int Chips100 = MyPlayer.Chips[3][1];

	system("cls");

	// Prints to screen total of CurrentCash from Player class
	cout << "Total Available Cash: $" << Cash << "\n\n";

	// If player has no cash then no exchange is possible
	if (MyPlayer.ChipsValue <= 0)
	{
		cout << "\nYou don't have enough chips to exchange\n\n";
		system("pause");
		MyCasino.Lobby();
		return;
	}

	// Prints out total NEW chips player gets from the exchange
	cout << "\nHere are your available chips:\n\n"
		<< "[1] Chips of $1: " << Chips1 << "\n"
		<< "[2] Chips of $20: " << Chips20 << "\n"
		<< "[3] Chips of $50: " << Chips50 << "\n"
		<< "[4] Chips of $100: " << Chips100 << "\n\n";

	// Will loop until a valid input is placed
	do {
		cout << "Which chips do you want to exchange to cash?\n"
			<< "Enter digit 1-4: ";
		cin >> ChipsToCash;

		if (ChipsToCash >= 1 && ChipsToCash <= 4)
		{
			bContinue = true;
		}
		else {
			cout << "\nInvalid Input. Try again\n";
			cin.clear();
			cin.ignore();
		}

	} while (!bContinue);

	switch (ChipsToCash)
	{
	case 1:
		for (int i = 0; i < Chips1; ++i)
		{
			Cash += 1;
		}
		MyPlayer.Chips[0][1] = 0;
		break;
	case 2:
		for (int i = 0; i < Chips20; ++i)
		{
			Cash += 20;
		}
		MyPlayer.Chips[1][1] = 0;
		break;
	case 3:
		for (int i = 0; i < Chips50; ++i)
		{
			Cash += 50;
			MyPlayer.Chips[2][1] = 0;
		}
		break;
	case 4:
		for (int i = 0; i < Chips100; ++i)
		{
			Cash += 100;
			MyPlayer.Chips[3][1] = 0;
		}
		break;
	default:
		break;
	}

	cout << "Your new total cash is $" << Cash << "\n\n";

	bContinue = false;

	do {

		cout << "Would you like to to do another exchange? [1] Yes, [2] No\n";
		cin >> AnotherExchange;

		if (AnotherExchange == 1 || AnotherExchange == 2)
		{
			bContinue = true;
		}
		else
		{
			cout << "\nInvalid Input. Try again\n";
			cin.clear();
			cin.ignore();
		}

	} while (!bContinue);

	if (AnotherExchange == 1) {
		MyCasino.CashExchange(Cash);
		return;
	}
	else if (AnotherExchange == 2) {
		MyPlayer.CurrentCash = Cash;
		MyCasino.Lobby();
		return;
	}

}

void Casino::ChooseGame() {
	
	int GameChoice = 0;
	bool bContinue = false;
	int Chips1 = MyPlayer.Chips[0][1];
	int Chips20 = MyPlayer.Chips[1][1];
	int Chips50 = MyPlayer.Chips[2][1];
	int Chips100 = MyPlayer.Chips[3][1];

	system("cls");

	// Shows on screen player name, current value of chips, and all current chips
	cout << "Name: " << MyPlayer.PName << "                      " << "Value of Chips: $" << MyPlayer.ChipsValue << "\n";
	cout << "Chips $1: " << MyPlayer.Chips[0][1] << "   "
		<< "Chips $20: " << MyPlayer.Chips[1][1] << "   "
		<< "Chips $50: " << MyPlayer.Chips[2][1] << "   "
		<< "Chips $100: " << MyPlayer.Chips[3][1] << "\n\n";

	if (Chips1 == 0 && Chips20 == 0 && Chips50 == 0 && Chips100 == 0)
	{
		cout << "You don't have any chips to exchange, please return when you have some\n\n";
		system("pause");
		MyCasino.Lobby();
		return;
	}

	cout << "Inside the Casino there are two [2] tables available:\n"
		<< "[1] BlackJack\n"
		<< "[2] Craps\n"
		<< "[3] Exit\n"
		<< "What table do you want to play in?\n";
	do {
		cout << "Enter digit 1-3: ";
		cin >> GameChoice;
		
		if (GameChoice == 1 || GameChoice == 2 || GameChoice == 3)
		{
			bContinue = true;
		}
		else
		{
			cout << "\nInvalid Input. Try again\n";
			cin.clear();
			cin.ignore();
		}

	} while (!bContinue);

	if (GameChoice == 1) {
		MyCasino.BlackJack();
		return;
	}
	else if (GameChoice == 2) {
		MyCasino.Craps();
		return;
	}
	else if (GameChoice == 3) {
		MyCasino.Lobby();
		return;
	}

}

void Casino::BlackJack() {

	int Ready2Play = 0;
	bool bContinue = false;

	system("cls");

	cout << "Name: " << MyPlayer.PName << "                      " << "Value of Chips: $" << MyPlayer.ChipsValue << "\n";
	cout << "Chips $1: " << MyPlayer.Chips[0][1] << "   "
		<< "Chips $20: " << MyPlayer.Chips[1][1] << "   "
		<< "Chips $50: " << MyPlayer.Chips[2][1] << "   "
		<< "Chips $100: " << MyPlayer.Chips[3][1] << "\n\n";

	cout << "Welcome to Blackjack!\n\n"
		<< "Rules:\n"
		<< "1)If you pass 21, you lose\n2)If you get 21, you win\n3)If the dealer passes 21, you win\n"
		<< "4)If the dealer gets 21, you lose\n5)If your hand is higher than the dealer, you win\n6)If the dealer's hand is higher than yours, you lose\n\n";

	do {
		cout << "\nReady to play? [1] Yes, [2] No, go back\n"
			<< "Enter digit 1-2: ";
		cin >> Ready2Play;

		if (Ready2Play == 1 || Ready2Play == 2)
		{
			bContinue = true;
		}
		else
		{
			cout << "Invalid Input. Try again\n";
			cin.clear();
			cin.ignore();
		}

	} while (!bContinue);

	if (Ready2Play == 1) {
		MyGame.PlayBJ();
	}
	else if (Ready2Play == 2) {
		MyCasino.ChooseGame();
		return;
	}

}

void Casino::Craps() {

	int Ready2Play = 0;
	bool bContinue = false;

	system("cls");

	cout << "Welcome to Craps";
	cout << "\n\nThe Rules\n*6 Dice are thrown\n1)If the sum of both dice is 7 or 11,you win\n"
		<< "2)If the sum of both dice is 2, 3 , 12 then you lose\n"
		<< "3)Any other number is a tie and the dice are thrown again, if you land on your original number you win,\n if you land on 7 or 11 you lose, any other number is a tie\n"
		<< "4)If it is a tie, you get your money back\n\n";

	do {
		cout << "\nReady to play? [1] Yes, [2] No, go back\n"
			<< "Enter digit 1-2: ";
		cin >> Ready2Play;

		if (Ready2Play == 1 || Ready2Play == 2)
		{
			bContinue = true;
		}
		else
		{
			cout << "Invalid Input. Try again\n";
			cin.clear();
			cin.ignore();
		}

	} while (!bContinue);

	if (Ready2Play == 1) {
		MyGame.PlayCraps();
	}
	else if (Ready2Play == 2) {
		MyCasino.ChooseGame();
		return;
	}
}

void Game::PlayBJ() {

	int Chips1 = MyPlayer.Chips[0][1];
	int Chips20 = MyPlayer.Chips[1][1];
	int Chips50 = MyPlayer.Chips[2][1];
	int Chips100 = MyPlayer.Chips[3][1];
	int Bet = 0;
	bool bContinue = false;
	int PFirstCard = 0; // First Card drawn by player
	int PSecondCard = 0; // Second Card drawn by player
	int PTotalOfCards = 0; // Sum of int PFirstCard and int PSecondCard
	int DFirstCard = 0; // First Card drawn by dealer
	int DSecondCard = 0; // Second Card drawn by dealer
	int DTotalOfCards = 0; // Sum of int DFirstCard and int DSecondCard
	int NewCard = 0; // New Card when Player or Dealer Hits
	int HitOrHold = 0;
	int PlayAgain = 0;

	system("cls");

	cout << "Name: " << MyPlayer.PName << "                      " << "Value of Chips: $" << MyPlayer.ChipsValue << "\n";
	cout << "Chips $1: " << Chips1 << "   "
		<< "Chips $20: " << Chips20 << "   "
		<< "Chips $50: " << Chips50 << "   "
		<< "Chips $100: " << Chips100 << "\n\n";
	
	do {
		cout << "How much do you want to bet?\n"
			<< "Bet amount: ";
		cin >> Bet;

		if (Bet > MyPlayer.ChipsValue || Bet == 0) {
			cout << "\nInvalid Amount. Try again\n";
			cin.clear();
			cin.ignore();
		}
		else {
			bContinue = true;
		}

	} while (!bContinue);
	

	system("cls");

	// Player's Hand
	PFirstCard = MyGame.DrawCard();
	PSecondCard = MyGame.DrawCard();
	PTotalOfCards = PFirstCard + PSecondCard;
	cout << "Your hand:\n";
	cout << "============================================================\n \n"
		<< "  Your first card is " << PFirstCard << "\n"
		<< "  Your second card is " << PSecondCard << "\n\n"
		<< "  Your total hand is " << PTotalOfCards << "\n"
		<< "============================================================\n\n\n\n\n";


	// Dealer's Hand
	DFirstCard = MyGame.DrawCard();
	DSecondCard = MyGame.DrawCard();
	DTotalOfCards = DFirstCard + DSecondCard;
	cout << "Dealer's hand:\n";
	cout << "============================================================\n \n"
		<< "  Dealer first card is " << DFirstCard << "\n\n\n\n"
		//<< "  Dealer second card is " << DSecondCard << "\n\n"
		//<< "  Dealer total hand is " << DTotalOfCards << "\n"
		<< "============================================================\n\n\n\n\n";

	bContinue = false;

	if (PTotalOfCards < 21)
	do {

		cout << "\nYour total hand is " << PTotalOfCards << ".\n"
			<< "Do you want to [1] hit for another card or [2] hold?\n"
			<< "Enter digit 1-2: ";
		cin >> HitOrHold;

		if (HitOrHold == 1) {
			NewCard = MyGame.DrawCard();
			PTotalOfCards += NewCard;
			cout << "\nYour new card is " << NewCard << "\n";
			cin.clear();
			cin.ignore();
		}
		else if (HitOrHold == 2) {
			bContinue = true;
		}
		else {
			cout << "\nInvalid Input. Try Again\n";
			cin.clear();
			cin.ignore();
		}

	} while (!bContinue);


	cout << "\nDealer's hand:\n";
	cout << "============================================================\n \n"
		<< "  Dealer first card is " << DFirstCard << "\n"
		<< "  Dealer second card is " << DSecondCard << "\n\n"
		<< "  Dealer total hand is " << DTotalOfCards << "\n"
		<< "============================================================\n\n\n\n\n";

	if (DTotalOfCards <= 16)
	{
		bContinue = false;
	}

	while (!bContinue) {


		NewCard = MyGame.DrawCard();
		DTotalOfCards += NewCard;

		cout << "\nDealer drew a new card: " << NewCard << "\n"
			<< "His total is now: " << DTotalOfCards << "\n\n";
		
		if (DTotalOfCards > 16)
		{
			bContinue = true;
		}

		
	}

	// If statementes to decide the winner, then the function restarts.
	if (PTotalOfCards == 21 && DTotalOfCards == 21) {
		cout << "\nIt's a tie, you don't lose your money!\n";
		system("pause");
	} 
	else if (PTotalOfCards == 21 && DTotalOfCards != 21) {
		cout << "\nYou got 21! Congratulations you won this hand!\n";
		MyCasino.GiveNewChips(Bet);
		MyPlayer.ChipsValue += Bet;
		system("pause");
	} 
	else if (PTotalOfCards != 21 && DTotalOfCards == 21) {
		cout << "\nThe dealer has 21, you lose!\n";
		MyPlayer.ChipsValue -= Bet;
		MyPlayer.Chips[0][1] = 0;
		MyPlayer.Chips[1][1] = 0;
		MyPlayer.Chips[2][1] = 0;
		MyPlayer.Chips[3][1] = 0;
		MyCasino.GiveNewChips(MyPlayer.ChipsValue);
			system("pause");
	} 
	else if (PTotalOfCards > 21) {
		cout << "\nYou're hand is over 21, you lose!\n";
		MyPlayer.ChipsValue -= Bet;
		MyPlayer.Chips[0][1] = 0;
		MyPlayer.Chips[1][1] = 0;
		MyPlayer.Chips[2][1] = 0;
		MyPlayer.Chips[3][1] = 0;
		MyCasino.GiveNewChips(MyPlayer.ChipsValue);
		system("pause");
	}
	else if (DTotalOfCards > 21) {
		cout << "\nDealer's hand is over 21, you won!\n";
		MyCasino.GiveNewChips(Bet);
		MyPlayer.ChipsValue += Bet;
		system("pause");
	}
	else if (PTotalOfCards > DTotalOfCards) {
		cout << "\nYou have a higher hand than the dealer, you won!\n";
		MyCasino.GiveNewChips(Bet);
		MyPlayer.ChipsValue += Bet;
		system("pause");
	}
	else if (PTotalOfCards < DTotalOfCards) {
		cout << "\nYou're hand lower than the dealer's, you lose!\n";
		MyPlayer.ChipsValue -= Bet;
		MyPlayer.Chips[0][1] = 0;
		MyPlayer.Chips[1][1] = 0;
		MyPlayer.Chips[2][1] = 0;
		MyPlayer.Chips[3][1] = 0;
		MyCasino.GiveNewChips(MyPlayer.ChipsValue);
		system("pause");
	}

	system("cls");
	bContinue = false;

	cout << "\nDo you want to play again?\n"
			<< "[1] Yes\n"
			<< "[2] No\n";

	do {

		cout << "Enter a digit 1-2: ";
		cin >> PlayAgain;

		if (PlayAgain == 1) {
			MyGame.PlayBJ();
			bContinue = true;
			return;
		}
		else if (PlayAgain == 2) {
			MyCasino.ChooseGame();
			bContinue = true;
			return;
		}
		else {
			cout << "\nInvalid Input.Try Again\n";
			cin.clear();
			cin.ignore();
		}

	} while (!bContinue);

}

void Game::PlayCraps() {

	int Chips1 = MyPlayer.Chips[0][1];
	int Chips20 = MyPlayer.Chips[1][1];
	int Chips50 = MyPlayer.Chips[2][1];
	int Chips100 = MyPlayer.Chips[3][1];
	int Bet = 0;
	int FDice = 0;
	int SDice = 0;
	int TotalOfDice = 0;
	bool bContinue = false;
	int PlayAgain = 0;
	int ThrowAgain = 0;

	system("cls");

	cout << "Name: " << MyPlayer.PName << "                      " << "Value of Chips: $" << MyPlayer.ChipsValue << "\n";
	cout << "Chips $1: " << Chips1 << "   "
		<< "Chips $20: " << Chips20 << "   "
		<< "Chips $50: " << Chips50 << "   "
		<< "Chips $100: " << Chips100 << "\n\n";

	do {
		cout << "How much do you want to bet?\n"
			<< "Bet amount: ";
		cin >> Bet;

		if (Bet > MyPlayer.ChipsValue || Bet == 0) {
			cout << "\nInvalid Amount. Try again\n";
			cin.clear();
			cin.ignore();
		}
		else {
			bContinue = true;
		}

	} while (!bContinue);


	system("cls");

	cout << "Ready to roll dice?\n";
	
	system("pause");

	FDice = MyGame.RollDice();
	SDice = MyGame.RollDice();
	TotalOfDice = FDice + SDice;

	cout << "Your first dice is a " << FDice << "\n\n";

	if (FDice == 1)
	{
		cout
			<< "===========\n"
			<< "=         =\n"
			<< "=    *    =\n"
			<< "=         =\n"
			<< "===========\n";
	}
	else if (FDice == 2)
	{
		cout
			<< "===========\n"
			<< "= *       =\n"
			<< "=         =\n"
			<< "=       * =\n"
			<< "===========\n";
	}
	else if (FDice == 3)
	{
		cout
			<< "===========\n"
			<< "= *       =\n"
			<< "=    *    =\n"
			<< "=       * =\n"
			<< "===========\n";
	}
	else if (FDice == 4)
	{
		cout
			<< "===========\n"
			<< "= *     * =\n"
			<< "=         =\n"
			<< "= *     * =\n"
			<< "===========\n";
	}
	else if (FDice == 5)
	{
		cout
			<< "===========\n"
			<< "= *     * =\n"
			<< "=    *    =\n"
			<< "= *     * =\n"
			<< "===========\n";
	}
	else if (FDice == 6)
	{
		cout
			<< "===========\n"
			<< "= *     * =\n"
			<< "= *     * =\n"
			<< "= *     * =\n"
			<< "===========\n";
	}


	cout << "\n\nYour second dice is a " << SDice << "\n\n";

	if (SDice == 1)
	{
		cout
			<< "===========\n"
			<< "=         =\n"
			<< "=    *    =\n"
			<< "=         =\n"
			<< "===========\n";
	}
	else if (SDice == 2)
	{
		cout
			<< "===========\n"
			<< "= *       =\n"
			<< "=         =\n"
			<< "=       * =\n"
			<< "===========\n";
	}
	else if (SDice == 3)
	{
		cout
			<< "===========\n"
			<< "= *       =\n"
			<< "=    *    =\n"
			<< "=       * =\n"
			<< "===========\n";
	}
	else if (SDice == 4)
	{
		cout
			<< "===========\n"
			<< "= *     * =\n"
			<< "=         =\n"
			<< "= *     * =\n"
			<< "===========\n";
	}
	else if (SDice == 5)
	{
		cout
			<< "===========\n"
			<< "= *     * =\n"
			<< "=    *    =\n"
			<< "= *     * =\n"
			<< "===========\n";
	}
	else if (SDice == 6)
	{
		cout
			<< "===========\n"
			<< "= *     * =\n"
			<< "= *     * =\n"
			<< "= *     * =\n"
			<< "===========\n";
	}

	cout << "\n\nYour total dice is a " << TotalOfDice << "\n\n";

	if (TotalOfDice == 7 || TotalOfDice == 11) {
		cout << "\nYou win!\n";
		MyCasino.GiveNewChips(Bet);
		MyPlayer.ChipsValue += Bet;
		system("pause");
	}
	else if (TotalOfDice == 2 || TotalOfDice == 3 || TotalOfDice == 12) {
		cout << "\nYou lose!\n";
		MyPlayer.ChipsValue -= Bet;
		MyPlayer.Chips[0][1] = 0;
		MyPlayer.Chips[1][1] = 0;
		MyPlayer.Chips[2][1] = 0;
		MyPlayer.Chips[3][1] = 0;
		MyCasino.GiveNewChips(MyPlayer.ChipsValue);
		system("pause");
	}
	else {

		MyGame.OriginalTotalOfDice = TotalOfDice;


		cout << "\nYou tied, ready to roll again?\n";

		system("pause");
		system("cls");


		FDice = MyGame.RollDice();
		SDice = MyGame.RollDice();
		TotalOfDice = FDice + SDice;

		cout << "Your first dice is a " << FDice << "\n\n";

		if (FDice == 1)
				{
					cout
						<< "===========\n"
						<< "=         =\n"
						<< "=    *    =\n"
						<< "=         =\n"
						<< "===========\n";
				}
		else if (FDice == 2)
				{
					cout
						<< "===========\n"
						<< "= *       =\n"
						<< "=         =\n"
						<< "=       * =\n"
						<< "===========\n";
				}
		else if (FDice == 3)
				{
					cout
						<< "===========\n"
						<< "= *       =\n"
						<< "=    *    =\n"
						<< "=       * =\n"
						<< "===========\n";
				}
		else if (FDice == 4)
				{
					cout
						<< "===========\n"
						<< "= *     * =\n"
						<< "=         =\n"
						<< "= *     * =\n"
						<< "===========\n";
				}
		else if (FDice == 5)
				{
					cout
						<< "===========\n"
						<< "= *     * =\n"
						<< "=    *    =\n"
						<< "= *     * =\n"
						<< "===========\n";
				}
		else if (FDice == 6)
				{
					cout
						<< "===========\n"
						<< "= *     * =\n"
						<< "= *     * =\n"
						<< "= *     * =\n"
						<< "===========\n";
				}


		cout << "\n\nYour second dice is a " << SDice << "\n\n";

		if (SDice == 1)
				{
					cout
						<< "===========\n"
						<< "=         =\n"
						<< "=    *    =\n"
						<< "=         =\n"
						<< "===========\n";
				}
		else if (SDice == 2)
				{
					cout
						<< "===========\n"
						<< "= *       =\n"
						<< "=         =\n"
						<< "=       * =\n"
						<< "===========\n";
				}
		else if (SDice == 3)
				{
					cout
						<< "===========\n"
						<< "= *       =\n"
						<< "=    *    =\n"
						<< "=       * =\n"
						<< "===========\n";
				}
		else if (SDice == 4)
				{
					cout
						<< "===========\n"
						<< "= *     * =\n"
						<< "=         =\n"
						<< "= *     * =\n"
						<< "===========\n";
				}
		else if (SDice == 5)
				{
					cout
						<< "===========\n"
						<< "= *     * =\n"
						<< "=    *    =\n"
						<< "= *     * =\n"
						<< "===========\n";
				}
		else if (SDice == 6)
				{
					cout
						<< "===========\n"
						<< "= *     * =\n"
						<< "= *     * =\n"
						<< "= *     * =\n"
						<< "===========\n";
				}

		cout << "\n\nYour total dice is a " << TotalOfDice << "\n\n";

		if (TotalOfDice == OriginalTotalOfDice) { // if you land on your original number you win, \n if you land on 7 or 11 you lose, any other number is a tie\n"
			cout << "\nYou win!\n";
			MyCasino.GiveNewChips(Bet);
			MyPlayer.ChipsValue += Bet;

		}
		else if (TotalOfDice == 7 || TotalOfDice == 11) {
			cout << "\nYou lose!\n";
			MyPlayer.ChipsValue -= Bet;
			MyPlayer.Chips[0][1] = 0;
			MyPlayer.Chips[1][1] = 0;
			MyPlayer.Chips[2][1] = 0;
			MyPlayer.Chips[3][1] = 0;
			MyCasino.GiveNewChips(MyPlayer.ChipsValue);
		}
		else {
			cout << "You tied again, you don't lose your bet!\n";
		}


		system("pause");


	}

	system("cls");

	bContinue = false;

	cout << "\n\nDo you want to play again?\n"
		<< "[1] Yes\n"
		<< "[2] No\n";

	do {

		cout << "Enter a digit 1-2: ";
		cin >> PlayAgain;

		if (PlayAgain == 1) {
			MyGame.PlayCraps();
			bContinue = true;
			return;
		}
		else if (PlayAgain == 2) {
			MyCasino.ChooseGame();
			bContinue = true;
			return;
		}
		else {
			cout << "\nInvalid Input.Try Again\n";
			cin.clear();
			cin.ignore();
		}

	} while (!bContinue);


}

int Game::DrawCard() {

	int  RandMax[1] = { 52 };

	int RCard = rand() % RandMax[0];

	int Draw = Deck[RCard];

	return Draw;
}

int Game::RollDice() {

	int RandMax[1] = { 6 };

	int RDice = rand() % RandMax[0];

	int Roll = Dice[RDice];

	return Roll;

}

void Casino::GiveNewChips(int Bet) {

	int Chips1 = 0;
	int Chips20 = 0;
	int Chips50 = 0;
	int Chips100 = 0;

	// Takes Bet and Gives Chips
	while (Bet >= 100)
	{
		Chips100++;
		Bet -= 100;
	}
	while (Bet >= 50) {
		Chips50++;
		Bet -= 50;
	}
	while (Bet >= 20)
	{
		Chips20++;
		Bet -= 20;
	}
	while (Bet >= 1)
	{
		Chips1++;
		Bet -= 1;
	}

	// Places Total Chips of each type into Two-Dimensional Array
	for (int i = 4; i >= 0; --i)
	{
		if (i == 0)
		{
			Chips1 += MyPlayer.Chips[i][1];
			MyPlayer.Chips[i][1] = Chips1;
		}
		if (i == 1)
		{
			Chips20 += MyPlayer.Chips[i][1];
			MyPlayer.Chips[i][1] = Chips20;
		}
		if (i == 2)
		{
			Chips50 += MyPlayer.Chips[i][1];
			MyPlayer.Chips[i][1] = Chips50;
		}
		if (i == 3)
		{
			Chips100 += MyPlayer.Chips[i][1];
			MyPlayer.Chips[i][1] = Chips100;
		}
	}

}

