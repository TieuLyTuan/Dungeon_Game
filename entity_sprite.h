#ifndef ENTITY_SPRITE_H_INCLUDED
#define ENTITY_SPRITE_H_INCLUDED

const char *SKELETON_SPRITE_FILE = "D:\Knight_1.1\Skeleton enemy.png";

const int SKELETON_ATTACK[][4] = {
    {0, 0, 64, 64},
    {64, 0, 64, 64},
    {128, 0, 64, 64},
    {192, 0, 64, 64},
    {256, 0, 64, 64},
    {320, 0, 64, 64},
    {384, 0, 64, 64},
    {448, 0, 64, 64},
    {512, 0, 64, 64},
    {576, 0, 64, 64},
    {640, 0, 64, 64},
    {704, 0, 64, 64},
    {768, 0, 64, 64},
};
const int SKELETON_ATTACK_FRAMES = 13;

const int SKELETON_DEATH[][4] = {
    {0, 64, 64, 64},
    {64, 64, 64, 64},
    {128, 64, 64, 64},
    {192, 64, 64, 64},
    {256, 64, 64, 64},
    {320, 64, 64, 64},
    {384, 64, 64, 64},
    {448, 64, 64, 64},
    {512, 64, 64, 64},
    {576, 64, 64, 64},
    {640, 64, 64, 64},
    {704, 64, 64, 64},
    {768, 64, 64, 64},
};
const int SKELETON_DEATH_FRAMES = 13;

const int SKELETON_WALK[][4] = {
    {0, 0, 64, 64},
    {64, 0, 64, 64},
    {128, 0, 64, 64},
    {192, 0, 64, 64},
    {256, 0, 64, 64},
    {320, 0, 64, 64},
    {384, 0, 64, 64},
    {448, 0, 64, 64},
    {512, 0, 64, 64},
    {576, 0, 64, 64},
    {640, 0, 64, 64},
    {704, 0, 64, 64},
};
const int SKELETON_WALK_FRAMES = 12;


const int SKELETON_IDLE[][4] = {
    {0, 192, 64, 64},
    {64, 192, 64, 64},
    {128, 192, 64, 64},
    {192, 192, 64, 64},
};
const int SKELETON_IDLE_FRAMES = 4;

const int SKELETON_HURT[][4] = {
    {0, 256, 64, 64},
    {64, 256 , 64 ,64},
    {128, 256 , 64, 64},
};
const int SKELETON_HURT_FRAMES = 3;
#endif // ENTITY_SPRITE_H_INCLUDED
