#ifndef COLLISION_CHECK_H_INCLUDED
#define COLLISION_CHECK_H_INCLUDED

bool AABB_Collision(SDL_Rect a, SDL_Rect b) {
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

bool checkGroundCollision(SDL_Rect& dst) {
    SDL_Rect nextPos = {dst.x, dst.y + 1, dst.w, dst.h};
    for (auto& wall : walls) {
        if (AABB_Collision(nextPos, wall)) {
            return true;
        }
    }
    return false;
}

bool checkXCollision(int dx, SDL_Rect &player){
    SDL_Rect nextX = {player.x + dx, player.y , player.w, player.h};
    for (auto& wall : walls) {
        if (AABB_Collision(nextX, wall)) {
            return true;
        }
    }
    return false;
}

bool checkAttack(SDL_Rect a, SDL_Rect b, bool flip){
    if(!flip) a.x += 32;
    else a.x -= 32;
    AABB_Collision(a, b);
}

#endif // COLLISION_CHECK_H_INCLUDED
