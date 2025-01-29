#include <iostream>
#include <windows.h>
#include <cstdlib> //�H���ƥͦ� 
#include <ctime> //�����H���ؤl�� 

using namespace std;

int board[9][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    
};

bool editable[9][9];

int cur_r = 0, cur_c = 0;

void fill_number(char c)//��Ʀr 
{
    switch(c){
    	case '0':
			board[cur_r][cur_c]=0; break;
		case '1':
			board[cur_r][cur_c]=1; break;
    	case '2':
			board[cur_r][cur_c]=2; break;
    	case '3':
			board[cur_r][cur_c]=3; break;
    	case '4':
			board[cur_r][cur_c]=4; break;
		case '5':
			board[cur_r][cur_c]=5; break;
    	case '6':
			board[cur_r][cur_c]=6; break;
    	case '7':
			board[cur_r][cur_c]=7; break;
    	case '8':
			board[cur_r][cur_c]=8; break;
		case '9':
			board[cur_r][cur_c]=9; break;
		}
}

int up(int n){
    if(cur_r - n >= 0) { // �T�O���W�X���
        if(editable[cur_r - n][cur_c] != 0) { // �p�G�i�s��A�~��V�W�ˬd
            return up(n + 1);
        }
        return n; // �J�줣�i�s�誺��l�A��^�Z��
    }
    return 0;
}

int down(int n){
    if(cur_r + n <= 8) { // �T�O���W�X���
        if(editable[cur_r + n][cur_c] != 0) { // �p�G�i�s��A�~��V�U�ˬd
            return down(n + 1);
        }
        return n; // �J�줣�i�s�誺��l�A��^�Z��
    }
    return 0;
}

int left(int n){
    if(cur_c - n >= 0) { 
        if(editable[cur_r][cur_c - n] != 0) { 
            return left(n + 1); 
        }
        return n; 
    }
    return 0;
}

int right(int n){
    if(cur_c + n <= 8) { 
        if(editable[cur_r][cur_c + n] != 0) { 
            return right(n + 1); 
        }
        return n; 
    }
    return 0;
}

void move_cursor(char c)//���ʥ��� 
{
	c=toupper(c); //�����j�g 
    switch(c){
    	case 'W':
			cur_r-=up(1);break;
    	case 'S':
			cur_r+=down(1);break;
    	case 'A':
			cur_c-=left(1);break;
    	case 'D':
			cur_c+=right(1);break;
   
	}    
}

bool is_invalid(int i, int j)//������C��O�_���~ 
{
    //��� 
    bool row_seen[10] = {false};  //�����Ʀr�X�{���p(0����)(bool�w�]0) 
    for (int col = 0; col < 9; ++col)
    {
        int num = board[i][col];
        if (num != 0)//�Y���椣���šA�h���ܦ���bool�A�ϤU���S�J�즹�Ʈɦ^��1 
        {
            if (row_seen[num]) return true;  //�����Ʀr�O�_����
            row_seen[num] = true;
        }
    }

    //����
    bool col_seen[10] = {false};  //�����Ʀr�X�{���p(0����) 
    for (int row = 0; row < 9; ++row)
    {
        int num = board[row][j];
        if (num != 0)
        {
            if (col_seen[num]) return true;  //�����Ʀr�O�_����
            col_seen[num] = true;
        }
    }

	//��l
	int start_row = (i / 3) * 3;  
    int start_col = (j / 3) * 3;  //�w��Ʀr�Ҧb��l 

    bool block_seen[10] = {false}; 
    for (int row = start_row; row < start_row + 3; ++row)
    {
        for (int col = start_col; col < start_col + 3; ++col)
        {
            int num = board[row][col];
            if (num != 0)
            {
                if (block_seen[num]) return true;  
                block_seen[num] = true;
            }
        }
    }



    return false;
}

bool is_done(int i, int j)
{
     //��� 
    bool row_seen[10] = {false};  //�P�W���P�z�A�ȭY���Ʀr���ơA�^�ǭȧאּ0 
    for (int col = 0; col < 9; ++col)
    {
        int num = board[i][col];
        if (num != 0)
        {
            if (row_seen[num]) return false; // �����Ʀr�O�_����
            row_seen[num] = true;
        }
    }
	if(row_seen[1]&&row_seen[2]&&row_seen[3]&&row_seen[4]&&row_seen[5]&&row_seen[6]&&row_seen[7]&&row_seen[8]&&row_seen[9]){//�Y�L�Ʀr���ơA�h�^��1 
		return true;
	}
	
	 //���� 
    bool col_seen[10] = {false};  
    for (int row = 0; row < 9; ++row)
    {
        int num = board[row][j];
        if (num != 0)
        {
            if (col_seen[num]) return false; // �����Ʀr�O�_����
            col_seen[num] = true;
        }
    }
	if(col_seen[1]&&col_seen[2]&&col_seen[3]&&col_seen[4]&&col_seen[5]&&col_seen[6]&&col_seen[7]&&col_seen[8]&&col_seen[9]){
		return true;
	}

	//��l
	int start_row = (i / 3) * 3;  
    int start_col = (j / 3) * 3;  //�w��Ʀr�Ҧb��l 

    bool block_seen[10] = {false}; 
    for (int row = start_row; row < start_row + 3; ++row)
    {
        for (int col = start_col; col < start_col + 3; ++col)
        {
            int num = board[row][col];
            if (num != 0)
            {
                if (block_seen[num]) return false;  
                block_seen[num] = true;
            }
        }
    }
	if(block_seen[1]&&block_seen[2]&&block_seen[3]&&block_seen[4]&&block_seen[5]&&block_seen[6]&&block_seen[7]&&block_seen[8]&&block_seen[9]){
		return true;
	}

    return false;
}

