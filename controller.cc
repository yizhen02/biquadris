#include "controller.h"
#include "view.h"
#include "board.h"
#include "score.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
using namespace std;

Controller::Controller(bool ableGraph,int level, string file1, string file2):
	canGraph{ableGraph}, level{level}{
	view = new View(canGraph);
	scorePlayer1 = new Score(view, level, 150, 150);
        scorePlayer2 = new Score(view, level, 650, 150);
        player1 = new Board(level,view, scorePlayer1, file1, 150, 150);
        player2 = new Board(level,view, scorePlayer2, file2, 650, 150);
}

void Controller::run(){
	string command;
	Board* curPlayer = player1;
	ifstream fileRead;
	bool needFile = false;
	while(true){
		view->textDisplay(player1,player2);
		if(player1->specialAvail){
			specialAction(player2);
			player2->unsetBlind();
                	player2->setHeavy(false);
                	player2->setForce(false);
			player1->specialAvail = false;
		} else if (player2->specialAvail){
                        specialAction(player1);
			player1->unsetBlind();
                        player1->setHeavy(false);
                        player1->setForce(false);
			player2->specialAvail = false;
       		}
		if (needFile){
			while (fileRead >> command){
				cout << command << endl;
			}
			needFile =false;
			if(!(cin>>command)) {
				break;
			}
		} else {
			if (!(cin >> command)) {
				break;
			}
		}
		stringstream ss{command};
		string partCom;
		int num = 1;
		if (!(ss >> num)){
			ss.clear();
			stringstream secondss{command};
			secondss >> partCom;
			num = 1;
		} else {
			ss >> partCom;
		}
		if (partCom.substr(0,3) == "lef") {
			curPlayer->moveBlock(-1 * num,0, 0);
		} else if (partCom.substr(0,2) == "ri"){
			curPlayer->moveBlock(num,0, 0);
		} else if (partCom.substr(0,2) == "do"){
			curPlayer->moveBlock(0,num, 0);
		} else if (partCom.substr(0,2) == "cl"){
			curPlayer->moveBlock(0,0,num);
		} else if (partCom.substr(0,2) == "co"){
			curPlayer->moveBlock(0,0,-1 *num);
		} else if (partCom.substr(0,2) == "dr"){
			curPlayer->drop();		
			if (curPlayer == player1) {
                        	curPlayer = player2;
                	} else {
                        	curPlayer = player1;
                	}
		} else if (partCom.substr(0,6) == "levelu"){
			for(int i = 0; i < num; ++i) {
				curPlayer->levelup();
			}
		} else if (partCom.substr(0,6) == "leveld"){
			for(int i = 0; i < num; ++i) {
				curPlayer->leveldown();
			}
		} else if (partCom.substr(0,1) == "n") {
			string f;
			cin >> f;
			curPlayer->random(f);
		} else if (partCom.substr(0,2) == "ra"){
			curPlayer->lev->file = "";
		} else if (partCom.substr(0,2) == "se"){
			string f;
			cin >> f;
			fileRead = ifstream{f};
			needFile = true;
		} else if (partCom == "I" ||partCom == "J"||partCom == "L"||
				partCom == "O"||partCom == "Z"||partCom == "S"||
				partCom == "T"){
			curPlayer->changeBlock(partCom[0]);
		} else if (partCom.substr(0,2) == "re"){
			restart();
		} else {
			cout << "Invalid command"<< endl;
			continue;
		}
		if (curPlayer->endGame){
			view->textDisplay(player1, player2);
			cout << "Game ends" << endl;
			restart();
			end();
			break;
		}
		cout << endl;
	}
}

void Controller::restart(){
	int score1 = scorePlayer1->curScoreGetter();
	int score2 = scorePlayer2->curScoreGetter();
	cout << "Player 1's score: " << score1 << endl;
	cout << "Player 2's score: " << score2 << endl;
	if (score1 > score2 ) {
		cout << "Player 1 wins!" << endl;
	} else if (score1 < score2) {
		cout << "Player 2 wins!" << endl;
	} else {
		cout << "Tie!" << endl;
	}
	reset();
}

void Controller::end(){
	string go = "";
	while (go != "reset" && go != "end") {
		cout << "Enter reset to RESET GAME, end to END GAME" << endl;
		cin >> go;
		if (cin.eof()) break;
	}
	if (go == "reset") {
		reset();
		run();
	} else if (go == "end") {
		int score1 = scorePlayer1->curScoreGetter();
        	int score2 = scorePlayer2->curScoreGetter();
       	 	cout << "Player 1's score: " << score1 << endl;
        	cout << "Player 2's score: " << score2 << endl;
        	if (score1 > score2 ) {
                	cout << "Player 1 wins!" << endl;
       		} else if (score1 < score2) {
                	cout << "Player 2 wins!" << endl;
        	} else {
                	cout << "Tie!" << endl;
        	}
		view->terminateGame(player1, player2);
	}
}

void Controller::reset(){
	scorePlayer1->scoreReset();
	scorePlayer2->scoreReset();
	player1->resetBoard();
	player2->resetBoard();
	player1->setCurLevel(player1->getCurLevel());
	player2->setCurLevel(player2->getCurLevel());
	player1->endGame = false;
	player2->endGame = false;
	player1->unsetBlind();
        player1->setHeavy(false);
        player1->setForce(false);
	player2->unsetBlind();
        player2->setHeavy(false);
        player2->setForce(false);
}


void Controller::specialAction(Board* p){
	while(true) {
		cout << "Special Action to take(blind/heavy/force): " << endl;
		string special;
		cin >> special;
		if (special == "blind") {
			p->setBlind();
			view->textDisplay(player1, player2);
			break;
		} else if(special == "heavy") {
			p->setHeavy(true);
			view->textDisplay(player1, player2);
		} else if(special == "force") {
			p->setForce(true);
			char t= ' ';
			while (t != 'I' ||t != 'J'||t !=  'L'||
                                t !=  'O'||t !=  'Z'||t !=  'S'||
                                t !=  'T'){
				cout << "Choose type: I, J , L, O, Z, S, T" << endl;
				cin >> t;
			}
                        p->changeBlock(t);
			view->textDisplay(player1, player2);
		} else {
			cout << "Invalid special action.";
		}
	}
}
