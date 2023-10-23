#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>
#include <iostream>

/*
 * You may need to define some global variables for the information of the game map here.
 * Although we don't encourage to uss global variables in real cpp projects, you may have to use them because the use of
 * class is not taught yet. However, if you are member of A-class or have learnt the use of cpp class, member functions,
 * etc., you're free to modify this structure.
 */
int rows; // The count of rows of the game map
int columns;  // The count of columns of the game map
int game_state; // The state of the game, 0 for continuing, 1 for winning, -1 for losing
int num_of_visited_blocks, num_of_mines; // 分别存储已访问方块数量和雷的数量
int step_count; // 存储访问次数
int blocks_waiting_to_visit_queue_x[1024], blocks_waiting_to_visit_queue_y[1024], tail_of_bwtv, head_of_bwtv; // 存储扩散出来的需要访问的方块以及队列的头尾指针
int map[32][32]; // 地图 -1代表有雷 其余数字大小代表周围地雷个数
int visit[32][32]; // 记录地图探索情况 已访问部分记为1 未访问部分记为0
/**
 * @brief The definition of function InitMap()
 *
 * @details This function is designed to read the initial map from stdin. For example, if there is a 3 * 3 map in which
 * mines are located at (0, 1) and (1, 2) (0-based), the stdin would be
 *     3 3
 *     .X.
 * 
 *     ...
 *     ..X
 * where X stands for a mine block and . stands for a normal block. After executing this function, your game map would
 * be initialized, with all the blocks unvisited.
 */
void InitMap() {
  std::cin >> rows >> columns;
  for (int row = 0; row < rows; row++) {
      for (int column = 0; column < columns; column++) {
        char temp; // 申请临时变量
        std::cin >> temp; // 读入并判断是否为雷
        if (temp != '.') {
          map[row][column] = -1; // 雷记为-1
          num_of_mines++; // 雷的数量加一
          if (row > 0 and map[row - 1][column] != -1) map[row - 1][column]++; // 如果存在上一层且上一层与此方块邻近的方块不是雷，周围雷的个数加一
          if (row < rows - 1 and map[row + 1][column] != -1) map[row + 1][column]++; // 如果存在下一层且下一层与此方块邻近的方块不是雷，周围雷的个数加一
          if (column > 0 and map[row][column - 1] != -1) map[row][column - 1]++; // 如果存在左一列且左一列与此方块邻近的方块不是雷，周围雷的个数加一
          if (column < columns - 1 and map[row][column + 1] != -1) map[row][column + 1]++; // 如果存在右一列且右一列与此方块邻近的方块不是雷，周围雷的个数加一
          if (row > 0 and column > 0 and map[row - 1][column - 1] != -1) map[row - 1][column - 1]++; //如果存在左上角且左上角不是雷，周围雷的个数加一
          if (row > 0 and column < columns - 1 and map[row - 1][column + 1] != -1) map[row - 1][column + 1]++; //如果存在右上角且右上角不是雷，周围雷的个数加一
          if (row < rows - 1 and column > 0 and map[row + 1][column - 1] != -1) map[row + 1][column - 1]++; //如果存在左下角且左下角不是雷，周围雷的个数加一
          if (row < rows - 1 and column < columns - 1 and map[row + 1][column + 1] != -1) map[row + 1][column + 1]++; //如果存在右下角且右下角不是雷，周围雷的个数加一        
        }
      }
  }
}

/**
 * @brief The definition of function VisitBlock(int, int)
 *
 * @details This function is designed to visit a block in the game map. We take the 3 * 3 game map above as an example.
 * At the beginning, if you call VisitBlock(0, 0), the return value would be 0 (game continues), and the game map would
 * be
 *     1??
 *     ???
 *     ???
 * If you call VisitBlock(0, 1) after that, the return value would be -1 (game ends and the players loses) , and the
 * game map would be
 *     1X?
 *     ???
 *     ???
 * If you call VisitBlock(0, 2), VisitBlock(2, 0), VisitBlock(1, 2) instead, the return value of the last operation
 * would be 1 (game ends and the player wins), and the game map would be
 *     1@1
 *     122
 *     01@
 *
 * @param row The row coordinate (0-based) of the block to be visited.
 * @param column The column coordinate (0-based) of the block to be visited.
 *
 * @note You should edit the value of game_state in this function. Precisely, edit it to
 *    0  if the game continues after visit that block, or that block has already been visited before.
 *    1  if the game ends and the player wins.
 *    -1 if the game ends and the player loses.
 */
