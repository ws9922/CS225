/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas * result = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    
    vector<Point<3>> averageColors;
    std::map<Point<3>, TileImage*> Map;
    Point<3> averageColor;
    for (size_t i = 0; i < theTiles.size(); i++) {
        averageColor = convertToXYZ(theTiles[i].getAverageColor());
        averageColors.push_back(averageColor);
        Map[averageColor] = &(theTiles[i]);
    }
    KDTree<3> tree(averageColors);
    for (int x = 0; x < theSource.getRows(); x++) {
        for (int y = 0; y < theSource.getColumns(); y++) {
            LUVAPixel color = theSource.getRegionColor(x, y);
            Point<3> P_color = convertToXYZ(color);
            Point<3> neighbor = tree.findNearestNeighbor(P_color);
            TileImage* to_tile = Map[neighbor];
            result->setTile(x, y, to_tile);
        }
    }
    return result;
}

