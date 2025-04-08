#ifndef GAME_RENDER_H_INCLUDED
#define GAME_RENDER_H_INCLUDED

#include "graphics.h"
#include "knight.h"
#include "entity.h"

void renderHealthBar(Graphics &graphics, int x, int y, int w, int h, int current, int max) {
    // Tính tỉ lệ máu
    float ratio = (float)current / max;
    if (ratio < 0) ratio = 0;

    // Viền đen
    SDL_Rect border = {x - 1, y - 1, w + 2, h + 2};
    SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255); // Màu đen
    SDL_RenderFillRect(graphics.renderer, &border);

    // Nền đỏ (máu mất)
    SDL_Rect background = {x, y, w, h};
    SDL_SetRenderDrawColor(graphics.renderer, 255, 0, 0, 255); // Màu đỏ
    SDL_RenderFillRect(graphics.renderer, &background);

    SDL_Rect health = {x, y, (int)(w * ratio), h};
    SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 255); // Màu xanh lá
    SDL_RenderFillRect(graphics.renderer, &health);
}


void initSpriteKnight(Graphics graphics, SDL_Texture *texture, Sprite &KnightAttack1, Sprite &KnightAttack2,
                      Sprite &KnightAttack3, Sprite &KnightDeath, Sprite &KnightDefend, Sprite &KnightHurt,
                      Sprite &KnightIdle, Sprite &KnightJump, Sprite &KnightWalk, Sprite &KnightRun) {
    texture = graphics.loadTexture("ATTACK 1.png");
    KnightAttack1.init(texture, KNIGHT_ATTACK_1_FRAMES, KNIGHT_ATTACK_1_SPRITE_CLIPS);

    texture = graphics.loadTexture("ATTACK 2.png");
    KnightAttack2.init(texture, KNIGHT_ATTACK_2_FRAMES, KNIGHT_ATTACK_2_SPRITE_CLIPS);

    texture = graphics.loadTexture("ATTACK 3.png");
    KnightAttack3.init(texture, KNIGHT_ATTACK_3_FRAMES, KNIGHT_ATTACK_3_SRPITE_CLIPS);

    texture = graphics.loadTexture("DEFEND.png");
    KnightDefend.init(texture, KNIGHT_DEFEND_FRAMES, KNIGHT_DEFEND_SPRITE_CLIPS);

    texture = graphics.loadTexture("HURT.png");
    KnightHurt.init(texture, KNIGHT_HURT_FRAMES, KNIGHT_HURT_SPRITE_CLIPS);

    texture = graphics.loadTexture("IDLE.png");
    KnightIdle.init(texture, KNIGHT_IDLE_FRAMES, KNIGHT_IDLE_SPRITE_CLIPS);

    texture = graphics.loadTexture("JUMP.png");
    KnightJump.init(texture, KNIGHT_JUMP_FRAMES, KNIGHT_JUMP_SPRITE_CLIPS);

    texture = graphics.loadTexture("DEATH.png");
    KnightDeath.init(texture, KNIGHT_DEATH_FRAMES, KNIGHT_DEATH_SPRITE_CLIPS);

    texture = graphics.loadTexture("WALK.png");
    KnightWalk.init(texture, KNIGHT_WALK_FRAMES, KNIGHT_WALK_SPRITE_CLIPS);

    texture = graphics.loadTexture("RUN.png");
    KnightRun.init(texture, KNIGHT_RUN_FRAMES, KNIGHT_RUN_SPRITE_CLIPS);
}


void renderNPC(Graphics &graphics, Entity *skeleton, Sprite *SkeletonAttack, Sprite *SkeletonDeath,
               Sprite *SkeletonWalk, Sprite *SkeletonIdle, Sprite *SkeletonHurt) {
    for (int i = 0; i < number_entity[currentMap]; i++) {
        if (!skeleton[i].display) continue;
        if (!skeleton[i].isAlive) {
            SkeletonDeath[i].tick();
            if(SkeletonDeath[i].currentFrame == SKELETON_DEATH_FRAMES - 1) skeleton[i].display = false;
            graphics.renderSprite(skeleton[i].flip, skeleton[i].x , skeleton[i].y, skeleton[i].w, SkeletonDeath[i]);
        }
        if (skeleton[i].isHurt) {
            SkeletonHurt[i].tick();
            graphics.renderSprite(skeleton[i].flip, skeleton[i].x, skeleton[i].y, skeleton[i].w, SkeletonHurt[i]);
        }
        if (skeleton[i].isAttacking) {
            SkeletonAttack[i].tick();
            graphics.renderSprite(skeleton[i].flip, skeleton[i].x, skeleton[i].y, skeleton[i].w, SkeletonAttack[i]);
        }
        if (skeleton[i].isChasingPlayer) {
            SkeletonWalk[i].tick();
            graphics.renderSprite(skeleton[i].flip, skeleton[i].x, skeleton[i].y, skeleton[i].w, SkeletonWalk[i]);
        }
        if (skeleton[i].isPatrol) {
            SkeletonIdle[i].tick();
            graphics.renderSprite(skeleton[i].flip, skeleton[i].x, skeleton[i].y, skeleton[i].w, SkeletonIdle[i]);
        }
    }
}

