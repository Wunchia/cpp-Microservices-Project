#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};
 
bool checkTree(struct TreeNode* root) {
	if (root->left->val + root->right->val == root->val) {
		return true;
	}
	else {
		return false;
	}
}

int main(void) {

}
