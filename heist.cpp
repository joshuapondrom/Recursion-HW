//Joshua Pondrom
//Data Structures 1510 with Dr. Taylor
//

#include <iostream>
//I use the unistd.h library to see the printing of the maze over time
//comment this out if you are not on a unix machine along with the
//usleep function call
#include <unistd.h>
using namespace std;

const bool DEBUG = false;
const bool PRINT = false;

const char EMPTY = ' ';
const char PATH = '.';
const char END = 'E';

struct pos2d{
  int y;
  int x;
};

struct maze{
  string* maze_data;
  int height;
  int width;
  pos2d start;
  pos2d end;
};

void print_maze(maze current){
  if(DEBUG) cout << "printing maze" << endl;
  for(int i = 0; i < current.height; i++)
    cout << current.maze_data[i] << endl;
}

bool solve_maze(maze current, int x, int y){
  current.maze_data[y][x] = PATH;
  if(PRINT){
    print_maze(current);
    //comment the usleep out if you are not on a unix machine
    usleep(125000);
  }
  if(x == current.end.x && y == current.end.y)
    return true;
  if(current.maze_data[y+1][x] == END)
    return true;
  if(current.maze_data[y][x+1] == END)
    return true;
  if(current.maze_data[y-1][x] == END)
    return true;
  if(current.maze_data[y][x-1] == END)
    return true;
  if(current.maze_data[y+1][x] == EMPTY &&
     solve_maze(current,x,y+1))
    return true;
  if(current.maze_data[y][x+1] == EMPTY &&
     solve_maze(current,x+1,y))
    return true;
  if(current.maze_data[y-1][x] == EMPTY &&
     solve_maze(current,x,y-1))
    return true;
  if(current.maze_data[y][x-1] == EMPTY &&
     solve_maze(current,x-1,y))
    return true;
  current.maze_data[y][x] = EMPTY;
  if(DEBUG) cout << "wrong path, backtracking" << endl;
  return false;
}

pos2d find_token(maze current, char unfound_token){
  if(DEBUG) cout << "finding token" << endl;
  pos2d token_location;
  token_location.y = -1;
  token_location.x = -1;
  for(int i = 0; i < current.height; i++)
    for(int j = 0; j < current.width; j++){
      if(DEBUG) cout << "looking at pos:" << i << " " << j << endl;
      if(DEBUG) cout << "char is " << current.maze_data[i][j] << endl;
      if(current.maze_data[i][j] == unfound_token){
        token_location.y = i;
	token_location.x = j;
      }
    }
  if(DEBUG) cout << "found token" << endl;
  return token_location;
}

pos2d get_direction(pos2d current, int move){
  if(DEBUG) cout << "getting direction" << endl;
  if(move == 0)
    current.y++;
  if(move == 1)
    current.x++;
  if(move == 2)
    current.y--;
  if(move == 3)
    current.x--;
  return current;
}

maze read_maze(){
  if(DEBUG) cout << "reading maze" << endl;
  maze current;
  cin >> current.height >> current.width;
  cin.ignore();
  current.maze_data = new string[current.width];
  for(int i = 0; i < current.height; i++)
    getline(cin, current.maze_data[i]);
  if(DEBUG) cout << "made a maze of " << current.height << " " << current.width << " size"<< endl;
  return current;
}

int main(){
  if(DEBUG) cout << "starting execution" << endl;
  maze current;
  int maze_num = 0;
  do{
    current = read_maze();
    if(current.height != 0 && current.width != 0){
      current.start = find_token(current, 'B');
      current.end = find_token(current, 'E');
      if(solve_maze(current,current.start.x,current.start.y)){
        cout << "Map : " << maze_num << endl;
        maze_num++;
        current.maze_data[current.start.y][current.start.x] = 'B';
        print_maze(current);
        cout << endl;
      }
      else
        cout << "Unsolvable" << endl;
    }
  }while(current.height != 0 && current.width != 0);
  if(DEBUG) cout << "ending execution" << endl;
  return 0;
}
  
