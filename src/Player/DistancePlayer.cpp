#include "DistancePlayer.h"
#include "Board.h"

#include <stdexcept>
#include <vector>
#include <cmath>

int DistancePlayer::EvaluateHeuristic(const Board& board)
{
    int result = 0;
    std::vector< std::pair<idx_t, idx_t> > green;
    std::vector< std::pair<idx_t, idx_t> > red;

    for (idx_t r = 0; r < BOARD_ROWS; ++r) {
        for (idx_t c = 0; c < BOARD_COLS; ++c) {
            switch (board.GetCell(r * BOARD_COLS + c)) {
            case 1:
                green.push_back(std::make_pair(c, r));
                break;
            case 2:
                red.push_back(std::make_pair(c, r));
                break;
            }
        }
    }

    double avgGreenDistance = 0.0;
    double avgRedDistance = 0.0;

    for (idx_t i = 0; i < green.size(); ++i) {
        double tmp = 0;
        for (idx_t j = 0; j < red.size(); ++j) {
            tmp += sqrt(pow(green[i].first - red[j].first, 2) + pow(green[i].second - red[j].second, 2));
        }
        avgRedDistance += tmp / (double)red.size();
    }
    avgRedDistance /= (double)green.size();

    for (idx_t i = 0; i < green.size(); ++i) {
        double tmp = 0;
        for (idx_t j = 0; j < i; ++j) {
            tmp += sqrt(pow(green[i].first - green[j].first, 2) + pow(green[i].second - green[j].second, 2));
        }
        for (idx_t j = i+1; j < green.size(); ++j) {
            tmp += sqrt(pow(green[i].first - green[j].first, 2) + pow(green[i].second - green[j].second, 2));
        }
        avgGreenDistance += tmp / (double)green.size();
    }
    avgGreenDistance /= (double)green.size();

    return 10 * avgGreenDistance - 5 * avgRedDistance;
}