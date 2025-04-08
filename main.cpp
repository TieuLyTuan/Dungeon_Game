#include <iostream>
#include "def.h"
#include "graphics.h"
#include "knightSprite.h"
#include "entity_sprite.h"
#include "game_logic.h"
#include "game_render.h"
#include "menu.h"
#include "score_manipulate.h"
using namespace std;

int main(int argc, char *argv[]) {
    int score = 0;
    int highscore = 0;

    ifstream inFile("highscore.txt");
    if (inFile.is_open()) {
        inFile >> highscore;
        inFile.close();
    }


    Graphics graphics;
    graphics.init();

    SDL_Texture *background_1 = graphics.loadTexture("Starfield_03-1024x1024.png");
    SDL_Texture *background_2 = graphics.loadTexture("sky_layer_1.png");
    SDL_Texture *TILE_MAP = graphics.loadTexture("platformPack_tilesheet_walls (2).png");

    SDL_Texture *texture;

    Sprite KnightAttack1, KnightAttack2, KnightAttack3;
    Sprite KnightDeath, KnightDefend, KnightHurt, KnightIdle;
    Sprite KnightJump, KnightRun, KnightWalk;

    initSpriteKnight(graphics, texture, KnightAttack1, KnightAttack2, KnightAttack3,
                     KnightDeath, KnightDefend, KnightHurt, KnightIdle,
                     KnightJump, KnightRun, KnightWalk);

    Mix_Chunk* knightAttack = graphics.loadSound("07_human_atk_sword_1.wav");
    Mix_Chunk* knightDamage = graphics.loadSound("11_human_damage_1.wav");
    Mix_Chunk* knightJump = graphics.loadSound("12_human_jump_1.wav");
    Mix_Chunk* knightLand = graphics.loadSound("13_human_jump_land_2.wav");



    Sprite SkeletonAttack[10], SkeletonDeath[10], SkeletonWalk[10];
    Sprite SkeletonIdle[10], SkeletonHurt[10];
    Mix_Chunk* npcAttack = graphics.loadSound("17_orc_atk_sword_1.wav");
    Mix_Chunk* npcDamage = graphics.loadSound("21_orc_damage_1.wav");

    TTF_Font* font = graphics.loadFont("DungeonFont.ttf", 32);

    texture = graphics.loadTexture("Skeleton enemy.png");
    Entity skeleton[10];

    knightMove = true;
    bool running = true;
    bool inMap = false;
    bool knightDisplay = true;

    SDL_Event event;
    Knight knight;

    auto resetKnight = [&]() {
        knight.x = start_x;
        knight.y = start_y;
        knight.w = 32;
        knight.h = 70;
        knight.dst = {start_x, start_y, 32, 70};
        knight.life_point = 200;
        knight.isAlive = true;
        score = 0;
        inMap = false;
        knightDisplay = true;
    };

    resetKnight(); // init knight
    bool waiting = true;

    graphics.resizeRenderTexture(background_1, 0, 0, 1 );
    SDL_Color white = {255, 255, 255, 255};
    graphics.renderTextAt("Press any key to start", 350, 300, white, font);
    graphics.presentScene();

    while(waiting) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                waiting = false;
                return 0;
            } else if (event.type == SDL_KEYDOWN) {
                resetKnight();
                waiting = false;
            }
        }
    }
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        if (!knightDisplay) {

        if (score > highscore) {
        highscore = score;
        ofstream outFile("highscore.txt");
        if (outFile.is_open()) {
            outFile << highscore;
            outFile.close();
            }
        }

            graphics.prepareScene();
            graphics.resizeRenderTexture(background_1, 0, 0, 1 );
            SDL_Color white = {255, 255, 255, 255};
            graphics.renderTextAt("Press any key to restart", 350, 300, white, font);
            graphics.presentScene();
            waiting = true;
            while (waiting) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        running = false;
                        waiting = false;
                    } else if (event.type == SDL_KEYDOWN) {
                        resetKnight();
                        waiting = false;
                    }
                }
                SDL_Delay(16);
            }
            continue;
        }

        if (!inMap) {
            updateMap(inMap, skeleton, SkeletonAttack, SkeletonDeath, SkeletonWalk, SkeletonIdle, SkeletonHurt, texture, knight);
        }

        if(knight.x < 0 ){
            knight.x = 0;
        }

        if (knight.x + 32 >= 960) {
            inMap = false;
        }

        if(knight.y >= 640) {
            inMap = false;
            knight.isAlive = false;
            knightDisplay = false;
            knight.life_point = 0;
        }

        switchCameraMode(knight, knightMove);
        resetState(action, skeleton);
        applyGravity(knight, skeleton);

        const Uint8 *keystates = SDL_GetKeyboardState(NULL);
        handleInputKnight(knight, keystates);

        for (int i = 0; i < number_entity[currentMap]; i++) {
            if(skeleton[i].isAlive) skeleton[i].update_state_NPC(knight, score);
            skeleton[i].update_position_NPC(_dx, knightMove);
        }
        // Kiểm tra NPC bị tiêu diệt
        for (int i = 0; i < number_entity[currentMap]; i++) {
            if (!skeleton[i].isAlive && skeleton[i].display) {
                score += 100;  // hoặc giá trị bạn muốn
                skeleton[i].display = false; // đánh dấu đã được xử lý
                // Cập nhật highscore nếu cần
                if (score > highscore) {
                    highscore = score;
                    writeHighscore("highscore.txt", highscore);
                }
            }
        }


        graphics.prepareScene();
        graphics.resizeRenderTexture(background_1, 0, 0, 1);
        graphics.resizeRenderTexture(background_2, 0, 0, 3);

        renderNPC(graphics, skeleton, SkeletonAttack, SkeletonDeath, SkeletonWalk, SkeletonIdle, SkeletonHurt);
        insertSoundNPC(graphics, skeleton, npcAttack, npcDamage);

        if (knightDisplay) {
            renderHealthBar(graphics, knight.x + 32, knight.y + 16, 32, 8, knight.life_point, 200);
            renderKnight(graphics, action, knight, KnightDeath, KnightHurt, KnightAttack1, KnightAttack2, KnightAttack3,
                         KnightDefend, KnightRun, KnightWalk, KnightIdle, knightDisplay);
            insertSoundKnight(graphics, action, knight, knightAttack, knightDamage, knightJump, knightLand);
        }

        graphics.renderTileMap(TILE_MAP, _dx, MAPS[currentMap]);
        renderScore(graphics, font, score, highscore);
        graphics.presentScene();
        SDL_Delay(16);
    }

    cout << "GAME OVER!" << endl;
    graphics.quit();
    return 0;
}
