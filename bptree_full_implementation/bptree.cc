#include "bptree.h"
#include <vector>
#include <sys/time.h>

void
print_temp(TEMP t)
{
	int i;
	for (i = 0; i < t.nkey; i++) {
		printf("[%p]", t.chi[i]);
		printf("%d", t.key[i]);
	}
	printf("[%p]\n", t.chi[i]);
}

void
print_node(NODE *n)
{
	int i;
	for (i = 0; i < n->nkey; i++) {
		printf("[%p]", n->chi[i]);
		printf("%d", n->key[i]);
	}
	printf("[%p]\n", n->chi[i]);
}

void
print_tree_core(NODE *n)
{
	printf("[");fflush(stdout);
	for (int i = 0; i < n->nkey; i++) {
		if (!n->isLeaf) print_tree_core(n->chi[i]);
		printf("%d", n->key[i]);fflush(stdout);
		if (i != n->nkey-1 && n->isLeaf) putchar(' ');
	}
	if (!n->isLeaf) print_tree_core(n->chi[n->nkey]);
	printf("]");fflush(stdout);
}

void
print_tree(NODE *node)
{
	print_tree_core(node);
	printf("\n"); fflush(stdout);
}

NODE *
alloc_leaf(NODE *parent)
{
	NODE *node;
	if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
	node->isLeaf = true;
	node->parent = parent;
	node->nkey = 0;

	return node;
}

NODE *
alloc_internal(NODE *parent)
{
	NODE *node;
	if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
	node->isLeaf = false;
	node->parent = parent;
	node->nkey = 0;

	return node;
}

NODE *
//rs_key right small
alloc_root(NODE *left, int rs_key, NODE *right)
{
  NODE *node;
  if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
  node->parent = NULL;
  node->isLeaf = false; //this is a parent node
  node->key[0] = rs_key;
  node->chi[0] = left;
  node->chi[1] = right;
  node->nkey = 1;

  return node;
}

NODE *
find_leaf(NODE *node, int key)
{
	int kid;

	if (node->isLeaf) return node;
	for (kid = 0; kid < node->nkey; kid++) {
		if (key < node->key[kid]) break;
	}

	return find_leaf(node->chi[kid], key);
}

NODE *
insert_in_leaf(NODE *leaf, int key, DATA *data)
{
	int i;
	if (key < leaf->key[0]) {
		for (i = leaf->nkey; i > 0; i--) {
			leaf->chi[i] = leaf->chi[i-1] ;
			leaf->key[i] = leaf->key[i-1] ;
		}
		leaf->key[0] = key;
		leaf->chi[0] = (NODE *)data;
	}
	else {
    // Step 1: Find the place to insert
		for (i = 0; i < leaf->nkey; i++) {
			if (key < leaf->key[i]) break;
		}

    // Step 2: Shift and insert
		for (int j = leaf->nkey; j > i; j--) {
			leaf->chi[j] = leaf->chi[j-1] ;
			leaf->key[j] = leaf->key[j-1] ;
		}
		leaf->key[i] = key;
		leaf->chi[i] = (NODE *)data;
	}
	leaf->nkey++;

	return leaf;
}

void
copy_from_left_to_temp(TEMP *temp, NODE *left)
{
  // Step 1
  int i;
  bzero(temp, sizeof(TEMP));
  for (i = 0; i < N - 1; i++) {
    temp->chi[i] = left->chi[i];
    temp->key[i] = left->key[i];
  }
  temp->nkey = N - 1;
  temp->chi[i] = left->chi[i];
}

void //if temp contains leaves len(key) == len(chi)
insert_in_temp(TEMP *temp, int key, void *ptr)
{
  // Step 2
  int i;
  if (key < temp->key[0]) {
    for (i = temp->nkey; i > 0; i--) {
      temp->chi[i] = temp->chi[i-1] ;
      temp->key[i] = temp->key[i-1] ;
    }
    temp->key[0] = key;
    temp->chi[0] = (NODE *)ptr;
  }
  else {
    // Find the place to insert
      for (i = 0; i < temp->nkey; i++) {
        if (key < temp->key[i]) break;
      }

    // Shift and insert
    for (int j = temp->nkey; j > i; j--) {
      temp->chi[j] = temp->chi[j-1] ;
      temp->key[j] = temp->key[j-1] ;
    }
    temp->key[i] = key;
    temp->chi[i] = (NODE *)ptr;
  }
  temp->nkey++;
}

void //if temp contains parent, len(key) + 1 == len(chi)
insert_in_temp_after_left(TEMP *temp, NODE *left, int key, void *ptr)
{
  int i; // Find the place to insert
  for (i = 0; i <= temp->nkey; i++) {
    if (temp->chi[i] == left) break;
  }

  int j; // Shift and insert
  temp->chi[temp->nkey + 1] = temp->chi[temp->nkey];
  for (j = temp->nkey; j > i; j--) {
    temp->chi[j] = temp->chi[j-1] ;
    temp->key[j] = temp->key[j-1] ;
  }
  temp->key[j] = temp->key[j-1];
  temp->key[i] = key;
  temp->chi[i+1] = (NODE *)ptr;
  temp->nkey++;
}

void
erase_entries(NODE *node)
{
  // Step 4
  for (int i = 0; i < node->nkey; i++) {
    node->key[i] = -1;
  }
  for (int i = 0; i < node->nkey + 1; i++) {
    node->chi[i] = NULL;
  }
	node->nkey = 0;
}

