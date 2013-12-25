// Binary Tree's ADT by recurse
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct tree {
  int element;
  struct tree *lchild;
  struct tree *rchild;
} tree;

tree *maketree(int elem) 
{
  tree *root = (tree *)malloc(sizeof(tree));
  assert (root != NULL && "malloc failed");
  root->element = elem;
  root->lchild = NULL;
  root->rchild = NULL;

  return root;
}

int containsnode(tree *T, int element)
{
  if (!T) {
    return 0;
  } 

  if (element < T->element) {
    containsnode(T->lchild, element);
  } else if (element > T->element){
    containsnode(T->rchild, element);
  } else {
    // find out
    return 1;
  }
}

tree *insertnode(tree *T, int element)
{
  if (containsnode(T, element) == 1) {
    printf("The node %d is exist, just ignore it\n", 
        element);
    return T;
  }

  tree *t = maketree(element);
  if (!T) {
    T = t;
  } else if (element < T->element) {
    // lvalue T is the father's node
    T->lchild = insertnode(T->lchild, element);
  } else {
    T->rchild = insertnode(T->rchild, element);
  }

  return T;
}

void printtree(tree *T)
{
  if (!T)  {
    return;
  }

  // inorder traversal 
  printtree(T->lchild);
  printf("%d\n", T->element);
  printtree(T->rchild);
}

// lchild is always less than
// root node.
int findMin(tree *T)
{
  if (T->lchild == NULL)
    return T->element;
  else 
    findMin(T->lchild);
}

// rchild is always greater than
// root node.
int findMax(tree *T)
{
  if (T->rchild == NULL)
    return T->element;
  else 
    findMax(T->rchild);
}

int treeheight(tree *T)
{
#define Max(i, k) ((i) > (k)) ? (i) : (k)
  if (!T) return 0;
  return Max(treeheight(T->lchild), treeheight(T->rchild)) + 1;
#undef Max
}

// In C++ is much convenient cause it is called 
// by reference
// No need to set return value;
tree *removenode(tree *T, int element)
{
  if (!T) {
    return NULL;
  } else if (T->element > element) {
    T->lchild = removenode(T->lchild, element);
  } else if (T->element < element) {
    T->rchild = removenode(T->rchild, element);
  } else if (T->element == element && !T->lchild && !T->rchild) {
    // The leaf node, just remove it.
    free(T);
    return NULL;
  } else if (T->element == element && T->lchild && T->rchild) {
    // If this node both has lchild and rchild, use the maximum node to replace
    // it in left sub-tree, and remove the replacement node in the left sub-tree.
    int lelement = findMax(T->lchild);
    printf("lelement is %d\n", lelement);
    T->element = lelement;
    T->lchild = removenode(T->lchild, lelement);
    // must be executed into the last else.
  } else {
    // If this node has lchild or rchild, father->child = T->child.
    tree *bak;
#if 0
    if (T->lchild) {
      bak = T->lchild;
      free(T);
    }
    else {
      bak = T->rchild;
      free(T);
    }
#else
    bak = T->lchild ? T->lchild : T->rchild;
    free(T);
#endif

    return bak; 
  }

  return T;
}

int main(void)
{
  int i;
  int arr[] = {5, 6, 4, 8, 9, 2, 1, 3, 7, 6}; 

  tree *root = maketree(arr[0]);
  for (i = 1; i < sizeof(arr)/sizeof(arr[1]); i++) {
    insertnode(root, arr[i]); 
  }
  printtree(root);
  printf("find out %d\n", containsnode(root, 4));
  printf("find out %d\n", containsnode(root, 12));
  printf("Min value is %d\n", findMin(root));
  printf("Max value is %d\n", findMax(root));
  printf("Tree height is %d\n", treeheight(root));
  removenode(root, 9);
  printtree(root);
  printf("----------------------------------\n");
  removenode(root, 5);
  printtree(root);

  return 0;
}
