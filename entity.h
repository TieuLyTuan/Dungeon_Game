#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include "knight.h"
#include "collision_check.h"
#include "collision_map.h"

const int NPC_POS_MAP_1 [] = {
        529, 299,
        809, 203
};
int number_npc_1 = 2;

const int NPC_POS_MAP_2[]= {
        425, 203,
        732, 107,
        1032, 171
};
int number_npc_2 = 3;

const int NPC_POS_MAP_3[]= {
        594, 363,
        858, 267
};
int number_npc_3 = 2;

const int NPC_POS_MAP_4[] = {
        565, 442,
        885, 346,
};
int number_npc_4 = 2;

vector<const int* > NPC_POS = {NPC_POS_MAP_1, NPC_POS_MAP_2, NPC_POS_MAP_3, NPC_POS_MAP_4};
vector<int> number_entity = {number_npc_1, number_npc_2, number_npc_3, number_npc_4};

void moveNPC(bool &oG, int &x, int &y, int dx, int dy, SDL_Rect &dst) {
        SDL_Rect nextX = {dst.x + dx, dst.y , dst.w, dst.h};
        SDL_Rect nextY = {dst.x, dst.y + dy, dst.w, dst.h};

        // Di chuyển trục X
        for (auto& wall : walls) {
            if (AABB_Collision(nextX, wall)) {
                dx = 0;
                break;
            }
        }
        x += dx;

        oG = false;
        bool collided = false;

        for (auto& wall : walls) {
            if (AABB_Collision(nextY, wall)) {
                if (dy > 0 && (y + dst.h <= wall.y + 1)) {
                    y = wall.y - dst.h;
                    dy = 0;
                    oG = true;
                    collided = true;
                }
                break;
            }
        }

        if (!collided) {
            y += dy;
        }
}

struct Entity {
    int x, start_x, y;
    int w = 24, h = 48;

    int life_point = 80;

    SDL_Rect dst = {x, y, w, h};
    int dx = 0, dy = 0;
    int gravity = 1;
    int maxFallSpeed = 10;
    int jumpStrength = -13;

    bool onGround = false;
    bool isAlive = true;
    bool isChasingPlayer = false;
    bool isAttacking = false;
    bool isHurt = false;
    bool isPatrol = true;
    bool display = true;

    bool flip = 0;

    void applyGravity() {
        if (!onGround) {
            dy += gravity;
            if (dy > maxFallSpeed) {
                dy = maxFallSpeed;
            }
            moveNPC(onGround, x, y, dx, dy, dst);
        }
        else {
            dy = 0;
        }
        dst = {x, y, w, h};
    }
    void hurt(Knight knight) {
        if(knight.x - x > 0 ) dx = -3;
        else dx = 3;
        isHurt = true;
        life_point -= 5;
        if(life_point <= 0){
          isAlive = false;
        }
        dst = {x, y, w, h};
    }
    void attack() {
        isAttacking = true;
    }
    void turnLeft(){
        dx = -1;
        dst = {x, y, w, h};
    }
    void turnRight(){
        dx = 1;
        dst = {x, y, w, h};
    }
    void chasingPlayer(Knight knight){
        if(knight.x - x > 0) {
            turnRight();
            flip = 0;
        }
        else {
            turnLeft();
            flip = 1;
        }
        isChasingPlayer = true;
    }
    void patrol() {
        isPatrol = true;
    }
    void update_state_NPC(Knight &knight, int &score){
        if( isAlive == false) {
            score ++;
            return ;
        }
        else {
            if( ( action[3] || action[4] || action[5] ) && checkAttack(knight.dst, dst, knight.flip) && knight.flip + flip == 1) {
            hurt(knight);
            return;
        }
        else if( checkAttack(dst, knight.dst, flip) && knight.isAlive == true ){
            if( x < knight.x ) {
                attack();
                knight.hurt(1);
            }
            else {
                attack();
                knight.hurt(0);
            }
            return;
        }
        else if(abs(knight.x - x) < 100 && knight.isAlive == true){
            chasingPlayer(knight);
            return;
        }
        else {
            patrol();
            return;
        }
        }
    }
    void update_position_NPC(int camRoll, bool knightMove) {
            moveNPC(onGround, start_x, y, dx, dy, dst);
            x = start_x - camRoll;
            dx = 0;
            dst = {x, y, w, h};
    }
};

void debugSkeleton(Entity skeleton[], int currentMap){
    for(int i = 0 ; i < number_entity[currentMap] ; i ++){
        cout << "Skeleton " << i << " " << skeleton[i].x << " " << skeleton[i].y << " " << skeleton[i].onGround << endl;
    }
}

//toa do npc moi map



#endif // ENTITY_H_INCLUDED
