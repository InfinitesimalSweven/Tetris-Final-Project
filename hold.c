#include "piece.h"
#include "board.h"
#include "hold.h"
#include "blockOffsets.h"

//Puts held in if piece is empty. If piece was held last turn locks the system. If there is a piece swaps the pieces.
void doHold(Piece *current, HoldSlot *HeldItem){
    if (HeldItem->hasHeld) return;
    else if (HeldItem->heldEmpty){
        HeldItem->piece = *current;
        HeldItem->heldEmpty = 0;

    }
    else{
        Piece temp = HeldItem->piece;
        HeldItem->piece = *current;
        *current = temp;
    }
    HeldItem->hasHeld = 1;
}


