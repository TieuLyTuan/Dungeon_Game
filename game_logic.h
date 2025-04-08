#ifndef GAME_LOGIC_H_INCLUDED
#define GAME_LOGIC_H_INCLUDED
#include <SDL.h>
#include "knight.h"
#include "entity.h"

void applyGravity(Knight &knight, Entity *skeleton) {
    for (int i = 0; i < number_entity[currentMap]; i++) {
        skeleton[i].applyGravity();
        skeleton[i].onGround = checkGroundCollision(skeleton[i].dst);
    }

    knight.applyGravity();
    knight.onGround = checkGroundCollision(knight.dst);
}


void updateMap(bool &inMap, Entity *skeleton, Sprite *SkeletonAttack, Sprite *SkeletonDeath, Sprite *SkeletonWalk,
               Sprite *SkeletonIdle, Sprite *SkeletonHurt, SDL_Texture *texture, Knight &knight) {
    _dx = 0;
    currentMap = getCurrentMap();
    walls = updateWalls(0, MAPS[currentMap]);
    inMap = true;
    for (int i = 0; i < number_entity[currentMap]; i++) {
        skeleton[i].display = true;
        skeleton[i].isAlive = true;
        skeleton[i].life_point = 80;
        skeleton[i].x = NPC_POS[currentMap][i * 2];
        skeleton[i].start_x = NPC_POS[currentMap][i * 2];
        skeleton[i].y = NPC_POS[currentMap][i * 2 + 1];
        skeleton[i].dst = {skeleton[i].x, skeleton[i].y, skeleton[i].w, skeleton[i].h};
        skeleton[i].dx = 0;
        skeleton[i].dy = 0;
    }
    for (int i = 0; i < number_entity[currentMap]; i++) {
        SkeletonAttack[i].init(texture, SKELETON_ATTACK_FRAMES, SKELETON_ATTACK);
        SkeletonDeath[i].init(texture, SKELETON_DEATH_FRAMES, SKELETON_DEATH);
        SkeletonDeath[i].currentFrame = 0;
        SkeletonWalk[i].init(texture, SKELETON_WALK_FRAMES, SKELETON_WALK);
        SkeletonWalk[i].currentFrame = 0;
        SkeletonIdle[i].init(texture, SKELETON_IDLE_FRAMES, SKELETON_IDLE);
        SkeletonIdle[i].currentFrame = 0;
        SkeletonHurt[i].init(texture, SKELETON_HURT_FRAMES, SKELETON_HURT);
        SkeletonHurt[i].currentFrame = 0;
    }

    debugSkeleton(skeleton, currentMap);
    walls = updateWalls(0, MAPS[currentMap]);
    debugWalls();

    knight.x = start_x;
    knight.y = start_y;
    knight.dx = 0;
    knight.dy = 0;
    knight.dst = {start_x, start_y, 32, 70};

    applyGravity(knight, skeleton);
    knight.onGround = checkGroundCollision(knight.dst);
}

void resetState(bool *action, Entity *skeleton) {
    for (int i = 0; i < 13; i++) action[i] = false;
    for (int i = 0; i < number_entity[currentMap]; i++) {
        skeleton[i].isHurt = false;
        skeleton[i].isAttacking = false;
        skeleton[i].isChasingPlayer = false;
        skeleton[i].isPatrol = false;
    }
}

void switchCameraMode(Knight knight, bool KnightMove) {
    if (_dx + knight.x - start_x <= 0) {
        _dx = 0;
        knightMove = true;
    } else if (_dx + knight.x - start_x >= 960) {
        _dx = 960;
        knightMove = true;
    } else knightMove = false;
}

void handleInputKnight(Knight &knight, const Uint8 *keystates) {
    if(!knight.isAlive){
        knight.death();
    } else {
    if (keystates[SDL_SCANCODE_J]) {
        knight.attack1();
    } else if (keystates[SDL_SCANCODE_K]) {
        knight.attack2();
    } else if (keystates[SDL_SCANCODE_L]) {
        knight.attack3();
    } else if (keystates[SDL_SCANCODE_S]) {
        knight.defend();
    }
    if (keystates[SDL_SCANCODE_SPACE]) {
        knight.jump();
    }
    if (keystates[SDL_SCANCODE_D] && keystates[SDL_SCANCODE_LSHIFT]) {
        knight.runRight();
        knight.dx = 0;
        knight.flip = 0;
        cout << knight.x + _dx << " " << knight.y << endl;
    } else if (keystates[SDL_SCANCODE_D]) {
        knight.turnRight();
        knight.dx = 0;
        knight.flip = 0;
        cout << knight.x + _dx << ' ' << knight.y << endl;
    } else if (keystates[SDL_SCANCODE_A] && keystates[SDL_SCANCODE_LSHIFT]) {
        knight.runLeft();
        knight.dx = 0;
        knight.flip = 1;
        cout << knight.x  + _dx << ' ' << knight.y << endl;
    } else if (keystates[SDL_SCANCODE_A]) {
        knight.turnLeft();
        knight.dx = 0;
        knight.flip = 1;
        cout << knight.x + _dx<< ' ' << knight.y << endl;
    }
    }
}


#endif // GAME_LOGIC_H_INCLUDED
