#pragma once

#include "Board.h"

struct Move
{
    idx_t mStartPos;
    idx_t mEndPos;

    Move() : mStartPos(0), mEndPos(0) {}
    Move(const idx_t& start, const idx_t& end) : mStartPos(start), mEndPos(end) {}

    bool operator==(const Move& rhs) const
    {
        return mStartPos == rhs.mStartPos && mEndPos == rhs.mEndPos;
    }

    bool operator!=(const Move& rhs) const
    {
        return !(rhs == *this);
    }
};