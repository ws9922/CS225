/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    startingVertex_ = "p1-" + std::to_string(startingTokens);
    for(int i = startingTokens; i >= 0; i--){
      Vertex v1 = "p1-" + std::to_string(i);
      Vertex v2 = "p2-" + std::to_string(i);
      g_.insertVertex(v1);
      g_.insertVertex(v2);
    }
    for(int i = startingTokens; i >= 2; i--){
      Vertex v1 = "p1-" + std::to_string(i);
      Vertex v2 = "p2-" + std::to_string(i);
      Vertex v1_dest1 = "p2-" + std::to_string(i - 1);
      Vertex v1_dest2 = "p2-" + std::to_string(i - 2);
      Vertex v2_dest1 = "p1-" + std::to_string(i - 1);
      Vertex v2_dest2 = "p1-" + std::to_string(i - 2);
      g_.insertEdge(v1, v1_dest1);
      g_.insertEdge(v1, v1_dest2);
      g_.insertEdge(v2, v2_dest1);
      g_.insertEdge(v2, v2_dest2);
      g_.setEdgeWeight(v1, v1_dest1, 0);
      g_.setEdgeWeight(v1, v1_dest2, 0);
      g_.setEdgeWeight(v2, v2_dest1, 0);
      g_.setEdgeWeight(v2, v2_dest2, 0);
    }
    Vertex v1 = "p1-1";
    Vertex v2 = "p2-1";
    Vertex v1_dest = "p2-0";
    Vertex v2_dest = "p1-0";
    g_.insertEdge(v1, v1_dest);
    g_.insertEdge(v2, v2_dest);
    g_.setEdgeWeight(v1, v1_dest, 0);
    g_.setEdgeWeight(v2, v2_dest, 0);
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
  // int startingTokens = std::stoi(startingVertex_.substr(3));
  Vertex cur = startingVertex_;
  while (std::stoi(cur.substr(3)) != 0){
    vector<Vertex> adjacents = g_.getAdjacent(cur);
    int idx = rand() % adjacents.size();
    Vertex dest = adjacents[idx];
    path.push_back(g_.getEdge(cur, dest));
    cur = dest;
  }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 Edge last = path[path.size() - 1];
 std::string winner = last.source.substr(1, 1);
 if(winner == "1"){
   for(Edge e : path){
     if(e.source.substr(1, 1) == "1"){
       g_.setEdgeWeight(e.source, e.dest, g_.getEdgeWeight(e.source, e.dest) + 1);
     } else{
       g_.setEdgeWeight(e.source, e.dest, g_.getEdgeWeight(e.source, e.dest) - 1);
     }
   }
 }else{
   for(Edge e : path){
     if(e.source.substr(1, 1) == "1"){
       g_.setEdgeWeight(e.source, e.dest, g_.getEdgeWeight(e.source, e.dest) - 1);
     } else{
       g_.setEdgeWeight(e.source, e.dest, g_.getEdgeWeight(e.source, e.dest) + 1);
     }
   }
 }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
