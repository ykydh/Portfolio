//Use it as the node in the BST MyMap.

#ifndef TREENODE_H
#define TREENODE_H

template <typename K, typename V> struct TreeNode {
  K key;
  V value;
  TreeNode *left;
  TreeNode *right;
  TreeNode(const K &k, const V &v, TreeNode *lc, TreeNode *rc)
      : key(k), value(v), left(lc), right(rc) {}
  TreeNode(const K &k, const V &v)
      : key(k), value(v), left(nullptr), right(nullptr) {}
};

#endif