void renderKnight(Graphics graphics, bool *action, Knight knight, Sprite &KnightDeath, Sprite &KnightHurt, Sprite &KnightAttack1,
                  Sprite &KnightAttack2, Sprite &KnightAttack3, Sprite &KnightDefend, Sprite &KnightRun,
                  Sprite &KnightWalk, Sprite &KnightIdle, bool &knightDisplay) {
    if(knightDisplay == false) return;
    if(action[1]) {
       for(int i = 2; i < 12 ; i ++){
            action[i] = false;
       }
       KnightDeath.tick();
       if(KnightDeath.currentFrame == KNIGHT_DEATH_FRAMES - 1) knightDisplay = false;
       graphics.renderSprite(knight.flip, knight.x, knight.y, knight.w, KnightDeath);
    }
    if (action[2]) {
        for (int i = 3; i < 12; i++) {
            action[i] = false;
        }
        KnightHurt.tick();
        graphics.renderSprite(knight.flip, knight.x, knight.y, knight.w, KnightHurt);
    }
    if (action[3]) {
        for (int i = 4 ; i < 12; i ++) action[i] = false;
        KnightAttack1.tick();
        graphics.renderSprite(knight.flip, knight.x, knight.y, knight.w, KnightAttack1);
    }

    if (action[4]) {
        for (int i  = 5; i < 12 ; i ++) action[i] = false;
        KnightAttack2.tick();
        graphics.renderSprite(knight.flip, knight.x, knight.y, knight.w, KnightAttack2);
    }

    if (action[5]) {
        for (int i = 6 ; i < 12 ; i ++) action[i] = false;
        KnightAttack3.tick();
        graphics.renderSprite(knight.flip, knight.x, knight.y, knight.w, KnightAttack3);
    }

    if (action[6]) {
        for (int i  = 7 ; i < 12; i ++) action[i] = false;
        KnightDefend.tick();
        graphics.renderSprite(knight.flip, knight.x, knight.y, knight.w, KnightDefend);
    }
    if (action[8] || action[10]) {
        KnightRun.tick();
        graphics.renderSprite(knight.flip, knight.x, knight.y, knight.w, KnightRun);
    }
    if (action[11] || action[9]) {
        KnightWalk.tick();
        graphics.renderSprite(knight.flip, knight.x, knight.y, knight.w, KnightWalk);
    }
    if (!(action[1] || action[2] || action[3] || action[4] || action[5] || action[6] || action[7] || action[8] || action[9] || action
          [10] || action[11])) {
        KnightIdle.tick();
        graphics.renderSprite(knight.flip, knight.x, knight.y, knight.w, KnightIdle);
    }
}

void insertSoundNPC(Graphics &graphics, Entity* skeleton, Mix_Chunk* npcAttack, Mix_Chunk* npcHurt){
    for (int i = 0; i < number_entity[currentMap]; i++) {
        if (!skeleton[i].display) continue;
        if (skeleton[i].isHurt) {
            graphics.play(npcHurt);
        }
        if (skeleton[i].isAttacking) {
            graphics.play(npcAttack);
        }
    }
}

void insertSoundKnight(Graphics &graphics, bool* action, Knight knight, Mix_Chunk* knightAttack, Mix_Chunk* knightDamage, Mix_Chunk* knightJump, Mix_Chunk *knightLand){
    if (action[2]) {
        for (int i = 3; i < 12; i++) {
            action[i] = false;
        }
        graphics.play(knightDamage);
    }
    if (action[3]) {
        for (int i = 4 ; i < 12; i ++) action[i] = false;
        graphics.play(knightAttack);
    }
    if (action[4]) {
        for (int i  = 5; i < 12 ; i ++) action[i] = false;
        graphics.play(knightAttack);
    }
    if (action[5]) {
        for (int i = 6 ; i < 12 ; i ++) action[i] = false;
        graphics.play(knightAttack);
    }
}

void renderScore(Graphics &graphics, TTF_Font* font, int score, int highscore) {
    SDL_Color white = {255, 255, 255};

    std::string scoreText = "Score: " + std::to_string(score);
    std::string bestText = "Best: " + std::to_string(highscore);

    SDL_Texture* scoreTex = graphics.renderText(scoreText.c_str(), font, white);
    SDL_Texture* bestTex = graphics.renderText(bestText.c_str(), font, white);

    int textW, textH;

    if (scoreTex) {
        SDL_QueryTexture(scoreTex, NULL, NULL, &textW, &textH);
        graphics.renderTexture(scoreTex, SCREEN_WIDTH - textW - 10, 10);
        SDL_DestroyTexture(scoreTex);
    }

    if (bestTex) {
        SDL_QueryTexture(bestTex, NULL, NULL, &textW, &textH);
        graphics.renderTexture(bestTex, SCREEN_WIDTH - textW - 10, 40);
        SDL_DestroyTexture(bestTex);
    }
}


#endif // GAME_RENDER_H_INCLUDED
