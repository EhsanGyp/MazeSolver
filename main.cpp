#include <iostream>
#include <vector>
using namespace std;

/*creating position struct with row and cols*/
struct Position
{
    int Row;
    int Col;
};

int main()
{
    /*end point existing flag*/
    bool found = false;

    /*Rows and Cols decleration*/
    int ROWS;
    int COLS;
    
    /*getting rows and cols as input from the user*/
    cout << "Enter number of rows: ";
    cin >> ROWS;

    cout << "Enter number of columns: ";
    cin >> COLS;

    /*dynamic maze*/
    vector<vector<char>> maze(ROWS, vector<char>(COLS));
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            cin >> maze[i][j];
        }
    }

    /* initializing start & end */
    int startRow = -1;
    int startCol = -1;
    int endRow = -1;
    int endCol = -1;

    /*making visited flag*/
    vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false)); 

    /*parent array for reconstructing path*/
    vector<vector<Position>> parent(ROWS, vector<Position>(COLS));

    /*finding start & end rows & cols*/
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(maze[i][j] == 'S')
            {
                startRow = i;
                startCol = j;
            }
            if(maze[i][j] == 'E')
            {
                endRow = i;
                endCol = j;
            }
        }
    }
    
    /*creating simple stack*/
    vector<Position> stack;

    /*making start as whole position struct*/
    Position start;
    start.Row = startRow;
    start.Col = startCol;

    /*pushing start position into stack*/
    stack.push_back(start); 
	
    /*mark start point as visited*/
    visited[startRow][startCol] = true;

    /*defining directions*/
    int dr[4] = {-1, 1, 0, 0};  /*up & down*/
    int dc[4] = {0, 0, -1, 1};  /*left & right*/
    
    /*main DFS logic*/
    while(!stack.empty())
    {
        Position current = stack.back();
		stack.pop_back();

        if(current.Row == endRow && current.Col == endCol)  /*end point found*/
        {
            cout << "Exit found" << endl;
            found = true;
            break;
        }

        /*exploring directions*/
        for(int i = 0; i < 4; i++)
        {
            int newRow = current.Row + dr[i];
            int newCol = current.Col + dc[i];
        
            /*validating new position*/
            if(newRow >= 0 && newRow < ROWS &&
               newCol >= 0 && newCol < COLS &&
               maze[newRow][newCol] != '#' &&
               !visited[newRow][newCol])
            {
                Position next;
                next.Row = newRow;
                next.Col = newCol;

                /*pushing new position into the stack*/
				stack.push_back(next);

                /*mark next position as visited*/
                visited[newRow][newCol] = true;

                /*having track of parent point*/
                parent[next.Row][next.Col] = current;
            }
        }  
    }
    
    if(found)
    {
        Position current;
        current.Row = endRow;
        current.Col = endCol;

        while(!(current.Row == startRow && current.Col == startCol))
        {
            cout << "(" << current.Row << ", " << current.Col << ")" << endl;

            /*mark path in maze*/
            if(!(current.Row == endRow && current.Col == endCol))
            {
                maze[current.Row][current.Col] = '*';
            }

            current = parent[current.Row][current.Col];
        }
        
        cout << "(" << startRow << ", " << startCol << ")" << endl;  
    
        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLS; j++)
            {
                cout << maze[i][j] << " ";
            }
            cout << endl;
        }
        
    }
    else
    {
        cout << "No path found" << endl;
    }

    return 0;
}
