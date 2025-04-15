//
// Created by JoonHo Son on 2025. 4. 15..
//

#include "main.h"

int main() {
    Game *game = new Game();

    if (game->Init()) {
        game->Run();
    }

    delete game;

    return 0;
}
