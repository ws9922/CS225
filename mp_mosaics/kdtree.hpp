/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] == second[curDim]) {
      return first < second;
    }
    if (first[curDim] < second[curDim]) {
      return true;
    } else {
      return false;
    }   
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int distance_tc = 0;
    int distance_tp = 0;
    for (int i = 0; i < Dim; i++){
      distance_tc = distance_tc + (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      distance_tp = distance_tp + (target[i] - potential[i]) * (target[i] - potential[i]);
    }
    //std::cout<<distance_tc<< " "<<distance_tp<<std::endl;
    if (distance_tp == distance_tc) {
      return potential < currentBest;
    }
    if (distance_tp < distance_tc) {
      return true;
    } else
      return false;
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& points, int left, int right, int pivotIndex, int dim){
      Point<Dim> pivotValue = points[pivotIndex];
      swap(points[pivotIndex], points[right]);
      int storeIndex = left;
      for (int i = left; i <= right - 1; i++) {
        if (smallerDimVal(points[i], pivotValue, dim)){
          swap(points[storeIndex], points[i]);
          storeIndex++;
        }
      }
      swap(points[right], points[storeIndex]);
      return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickselect(vector<Point<Dim>>& points, int left, int right, int k, int dim) {
  while (right != left) {
    int pivotIndex = k;
    pivotIndex = partition(points, left, right, pivotIndex, dim);
    if (k == pivotIndex) {
      return points[k];
    } else if (k < pivotIndex) {
      right = pivotIndex - 1;
    } else {
      left = pivotIndex + 1;
    }
  }
  return points[left];
   
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> points;
    for (size_t i = 0; i < newPoints.size(); ++i) {
      points.push_back(newPoints[i]);
    } 
    if (points.empty()) {
      this->root = NULL;
      this->size = 0;
    }
    this->root = buildTree(points, 0, 0, points.size() - 1);
    this->size = points.size();
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& points, int dim, int left, int right) {
  if (left > right) {
    return NULL;
  }
  int middle = (left + right) / 2;
  Point<Dim> point = this->quickselect(points, left, right, middle, dim);
  KDTreeNode * root = new KDTreeNode(point);
  root->left = buildTree(points, (dim + 1) % Dim, left, middle - 1);
  root->right = buildTree(points, (dim + 1) % Dim, middle + 1, right);
  return root;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy(other);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs) {
         clear(root);
         copy(rhs);
    }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
}

template <int Dim>
void KDTree<Dim>::copy(const KDTree<Dim>& rhs)
{
    root = copy(rhs.root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const KDTreeNode* current)
{
    if (current == NULL)
        return NULL;
    KDTreeNode* node = new KDTreeNode(current->point);
    node->left = copy(current->left);
    node->right = copy(current->right);
    return node;
}

template<int Dim>
void KDTree<Dim>::clear(KDTreeNode* current)
{
    if (current == NULL)
        return;
    clear(current->left);
    clear(current->right);
    delete current;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighbor_(query, 0, root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor_(const Point<Dim>& query, int dim, const KDTreeNode* curRoot) const {
  Point<Dim> nearest;
  if (curRoot->left == NULL && curRoot->right == NULL) {
    return curRoot->point;
  } else if (curRoot->left == NULL) {
    nearest = findNearestNeighbor_(query, (dim + 1) % Dim, curRoot->right);
    if (shouldReplace(query, nearest, curRoot->point)) {
      nearest = curRoot->point;
    }
    return nearest;
  } else if (curRoot->right == NULL) {
    nearest = findNearestNeighbor_(query, (dim + 1) % Dim, curRoot->left);
    if (shouldReplace(query, nearest, curRoot->point)) {
      nearest = curRoot->point;
    }
    return nearest;
  }
  if (smallerDimVal(query, curRoot->point, dim)) {
    nearest = findNearestNeighbor_(query, (dim + 1) % Dim, curRoot->left);
  } else {
    nearest = findNearestNeighbor_(query, (dim + 1) % Dim, curRoot->right);
  }
  if (shouldReplace(query, nearest, curRoot->point)) {
    nearest = curRoot->point;
  }
  int radius = 0;
  for (int i = 0; i < Dim; i++) {
    radius = radius + (query[i] - nearest[i]) * (query[i] - nearest[i]);
  }
  int splitDist = (curRoot->point[dim] - query[dim]) * (curRoot->point[dim] - query[dim]);
  Point<Dim> tempNearest;
  if (radius >= splitDist) {
    if(smallerDimVal(query, curRoot->point, dim)){
      tempNearest = findNearestNeighbor_(query, (dim + 1) % Dim, curRoot->right);
    } else {
      tempNearest = findNearestNeighbor_(query, (dim + 1) % Dim, curRoot->left);
    }
    if (shouldReplace(query, nearest, tempNearest)) {
      nearest = tempNearest;
    }
  }
  return nearest;
}

