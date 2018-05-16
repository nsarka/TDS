#pragma once

#include "../include/entity.h"

class Player: public Entity {
    public:
        Player();
		~Player();

        int Draw();

    private:
        int player_class;
};