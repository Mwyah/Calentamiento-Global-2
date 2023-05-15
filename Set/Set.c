//
// Set.c
//

// Welcome to a red-black tree's domain. Enjoy

#include "Set.h"

#include <stdlib.h>
#include <inttypes.h>

#include <stdio.h>


typedef struct Node Node;
typedef enum Colour {BLACK, RED} Colour;

struct Node {
	size_t key;
	void* data;

	Node* parent;
	Node* leftChild;
	Node* rightChild;

	Colour colour;
	size_t leftBranchSize;        // Number of items in the lefs subtree of this node
};

typedef struct Set {
	size_t itemSize;
	size_t itemCount;

	Node* root;

	size_t (*hash)(const void*);
	bool (*equals)(const void*, const void*);
} Set;



// Test functions

static void printNode(Node* node) {
	printf("%i[%zi %i]", *((char*) node->data), node->leftBranchSize, node->colour);

	if (node->leftChild) 
		printf("<");

	if (node->rightChild) 
		printf(">");

	if (node->leftChild) 
		printNode(node->leftChild);

	if (node->rightChild) 
		printNode(node->rightChild);
}

void printTree(void* set) {
	if (set) {
		if (((Set*) set)->root) {
			printNode(((Set*) set)->root);
			printf("\n");
		}
		else 
			printf("empty\n");
	}
	else
		printf("allah\n");
}



// Static Declarations

static void _setInit(Set* set, size_t itemSize,
					size_t hash(const void*),
					bool (*equals)(const void*, const void*));

static Node* createNode(size_t key, const void* data, Node* parent);
static void deleteNode(Set* set, Node* node, void(*destroy)(void*));

/// Returns Node** to the node with same data 
/// or to the place this data should be.
/// parent_p contains the parent of the returned node.
static Node** findNode(Set* set, const void* data, Node** parent_p);

static Node* findNodeByIndex(Set* set, size_t index);
static Node* findLastNode(Node* root);


static inline bool isBlack(Node* node) { 

	return !node || node->colour == BLACK; 
};

static inline bool isRightChild(Node* X, Node* P) { 

	return P->rightChild == X; 
};

// Structure of small right rotaton (left rotation is mirrored right rotation):
//
//        |                  |
//        P                  X
//       / \                / \
//      X   C      ->      A   P
//     / \                    / \
//    A   B                  B   C
//
static void smallRotation(Set* set, Node* X);

// Structure of big right rotaton (left rotation is mirrored right rotation):
//
//        |                   |
//        G                   X
//       / \                /   \
//      P   D      ->      P     G
//     / \                / \   / \
//    A   X              A   B C   D
//       / \
//      B   C 
//
static void bigRotation(Set* set, Node* X);

/// Ascends from X to the root and changes leftBranchSize by value 
/// for all nodes on the path that are got to on the left.
static void climbAndUpdateLeftBranchSize(Node* X, int value);

// Insertion balance subtree: X - current node (added node for the first call),
//                            P - X's parent,
//             |              G - X's grandparent (P's parent),
//             G              U - X's uncle (G's second child).
//           /   \
//          P     U
//         / \   / \
//        X             (an LL variation)
//       / \
//
static void insertionBalance(Set* set, Node* X);

// Deletion balance subtree:  X - current node (deleted node, (Null) for the first call),
//                            P - X's parent,
//              |             S - X's sibling (P's second child),
//              P             SL - S's left child,
//           /     \          SR - S's right child.
//          X       S
//         / \   /     \
//              SL     SR     (an L variation)
//             /  \   /  \
//
static void deletionBalance(Set* set, Node* X);

static void removeNode(Set* set, Node* X, void* (*destroy)(void*));

static inline bool isInRange(void* set, size_t ind) { 

	return ind < ((Set*) set)->itemCount; 
}



// Header Declarations

void* set_create(size_t itemSize, size_t hash(const void*),
				 bool (*equals)(const void*, const void*)) {
	
	Set* res = NULL;

	if (itemSize != 0 && hash && equals) {
		res = malloc(sizeof(Set));

		if (res)
			_setInit(res, itemSize, hash, equals);
	}

	return res;
}


void set_destroy(void* set, void (*destroy)(void*)) {

	if (set) {
		set_clear(set, destroy);
		free(set);
	}
}

void* set_init(void* set, size_t itemSize, 
			  size_t hash(const void*),
			  bool (*equals)(const void*, const void*), 
			  void (*destroy)(void*)) {

	void* res = NULL;

	if (set) {
		res = set;

		if (itemSize > 0 && hash && equals) {
			set_clear(set, destroy);
			_setInit(set, itemSize, hash, equals);
		}
	}

	return res;
}

