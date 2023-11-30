/***
 * Isabella Phung
 * itphung
 * 2023 Fall CSE 101 PA7
 * Dictionary.cpp
 * Implementation for Dictionary ADT
 ***/

#include<stdexcept>
#include<string>
#include "Dictionary.h"

// node constructor
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// transplant()
// swaps and places nodes in specified locations
void Dictionary::transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    }else if(u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }

    if(v != nil){
        v->parent = u->parent;
    }
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R != nil){
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R != N){
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
    if(R!=nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R; 
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if(R == nil || k == R->key){
        return R;
    }else if (k < R->key){
        return search(R->left, k);
    }else{
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    if(R != nil){
        while(R->left != nil){
            R = R->left;
        }
        return R;
    }
    return nil;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    if(R != nil){
        while(R->right != nil){
            R = R->right;
        }
        return R;
    }
    return nil;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if(N == nil || N == findMax(root)){
        return nil;
    }
    if(N->right != nil){
        return findMin(N->right);
    }
    Node* y = N->parent;
    while(y != nil && N == y->right){
        N = y;
        y = y->parent;
    }
    return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if(N == nil || N == findMin(root)){
        return nil;
    }
    if(N->left != nil){
        return findMax(N->left);
    }
    Node* y = N->parent;
    while(y != nil && N == y->left){
        N = y;
        y = y->parent;
    }
    return y;
}



// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
    nil = new Node("null", -1);
    root = nil;
    current = root;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("null", -1);
    root = nil;
    current = root;
    preOrderCopy(D.root, D.nil);
    num_pairs = D.num_pairs;
}

// Destructor
Dictionary::~Dictionary(){
    clear();
    delete nil;
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    return search(root, k) != nil;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if(contains(k)){
        Node* n = search(root, k);
        return n->val;
    }else{
        throw std::invalid_argument("Dictionary: getValue(): key \""+k+"\" does not exist");
    }
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    return current != nil;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if(!hasCurrent()){
        throw std::invalid_argument("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(!hasCurrent()){
        throw std::invalid_argument("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    num_pairs = 0;
    postOrderDelete(root);
    root = nil;
    current = root;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    //printf("contains: %d\n", contains(k));
    if(contains(k)){//overwrite
        Node* n = search(root, k); 
        n->val = v; 
    }else{//add new node
        Node* z = new Node(k, v);
        z->parent = nil;
        z->left = nil;
        z->right = nil;
        Node* y=nil;
        Node* x = root;
        while(x != nil){
            y = x;
            if (k < x->key){
                x = x->left;
            }else{
                x = x->right;
            }
        }

        z->parent = y;
        if(y == nil){
            root = z;
        }else if(k < y->key){
            y->left = z;
        }else{
            y->right = z;
        }
        num_pairs++;
    }
}


// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    if(!contains(k)){
        throw std::invalid_argument("Dictionary: remove(): key \""+k+"\" does not exist");
    }
    if(hasCurrent() && currentKey() == k){//if cursor on pair, cursor becomes undefined
        current = nil;
    }
    Node* n = search(root, k);
    if(n->left == nil){
        transplant(n, n->right);
    }else if(n->right == nil){
        transplant(n, n->left);
    }else{
        Node* y = findMin(n->right);
        if(y->parent != n){
            transplant(y, y->right);
            y->right = n->right;
            y->right->parent = y;
        }
        transplant(n, y);
        y->left = n->left;
        y->left->parent = y;
    }
    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if(!hasCurrent()){
        throw std::invalid_argument("Dictionary: next(): current undefined");
    }

    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if(!hasCurrent()){
        throw std::invalid_argument("Dictionary: prev(): current undefined");
    }

    current = findPrev(current);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s = "";
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    return to_string()==D.to_string();
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if(this != &D){
        Dictionary temp = D;
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
        std::swap(nil, temp.nil);
    }
    return *this;
}

