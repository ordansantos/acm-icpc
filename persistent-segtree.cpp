#include <bits/stdc++.h>

using namespace std;

struct node {
    int qtd;
    node *l, *r;
    node (int qtd = 0, node* l = NULL, node* r = NULL) : l(l), r(r), qtd(qtd) {}
};

int get (node *root){
    return root? root->qtd : 0;
}

// NULL is a empty tree
// l = 1, r = n
// p is the position to modify
node* add (node *root, int l, int r, int p){
    if (p > r || p < l) return root;
    if (l == r)
        return new node (get(root) + 1);
    node *left = add(root ? root->l : NULL, l, (l+r)/2, p);
    node *right = add(root ? root->r : NULL, (l+r)/2 + 1, r, p);
    return new node (get(left) + get(right), left, right);
}

int query (node *root, int l, int r, int a, int b){
    if (!root) return 0;
    if (l > b || r < a) return 0;
    if (l >= a && r <= b) return get(root);
    return query (root->l, l, (l + r)/2, a, b) + query (root->r, (l + r)/2 + 1, r, a, b);
}

