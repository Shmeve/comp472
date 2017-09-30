#pragma once

struct Move
{
    int mStartPos;
    int mEndPos;

    Move() : mStartPos(0), mEndPos(0) {}
    Move(int start, int end) : mStartPos(start), mEndPos(end) {}
};