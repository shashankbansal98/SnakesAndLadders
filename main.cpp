#include <bits/stdc++.h>
using namespace std;

class SnakesAndLadders{
public:
	int boardSize;
	int	numberOfPlayers;
	deque<string> players;
	vector<pair<int, int>> snakes;
	vector<pair<int, int>> ladders;
	map<string, int> playerPositionMap;

	SnakesAndLadders(int boardSize, int	numberOfPlayers, deque<string>& players, vector<pair<int, int>>& snakes, vector<pair<int, int>>& ladders){
		this->boardSize = boardSize;
		this->numberOfPlayers = numberOfPlayers;
		this->players = players;
		this->snakes = snakes;
		this->ladders = ladders;
		srand(time(0));

		for(auto player : players){
			playerPositionMap[player] = 0;
		}
	}

	int rollDice(){
		return (rand()%6)+1;
	}

	bool isGameCompleted(){
		if(players.size() < numberOfPlayers){
			return true;
		}
		return false;
	}

	bool hasPlayerWon(string player) {
        int playerPosition = playerPositionMap[player];
        int winningPosition = boardSize;
        return playerPosition == winningPosition; 
    }


	int getNewPositionAfterGoingThroughSnakesAndLadders(int newPosition){
		int previousPosition;

        do {
            previousPosition = newPosition;
            for (auto snake : snakes) {
                if (snake.first == newPosition) {
                    newPosition = snake.second; 
                }
            }

            for (auto ladder : ladders) {
                if (ladder.first == newPosition) {
                    newPosition = ladder.second; 
                }
            }
        } while (newPosition != previousPosition); 

        return newPosition;
	}

	void movePlayer(string currPlayer, int diceValue){
		int prevPosition = playerPositionMap[currPlayer];
		int newPosition = prevPosition + diceValue;

		if(newPosition > boardSize){
			newPosition = prevPosition;
		}

		else{
			newPosition = getNewPositionAfterGoingThroughSnakesAndLadders(newPosition);
			playerPositionMap[currPlayer] = newPosition;
		}
		cout<<currPlayer<<" rolled a "<< diceValue <<" and moved from " << prevPosition << " to " << newPosition <<endl;
	}

	void startGame(){
		while(!isGameCompleted()){
			string currPlayer = players.front();
			players.pop_front();
			
			int diceValue = rollDice();
			movePlayer(currPlayer, diceValue);

            if (hasPlayerWon(currPlayer)) {
                cout<<currPlayer<<" wins the game";
                return;
            } 

            else {
                players.push_back(currPlayer);
            }
		}
	}
};

int main(){
	int numberOfSnakes;
	cin>>numberOfSnakes;

	vector<pair<int, int>> snakes;
	for(int i=0; i<numberOfSnakes; i++){
		int startPosition, endPosition;
		cin>>startPosition>>endPosition;
		snakes.push_back(make_pair(startPosition, endPosition));
	}

	int numberOfLadders;
	cin>>numberOfLadders;

	vector<pair<int, int>> ladders;
	for(int i=0; i<numberOfLadders; i++){
		int startPosition, endPosition;
		cin>>startPosition>>endPosition;
		ladders.push_back(make_pair(startPosition, endPosition));
	}

	int numberOfPlayers;
	cin>>numberOfPlayers;

	deque<string> players;
	for(int i=0; i<numberOfPlayers; i++){
		string playerName;
		cin>>playerName;
		players.push_back(playerName);
	}	

	SnakesAndLadders snakesandladders(100, numberOfPlayers, players, snakes, ladders);
	snakesandladders.startGame();
	return 0;
}