bool check_win()//�����ӧQ���� 
{
    for (int i = 0; i < 9; ++i) //�Ҧ���l����0 
    {
        for (int j = 0; j < 9; ++j)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
        }
    }

    for (int i = 0; i < 9; ++i)	//�Ҧ���l�L�~
    {
        for (int j = 0; j < 9; ++j)
        {
            if (is_invalid(i, j))
            {
                return false; 
            }
        }
    }
 

    return true; //��̳��q�L�Y���\ 
    
    
    
    return false;
}

bool solve()//�^�Ҫk���͸ѵ� 
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (board[i][j] == 0)
            {
                for (int num = 1; num <= 9; ++num)
                {
                    board[i][j] = num;
                    if (!is_invalid(i, j) && solve())//�^�Ҫk 
                        return true;
                    board[i][j] = 0;
                }
                return false;
            }
        }
    }
    return true;
}

void generate_random_puzzle() {
    srand(time(0));// �ϥη�e�ɶ���l���H���ؤl
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            board[i][j] = 0;// �N��ӴѽL���]�� 0 (�Ů�)

    solve();// �ϥΦ^���k�񺡾�ӼƿW�ѽL

    int clues_to_remove = 50 + rand() % 10; // ���� 50�� 60 �ӼƦr
    while (clues_to_remove > 0)
    {
        int r = rand() % 9;// �M���H���Ʀr 
        int c = rand() % 9;
        if (board[r][c] != 0)
        {
            board[r][c] = 0;
            clues_to_remove--;
        }
    }
}


bool is_ans(char c)
{
    return (c == 'x' || c == 'X');
}

bool is_moving_action(char c)
{
    return (c == 'W' || c == 'w' || c == 'S' || c == 's' ||
            c == 'A' || c == 'a' || c == 'D' || c == 'd');
}

bool is_filling_action(char c)
{
    return (c >= '0' && c <= '9');
}

string get_styled_text(string text, string style)
{
    string color = "", font = "";
    for (char c : style)
    {
        if (c == 'R')
            color = "31";
        if (c == 'G')
            color = "32";
        if (c == 'E')
            color = "41";
        if (c == 'C')
            color = "106";
        if (c == 'B')
            font = ";1";
    }
    return "\x1b[" + color + font + "m" + text + "\x1b[0m";
}

void print_board()
{
    // Flush the screen
    cout << "\x1b[2J\x1b[1;1H";

    // Print usage hint.
    cout << get_styled_text("W/A/S/D: ", "B") << "move cursor" << endl;
    cout << get_styled_text("    1-9: ", "B") << "fill in number" << endl;
    cout << get_styled_text("      0: ", "B") << "clear the cell" << endl;
    cout << get_styled_text("      Q: ", "B") << "quit" << endl;
    cout << get_styled_text("      X: ", "B") << "show answer" << endl;
    cout << endl;

    // Iterate through and print each cell.
    for (int i = 0; i < 9; ++i)
    {
        // Print horizontal divider.
        if (i && i % 3 == 0)
            cout << "-------------------------------" << endl;

        // Print the first vertical divider in each line.
        cout << "|";
        for (int j = 0; j < 9; ++j)
        {
            // Set text style based on the state of the cell.
            string style = "";

            // Set style for the cell the cursor pointing to.
            if (cur_r == i && cur_c == j)
                style = "C";
            // Set style for the cell in an invalid line.
            else if (is_invalid(i, j))
                style = "E";
            // Set style for the cell in a finished line.
            else if (is_done(i, j))
                style = "G";

            // Set style for a the cell that is immutable.
            if (!editable[i][j])
                style += "B";

            // Print the cell out in styled text.
            // If the content is 0, print a dot, else print the number.
            if (board[i][j] == 0)
                cout << get_styled_text(" �P ", style);
            else
                cout << get_styled_text(" " + to_string(board[i][j]) + " ", style);

            // Print the vertical divider for each block.
            if ((j + 1) % 3 == 0)
                cout << "|";
        }
        cout << endl;
    }
}

void initialize()
{
    // Set up styled text for Windows.
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    // Mark editable cells
    generate_random_puzzle();
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            editable[i][j] = (board[i][j] != 0);
    print_board();

}

int main()
{
    char c;
    bool action_ok;

    initialize();
    while (cin >> c)
    {
    	if (is_ans(c))
        {
            	solve(); 
                print_board();
                break;
		}   
		
        action_ok = false;
        if (is_moving_action(c))
        {
            action_ok = true;
            move_cursor(c);
        }

        if (is_filling_action(c))
        {
            action_ok = true;
            fill_number(c);
        }

        if (c == 'Q' || c == 'q')
            break;
        
		                  

        print_board();

        if (check_win())
        {
            cout << "YOU WIN!" << endl;
            break;
        }

        if (!action_ok)
            cout << get_styled_text("!!! Invalid action !!!", "R");
    }

    return 0;
}

