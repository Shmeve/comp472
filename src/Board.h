class Board
{
private:
    int* mCells;
    int mSize;
public:
    Board();
    Board(int size);
    ~Board();
    inline int* GetCells() { return mCells; }
    inline bool IsBlack(int idx) { return idx % 2 == 0; }
    int GetPlayer(int idx);
    void Clear(int idx);
    void MoveTo(int from, int to);
};