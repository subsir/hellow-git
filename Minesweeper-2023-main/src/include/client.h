#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <utility>
#include <cstring>
#include <cstdlib>
#include <ctime>

extern int rows;     // The count of rows of the game map
extern int columns;  // The count of columns of the game map
// You can not use any other external variables except for rows and columns.
int readmap[32][32]; // 地图读入，其中数字>=0代表周围雷的个数，-1代表未访问
float analysemap[32][32]; // 分析地图，数字大小代表周围是雷的概率(需要初始化)
int num_of_unknown_blocks_surrounding[32][32]; // 存储方块周围未访问的方块数量(需要初始化)
int edge_line[1024 * 8][2], top_of_line; // 存储边缘线和边缘线方块个数，其中[0]代表row，[1]代表column(需要初始化)
int core_sequence[1024][2], top_of_core; // 存储周围有雷的方块坐标和数量，其中[0]代表row，[1]代表column(需要初始化)
int time_out; // 卡时

std::string surrounding[32][32]; // 存储方块周围未访问的方块坐标，其中偶数位是row，奇数位是column(需要初始化)

// 名词解释：周围有雷的方块称为core，core周围的方块连成的线称为line

std::string Sequence_of_the_surrounding_blocks(int row, int column) { // 用字符串方式返回方块周围的方块坐标，其中偶数位是row，奇数位是column
  std::string sequence = "";
  if (row > 0) { // 存在上方的方块
    sequence += (char)(row + '0' - 1);
    sequence += (char)(column + '0');
  }
  if (row < rows - 1) { // 存在下方的方块
    sequence += (char)(row + '0' + 1);
    sequence += (char)(column + '0');
  }
  if (column > 0) { // 存在左方的方块
    sequence += (char)(row + '0');
    sequence += (char)(column + '0' - 1);
  }
  if (column < columns - 1) { // 存在右方的方块
    sequence += (char)(row + '0');
    sequence += (char)(column + '0' + 1);
  }
  if (row > 0 and column > 0) { // 存在左上方的方块
    sequence += (char)(row + '0' - 1);
    sequence += (char)(column + '0' - 1);
  }
  if (row > 0 and column < columns - 1) { // 存在右上方的方块
    sequence += (char)(row + '0' - 1);
    sequence += (char)(column + '0' + 1);
  }
  if (row < rows - 1 and column > 0) { // 存在左下方的方块
    sequence += (char)(row + '0' + 1);
    sequence += (char)(column + '0' - 1);
  }
  if (row < rows - 1 and column < columns - 1) { // 存在右下方的方块
    sequence += (char)(row + '0' + 1);
    sequence += (char)(column + '0' + 1);
  }
  return sequence; // 返回方块队列
}

void Regist_unknowned_blocks(int row, int column) { // 登记未访问方块数量和坐标，同时加入边缘线
  std::string sequence = Sequence_of_the_surrounding_blocks(row, column); // 获取周围的方块坐标
  std::string unknown_sequence = ""; // 获取周围未访问的方块坐标
  for (int surrounding_num = 0; surrounding_num < sequence.length(); surrounding_num += 2) {
    int temp_row = sequence[surrounding_num] - '0';
    int temp_column = sequence[surrounding_num + 1] - '0';
    if (readmap[temp_row][temp_column] == -1) {
      edge_line[top_of_line][0] = temp_row;
      edge_line[top_of_line][1] = temp_column;
      top_of_line++; // 边缘线入队
      unknown_sequence += sequence.substr(surrounding_num, 2); // 周围方块坐标录入
    }
  }
  surrounding[row][column] = unknown_sequence; // 周围方块坐标录入
}

void Devide_core(int row, int column) { // 初步处理line上的方块有雷的概率
  std::string temp = surrounding[row][column]; //获取周围未访问方块坐标
  for (int num = 0; num < temp.length(); num +=2) {
    analysemap[temp[num] - '0'][temp[num + 1] - '0'] += readmap[row][column] * 1.0 / num_of_unknown_blocks_surrounding[row][column]; // 周围方块有雷的概率与方块周围的雷的数量成正相关，与周围方块数量成负相关
  }
}

void Normalization() { // 考虑到多个core的相互影响，会导致core周围的有雷的概率和大于core的有雷数，现作归一处理，实现line上方块有雷概率的相互影响(归一是不完备的，但是可以有所启发)
  for (int num = 0; num < top_of_core; num++) {
    float sum = 0; // core周围雷的概率总和
    int row = core_sequence[num][0];
    int column = core_sequence[num][1];
    std::string temp = surrounding[row][column]; //获取周围未访问方块坐标
    for (int temp_num = 0; temp_num < temp.length(); temp_num += 2) {
      sum += analysemap[temp[temp_num] - '0'][temp[temp_num + 1] - '0'];
    }
    for (int temp_num = 0; temp_num < temp.length(); temp_num += 2) {
      analysemap[temp[temp_num] - '0'][temp[temp_num + 1] - '0'] /= (sum / readmap[row][column]);

    }
  }
}

