/**
* implement a container like std::map
*/
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

template<
   class Key,
   class T,
   class Compare = std::less <Key>
   > class map {
  public:
   /**
  * the internal type of data.
  * it should have a default constructor, a copy constructor.
  * You can use sjtu::map as value_type by typedef.
    */
   typedef pair<const Key, T> value_type;

  private:
   struct Node {
       value_type* data;
       Node* left;
       Node* right;
       Node* parent;
       int height;

       Node(const value_type& val, Node* p = nullptr)
           : data(new value_type(val)), left(nullptr), right(nullptr), parent(p), height(1) {}

       Node(const Key& k, const T& v, Node* p = nullptr)
           : data(new value_type(k, v)), left(nullptr), right(nullptr), parent(p), height(1) {}

       ~Node() {
           delete data;
       }
   };

   Node* root;
   size_t sz;
   Compare comp;

   int getHeight(Node* node) const {
       return node ? node->height : 0;
   }

   int getBalance(Node* node) const {
       return node ? getHeight(node->left) - getHeight(node->right) : 0;
   }

   void updateHeight(Node* node) {
       if (node) {
           int lh = getHeight(node->left);
           int rh = getHeight(node->right);
           node->height = 1 + (lh > rh ? lh : rh);
       }
   }

   Node* rotateRight(Node* y) {
       Node* x = y->left;
       Node* T2 = x->right;

       x->right = y;
       x->parent = y->parent;
       y->parent = x;
       y->left = T2;
       if (T2) T2->parent = y;

       updateHeight(y);
       updateHeight(x);

       return x;
   }

   Node* rotateLeft(Node* x) {
       Node* y = x->right;
       Node* T2 = y->left;

       y->left = x;
       y->parent = x->parent;
       x->parent = y;
       x->right = T2;
       if (T2) T2->parent = x;

       updateHeight(x);
       updateHeight(y);

       return y;
   }

   Node* insertNode(Node* node, const value_type& val, Node* parent, bool& inserted, Node*& result) {
       if (!node) {
           inserted = true;
           result = new Node(val, parent);
           sz++;
           return result;
       }

       if (comp(val.first, node->data->first)) {
           node->left = insertNode(node->left, val, node, inserted, result);
       } else if (comp(node->data->first, val.first)) {
           node->right = insertNode(node->right, val, node, inserted, result);
       } else {
           inserted = false;
           result = node;
           return node;
       }

       updateHeight(node);
       int balance = getBalance(node);

       // Left Left Case
       if (balance > 1 && comp(val.first, node->left->data->first)) {
           return rotateRight(node);
       }

       // Right Right Case
       if (balance < -1 && comp(node->right->data->first, val.first)) {
           return rotateLeft(node);
       }

       // Left Right Case
       if (balance > 1 && comp(node->left->data->first, val.first)) {
           node->left = rotateLeft(node->left);
           node->left->parent = node;
           return rotateRight(node);
       }

       // Right Left Case
       if (balance < -1 && comp(val.first, node->right->data->first)) {
           node->right = rotateRight(node->right);
           node->right->parent = node;
           return rotateLeft(node);
       }

       return node;
   }

   Node* findMin(Node* node) const {
       while (node && node->left) {
           node = node->left;
       }
       return node;
   }

   Node* findMax(Node* node) const {
       while (node && node->right) {
           node = node->right;
       }
       return node;
   }

   Node* deleteNode(Node* node, const Key& key, bool& deleted) {
       if (!node) {
           deleted = false;
           return nullptr;
       }

       if (comp(key, node->data->first)) {
           node->left = deleteNode(node->left, key, deleted);
           if (node->left) node->left->parent = node;
       } else if (comp(node->data->first, key)) {
           node->right = deleteNode(node->right, key, deleted);
           if (node->right) node->right->parent = node;
       } else {
           deleted = true;

           if (!node->left || !node->right) {
               sz--;
               Node* temp = node->left ? node->left : node->right;
               if (temp) temp->parent = node->parent;
               delete node;
               return temp;
           } else {
               Node* temp = findMin(node->right);
               value_type* oldData = node->data;
               node->data = new value_type(temp->data->first, temp->data->second);
               delete oldData;
               bool dummyDeleted;
               node->right = deleteNode(node->right, temp->data->first, dummyDeleted);
               if (node->right) node->right->parent = node;
           }
       }

       if (!node) return nullptr;

       updateHeight(node);
       int balance = getBalance(node);

       // Left Left Case
       if (balance > 1 && getBalance(node->left) >= 0) {
           return rotateRight(node);
       }

       // Left Right Case
       if (balance > 1 && getBalance(node->left) < 0) {
           node->left = rotateLeft(node->left);
           node->left->parent = node;
           return rotateRight(node);
       }

       // Right Right Case
       if (balance < -1 && getBalance(node->right) <= 0) {
           return rotateLeft(node);
       }

       // Right Left Case
       if (balance < -1 && getBalance(node->right) > 0) {
           node->right = rotateRight(node->right);
           node->right->parent = node;
           return rotateLeft(node);
       }

       return node;
   }

   Node* findNode(const Key& key) const {
       Node* current = root;
       while (current) {
           if (comp(key, current->data->first)) {
               current = current->left;
           } else if (comp(current->data->first, key)) {
               current = current->right;
           } else {
               return current;
           }
       }
       return nullptr;
   }

   Node* copyTree(Node* node, Node* parent) {
       if (!node) return nullptr;
       Node* newNode = new Node(*(node->data), parent);
       newNode->height = node->height;
       newNode->left = copyTree(node->left, newNode);
       newNode->right = copyTree(node->right, newNode);
       return newNode;
   }

   void clearTree(Node* node) {
       if (!node) return;
       clearTree(node->left);
       clearTree(node->right);
       delete node;
   }

  public:
   /**
  * see BidirectionalIterator at CppReference for help.
  *
  * if there is anything wrong throw invalid_iterator.
  *     like it = map.begin(); --it;
  *       or it = map.end(); ++end();
    */
   class const_iterator;
   class iterator {
      friend class map;
      friend class const_iterator;
      private:
       /**
    * TODO add data members
    *   just add whatever you want.
        */
       const map* container;
       Node* node;

       iterator(const map* m, Node* n) : container(m), node(n) {}

      public:
       iterator() : container(nullptr), node(nullptr) {}

       iterator(const iterator &other) : container(other.container), node(other.node) {}

       /**
    * TODO iter++
        */
       iterator operator++(int) {
           if (!node) throw invalid_iterator();
           iterator temp = *this;
           if (node->right) {
               node = container->findMin(node->right);
           } else {
               Node* p = node->parent;
               while (p && node == p->right) {
                   node = p;
                   p = p->parent;
               }
               node = p;
           }
           return temp;
       }

       /**
    * TODO ++iter
        */
       iterator &operator++() {
           if (!node) throw invalid_iterator();
           if (node->right) {
               node = container->findMin(node->right);
           } else {
               Node* p = node->parent;
               while (p && node == p->right) {
                   node = p;
                   p = p->parent;
               }
               node = p;
           }
           return *this;
       }

       /**
    * TODO iter--
        */
       iterator operator--(int) {
           iterator temp = *this;
           if (!node) {
               if (!container || !container->root) throw invalid_iterator();
               node = container->findMax(container->root);
           } else if (node->left) {
               node = container->findMax(node->left);
           } else {
               Node* p = node->parent;
               while (p && node == p->left) {
                   node = p;
                   p = p->parent;
               }
               if (!p) throw invalid_iterator();
               node = p;
           }
           return temp;
       }

       /**
    * TODO --iter
        */
       iterator &operator--() {
           if (!node) {
               if (!container || !container->root) throw invalid_iterator();
               node = container->findMax(container->root);
           } else if (node->left) {
               node = container->findMax(node->left);
           } else {
               Node* p = node->parent;
               while (p && node == p->left) {
                   node = p;
                   p = p->parent;
               }
               if (!p) throw invalid_iterator();
               node = p;
           }
           return *this;
       }

       /**
    * a operator to check whether two iterators are same (pointing to the same memory).
        */
       value_type &operator*() const {
           if (!node) throw invalid_iterator();
           return *(node->data);
       }

       bool operator==(const iterator &rhs) const {
           return container == rhs.container && node == rhs.node;
       }

       bool operator==(const const_iterator &rhs) const {
           return container == rhs.container && node == rhs.node;
       }

       /**
    * some other operator for iterator.
        */
       bool operator!=(const iterator &rhs) const {
           return !(*this == rhs);
       }

       bool operator!=(const const_iterator &rhs) const {
           return !(*this == rhs);
       }

       /**
    * for the support of it->first.
    * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
        */
       value_type *operator->() const noexcept {
           return node->data;
       }
   };

   class const_iterator {
       // it should has similar member method as iterator.
       //  and it should be able to construct from an iterator.
      friend class map;
      private:
       const map* container;
       Node* node;

       const_iterator(const map* m, Node* n) : container(m), node(n) {}

      public:
       const_iterator() : container(nullptr), node(nullptr) {}

       const_iterator(const const_iterator &other) : container(other.container), node(other.node) {}

       const_iterator(const iterator &other) : container(other.container), node(other.node) {}

       const_iterator operator++(int) {
           if (!node) throw invalid_iterator();
           const_iterator temp = *this;
           if (node->right) {
               node = container->findMin(node->right);
           } else {
               Node* p = node->parent;
               while (p && node == p->right) {
                   node = p;
                   p = p->parent;
               }
               node = p;
           }
           return temp;
       }

       const_iterator &operator++() {
           if (!node) throw invalid_iterator();
           if (node->right) {
               node = container->findMin(node->right);
           } else {
               Node* p = node->parent;
               while (p && node == p->right) {
                   node = p;
                   p = p->parent;
               }
               node = p;
           }
           return *this;
       }

       const_iterator operator--(int) {
           const_iterator temp = *this;
           if (!node) {
               if (!container || !container->root) throw invalid_iterator();
               node = container->findMax(container->root);
           } else if (node->left) {
               node = container->findMax(node->left);
           } else {
               Node* p = node->parent;
               while (p && node == p->left) {
                   node = p;
                   p = p->parent;
               }
               if (!p) throw invalid_iterator();
               node = p;
           }
           return temp;
       }

       const_iterator &operator--() {
           if (!node) {
               if (!container || !container->root) throw invalid_iterator();
               node = container->findMax(container->root);
           } else if (node->left) {
               node = container->findMax(node->left);
           } else {
               Node* p = node->parent;
               while (p && node == p->left) {
                   node = p;
                   p = p->parent;
               }
               if (!p) throw invalid_iterator();
               node = p;
           }
           return *this;
       }

       const value_type &operator*() const {
           if (!node) throw invalid_iterator();
           return *(node->data);
       }

       bool operator==(const iterator &rhs) const {
           return container == rhs.container && node == rhs.node;
       }

       bool operator==(const const_iterator &rhs) const {
           return container == rhs.container && node == rhs.node;
       }

       bool operator!=(const iterator &rhs) const {
           return !(*this == rhs);
       }

       bool operator!=(const const_iterator &rhs) const {
           return !(*this == rhs);
       }

       const value_type *operator->() const noexcept {
           return node->data;
       }
   };

   /**
  * TODO two constructors
    */
   map() : root(nullptr), sz(0) {}

   map(const map &other) : root(nullptr), sz(0) {
       root = copyTree(other.root, nullptr);
       sz = other.sz;
   }

   /**
  * TODO assignment operator
    */
   map &operator=(const map &other) {
       if (this != &other) {
           clearTree(root);
           root = copyTree(other.root, nullptr);
           sz = other.sz;
       }
       return *this;
   }

   /**
  * TODO Destructors
    */
   ~map() {
       clearTree(root);
   }

   /**
  * TODO
  * access specified element with bounds checking
  * Returns a reference to the mapped value of the element with key equivalent to key.
  * If no such element exists, an exception of type `index_out_of_bound'
    */
   T &at(const Key &key) {
       Node* node = findNode(key);
       if (!node) throw index_out_of_bound();
       return node->data->second;
   }

   const T &at(const Key &key) const {
       Node* node = findNode(key);
       if (!node) throw index_out_of_bound();
       return node->data->second;
   }

   /**
  * TODO
  * access specified element
  * Returns a reference to the value that is mapped to a key equivalent to key,
  *   performing an insertion if such key does not already exist.
    */
   T &operator[](const Key &key) {
       Node* node = findNode(key);
       if (node) {
           return node->data->second;
       }
       // Need to insert with default value
       value_type val(key, T());
       bool inserted;
       Node* result;
       root = insertNode(root, val, nullptr, inserted, result);
       if (root) root->parent = nullptr;
       return result->data->second;
   }

   /**
  * behave like at() throw index_out_of_bound if such key does not exist.
    */
   const T &operator[](const Key &key) const {
       return at(key);
   }

   /**
  * return a iterator to the beginning
    */
   iterator begin() {
       return iterator(this, findMin(root));
   }

   const_iterator cbegin() const {
       return const_iterator(this, findMin(root));
   }

   /**
  * return a iterator to the end
  * in fact, it returns past-the-end.
    */
   iterator end() {
       return iterator(this, nullptr);
   }

   const_iterator cend() const {
       return const_iterator(this, nullptr);
   }

   /**
  * checks whether the container is empty
  * return true if empty, otherwise false.
    */
   bool empty() const {
       return sz == 0;
   }

   /**
  * returns the number of elements.
    */
   size_t size() const {
       return sz;
   }

   /**
  * clears the contents
    */
   void clear() {
       clearTree(root);
       root = nullptr;
       sz = 0;
   }

   /**
  * insert an element.
  * return a pair, the first of the pair is
  *   the iterator to the new element (or the element that prevented the insertion),
  *   the second one is true if insert successfully, or false.
    */
   pair<iterator, bool> insert(const value_type &value) {
       bool inserted;
       Node* result;
       root = insertNode(root, value, nullptr, inserted, result);
       if (root) root->parent = nullptr;
       return pair<iterator, bool>(iterator(this, result), inserted);
   }

   /**
  * erase the element at pos.
  *
  * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
    */
   void erase(iterator pos) {
       if (!pos.node || pos.container != this) throw invalid_iterator();
       bool deleted;
       root = deleteNode(root, pos.node->data->first, deleted);
       if (root) root->parent = nullptr;
       if (!deleted) throw invalid_iterator();
   }

   /**
  * Returns the number of elements with key
  *   that compares equivalent to the specified argument,
  *   which is either 1 or 0
  *     since this container does not allow duplicates.
  * The default method of check the equivalence is !(a < b || b > a)
    */
   size_t count(const Key &key) const {
       return findNode(key) ? 1 : 0;
   }

   /**
  * Finds an element with key equivalent to key.
  * key value of the element to search for.
  * Iterator to an element with key equivalent to key.
  *   If no such element is found, past-the-end (see end()) iterator is returned.
    */
   iterator find(const Key &key) {
       Node* node = findNode(key);
       return iterator(this, node);
   }

   const_iterator find(const Key &key) const {
       Node* node = findNode(key);
       return const_iterator(this, node);
   }
};

}

#endif
