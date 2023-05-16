//#include "menu.h"
#include "game.h"
int main()
{
    Game g;
    do {
        g.replay = 0;
    bool flag = 0;
    g.start_game(flag);
    } while (g.replay);
    //Menu m;
   // m.display_menu(); 
    return 0;
}



