template <typename K, typename V>
// deallocation of all nodes
void MyMap<K, V>::clear_helper(TreeNode<K, V> *&root) {
  if (root == nullptr) {
    return;
  }
  clear_helper(root->left);
  clear_helper(root->right);
  delete root;
  root = nullptr;
}

template <typename K, typename V>
void MyMap<K, V>::insert_helper(TreeNode<K, V> *&root, const K &new_key,
                                const V &new_value) {
  if (root == nullptr) {
    root = new TreeNode<K, V>(new_key, new_value);
  } else if (root->key > new_key) {
    insert_helper(root->left, new_key, new_value);
  } else if (root->key < new_key) {
    insert_helper(root->right, new_key, new_value);
  } else {
    return;
  }
}

template <typename K, typename V>
TreeNode<K, V> *MyMap<K, V>::get_min(TreeNode<K, V> *root) {
  if (root->left == nullptr)
    return root;
  return get_min(root->left);
}

template <typename K, typename V>
void MyMap<K, V>::erase_helper(TreeNode<K, V> *&root, const K &erase_key) {
  if (root == nullptr) {
    return;
  }

  if (erase_key > root->key) {
    erase_helper(root->right, erase_key);
  } else if (erase_key < root->key) {
    erase_helper(root->left, erase_key);
  } else { // erase_key == root->key
    // Degree 0: No children
    if (root->left == nullptr && root->right == nullptr) {
      delete root;
      root = nullptr;
    }
    // Degree 1: Only right child
    else if (root->left == nullptr) {
      TreeNode<K, V> *child = root->right;
      delete root;
      root = child;
    }
    // Degree 1: Only left child
    else if (root->right == nullptr) {
      TreeNode<K, V> *child = root->left;
      delete root;
      root = child;
    }
    // Degree 2: Both children
    else {
      // Find in-order successor (minimum in the right subtree)
      TreeNode<K, V> *successor = get_min(root->right);
      root->key = successor->key;
      root->value = successor->value;
      // Recursively delete the successor node
      erase_helper(root->right, successor->key);
    }
  }
}

template <typename K, typename V>
V &MyMap<K, V>::bracket_helper(TreeNode<K, V> *&root, const K &access_key) {
  if (root == nullptr) {
    // Key not found, create a new node with access_key and default value
    root = new TreeNode<K, V>(access_key, V()); // V() constructs default value
    return root->value;
  } else if (access_key < root->key) {
    // Recur to the left subtree
    return bracket_helper(root->left, access_key);
  } else if (access_key > root->key) {
    // Recur to the right subtree
    return bracket_helper(root->right, access_key);
  } else {
    // Key found, return reference to the value
    return root->value;
  }
}

template <typename K, typename V>
TreeNode<K, V> *MyMap<K, V>::find_helper(TreeNode<K, V> *root,
                                         const K &search_key) const {
  if (root == nullptr) {
    return nullptr;
  }

  if (search_key == root->key) {
    return root;
  } else if (search_key > root->key) {
    return find_helper(root->right, search_key);
  }
  return find_helper(root->left, search_key);
}

template <typename K, typename V>
TreeNode<K, V> *MyMap<K, V>::clone(const TreeNode<K, V> *root) {
  if (root == nullptr) {
    return nullptr;
  }
  TreeNode<K, V> *Copied_Node =
      new TreeNode<K, V>(root->key, root->value, nullptr, nullptr);

  Copied_Node->left = clone(root->left);
  Copied_Node->right = clone(root->right);

  return Copied_Node;
}

template <typename K, typename V>
MyMap<K, V>::MyMap(const MyMap<K, V> &source) {
  if (source.global_root == nullptr) {
    this->global_root = nullptr;
  } else {
    this->global_root = clone(source.global_root); // Clone the tree from source
  }
}

template <typename K, typename V>
MyMap<K, V> &MyMap<K, V>::operator=(const MyMap<K, V> &source) {
  if (this == &source) {
    return *this; // Avoid self-assignment
  }

  // Clear the current tree
  clear_helper(this->global_root);

  // Check if the source has a tree and clone it
  if (source.global_root != nullptr) {
    this->global_root = clone(source.global_root);
  } else {
    this->global_root = nullptr;
  }

  return *this; // Return reference to *this
}



template <typename K, typename V> MyMap<K, V>::MyMap() : global_root(nullptr) {}

template <typename K, typename V> MyMap<K, V>::~MyMap() { clear(); }

template <typename K, typename V> V &MyMap<K, V>::at(const K &access_key) {

  return at_helper(global_root, access_key);
}

template <typename K, typename V>
V &MyMap<K, V>::operator[](const K &access_key) {
  return bracket_helper(global_root, access_key);
}

template <typename K, typename V> bool MyMap<K, V>::empty() const {
  return global_root == nullptr;
}

template <typename K, typename V> int MyMap<K, V>::size() const {
  return size_helper(global_root);
}

template <typename K, typename V> void MyMap<K, V>::clear() {
  clear_helper(global_root);
}

template <typename K, typename V>
void MyMap<K, V>::insert(const K &new_key, const V &new_value) {
  insert_helper(global_root, new_key, new_value);
}

template <typename K, typename V> void MyMap<K, V>::erase(const K &erase_key) {
  erase_helper(global_root, erase_key);
}

template <typename K, typename V>
TreeNode<K, V> *MyMap<K, V>::find(const K &search_key) const {
  return find_helper(global_root, search_key);
}

template <typename K, typename V> void MyMap<K, V>::print() const {
  print_helper(global_root, "");
}

template <typename K, typename V> TreeNode<K, V> *&MyMap<K, V>::begin() {
  return global_root;
}

template <typename K, typename V>
void MyMap<K, V>::convert_to_sorted_list(TreeNode<K, V> *&root,
                                         std::vector<V> &sorted) {
  if (root == nullptr)
    return;

  convert_to_sorted_list(root->left, sorted);
  sorted.push_back(root->value);
  convert_to_sorted_list(root->right, sorted);
}

template <typename K, typename V>
void MyMap<K, V>::print_helper(TreeNode<K, V> *root, std::string indent) const {
  if (root == nullptr) {
    cout << indent << "   [empty]" << endl;
    return;
  }
  print_helper(root->right, indent += "  ");
  cout << indent << " [" << root->key << "]=" << root->value << endl;
  print_helper(root->left, indent);
}

template <typename K, typename V>
V &MyMap<K, V>::at_helper(TreeNode<K, V> *&root, const K &access_key) {
  if (root == nullptr) {
    throw std::out_of_range("key not found");
  }
  if (access_key == root->key)
    return root->value;
  else {
    if (access_key < root->key)
      return at_helper(root->left, access_key);
    // else if(access_key > rt->key)
    return at_helper(root->right, access_key);
  }
}

template <typename K, typename V>
int MyMap<K, V>::size_helper(TreeNode<K, V> *root) const {
  if (root == nullptr)
    return 0;
  else {
    return 1 + size_helper(root->left) + size_helper(root->right);
  }
}
