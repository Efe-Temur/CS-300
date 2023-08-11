
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<cstdlib>
#include "StackList.h"
#include <random>

using namespace std;




struct Cell {
    //location
    int row;
    int col;

    //walls
    bool down = true;
    bool up = true;
    bool left = true;
    bool right = true;

    bool visited = false;

    bool isexit = false;
};




vector<vector<vector<Cell>>> generatemaze(int K, int M, int N) {

    vector<vector<Cell>> mazematrix(M, vector<Cell>(N));//matrix of the maze
    vector<vector<vector<Cell>>> mazes(K);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            mazematrix[i][j] = { i, j, true, true, true, true, false,false };
        }
    }

    for (int j = 0; j < K; j++) {
        Stack<Cell> MazeStack;
        //add 0,0 to maze
        mazematrix[0][0].visited = true;
        MazeStack.push(mazematrix[0][0]);


        while (!MazeStack.isEmpty()) {
            Cell current = MazeStack.peek();

            //Checking neigbor status
            bool validneighbor = false;
            //down
            if (current.row > 0 && !mazematrix[current.row - 1][current.col].visited) {
                validneighbor = true;
            }
            //up
            if (current.row < M - 1 && !mazematrix[current.row + 1][current.col].visited) {
                validneighbor = true;
            }
            //left
            if (current.col > 0 && !mazematrix[current.row][current.col - 1].visited) {
                validneighbor = true;
            }
            //right
            if (current.col <   N - 1 && !mazematrix[current.row][current.col + 1].visited) {
                validneighbor = true;
            }

            if (validneighbor) {
                random_device dev;
                mt19937 rng(dev());
                uniform_int_distribution<int> dist6(0, 3);
                int direction = dist6(rng);//0 down 1 up 2 left 3 right

                bool check = true;
                while (check = true) {
                    //down
                    if (direction == 0 && current.row > 0 && !mazematrix[current.row - 1][current.col].visited) {
                        current.down = false;
                        mazematrix[current.row][current.col].down = false;

                        mazematrix[current.row - 1][current.col].up = false;
                        mazematrix[current.row - 1][current.col].visited = true;
                        MazeStack.push(mazematrix[current.row - 1][current.col]);

                        cout << "went down" << endl;
                        break;
                    }
                    //up
                    if (direction == 1 && current.row <  M - 1 && !mazematrix[current.row + 1][current.col].visited) {
                        current.up = false;
                        mazematrix[current.row][current.col].up = false;

                        mazematrix[current.row + 1][current.col].down = false;
                        mazematrix[current.row + 1][current.col].visited = true;
                        MazeStack.push(mazematrix[current.row + 1][current.col]);

                        cout << "went up" << endl;
                        break;
                    }
                    //left
                    if (direction == 2 && current.col > 0 && !mazematrix[current.row][current.col - 1].visited) {
                        current.left = false;
                        mazematrix[current.row][current.col].left = false;

                        mazematrix[current.row][current.col - 1].right = false;
                        mazematrix[current.row][current.col - 1].visited = true;
                        MazeStack.push(mazematrix[current.row][current.col - 1]);

                        cout << "went left" << endl;
                        break;
                    }
                    //right
                    if (direction == 3 && current.col < N - 1 && !mazematrix[current.row][current.col + 1].visited) {
                        current.right = false;
                        mazematrix[current.row][current.col].right = false;

                        mazematrix[current.row][current.col + 1].left = false;
                        mazematrix[current.row][current.col + 1].visited = true;
                        MazeStack.push(mazematrix[current.row][current.col + 1]);

                        cout << "went right" << endl;
                        break;
                    }
                    break;

                }
            }

            else {

                MazeStack.pop();
                cout << "went back 1 " << endl;
            }

        }


        cout << "maze done" << endl;

        ofstream writer("maze_" + to_string(K) + ".txt");//i have realized i mixed up the values of row and col here so i swapped them.
        writer << N << " " << M << "\n";
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < M; i++) {
                writer << "x=" << mazematrix[i][j].col << "   ";
                writer << "y=" << mazematrix[i][j].row << "   ";
                writer << "l=" << mazematrix[i][j].left << "   ";
                writer << "r=" << mazematrix[i][j].right << "   ";
                writer << "u=" << mazematrix[i][j].up << "   ";
                writer << "d=" << mazematrix[i][j].down << "   " << "\n";
            }
        }
        cout << "writing done" << endl;

        mazes[j] = mazematrix;

        MazeStack.clear();

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                mazematrix[i][j] = { i, j, true, true, true, true, false };
            }
        }
    }
    cout << "pog"<<endl;
    return mazes;
}

