# Chess_Engine
1. Create the Board
2. Generate all the moves
3. Evaluate the moves

## Creating the Board
To ensure that everything is organized, there is a struct that stores all the important information in a chess match found here:
```c++
typedef struct {
    int pieces[BOARD_SQUARE_NUM];  //120 board representation
    unsigned long long pawns[3];   //WHITE,BLACK,BOTH where each bit is set to 1 for pawn and 0 for no pawn

    int king_square[2];  //keeps track of where the king is
    int side;         //keeps track of who's move it is
    int en_passant;   //if en passant is available
    int fifty_move;   //draw if fifty  moves
    int ply;          //number of half moves into search
    int ply_history;       //how many half moves made
    int castle_perm;  //if castle available

    unsigned long long position_key;  //unique key for each board state

    int piece_num[13]; //know number of pieces on the board

    int big_piece[2];     //not pawns
    int major_piece[2];   //Rook and queen
    int minor_piece[2];   //Bishop and knights
    int material[2];

    HISTORY history[MAX_GAME_MOVES];

    int piece_list[13][10];

    PV_TABLE pv_table[1];
}BOARD;
```
We are also using two different arrays, a 64 length array to mimic an actual chessboard and to make runtimes faster and a 120 length array where the chess pieces will be located and will also be used for move generation in the next section. 
```

 120 BOARD  
         a    b    c    d    e    f    g    h      
    65   65   65   65   65   65   65   65   65   65
    65   65   65   65   65   65   65   65   65   65
 1  65    0    1    2    3    4    5    6    7   65
 2  65    8    9   10   11   12   13   14   15   65
 3  65   16   17   18   19   20   21   22   23   65
 4  65   24   25   26   27   28   29   30   31   65
 5  65   32   33   34   35   36   37   38   39   65
 6  65   40   41   42   43   44   45   46   47   65
 7  65   48   49   50   51   52   53   54   55   65
 8  65   56   57   58   59   60   61   62   63   65
    65   65   65   65   65   65   65   65   65   65
    65   65   65   65   65   65   65   65   65   65

64 BOARD
    a    b    c    d    e    f    g    h           
 1  21   22   23   24   25   26   27   28
 2  31   32   33   34   35   36   37   38
 3  41   42   43   44   45   46   47   48
 4  51   52   53   54   55   56   57   58
 5  61   62   63   64   65   66   67   68
 6  71   72   73   74   75   76   77   78
 7  81   82   83   84   85   86   87   88
 8  91   92   93   94   95   96   97   98
```