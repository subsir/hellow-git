#include <iostream>

#include "include/server.h"

int main() {
  freopen("test.txt", "w", stdout);
  InitMap();
  PrintMap();
  while (true) {
    int pos_x;
    int pos_y;
    std::cin >> pos_x >> pos_y;
    VisitBlock(pos_x, pos_y);
    PrintMap();
    if (game_state != 0) {
      ExitGame();
    }
  }
  return 0;
}
