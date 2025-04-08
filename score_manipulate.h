#ifndef SCORE_MANIPULATE_H_INCLUDED
#define SCORE_MANIPULATE_H_INCLUDED
#include <fstream>
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Graphics.h"  // Đảm bảo bạn có Graphics renderer và TTF_Font

// Đọc điểm cao từ file
int readHighscore(const std::string& filename) {
    std::ifstream file(filename);
    int highscore = 0;
    if (file.is_open()) {
        if (!(file >> highscore)) {
            std::cerr << "Lỗi đọc highscore, dùng mặc định 0.\n";
            highscore = 0;
        }
        file.close();
    }
    return highscore;
}

// Ghi điểm cao vào file
void writeHighscore(const std::string& filename, int highscore) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Không thể ghi highscore vào file!\n";
        return;
    }
    file << highscore;
    file.close();
}

// Cập nhật highscore nếu cần
void updateHighscore(int currentScore, int& bestScore, const std::string& filename) {
    if (currentScore > bestScore) {
        bestScore = currentScore;
        writeHighscore(filename, bestScore);
    }
}

// Hiển thị điểm số góc phải màn hình
void renderScore(Graphics& graphics, int currentScore, int bestScore, TTF_Font* font) {
    SDL_Color white = {255, 255, 255};

    std::string currentText = "Score: " + std::to_string(currentScore);
    std::string bestText = "Best: " + std::to_string(bestScore);

    SDL_Texture* currentTexture = graphics.renderText(currentText.c_str(), font, white);
    SDL_Texture* bestTexture = graphics.renderText(bestText.c_str(), font, white);

    int w, h;
    SDL_QueryTexture(currentTexture, nullptr, nullptr, &w, &h);
    SDL_Rect dstCurrent = { SCREEN_WIDTH - w - 20, 20, w, h };

    SDL_QueryTexture(bestTexture, nullptr, nullptr, &w, &h);
    SDL_Rect dstBest = { SCREEN_WIDTH - w - 20, 20 + dstCurrent.h + 10, w, h };

    SDL_RenderCopy(graphics.renderer, currentTexture, nullptr, &dstCurrent);
    SDL_RenderCopy(graphics.renderer, bestTexture, nullptr, &dstBest);

    SDL_DestroyTexture(currentTexture);
    SDL_DestroyTexture(bestTexture);
}


#endif // SCORE_MANIPULATE_H_INCLUDED
