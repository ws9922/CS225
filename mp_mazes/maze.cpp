/* Your code here! */
#include "maze.h"
#include <random>
#include <stdlib.h>
#include <queue>
#include <set>

SquareMaze::SquareMaze(){
}	

void SquareMaze::makeMaze(int width, int height){
    _height = height;
    _width =  width;
    if(!walls.empty()){
        walls.clear();
    }
    DisjointSets maze;
    maze.addelements(width * height);
    std::vector<std::pair<bool, bool>> row;
    for(int i = 0; i < height; i++){
        walls.push_back(row);
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            walls[i].push_back(std::make_pair(true, true));
        }
    }
    std::vector<int> wall_cells;
    for (int i = 0; i < width * height - 1; i++){
        wall_cells.push_back(i);
    }
    auto rng = std::default_random_engine{};
    while(!wall_cells.empty()){
        std::shuffle(wall_cells.begin(), wall_cells.end(), rng);
        for(size_t i = 0; i < wall_cells.size(); i++){
            int x = wall_cells[i] % width;
            int y = wall_cells[i] / width;
            int idx = wall_cells[i];
            if(y == height - 1){
                if(maze.find(idx) != maze.find(idx + 1)){
                    walls[y][x].second = false;
                    maze.setunion(idx, idx + 1);
                }
                wall_cells.erase(wall_cells.begin() + i);
                i--;
            }else if(x == width - 1){
                if(maze.find(idx) != maze.find(idx + width)){
                    walls[y][x].first = false;
                    maze.setunion(idx, idx + width);
                }
                wall_cells.erase(wall_cells.begin() + i);
                i--;
            }else{
                if(maze.find(idx) == maze.find(idx + 1) &&  maze.find(idx) == maze.find(idx + width)){
                    wall_cells.erase(wall_cells.begin() + i);
                    i--;
                }else if(maze.find(idx) == maze.find(idx + 1)){
                    walls[y][x].first = false;
                    maze.setunion(idx, idx + width);
                    wall_cells.erase(wall_cells.begin() + i);
                    i--;
                }else if(maze.find(idx) == maze.find(idx + width)){
                    walls[y][x].second = false;
                    maze.setunion(idx, idx + 1);
                    wall_cells.erase(wall_cells.begin() + i);
                    i--;
                }else{
                    int dir = rand() % 2;
                    if(dir == 0){
                        walls[y][x].second = false;
                        maze.setunion(idx, idx + 1);
                    }else{
                        walls[y][x].first = false;
                        maze.setunion(idx, idx + width);
                    }
                }
            }
        }
    }
}		
bool SquareMaze::canTravel(int x, int y, int dir) const{
    std::pair<bool, bool> wall = walls[y][x];
    if(dir == 1){
        return !wall.first;
    } else if(dir == 0){
        return !wall.second;
    } else if(dir == 2){
        if(x == 0){
            return false;
        }
        std::pair<bool, bool> left_wall = walls[y][x - 1];
        return !left_wall.second;
    } else{
        if(y == 0){
            return false;
        }
        std::pair<bool, bool> up_wall = walls[y - 1][x];
        return !up_wall.first;
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(dir == 0){
        walls[y][x].second = exists;
    }else{
        walls[y][x].first = exists;
    }
}		

std::vector<int> SquareMaze::solveMaze(){
    std::queue<std::pair<std::pair<int, int>, std::vector<int>>> q;
    std::set<std::pair<int, int>> visited;
    visited.insert(std::make_pair(0, 0));
    std::vector<int> path;
    std::vector<int> curlongest;
    int curlongest_x = 0;
    q.push(std::make_pair(std::make_pair(0, 0), path));
    while(!q.empty()){
        std::pair<std::pair<int, int>, std::vector<int>> elem = q.front();
        q.pop();
        int x = elem.first.first;
        int y = elem.first.second;
        path = elem.second;
        if(y == _height - 1){
            if(path.size() > curlongest.size()){
                curlongest = path;
                curlongest_x = x;
            }
            if(path.size() == curlongest.size() && x < curlongest_x){
                curlongest = path;
                curlongest_x = x;
            }
        }
        if(canTravel(x, y, 0) && visited.count(std::make_pair(x + 1, y)) == 0){
            std::vector<int> right_path = path;
            right_path.push_back(0);
            q.push(std::make_pair(std::make_pair(x + 1, y), right_path));
            visited.insert(std::make_pair(x + 1, y));
        }
        if(canTravel(x, y, 1) && visited.count(std::make_pair(x, y + 1)) == 0){
            std::vector<int> down_path = path;
            down_path.push_back(1);
            q.push(std::make_pair(std::make_pair(x, y + 1), down_path));
            visited.insert(std::make_pair(x, y + 1));
        }
        if(canTravel(x, y, 2) && visited.count(std::make_pair(x - 1, y)) == 0){
            std::vector<int> left_path = path;
            left_path.push_back(2);
            q.push(std::make_pair(std::make_pair(x - 1, y), left_path));
            visited.insert(std::make_pair(x - 1, y));
        }
        if(canTravel(x, y, 3) && visited.count(std::make_pair(x, y - 1)) == 0){
            std::vector<int> up_path = path;
            up_path.push_back(3);
            q.push(std::make_pair(std::make_pair(x, y - 1), up_path));
            visited.insert(std::make_pair(x, y - 1));
        }
    }
    return curlongest;
}	

PNG * SquareMaze::drawMaze()const{
    PNG * result = new PNG (_width * 10 + 1, _height * 10 + 1);
    HSLAPixel blackPixel(0, 0, 0);
    for(unsigned int x = 10; x < result->width(); x++){
        result->getPixel(x, 0) = blackPixel;
    }
    for(unsigned int y = 0; y < result->height(); y++){
        result->getPixel(0, y) = blackPixel;
    }
    for(int y = 0; y < _height; y++){
        for(int x = 0; x < _width; x++){
            std::pair<bool, bool> wall = walls[y][x];
            if(wall.first){
                for(int k = 0; k <= 10; k++){
                    result->getPixel(x * 10 + k, (y + 1) * 10) = blackPixel;
                }
            }
            if(wall.second){
                for(int k = 0; k <= 10; k++){
                    result->getPixel((x + 1) * 10, y * 10 + k) = blackPixel;
                }
            }
        }
    }
    return result;
}

PNG * SquareMaze::drawMazeWithSolution(){
    PNG *result = drawMaze();
    std::vector<int> solpath = solveMaze();
    HSLAPixel redPixel(0, 1, 0.5, 1);
    HSLAPixel whitePixel(0, 0 ,1);
    int x = 5;
    int y = 5;
    for(int& dir : solpath){
        if(dir == 0){
            for(int i = x; i <= x + 10; i++){
                result->getPixel(i, y) = redPixel;
            }
            x = x + 10;
        }
        if(dir == 1){
            for(int i = y; i <= y + 10; i++){
                result->getPixel(x, i) = redPixel;
            }
            y = y + 10;
        }
        if(dir == 2){
            for(int i = x; i >= x - 10; i--){
                result->getPixel(i, y) = redPixel;
            }
            x = x - 10;
        }
        if(dir == 3){
            for(int i = y; i >= y - 10; i--){
                result->getPixel(x, i) = redPixel;
            }
            y = y - 10;
        }
    }
    for(int i = x - 4; i <= x + 4; i++){
        result->getPixel(i, y + 5) = whitePixel;
    }
    return result;
}