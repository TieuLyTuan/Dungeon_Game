#ifndef KNIGHT_H_INCLUDED
#define KNIGHT_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include "collision_map.h"
#include "collision_check.h"
#include "def.h"


void movePlayer_1 (bool &oG, int &x, int &y, int &dx, int &dy, SDL_Rect &player) {
    SDL_Rect nextX = {player.x + dx, player.y , player.w, player.h};
    SDL_Rect nextY = {player.x, player.y + dy, player.w, player.h};

    for (auto& wall : walls) {
        if (AABB_Collision(nextX, wall)) {
            dx = 0;
            break;
        }
    }
    x += dx;

    for (auto& wall : walls) {
        if (AABB_Collision(nextY, wall)) {
            y = wall.y - player.h;
            dy = 0;
            oG = true;
            break;
        } else {
            oG = false;
        }
    }
    y += dy;
}


void movePlayer_2 (bool &oG, int &x, int &y, int dx, int dy, SDL_Rect &player) {
    SDL_Rect nextX = {player.x + dx, player.y , player.w, player.h};
    SDL_Rect nextY = {player.x, player.y + dy, player.w, player.h};

    for (auto& wall : walls) {
        if (AABB_Collision(nextX, wall)) {
            dx = 0;
            break;
        }
    }

    x += dx;
    // Kiểm tra va chạm theo trục Y
    for (auto& wall : walls) {
        if (AABB_Collision(nextY, wall)) {
            y = wall.y - player.h;
            dy = 0;
            oG = true;
            break;
        } else {
            oG = false;
        }
    }
    y += dy;
}

bool action[20];

bool knightMove = false;
int _dx = 0;

struct Knight {
    int x, y, w, h;

    SDL_Rect dst = {x, y, w, h} ;
    int dx = 0, dy = 0;
    int life_point = 200;
    int gravity = 1;
    int maxFallSpeed = 10;
    int jumpStrength = -13;
    bool onGround = true;
    bool flip = false;
    bool isAlive = true;

    void death() {
        action[1] = true;
    }

    void hurt(bool left){
        if(!left) dx = -2;
        else dx = 2;
        if(knightMove)
        {
            movePlayer_1(onGround, x, y, dx, dy, dst);
            dst = {x, y, w, h};
                    if(action[6]) life_point -= 1;
        else life_point -= 4;
        if(life_point <= 0){
            death();
            isAlive = false;
        }
        if(action[6]) action[2] = false;
        else action[2] = true;
        }
        else {
            if(!checkXCollision(dx, dst)) {
            _dx += dx;
            walls = updateWalls(_dx, MAPS[currentMap] );
            movePlayer_2(onGround, x, y, 0, dy, dst);
            dst.y = y;
            }
        }
        if(action[6]) life_point -= 1;
        else life_point -= 4;
        if(life_point <= 0){
            death();
            isAlive = false;
        }
        if(action[6]) action[2] = false;
        else action[2] = true;
    }
    void attack1() {
        action[3] = true;
    }

    void attack2() {
        action[4] = true;
    }

    void attack3() {
        action[5] = true;
    }

    void defend() {
        action[6] = true;
    }

    void jump() {
        if (onGround) {
            dy = jumpStrength;
            onGround = false;
            action[7] = true;
        }
    }

    void runRight() {
        dx = 7;
        if(knightMove) movePlayer_1(onGround, x, y, dx, dy, dst);
        else {
            if(!checkXCollision(dx, dst)) {
            _dx += dx;
            walls = updateWalls(_dx, MAPS[currentMap] );
            movePlayer_2(onGround, x, y, 0, dy, dst);
            dst.y = y;
            }
        }
        dst = {x, y, w, h};
        action[8] = true;
    }

    void turnRight(){
        dx = 5;
        if(knightMove)
        {
            movePlayer_1(onGround, x, y, dx, dy, dst);
            dst = {x, y, w, h};
        }
        else {
            if(!checkXCollision(dx, dst)) {
            _dx += dx;
            walls = updateWalls(_dx, MAPS[currentMap] );
            movePlayer_2(onGround, x, y, 0, dy, dst);
            dst.y = y;
            }
        }
        action[9] = true;
    }

    void runLeft() {
        dx = -7;
        if(knightMove) {
            movePlayer_1(onGround, x, y, dx, dy, dst);
            dst = {x, y, w, h};
        }
        else {
            if(!checkXCollision(dx, dst)) {
            _dx += dx;
            walls = updateWalls(_dx, MAPS[currentMap] ) ;
            movePlayer_2(onGround, x, y, 0, dy, dst);
            dst.y = y;
            }
        }
        action[10] = true;
    }

    void turnLeft() {
        dx = -5;
        if(knightMove) {
            movePlayer_1(onGround, x, y, dx, dy, dst);
            dst = {x ,y , w, h};
        }
        else {
            if(!checkXCollision(dx, dst)) {
            _dx += dx;
            walls = updateWalls(_dx, MAPS[currentMap] );
            movePlayer_2(onGround, x, y, 0, dy, dst);
            dst.y = y;
            }
        }
        action[11] = true;
    }

    void applyGravity() {
    dy += gravity;
    if (dy > maxFallSpeed) {
        dy = maxFallSpeed;
    }

    if (knightMove)
        movePlayer_1(onGround, x, y, dx, dy, dst);
    else {
        walls = updateWalls(_dx, MAPS[currentMap]);
        movePlayer_2(onGround, x, y, 0, dy, dst);
    }

    if (onGround) dy = 0;

    dst = {x, y, w, h};
}

};


#endif // KNIGHT_H_INCLUDED
