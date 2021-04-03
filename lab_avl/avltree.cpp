/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp1 = t;
    Node * temp2 = t->right;

    temp1->right = temp2->left;
    temp2->left = temp1;
    t = temp2;
    temp1->height = std::max(heightOrNeg1(temp1->left), heightOrNeg1(temp1->right)) + 1;
    temp2->height = std::max(heightOrNeg1(temp2->left), heightOrNeg1(temp2->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp1 = t;
    Node * temp2 = t->left;

    temp1->left = temp2->right;
    temp2->right = temp1;
    t = temp2;
    temp1->height = std::max(heightOrNeg1(temp1->left), heightOrNeg1(temp1->right)) + 1;
    temp2->height = std::max(heightOrNeg1(temp2->left), heightOrNeg1(temp2->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    /*
    if(subtree == NULL)
    {
      return;
    }
    if(heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right) > 1){

      int needRight = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
      if(needRight == -1){
        rotateRight(subtree);
      }else{rotateLeftRight(subtree);}

    }else if(heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right) < -1){
      int needLeft = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
      if(needLeft == -1){
        rotateRight(subtree);
      }else{rotateRightLeft(subtree);}
    }
    subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
    */
    if(subtree == NULL)
    {
      return;
    }
    int unbal = (heightOrNeg1(subtree->left)-heightOrNeg1(subtree->right));
    if(unbal == -2)
    {
      int needLeft = (heightOrNeg1(subtree->right->left)-heightOrNeg1(subtree->right->right));
      if (needLeft == -1) {
        rotateLeft(subtree);
      } else {
        rotateRightLeft(subtree);
      }
    }
    if(unbal == 2)
    {
      int needRight = (heightOrNeg1(subtree->left->left)-heightOrNeg1(subtree->left->right));
      if (needRight == 1) {
        rotateRight(subtree);
      } else {
        rotateLeftRight(subtree);
      }
    }
    subtree->height =std::max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree==NULL){
      subtree = new Node(key, value);
    }
    else if (key < subtree->key) insert(subtree->left, key, value);
    else if (key > subtree->key) insert(subtree->right, key, value);
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * temp = subtree->left;
            while (temp->right!=NULL)
            {
              temp = temp->right;
            }
            swap(subtree, temp);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            Node* left = subtree->left;
            Node* right = subtree->right;

            if(left != NULL){
            delete subtree;
            subtree = left;
          }
          if(right!= NULL){
            delete subtree;
            subtree = right;
          }
        }
        // your code here
        rebalance(subtree);
    }
}
