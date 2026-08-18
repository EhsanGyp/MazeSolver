#include <iostream>
#include <vector>
using namespace std;

/*creating position struct with row and cols*/
struct Position
{
    int Row;
    int Col;
};

bool solveMaze(vector<vector<char>> & maze, vector<vector<bool>> & visited, vector<vector<Position>> & parent, Position end, vector<Position> & stack)
{
	/*defining directions*/
	int dr[4] = {-1, 1, 0, 0};  /*up & down*/
	int dc[4] = {0, 0, -1, 1};  /*left & right*/

	while(!stack.empty())
    {
        Position current = stack.back();
		stack.pop_back();

        if(current.Row == end.Row && current.Col == end.Col)  /*end point found*/
        {
			return true;
        }

        /*exploring directions*/
        for(int i = 0; i < 4; i++)
        {
            int newRow = current.Row + dr[i];
            int newCol = current.Col + dc[i];
        
            /*validating new position*/
            if(newRow >= 0 && newRow < maze.size() &&
               newCol >= 0 && newCol < maze[0].size() &&
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
	return false;
}

vector<vector<char>> mazeInput()
{

    /*Rows and Cols decleration*/
    int ROWS;
    int COLS;
    
    /*getting rows and cols as input from the user*/
    cout << "Enter number of rows: ";
    cin >> ROWS;

    cout << "Enter number of columns: ";
    cin >> COLS;

	if(ROWS == 0 || COLS == 0)
	{
		cout << "Invalid input,cant accept 0 rows or cols" << endl;
		return {};	

	}

    /*dynamic maze*/
    vector<vector<char>> maze(ROWS, vector<char>(COLS));
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            cin >> maze[i][j];
        }
    }
	return maze;
}

int main()
{
	vector<vector<char>> maze = mazeInput();

	if(maze.empty())
	{
		return 0;
	}

    /* initializing start & end */
    Position start;
	start.Row = -1;
	start.Col = -1;

    Position end;
	end.Row = -1;
	end.Col = -1;

    /*making visited flag*/
    vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false)); 
    /*parent array for reconstructing path*/
    vector<vector<Position>> parent(maze.size(), vector<Position>(maze[0].size()));

    /*finding start & end rows & cols*/
    for(int i = 0; i < maze.size(); i++)
    {
        for(int j = 0; j < maze[0].size(); j++)
        {
            if(maze[i][j] == 'S')
            {
                start.Row = i;
                start.Col = j;
            }
            if(maze[i][j] == 'E')
            {
                end.Row = i;
                end.Col = j;
            }
        }
    }

	if(start.Row == -1)
	{
		cout << "Start not found" << endl;
		return 0;
	}

	if(end.Row == -1)
	{
		cout << "End not found" << endl;
		return 0;
	}
	
    /*creating simple stack*/
    vector<Position> stack;

    /*pushing start position into stack*/
    stack.push_back(start); 
	
    /*mark start point as visited*/
    visited[start.Row][start.Col] = true;

	/*maze solver function call*/
	bool found_result = solveMaze(maze,visited,parent,end,stack);

    if(found_result)
    {
		cout << "Exit found" << endl;
        Position current;
        current.Row = end.Row;
        current.Col = end.Col;

        while(!(current.Row == start.Row && current.Col == start.Col))
        {
            cout << "(" << current.Row << ", " << current.Col << ")" << endl;

            /*mark path in maze*/
            if(!(current.Row == end.Row && current.Col == end.Col))
            {
                maze[current.Row][current.Col] = '*';
            }

            current = parent[current.Row][current.Col];
        }
        
        cout << "(" << start.Row << ", " << start.Col << ")" << endl;  
    
        for(int i = 0; i < maze.size(); i++)
        {
            for(int j = 0; j < maze[0].size(); j++)
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