void solver(vector<vector<vector<Cell>>> mazes, int M, int N) {
    int mazenumber = mazes.size();
    int mazeTOsolve;
    int entryx, entryy, exitx, exity;
    cout << "which maze would you like to solve (1 to " << mazes.size() << " )"<< endl;
    cin >> mazeTOsolve;

    cout << "what is the entry point (x,y): ";
    cin >> entryx >> entryy;
    cout << "what is the exit point (x,y): ";
    cin >> exitx >> exity;

    vector < vector < Cell>> mazematrix = mazes[mazeTOsolve - 1];

    mazematrix[exity][exitx].isexit = true;
    
    Stack<Cell> solvestack;
    //add entry to stack
    mazematrix[0][0].visited = true;
    solvestack.push(mazematrix[entryy][entryx]);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            mazematrix[i][j].visited = false;
        }
    }
    while (!solvestack.isEmpty()) {
        Cell current = solvestack.peek();
        if (current.isexit) {
            cout << "exit reached" << endl;
            break;
        }
        //Checking neigbor status
        bool validneighbor = false;
        //down
        if (current.row > 0 && !mazematrix[current.row - 1][current.col].up && !mazematrix[current.row - 1][current.col].visited) {
            validneighbor = true;
        }
        //up
        if (current.row < N - 1 && !mazematrix[current.row + 1][current.col].down && !mazematrix[current.row + 1][current.col].visited) {
            validneighbor = true;
        }
        //left
        if (current.col > 0 && !mazematrix[current.row][current.col - 1].right && !mazematrix[current.row][current.col - 1].visited) {
            validneighbor = true;
        }
        //right
        if (current.col < M - 1 && !mazematrix[current.row][current.col + 1].left && !mazematrix[current.row][current.col + 1].visited) {
            validneighbor = true;
        }

        if (validneighbor) {
            random_device dev;
            mt19937 rng(dev());
            uniform_int_distribution<int> dist6(0, 3);
            int direction = dist6(rng);//0 down 1 up 2 left 3 right

            bool check = true;
            while (check = true) {
                random_device dev;
                mt19937 rng(dev());
                uniform_int_distribution<int> dist6(0, 3);
                int direction = dist6(rng);//0 down 1 up 2 left 3 right
                //down
                if (current.isexit) {
                    cout << "exit reached" << endl;
                    check = false;

                }

                else if (direction == 0 && current.row > 0 && !mazematrix[current.row - 1][current.col].up && !mazematrix[current.row - 1][current.col].visited) {

                    mazematrix[current.row - 1][current.col].visited = true;
                    solvestack.push(mazematrix[current.row - 1][current.col]);

                    cout << "went down" << endl;

                    break;
                }

                //up
                else if (direction == 1 && current.row < N - 1 && !mazematrix[current.row + 1][current.col].down && !mazematrix[current.row + 1][current.col].visited) {
                    mazematrix[current.row + 1][current.col].visited = true;
                    solvestack.push(mazematrix[current.row + 1][current.col]);
                    cout << "went up" << endl;

                    break;
                }

                //left
                else if (direction == 2 && current.col > 0 && !mazematrix[current.row][current.col - 1].right && !mazematrix[current.row][current.col - 1].visited ) {
                    mazematrix[current.row][current.col - 1].visited = true;
                    solvestack.push(mazematrix[current.row][current.col - 1]);
                    cout << "went left" << endl;

                    break;
                }

                //right
                else if (direction == 3 && current.col < M - 1 && !mazematrix[current.row][current.col + 1].left && !mazematrix[current.row][current.col + 1].visited) {
                    mazematrix[current.row ][current.col+1].visited = true;
                    solvestack.push(mazematrix[current.row][current.col + 1]);
                    cout << "went right" << endl;

                    break;
                }


            }

        }
        else if (!current.isexit) {
            solvestack.pop();

        }

        cout << "done"<< endl;
    }
    Cell write = solvestack.peek();
    while (!solvestack.isEmpty() ){
        ofstream writer("maze_" + to_string(mazeTOsolve) + "_path_"+ to_string(entryx)+"_"+to_string(entryy)+"_" + to_string(exitx)+"_" + to_string(exity)+".txt");//i have realized i mixed up the values of row and col here so i swapped them.
        writer << write.row << " " << write.col << "\n";
        solvestack.pop();
        if (solvestack.isEmpty()) {
            break;
        }
        write = solvestack.peek();

    }
    cout << "solve doen" << endl;
}


int main() {
    int mazenum, ID, Minput, Ninput, Xentry, Yentry, Xexit, Yexit;

    cout << "enter the number of mazes: " << endl;
    cin >> mazenum;
    cout << "enter the size of the maze (M,N): " << endl;
    cin >> Minput >> Ninput;

    vector<vector<vector<Cell>>> mazes = generatemaze(mazenum, Minput, Ninput);

    

    solver(mazes,Minput,Ninput);

}


