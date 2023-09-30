#include <iostream>
#include <iomanip>

using namespace std;

class Sudoku
{

    int board[9][9];

public:
    Sudoku()
    {
        reset();
    }

    void reset()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                board[i][j] = 0;
            }
        }
    }

    void display()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if ((j + 1) % 3 == 0 & j != 8)
                {
                    cout << setw(4) << board[i][j] << "|";
                }
                else
                {
                    cout << setw(4) << board[i][j] << " ";
                }
            }
            cout << endl;
            if ((i + 1) % 3 == 0)
            {
                cout << "--------------------------------------------" << endl;
            }
        }
    }

    void accept()
    {
        int slotNum, value, row, col;
        reset();
        while (true)
        {
            cout << "Enter the slot number(Enter -1 to end):";
            cin >> slotNum;

            if (slotNum == -1)
            {
                break;
            }

            cout << "Enter the value:";
            cin >> value;

            if (value <= 0 | value > 9)
            {
                cout << "Value is invalid. Please re-enter the value:";
                cin >> value;
            }

            row = slotNum / 9;
            col = slotNum % 9;

            board[row][col - 1] = value;

            display();
        }
    }

    bool analyze(int num, int row, int col)
    {
        if (board[row][col] != 0)
        {
            return false;
        }

        for (int i = 0; i < 9; i++)
        {
            if (board[row][i] == num || board[i][col] == num)
            {
                return false;
            }
        }

        int x = row / 3, y = col / 3;
        int mid_x = (x * 3) + 1, mid_y = (y * 3) + 1;

        for (int i = mid_x - 1; i <= mid_x + 1; i++)
        {
            for (int j = mid_y - 1; j <= mid_y + 1; j++)
            {
                if (board[i][j] == num)
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool solver()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] == 0)
                {
                    for (int idx = 1; idx <= 9; idx++)
                    {
                        if (analyze(idx, i, j))
                        {
                            board[i][j] = idx;
                            bool nxtCall = solver();

                            if (nxtCall)
                            {
                                return true;
                            }
                            else
                            {
                                board[i][j] = 0;
                            }
                        }
                    }
                    if (board[i][j] == 0)
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void run()
    {
        solver();
        display();
    }

    void help()
    {
        cout << "Board Layout(numbers denote the slot number):" << endl;
        int counter = 1;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if ((j + 1) % 3 == 0 & j != 8)
                {
                    cout << setw(4) << counter << "|";
                }
                else
                {
                    cout << setw(4) << counter << " ";
                }
                counter++;
            }

            cout << endl;
            if ((i + 1) % 3 == 0)
            {
                cout << "--------------------------------------------" << endl;
            }
        }
    }
};

int main()
{
    Sudoku mySudoku;
    int choice;

    do
    {
        cout << "------------------------------------------------------------------\nChoices:\n1]Create\n2]Solve\n3]Display\n4]Help\n5]Exit\nEnter your choice:";
        cin >> choice;
        cout << "------------------------------------------------------------------" << endl;

        switch (choice)
        {
        case 1:
            mySudoku.accept();
            break;

        case 2:
            mySudoku.run();
            break;
        case 3:
            mySudoku.display();
            break;

        case 4:
            mySudoku.help();
            break;

        default:
            break;
        }
    } while (choice != 5);

    return 0;
}