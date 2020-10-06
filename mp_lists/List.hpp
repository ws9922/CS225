/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * current = head_;
  while (current != NULL && current->next != NULL) {
    current = current->next;
    delete current->prev;
  }
  if (current != NULL)
    delete current;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (!this->empty()) {
    head_ -> prev  = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> prev = tail_;
  newNode -> next = NULL;

  if (!this->empty()) {
    tail_ -> next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }
  tail_ = newNode;
  
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* temp = head_;
  ListNode* next;
  ListNode* last = NULL;
  if (temp == NULL || temp->next == NULL || temp->next->next == NULL) {
    return;
  }
  while(temp != NULL && temp->next != NULL && temp->next->next!=NULL) {
    if (temp == head_) {
      head_ = temp->next;
    } else {
      last->next = temp->next;   //5 temp->next  1 temp->prev
    }
    temp->next->prev = last;
    next = temp->next->next->next;     //next 4
    temp->next->next->next = temp;    //3 -> 1
    temp->prev = temp->next->next;    //3 <- 1
    temp->next = NULL;                // 1->Null
    last = temp;
    temp = next;   // temp = 4
  }
  if (temp != NULL) {
    temp->prev = last;
    last->next = temp;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == NULL || endPoint == NULL) {
    return;
  }
  ListNode * temp;
  ListNode * current = endPoint;
  ListNode* last;
  ListNode* next;
  if(startPoint->next != NULL) {
    last = startPoint->prev;
  } else {
    last = NULL;
  }
  if(endPoint->next != NULL) {
    next = endPoint->next;
  } else {
    next = NULL;
  }
  while (startPoint != endPoint) {
    temp = endPoint->prev;
    endPoint->prev = endPoint->next;
    endPoint->next = temp;
    endPoint = temp;
  }
  endPoint->prev = endPoint->next;
  endPoint->next = next;
  if(next != NULL) {
    next->next = endPoint;
  }
  startPoint = current;
  startPoint->prev = last;
  if(last != NULL) {
    last->next = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode * last = head_;
  ListNode * next = head_;
  bool for_result = true;
  bool while_result = true;
  while(true) {
    for(int i = 0; i < n; i++) {
      if (for_result) {
        i++;
      }
      if(!next->next) {
        reverse(last, next);
        return;
      } else {
        next = next->next;
      }
      for_result = false;
    }
    if(while_result)
      reverse(head_, next);
    else
      reverse(last, next);
    while_result = false;
    last = next->next;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL && second == NULL) {
    return NULL;
  }
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }
  /**ListNode* firsttail = first;
  while (firsttail->next != NULL) {
    firsttail = firsttail->next;
  }
  firsttail->next = second;
  second->pre = firsttail;
  first.s**/
  ListNode* head = NULL;
  ListNode* temp = NULL;
  ListNode* current = NULL;
  bool condition = true;
  while(true){
    if(second->data<first->data) {
      temp =second;
      second = second->next;
      if(condition) {
        head = temp;
      } else {
      current->next = temp;
      temp->prev = current;
      temp->next = NULL;
      }
      current = temp;
      if(second == NULL) {
        current->next = first;
        return head;
      }
    } else {
      temp = first;
      first = first->next;
      if(condition) {
        head = temp;
      } else {
        current->next = temp;
        temp->prev = current;
        temp->next = NULL;
      }
      current = temp;
      if (first == NULL) {
        current->next = second;
        return head;
      }
    }
    condition = false;
  }
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start == NULL) {
    return NULL;
  }
  if (chainLength <= 1) {
    return start;
  }
  ListNode* current = start;
  if (chainLength % 2 == 0) {
    int half = chainLength / 2;
    for(int i = 0; i < half && current->next != NULL; i++) {
      current = current->next;
    }
    if(current->prev) {
      current->prev->next = NULL;
      current->prev = NULL;
    }
    return merge(mergesort(start, half), mergesort(current, half));
  } else {
    int half = chainLength / 2;
    for (int i = 0; i < half && current->next!=NULL; i++) {
      current = current->next;
    }
    if (current->prev) {
      current->prev->next = NULL;
      current->prev = NULL;
    }
    return merge(mergesort(start, half), mergesort(current, half + 1));
  }
}