#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class Node
{
private:
    TKey nodeKey;

    Node* leftNode, * rightNode;

    TValue* keyValues;
    int capacity, size;

    void resize();

public:
    Node(TKey key);

    Node(const Node* nodeToCopy);

    void setKey(TKey newKey);
    void setLeftNode(Node* newLeftNode);
    void setRightNode(Node* newRightNode);

    void copyNodeData(Node* nodeToCopy);

    void addValue(TValue valueToAdd);
    bool removeValue(TValue valueToRemove);

    TKey getKey();
    Node* getLeftNode();
    Node* getRightNode();

    TValue* getKeyValues();
    int getSize();

    TElem getElementAtPosition(int position);
};


class SortedMultiMap {
	friend class SMMIterator;
    private:
		//TODO - Representation
        Node* root;
        Relation orderRelation;
        

        // private methods 
        Node* searchNodeKey(Node* currentNode, TKey keyToSearch) const;
        Node* insertNode(Node* currentNode, Node* nodeToInsert) const;

        void removeNode(Node* currentNode, Node* nodeToRemove);
        Node* findMin(Node* startNode);

        int getSize(Node* currentNode) const;

    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
