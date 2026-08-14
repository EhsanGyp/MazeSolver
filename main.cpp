#include <iostream>
using namespace std;

/*creating position stack with rows and cols*/
struct Position
{
    int Row;
    int Col;
};

int main()
{
    /*end point existing flag*/
    bool found = false;
    
    /* initializing start & end */
    int startRow = -1;
    int startCol = -1;
    int endRow = -1;
    int endCol = -1;

    /*hardcoding maze*/
    char maze[5][5] = 
    {
        {'S','.','#','.','.'},
        {'#','.','#','.','#'},
        {'.','.','.','.','#'},
        {'.','#','#','.','.'},
        {'.','.','.','.','E'}
    };

    /*making visited flag*/
    bool visited[5][5] = {}; 

    /*parent array for reconstructing path*/
    Position parent[5][5];

    /*finding start & end rows & cols*/
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
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
    Position stack[25];
    int top = -1;

    /*making start as whole position struct*/
    Position start;
    start.Row = startRow;
    start.Col = startCol;

    /*pushing start position into stack*/
    top++;
    stack[top] = start;

    /*mark start point as visited*/
    visited[startRow][startCol] = true;

    /*defining directions*/
    int dr[4] = {-1, 1, 0, 0};  /*up & down*/
    int dc[4] = {0, 0, -1, 1};  /*left & right*/
    
    /*main DFS logic*/
    while(top != -1)
    {
        Position current = stack[top];
        top--;

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
            if(newRow >= 0 && newRow < 5 &&
               newCol >= 0 && newCol < 5 &&
               maze[newRow][newCol] != '#' &&
               !visited[newRow][newCol])
            {
                Position next;
                next.Row = newRow;
                next.Col = newCol;

                /*pushing new position into the stack*/
                top++;
                stack[top] = next;

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
    
        for(int i = 0; i < 5; i++)
        {
            for(int j = 0; j < 5; j++)
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