void set_clear(void* set, void (*destroy)(void*)) {

	if (set) {
		Set* _set = set;
		Node* X = _set->root;
		Node* P;

		while (X) {
			X = findLastNode(X);
			P = X->parent;
			deleteNode(set, X, destroy);
			X = P;
		}

		_set->root = NULL;
		_set->itemCount = 0;
	}
}
                                                                               

size_t set_count(const void* set) { 
	
	return (set) ? ((Set*) set)->itemCount : INVALID; 
}

bool set_contains(const void* set, const void* item) { 

		return (set && item) ? *findNode(set, item, NULL) : false;
}

bool set_insert(void* set, const void* item) {
	bool res = false;

	if (set && item) {
		Set* _set = set;

		Node* parent;
		Node** node_p = findNode(_set, item, &parent);

		if (!(*node_p)) {
			*node_p = createNode(_set->hash(item), item, parent);

			if (*node_p) {
				res = true;
				_set->itemCount++;

				climbAndUpdateLeftBranchSize(*node_p, 1);
				insertionBalance(_set, *node_p);
			}
		}
	}

	return res;
}

void set_remove(void* set, const void* item, void (*destroy)(void*)) {         

	if (set && item) 
		removeNode(set, *findNode(set, item, NULL), destroy);
}


size_t set_first(const void* set) { 

	return (set && ((Set*) set)->root) ? 0 : INVALID; 
}

size_t set_last(const void* set) { 

	return (set) ? ((Set*) set)->itemCount-1 : INVALID; 
}

size_t set_next(const void* set, size_t item_id) {

	if (set && isInRange(set, item_id) && isInRange(set, item_id+1))
		return item_id + 1;
	else
		return INVALID;
}

size_t set_prev(const void* set, size_t item_id) { 

	if (set && isInRange(set, item_id) && isInRange(set, item_id-1)) 
		return item_id-1;
	else
		return INVALID;
}

size_t set_stop(const void* set) { return INVALID; }


const void* set_current(const void* set, size_t item_id) {
	void* res = NULL;

	if (set && isInRange(set, item_id)) 
		res = findNodeByIndex(set, item_id)->data;

	return res;
}

void set_erase(void* set, size_t item_id, void (*destroy)(void*)) {

	if (set && isInRange(set, item_id))
		removeNode(set, findNodeByIndex(set, item_id), destroy);
}



//Static Definitions

static void _setInit(Set* set, size_t itemSize,
					size_t hash(const void*),
					bool (*equals)(const void*, const void*)) {

	set->itemSize = itemSize;
	set->itemCount = 0;

	set->root = NULL;

	set->hash = hash;
	set->equals = equals;
}

static Node* createNode(size_t key, const void* data, Node* parent) {
	Node* res = malloc(sizeof(Node));

	if (res) {
		res->key = key;
		res->data = data;

		res->parent = parent;
		res->leftChild = NULL;
		res->rightChild = NULL;

		res->colour = RED;
		res->leftBranchSize = 0;
	}

	return res;
}

static void deleteNode(Set* set, Node* node, void (*destroy)(void*)) {
	Node* P = node->parent;

	if (P) {
		if (isRightChild(node, P)) 
			P->rightChild = NULL;
		else
			P->leftChild = NULL;
	}
	else 
		set->root = NULL;

	if (destroy)
		destroy(node->data);

	free(node);
}

static Node** findNode(Set* set, const void* data, Node** parent_p) {
	Node** res = &(set->root);
	Node* parent = NULL;

	size_t key = set->hash(data);
	bool isSameData = false;

	while (*res && !isSameData) {
		if (key >= (*res)->key) {
			if (key == (*res)->key && set->equals(data, (*res)->data))
				isSameData = true;
			else {
				parent = *res;
				res = &((*res)->rightChild);
			}


		}
		else {
			parent = *res;
			res = &((*res)->leftChild);
		}
	}

	if (parent_p)
		*parent_p = parent;

	return res;
}

static Node* findNodeByIndex(Set* set, size_t index) {
	Node* res = set->root;
	size_t count = set->itemCount-1;

	while (index != 0) {
		if (index > res->leftBranchSize) {
			index -= res->leftBranchSize;
			count -= res->leftBranchSize;
			res = res->rightChild;
		}
		else
			res = res->leftChild;

		index--;
		count--;
	}

	return res;
}

static Node* findLastNode(Node* root) {
	Node* res = root;
	bool isLastNode = false;

	while (!isLastNode) {
		if (res->rightChild)
			res = res->rightChild;
		else if (res->leftChild)
			res = res->leftChild;
		else
			isLastNode = true;
	}

	return res;
}