/**
 * @brief The definition of function Execute(int, int)
 *
 * @details This function is designed to take a step when player the client's (or player's) role, and the implementation
 * of it has been finished by TA. (I hope my comments in code would be easy to understand T_T) If you do not understand
 * the contents, please ask TA for help immediately!!!
 *
 * @param row The row coordinate (0-based) of the block to be visited.
 * @param column The column coordinate (0-based) of the block to be visited.
 */
void Execute(int row, int column);

/**
 * @brief The definition of function InitGame()
 *
 * @details This function is designed to initialize the game. It should be called at the beginning of the game, which
 * will read the scale of the game map and the first step taken by the server (see README).
 */
void InitGame() {
  int first_row, first_column;
  std::cin >> first_row >> first_column;
  Execute(first_row, first_column);
}

/**
 * @brief The definition of function ReadMap()
 *
 * @details This function is designed to read the game map from stdin when playing the client's (or player's) role.
 * Since the client (or player) can only get the limited information of the game map, so if there is a 3 * 3 map as
 * above and only the block (2, 0) has been visited, the stdin would be
 *     ???
 *     12?
 *     01?
 */
void ReadMap() {
  memset(analysemap,sizeof(analysemap),0);
  memset(num_of_unknown_blocks_surrounding,sizeof(num_of_unknown_blocks_surrounding),0);
  memset(edge_line,sizeof(edge_line),0);
  memset(core_sequence,sizeof(core_sequence),0);
  memset(surrounding,sizeof(surrounding),0);
  top_of_core = 0;
  top_of_line = 0; //初始化
  for (int row = 0; row < rows; row++) {
    for(int column = 0; column <columns; column++) {
      char temp; // 申请临时变量
      std::cin >> temp; 
      if(temp == '?') {
        readmap[row][column] = -1; // 未访问
        std::string surrounding = Sequence_of_the_surrounding_blocks(row,column); //获取周围方块坐标
        for (int surrounding_num = 0; surrounding_num < surrounding.length(); surrounding_num += 2) { //遍历，其中num是row的下标，num+1是column下标
          num_of_unknown_blocks_surrounding[surrounding[surrounding_num] - '0'][surrounding[surrounding_num + 1] - '0']++; // 未知方块数加一
        }
      } else {
        readmap[row][column] = temp - '0'; // 读入周围雷的个数 
        if(temp != '0') { // 周围有雷
          core_sequence[top_of_core][0] = row;
          core_sequence[top_of_core++][1] = column; //加入core
        } 
      }

    }
  }
}

/**
 * @brief The definition of function Decide()
 *
 * @details This function is designed to decide the next step when playing the client's (or player's) role. Open up your
 * mind and make your decision here!
 */
void Decide() {
  time_out++;
  std::srand(time(NULL));
  for (int temp = 0; temp < top_of_core; temp ++) {
    Regist_unknowned_blocks(core_sequence[temp][0], core_sequence[temp][1]); // surrounding初始
  }
  for (int temp = 0; temp < top_of_core; temp ++) {
    Devide_core(core_sequence[temp][0], core_sequence[temp][1]); // analysemap初始化
  }
  for (int temp = 0; temp < top_of_line * 0.9; temp++) { // 0.9? 试出来的
    Normalization(); // analysemap归一化，多进行几次，近似抹平
    if (time_out > 215 && temp > top_of_line * 0.1) { // 0.1? 试出来的
      break; // 卡时,TLE了多可惜
    }
  }
  int execute_row = edge_line[0][0];
  int execute_column = edge_line[0][1];
  for (int temp = 1; temp < top_of_line; temp++) {
    if (analysemap[execute_row][execute_column] > analysemap[edge_line[temp][0]][edge_line[temp][1]]) {
      execute_column = edge_line[temp][1];
      execute_row = edge_line[temp][0]; 
    } // 寻找line上有雷概率最小的方块
  }
  if(analysemap[execute_row][execute_column] > 0.8) { // 如果是雷的概率太大(防止雷封闭的情况)，选择随机访问未访问的方块
    while (analysemap[execute_row][execute_column] or readmap[execute_row][execute_column] >= 0) {
    execute_column = (int) (std::rand() * 1.0 / RAND_MAX * columns); 
    execute_row = (int) (std::rand() * 1.0 / RAND_MAX * rows); // 随机直到未访问且不在边缘线上
    }
  }
  Execute(execute_row, execute_column);
} 

#endif