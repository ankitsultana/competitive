/* Author: Ankit Sultana
 * DS: Treap
 * * * * * * * * * * * * */
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cassert>
#define MAXN 200003

using namespace std;

struct node {  // val is bst ordered, prior is heap ordered
    int val, prior, size, data;
    node *l, *r;
};
typedef node* pnode;

int deadpool = 0;

int sz(pnode t) {
    return t ? t->size: 0;
}
void upd_sz(pnode t) {
    if(t) t->size = sz(t->l) + 1 + sz(t->r);
}
void split(pnode t, pnode &l, pnode &r, int key) {
    if(!t) l = r = NULL;
    else if(t->val <= key)  split(t->r, t->r, r, key), l = t; // going right
    else split(t->l, l, t->l, key), r = t;                    // going left
    upd_sz(t);
}
void merge(pnode &t, pnode l, pnode r) {
    if(!l || !r) t = l ? l: r;
    else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    upd_sz(t);
}
void insert(pnode &t, pnode it) {
    if(!t)  t = it;
    else if(it->prior > t->prior) split(t, it->l, it->r, it->val), t = it;
    else insert(t->val <= it->val ? t->r: t->l, it);
    upd_sz(t);
}
void erase(pnode &t, int key) {
    if(!t)  return ;
    else if(t->val == key) { pnode temp=t; merge(t, t->l, t->r); free(temp); }
    else erase(t->val < key ? t->r: t->l, key);
    upd_sz(t);
}
pnode kth(pnode root, int k) {
    if(!root->l and !root->r)   return root;
    else if(!root->l || !root->r) {
        if(!root->l) {
            if(k == 1)  return root;
            return kth(root->r, k-1);
        } else {
            if(root->l->size + 1 == k)  return root;
            return kth(root->l, k);
        }
    } else if(root->l->size < k) {
        k -= root->l->size + 1;
        if(k == 0)  return root;
        return kth(root->r, k);
    } else {
        return kth(root->l, k);
    }
    return NULL;
}
pnode get_new_node(int val, int data) {
    pnode temp = new node();
    temp->val = val;
    temp->data = data;
    temp->size = 1;
    temp->l = temp->r = NULL;
    temp->prior = rand();
    return temp;
}

void inorder(pnode t) {
    if(t == NULL)   return ;
    printf("DEBUG: %d %d\n", t->val, t->data);
    inorder(t->l);
    inorder(t->r);
}

int main() {
    pnode root = NULL;
    int t, n, q, temp;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d:\n", tc);
        scanf("%d %d", &n, &q);
        deadpool = 0;
        pnode root = NULL;
        for(int i = 0; i < n; i++) {
            scanf("%d", &temp);
            insert(root, get_new_node(deadpool++, temp));
        }
        char opt;
        int x;
        while(q--) {
            scanf("\n%c %d", &opt, &x);
            if(opt == 'c') {
                if(!root || x > root->size) {
                    printf("none\n");
                } else {
                    pnode temp = kth(root, x);
                    printf("%d\n", temp->data);
                    erase(root, temp->val);
                }
            } else {
                insert(root, get_new_node(deadpool++, x));
            }
        }
    }
    return 0;
}