static void smallRotation(Set* set, Node* X) {
	Node* P = X->parent;
	Node* G = P->parent;
	Node* B;
	Node** G_child_p;

	if (G) 
		G_child_p = isRightChild(P, G) 
			        ? &(G->rightChild) 
			        : &(G->leftChild);
	else
		G_child_p = &(set->root);


	*(G_child_p) = X;
	X->parent = G;
	P->parent = X;

	if (isRightChild(X, P)) {    // Left rotation
		B = X->leftChild;

		P->rightChild = B;
		X->leftChild = P;

		X->leftBranchSize += P->leftBranchSize + 1;
	}
	else {                       // Right rotation
		B = X->rightChild;

		P->leftChild = B;
		X->rightChild = P;

		P->leftBranchSize -= X->leftBranchSize + 1;
	}

	if (B) B->parent = P;
}

static void bigRotation(Set* set, Node* X) {
	Node* P = X->parent;
	Node* G = P->parent;
	Node* GG = G->parent;
	Node* B = X->leftChild;
	Node* C = X->rightChild;
	Node** GG_child_p;

	if (GG)
		GG_child_p = isRightChild(G, GG) ? &(GG->rightChild) : &(GG->leftChild);
	else
		GG_child_p = &(set->root);


	*(GG_child_p) = X;
	X->parent = GG;
	P->parent = X;
	G->parent = X;

	if (isRightChild(X, P)) {    // Right rotation
		P->rightChild = B;
		G->leftChild = C;

		X->leftChild = P;
		X->rightChild = G;

		if (B) B->parent = P;
		if (C) C->parent = G;

		X->leftBranchSize += P->leftBranchSize + 1;
		G->leftBranchSize -= X->leftBranchSize + 1;
	}
	else {                       // Left rotation
		P->leftChild = C;
		G->rightChild = B;

		X->leftChild = G;
		X->rightChild = P;

		if (B) B->parent = G;
		if (C) C->parent = P;

		P->leftBranchSize -= X->leftBranchSize + 1;
		X->leftBranchSize += G->leftBranchSize + 1;
	}
}


static void climbAndUpdateLeftBranchSize(Node* X, int value) {
	Node* P = X->parent;

	while (P) {
		if (!isRightChild(X, P))
			P->leftBranchSize += value;

		X = P;
		P = X->parent;
	}
}


static void insertionBalance(Set* set, Node* X) {
	if (set->root == X)
		X->colour = BLACK;
	else {
		Node* P = X->parent;

		if (!isBlack(P)) {
			Node* G = P->parent;
			Node* U = isRightChild(P, G) ? G->leftChild : G->rightChild;

			if (isBlack(U)) {
				if (isRightChild(X, P) && isRightChild(P, G) ||
					!isRightChild(X, P) && !isRightChild(P, G)) {

					smallRotation(set, P);

					P->colour = BLACK;
					G->colour = RED;
				}
				else {
					bigRotation(set, X);

					X->colour = BLACK;
					G->colour = RED;
				}
			}
			else {
				P->colour = BLACK;
				G->colour = RED;
				U->colour = BLACK;

				insertionBalance(set, G);
			}
		}
	}
}

static void deletionBalance(Set* set, Node* X) {
	Node* P = X->parent;

	if (P) {
		Node *S, *S1, *S2;

		if (isRightChild(X, P)) {
			S = P->leftChild;
			S1 = S->rightChild;
			S2 = S->leftChild;
		}
		else {
			S = P->rightChild;
			S1 = S->leftChild;
			S2 = S->rightChild;
		}

		if (isBlack(S)) {
			if (isBlack(S1)) {
				if (isBlack(S2)) {
					S->colour = RED;

					if (isBlack(P))
						P->colour = BLACK;
					else 
						deletionBalance(set, P);
				}
				else {
					smallRotation(set, S);

					S->colour = P->colour;
					S2->colour = BLACK;
					P->colour = BLACK;
				}
			}
			else {
				bigRotation(set, S1);

				S1->colour = P->colour;
				P->colour = BLACK;
			}
		}
		else {
			smallRotation(set, S);

			S->colour = BLACK;
			P->colour = RED;

			deletionBalance(set, X);
		}
	}
}


static void removeNode(Set* set, Node* X, void* (*destroy)(void*)) {

	if (X) {
		if (X->rightChild) {
			Node* substitute = X->rightChild;

			while (substitute->leftChild)
				substitute = substitute->leftChild;

			X->data = substitute->data;
			X->key = substitute->key;

			removeNode(set, substitute, destroy);
		}
		else {
			set->itemCount--;
			climbAndUpdateLeftBranchSize(X, -1);

			if (X->leftChild) {
				Node* substitude = X->leftChild;

				X->data = substitude->data;
				X->key = substitude->key;
				X->leftBranchSize = 0;

				deleteNode(set, substitude, destroy);

			}
			else {

				if (X->colour == BLACK)
					deletionBalance(set, X);

				deleteNode(set, X, destroy);
			}
		}
	}
}