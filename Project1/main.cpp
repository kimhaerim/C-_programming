#include <iostream>
using namespace std;
bool ifEquality(int A[4][4], int B[4][4]){
    int i,j;
    int count=0;
    for (i=0; i<4;i++){
        for(j=0; j<4; j++){
            if(A[i][j] == B[i][j])
                count++;
        }
    }
    if (count == 16)
        return true;
    else
        return false;
}

void Static() {
    int card_fix[4][4] = {{1, 2, 3, 4},{5, 6, 7, 8},{8, 7, 6, 5},{4, 3, 2, 1}};
    int result[4][4] = {0,};

    int answer[2];
    int player[2]={0,};
    int a1, a2, a3, a4, i=20;

    while (i>0){
        if(ifEquality(card_fix,result))
            break;
        for (int i1 = 1; i1 <= 2; i1++) {
            cout << "P" << i1 << "'s turn, choose two cards (" << i << " turns remain): ";
            cin >> answer[0] >> answer[1];

            if (answer[0] >= 45 || answer[1] >= 45) {
                cout << "Please enter a number within the range: ";
                cin >> answer[0] >> answer[1];
            }

            a1 = answer[0] / 10 - 1;
            a2 = answer[0] % 10 - 1;
            a3 = answer[1] / 10 - 1;
            a4 = answer[1] % 10 - 1;

            if (card_fix[a1][a2] == result[a1][a2] && card_fix[a3][a4] == result[a3][a4] && card_fix[a1][a2] == card_fix[a3][a4]){
                cout << "This is the value you have already entered. Please enter a number: " ;
                cin >> answer[0] >> answer[1];
                a1 = answer[0] / 10 - 1;
                a2 = answer[0] % 10 - 1;
                a3 = answer[1] / 10 - 1;
                a4 = answer[1] % 10 - 1;
            }


            cout << "   1 2 3 4" << endl << "--+--------" << endl;
            result[a1][a2] = card_fix[a1][a2];
            result[a3][a4] = card_fix[a3][a4];
            for (int j = 0; j < 4; j++) {
                cout << j + 1 << " | ";
                for (int z = 0; z < 4; z++) {
                    if (result[j][z] == 0) {
                        cout << "x ";
                    } else
                        cout << result[j][z] << " ";
                }
                cout << endl;
            }

            if(card_fix[a1][a2] == card_fix[a3][a4]){
                if (card_fix[a1][a2] == 7){
                    player[i1-1] = player[i1-1] + 2;
                }
                else
                    player[i1-1] = player[i1-1] + 1;
                cout << "P" << i1 << " found a matching pair!" << "P1's score: " << player[0] << ", P2's score: "<< player[1] << endl;
            } else {
                result[a1][a2] = 0, result[a3][a4] = 0;
                cout << "P" << i1 << " failed to find a mathcing pair" << endl;
            }
            i--;
        }
    }
    cout << "Game end! " << "P1's score: " << player[0] << ", P2's score: "<< player[1] << endl;
}

void Random(){
    srand(time(NULL));
    int bCheck[16] = {0,};
    int card_random[4][4];
    int result[4][4] = {0,};

    for (int i = 0; i < 4;) {
        for(int j=0; j<4;){
            int nTemp = rand() % 8 + 1;
            if (bCheck[nTemp] < 2) {
                bCheck[nTemp]++;
                card_random[i][j]= nTemp;
                ++j;
            }
        }
        ++i;
    }

    int answer[2];
    int player[2]={0,};
    int a1, a2, a3, a4, i=20;

    while (i>0){
        if(ifEquality(card_random,result))
            break;
        for (int i1 = 1; i1 <= 2; i1++) {
            cout << "P" << i1 << "'s turn, choose two cards (" << i << " turns remain): ";
            cin >> answer[0] >> answer[1];

            if (answer[0] >= 45 || answer[1] >= 45) {
                cout << "Please enter a number within the range: ";
                cin >> answer[0] >> answer[1];
            }

            a1 = answer[0] / 10 - 1;
            a2 = answer[0] % 10 - 1;
            a3 = answer[1] / 10 - 1;
            a4 = answer[1] % 10 - 1;

            if (card_random[a1][a2] == result[a1][a2] && card_random[a3][a4] == result[a3][a4] && card_random[a1][a2] == card_random[a3][a4]){
                cout << "This is the value you have already entered. Please enter a number: " ;
                cin >> answer[0] >> answer[1];
                a1 = answer[0] / 10 - 1;
                a2 = answer[0] % 10 - 1;
                a3 = answer[1] / 10 - 1;
                a4 = answer[1] % 10 - 1;
            }

            cout << "   1 2 3 4" << endl << "--+--------" << endl;
            result[a1][a2] = card_random[a1][a2];
            result[a3][a4] = card_random[a3][a4];
            for (int j = 0; j < 4; j++) {
                cout << j + 1 << " | ";
                for (int z = 0; z < 4; z++) {
                    if (result[j][z] == 0) {
                        cout << "x ";
                    } else
                        cout << result[j][z] << " ";
                }
                cout << endl;
            }

            if(card_random[a1][a2] == card_random[a3][a4]){
                if (card_random[a1][a2] == 7){
                    player[i1-1] = player[i1-1] + 2;
                }
                else
                    player[i1-1] = player[i1-1] + 1;

                cout << "P" << i1 << " found a matching pair!" << "P1's score: " << player[0] << ", P2's score: "<< player[1] << endl;
            } else {
                result[a1][a2] = 0, result[a3][a4] = 0;
                cout << "P" << i1 << " failed to find a mathcing pair" << endl;
            }
            i--;
        }
    }
    cout << "Game end! " << "P1's score: " << player[0] << ", P2's score: "<< player[1] << endl;
}

int main() {
    int mode;
    cout << "Choose card generation mode (1: Static, 2: Random) : ";
    cin >> mode;
    cout << "   1 2 3 4"<<endl<<"--+--------"<<endl<<"1| x x x x"<<endl<<"2| x x x x"<<endl<<"3| x x x x"<<endl<<"4| x x x x"<<endl;
    if (mode == 1)
        Static();
    else if (mode==2)
        Random();
    return 0;
}