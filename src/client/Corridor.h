#pragma once

#include "BoardComponent.h"
#include "WallEnum.h"

/**
 * Subclass of BoardComponent and used to indicate the presence of a wall in the Board.
 */
class Corridor : public BoardComponent
{
private:
    /// The orientation of the wall when the corridor is occupied.
    WallOrientation orientation;

public:
    /**
     * Construct a new Corridor.
     *
     * @param orientation the orientation of the corridor
     */
    Corridor(const WallOrientation &orientation);
    ~Corridor();

    /**
     * Sets the corridor to be occupied.
     */
    void placeWall();

    void setOrientation(WallOrientation orientation);
    WallOrientation getOrientation();
};