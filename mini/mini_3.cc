#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
#define enc pair<int, int>
/*
struct compare
{
    bool operator()(auto a, auto b)
    {
	return a.first > b.first;
    }
};*/
typedef struct HuffmanTree
{
    int frequency;
    int index;
    HuffmanTree *left;
    HuffmanTree *right;
    HuffmanTree(int fr=0, int idx=-1, HuffmanTree *l = nullptr, HuffmanTree *r = nullptr): frequency(fr), index(idx), left(l), right(r) {};
}Tree, *ptrTree;
struct compare
{
    bool operator() (Tree *a, Tree *b)
    {
        return a->frequency > b->frequency;  // 升序排列
    }
};
priority_queue<ptrTree, vector<ptrTree>, compare > pile;

void Encode(Tree *target, string str, string *tablet)
{
    if(target->left)
    {
	string temp = str;
	temp += '0';
	Encode(target->left, temp, tablet);
    }
    if(target->right)
    {
	string temp = str;
	temp+='1';
	Encode(target->right, temp, tablet);
    }

    if(!target->left && !target->right)
    {
	int idx = target->index;
	tablet[idx] = str;
    }
}
void del(Tree *tree)
{
    if (tree == nullptr)
    {
        return;
    }
    del(tree->left);
    del(tree->right);

    delete tree;
}
void Huffman()
{
    int n;
    cin >> n;
    string tablet[n];
    for(int i=0;i<n;i++)
    {
	tablet[i] = "";
	Tree *tree = new HuffmanTree;
	int temp;
	cin >> temp;
	tree->frequency = temp;
	tree->index = i;
	pile.push(tree);
    }
    if(n==1)
    {
	cout << "0";
	return;
    }
    while(pile.size()>1)
    {
	Tree *newnode = new HuffmanTree;
	ptrTree leftBranch, rightBranch;
	leftBranch = pile.top();
	pile.pop();
	rightBranch = pile.top();
	pile.pop();
	newnode->frequency = leftBranch->frequency + rightBranch->frequency;
	newnode->left = leftBranch;
	newnode->right = rightBranch;
	pile.push(newnode);
    }
    string s = "";
    Encode(pile.top(), s, tablet);
    del(pile.top());
    for(int i=0;i<n;i++)
    {
	cout << tablet[i] << endl;
    }
}

int main()
{
    Huffman();
    return 0;
}
