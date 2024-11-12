#include <iostream>
#include <climits>

using namespace std;

class TicTacToe{

public:

    char p1, p2;
    char board[9];
    bool is_game_over;

    TicTacToe(){
        // initializing the board
        for(int i = 0; i < 9 ; i++){
            this->board[i] = i+'1';
        }
        is_game_over = false;
        cout << "Board is ready" << endl;
    }

    void choose_player(){
        cout << "Choose x or o : " ;
        cin >> this->p1;

        this->p2 = (this->p1 == 'x')?'o':'x';

        cout << "\nYou choose " << p1 << " your Oponent " << p2 << endl << endl;

        return ;
    }

    void display(){
        cout << "The Board ...." << endl << endl;
        cout << "\t| " << board[0] << " | " << board[1] << " | " << board[2] << " | " << endl;
        cout << "\t| " << board[3] << " | " << board[4] << " | " << board[5] << " | " << endl;
        cout << "\t| " << board[6] << " | " << board[7] << " | " << board[8] << " | " << endl;
        cout << endl;

        return ;
    }

    void make_move(){

        short num;

        while(true){
            cout << "Enter your choice : ";
            cin >> num;
            if(num == (int)board[num-1]-(int)'0'){
                board[num-1] = p1;
                break;
            }
            else{
                cout << "It's already filled. Choose some valid position damn it." << endl;
            }
        }
    }

    char isTerminalState(char board[]){
        if(board[0] == board[1] && board[1] == board[2]){
            return board[0];
        }
        else if(board[3] == board[4] && board[4] == board[5]){
            return board[3];
        }
        else if(board[6] == board[7] && board[7] == board[8]){
            return board[6];
        }
        else if(board[0] == board[3] && board[3] == board[6]){
            return board[0];
        }
        else if(board[1] == board[4] && board[4] == board[7]){
            return board[1];
        }
        else if(board[2] == board[5] && board[5] == board[8]){
            return board[2];
        }
        else if(board[0] == board[4] && board[4] == board[8]){
            return board[0];
        }
        else if(board[2] == board[4] && board[4] == board[6]){
            return board[2];
        }
        else if(isFull()){
            return 'T';
        }
        return 'N';
    }

    bool isFull(){
        for(int i=0; i<9 ;i++){
            if(this->board[i] == i+'1')   return false;
        }
        return true;
    }

    void check_status(){
        char status = isTerminalState(board);
        if(status == 'x'){   cout << "X won the game" << endl;is_game_over=true;}
        else if(status == 'o'){  cout << "O won the game" << endl;is_game_over=true;}
        else if(status == 'T'){  cout << "The game is tie" << endl;is_game_over=true;}
    }

    int miniMax(char board[], int depth, bool isMin) {
        char status = isTerminalState(board);

        if (status == p2) {
            return 10 - depth;
        }
        if (status == p1) {
            return depth - 10;
        }
        if (status == 'T') {
            return 0;
        }

        if (!isMin) {
            int bestMove = INT_MIN;
            for (int i = 0; i < 9; i++) {
                if (board[i] == '1' + i) {
                    board[i] = p2;
                    bestMove = max(bestMove, miniMax(board, depth + 1, !isMin));
                    board[i] = '1' + i;
                }
            }
            return bestMove;
        } else {
            int bestMove = INT_MAX;
            for (int i = 0; i < 9; i++) {
                if (board[i] == '1' + i) {
                    board[i] = p1;
                    bestMove = min(bestMove, miniMax(board, depth + 1, !isMin));
                    board[i] = '1' + i;
                }
            }
            return bestMove;
        }
    }

    void make_AI_move(){

        int bestval = INT_MIN;
        int best_move = -1;

        for(int i = 0; i < 9; i++) {
            if(board[i] == 'x' || board[i] == 'o') continue;

            board[i] = p2;
            int current_val = miniMax(board, 0, true);
            board[i] = '1' + i;

            if(current_val > bestval) {
                bestval = current_val;
                best_move = i;
            }
        }

        if(best_move != -1) {
            board[best_move] = p2;
        }
    }

};

int main(){
    cout << "Tic Tac Toe" << endl;

    TicTacToe game;

    game.choose_player();
    game.display();

    while (!game.is_game_over) {
        game.make_move();
        game.check_status();
        if(game.is_game_over)   break;
        game.make_AI_move();
        game.check_status();
        game.display();
    }

    return 0;
}