void VisitBlock(int row, int column) {  
  step_count++; // 访问次数加一
  if (map[row][column] != -1 and visit[row][column] == 0) { // 访问未访问方块
    num_of_visited_blocks++; // 访问方块数加一
    visit[row][column] = 1; // 方块已被访问
  }
  if (num_of_mines + num_of_visited_blocks == rows * columns) {  //检查是否访问完了
    game_state = 1; // 获胜
    return;
  }
  if (map[row][column] == -1) { // 踩中雷了
    visit[row][column] = 1; // 方块已被访问
    game_state = -1; // 游戏输了
    return;
  } else if (map[row][column] == 0) { // 周围无雷，向四周扩散未被访问过的点
    if (row > 0 and visit[row - 1][column] == 0) {
      num_of_visited_blocks++; 
      visit[row - 1][column] = 1; // 优化，避免队列中有重复元素
      blocks_waiting_to_visit_queue_x[tail_of_bwtv] = row - 1; // 向上
      blocks_waiting_to_visit_queue_y[tail_of_bwtv++] = column; //入队
    }
    if (row < rows - 1 and visit[row + 1][column] == 0) {
      num_of_visited_blocks++; 
      visit[row + 1][column] = 1; // 优化，避免队列中有重复元素      
      blocks_waiting_to_visit_queue_x[tail_of_bwtv] = row + 1; // 向下
      blocks_waiting_to_visit_queue_y[tail_of_bwtv++] = column; //入队
    }
    if (column > 0 and visit[row][column - 1] == 0) {
      num_of_visited_blocks++; 
      visit[row][column - 1] = 1; // 优化，避免队列中有重复元素
      blocks_waiting_to_visit_queue_x[tail_of_bwtv] = row; // 向左
      blocks_waiting_to_visit_queue_y[tail_of_bwtv++] = column - 1; //入队      
    }
    if (column < columns - 1 and visit[row][column + 1] == 0) {
      num_of_visited_blocks++; 
      visit[row][column + 1] = 1; // 优化，避免队列中有重复元素      
      blocks_waiting_to_visit_queue_x[tail_of_bwtv] = row; // 向右
      blocks_waiting_to_visit_queue_y[tail_of_bwtv++] = column + 1; //入队
    }
    if (column < columns - 1 and row > 0 and visit[row - 1][column + 1] == 0) {
      num_of_visited_blocks++; 
      visit[row - 1][column + 1] = 1; // 优化，避免队列中有重复元素   
      blocks_waiting_to_visit_queue_x[tail_of_bwtv] = row - 1; // 向右上
      blocks_waiting_to_visit_queue_y[tail_of_bwtv++] = column + 1; //入队
    } 
    if (column < columns - 1 and row < rows - 1 and visit[row + 1][column + 1] == 0) {
      num_of_visited_blocks++; 
      visit[row + 1][column + 1] = 1; // 优化，避免队列中有重复元素   
      blocks_waiting_to_visit_queue_x[tail_of_bwtv] = row + 1; // 向右下
      blocks_waiting_to_visit_queue_y[tail_of_bwtv++] = column + 1; //入队
    }   
    if (column > 0 and row > 0 and visit[row - 1][column - 1] == 0) {
      num_of_visited_blocks++; 
      visit[row - 1][column - 1] = 1; // 优化，避免队列中有重复元素   
      blocks_waiting_to_visit_queue_x[tail_of_bwtv] = row - 1; // 向左上
      blocks_waiting_to_visit_queue_y[tail_of_bwtv++] = column - 1; //入队
    }
    if (column > 0 and row < rows -1 and visit[row - 1][column - 1] == 0) {
      num_of_visited_blocks++; 
      visit[row + 1][column - 1] = 1; // 优化，避免队列中有重复元素   
      blocks_waiting_to_visit_queue_x[tail_of_bwtv] = row + 1; // 向左下
      blocks_waiting_to_visit_queue_y[tail_of_bwtv++] = column - 1; //入队
    }
  }
  if (head_of_bwtv < tail_of_bwtv) { //如果队列不为空
    head_of_bwtv++; // 队首出队
    step_count--; // 这一次访问不需要次数  
    VisitBlock(blocks_waiting_to_visit_queue_x[head_of_bwtv - 1], blocks_waiting_to_visit_queue_y[head_of_bwtv - 1]); //访问队首方块
  }
}

/**
 * @brief The definition of function PrintMap()
 *
 * @details This function is designed to print the game map to stdout. We take the 3 * 3 game map above as an example.
 * At the beginning, if you call PrintMap(), the stdout would be
 *    ???
 *    ???
 *    ???
 * If you call VisitBlock(2, 0) and PrintMap() after that, the stdout would be
 *    ???
 *    12?
 *    01?
 * If you call VisitBlock(0, 1) and PrintMap() after that, the stdout would be
 *    ?X?
 *    12?
 *    01?
 * If the player visits all blocks without mine and call PrintMap() after that, the stdout would be
 *    1@1
 *    122
 *    01@
 * (You may find the global variable game_state useful when implementing this function.)
 *
 * @note Use std::cout to print the game map, especially when you want to try the advanced task!!!
 */
void PrintMap() {
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      if (visit[row][column] == 0) { // 如果未访问
        if (game_state == 0 or game_state == -1) {
          std::cout << '?'; // 且游戏继续进行或者输了但是方块仍未访问则输出'?'
        } else if (game_state == 1) {
          std::cout << '@'; //若已经获胜则当前方块为未访问的雷，输出'@'
        }
      } else if (map[row][column] != -1) { // 如果不是雷，则输出周围的雷的数量
        std::cout << map[row][column];
      } else { // 是雷且已访问，则游戏一定输
          std::cout << 'X';       
      }
    }
    std::cout << std::endl; // 行末换行
  }
}

/**
 * @brief The definition of function ExitGame()
 *
 * @details This function is designed to exit the game. 
 * It outputs a line according to the result, and a line of two integers, visit_count and step_count,
 * representing the number of blocks visited and the number of steps taken respectively.
 */
void ExitGame() {
  if(game_state == -1) {
    std::cout << "GAME OVER!" << std::endl; //输
  } else {
    std::cout << "YOU WIN!" << std::endl; //赢
  }
  std::cout << num_of_visited_blocks << ' ' << step_count << std::endl; // 输出访问的方块数和使用的步数
  exit(0); // Exit the game immediately
}

#endif