void
copy_from_temp_to_left(TEMP temp, NODE *left)
{
  // Step 5
  for (int i = 0; i < (int)ceil(N/2); i++) {
    left->chi[i] = temp.chi[i];
    left->key[i] = temp.key[i];
  }
  left->nkey = (int)ceil(N/2);
}

void
copy_from_temp_to_right(TEMP temp, NODE *right)
{
  // Step 6
  for (int i = 0; i < (int)ceil(N/2); i++) {
    right->chi[i] = temp.chi[(int)ceil(N/2) + i];
    right->key[i] = temp.key[(int)ceil(N/2) + i];
  }
  right->nkey = (int)ceil(N/2);
}

void
copy_from_temp_to_left_parent(TEMP *temp, NODE *left)
{
  // Step 5
  int i;
  for (i = 0; i < (int)ceil((N+1)/2); i++) {
    left->chi[i] = temp->chi[i];
    left->key[i] = temp->key[i];
    left->nkey++;
    left->chi[i]->parent = left;
  }
  left->chi[i] = temp->chi[i];
  left->chi[i]->parent = left;
}

void
copy_from_temp_to_right_parent(TEMP *temp, NODE *right)
{
  // Step 6
  int i;
  for (i = 0; i < (int)ceil((N+1)/2) - 1; i++) {
    right->chi[i] = temp->chi[(int)ceil((N+1)/2) + i + 1];
    right->key[i] = temp->key[(int)ceil((N+1)/2) + i + 1];
    right->nkey++;
    right->chi[i]->parent = right;
  }
  right->chi[i] = temp->chi[(int)ceil((N+1)/2) + i + 1];
  right->chi[i]->parent = right;
}

void
insert_after_left_child(NODE *parent, NODE *left, int rs_key, NODE *right) {
  int lid = 0;
  int rid = 0;
  int i;
  // find left child pointer in parent
  for (i = 0; i < parent->nkey + 1; i++) {
    if (parent->chi[i] == left){
      lid = i;
      rid = lid + 1;
      break;
    }
  } assert(i != parent->nkey + 1);
  // shift keys and childs in parent
  for (i = parent->nkey + 1; i > rid; i--) {
    parent->chi[i] = parent->chi[i - 1];
  }
  for (i = parent->nkey; i > lid; i--) {
    parent->key[i] = parent->key[i - 1];
  }
  // insert new keys and childs
  parent->key[lid] = rs_key;
  parent->chi[rid] = right;
  parent->nkey++;
}

void
insert_in_parent(NODE *left_child, int rs_key, NODE *right_child)
{
  // Step 8
  // printf("RS_Key: "); printf("%d\n", rs_key);
  // printf("Left Child:  "); print_node(left_child);
  // printf("Right Child: "); print_node(right_child);

  if (Root == left_child) {
    Root = alloc_root(left_child, rs_key, right_child);
    left_child->parent = right_child->parent = Root;
    return;
  }
  NODE *left_parent = left_child->parent;
  if (left_parent->nkey < N - 1){
    insert_after_left_child(left_parent, left_child, rs_key, right_child);
  }
  else {
    TEMP temp;
    copy_from_left_to_temp(&temp, left_parent);
    insert_in_temp_after_left(&temp, left_child, rs_key, right_child);
    erase_entries(left_parent);
    NODE *right_parent = alloc_internal(left_parent->parent);
    copy_from_temp_to_left_parent(&temp, left_parent);
    int new_rs_key = temp.key[(int)ceil((N+1)/2)];
    copy_from_temp_to_right_parent(&temp, right_parent);

    // printf("Temp: "); print_temp(temp);
    // printf("Left Parent: "); print_node(left_parent);
    // printf("Right Parent: "); print_node(right_parent);

    insert_in_parent(left_parent, new_rs_key, right_parent);
  }
}

void
insert(int key, DATA *data)
{
	NODE *leaf;

	if (Root == NULL) {
		leaf = alloc_leaf(NULL);
		Root = leaf;
	}
	else {
		leaf = find_leaf(Root, key);
	}

	if (leaf->nkey < (N-1)) {
		insert_in_leaf(leaf, key, data);
	}
	else { // split
		NODE *left = leaf;
		NODE *right = alloc_leaf(leaf->parent);
		TEMP temp;

		copy_from_left_to_temp(&temp, left);   // 0
		insert_in_temp(&temp, key, data);      // 1
		right->chi[N-1] = left->chi[N-1];	     // 2
		left->chi[N-1] = right;                // 3
		erase_entries(left);                   // 4
		copy_from_temp_to_left(temp, left);    // 5
		copy_from_temp_to_right(temp, right);  // 6
		int rs_key = right->key[0];            // 7
		insert_in_parent(left, rs_key, right); // 8
	}
}

void
init_root(void)
{
	Root = NULL;
}

/*
void
search_core(const int key)
{
  NODE *n = find_leaf(Root, key);
	for (int i = 0; i < n->nkey+1; i++) {
		if (n->key[i] == key) return;
	}
  cout << "Key not found: " << key << endl;
	ERR;
}
*/

int
interactive()
{
  int key;

  std::cout << "Key: ";
  std::cin >> key;

  return key;
}

int
main(int argc, char *argv[])
{
	init_root();

  for (int i=0; i<100*100; i++) {
		// insert(interactive(), NULL);
    insert(i, NULL);
    print_tree(Root);
  }

	return 0;
}
