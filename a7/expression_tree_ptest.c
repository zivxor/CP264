/*
 -------------------------------------------------------
 File:     expression_tree_ptest.c
 About:    public test driver
 Author:   HBF
 Version:  2026-02-24
 -------------------------------------------------------
 */
#include <stdio.h>
#include "expression_tree.h"

DATA tree_tests[] = { {'*',1}, {'+',1}, {'-',1}, {1,0}, {2,0}, {4,0}, {1,0} };
int bfs_tests[] = { '+', '-', 1, 10 };
int dfs_tests[] = { 3, '-', '*', '%'};


TNODE *root = NULL;

void search_info(char *sf, int key, TNODE *tnp) {
	if (tnp) {
		printf("\n%s(%d): ", sf, key);
		print_node(tnp);
	} else {
		printf("\n%s(%d): NULL", sf, key);
	}
}

void display_tree(TNODE *root, int pretype, int prelen) {
	if (root) {
		int i;
		for (i = 0; i < prelen; i++) {
			printf("%c", ' ');
		}
		if (pretype == 0)
			printf("%s", "|___:");
		else if (pretype == 1)
			printf("%s", "|___L:");
		else if (pretype == 2)
			printf("%s", "|___R:");

		print_node(root);
		printf("\n");
		display_tree(root->right, 2, prelen + 4);
		display_tree(root->left, 1, prelen + 4);
	}
}

void test_before() {
	printf("------------------\n");
	printf("Test start: create testing tree\n\n");
	int n = sizeof tree_tests / sizeof *tree_tests;
	for (int i = 0; i < n; i++) {
		insert_tree(&root, tree_tests[i]);
	}
	display_tree(root, 0, 0);
	printf("\n");
}

void test_end() {
	printf("------------------\n");
	printf("Test end: clean testing tree\n\n");
	clean_tree(&root);
	printf("\n");
}

void test_tree_info() {
	printf("------------------\n");
	printf("Test: tree_info\n\n");
	TINFO info = tree_info(root);
	printf("tree_info(%s).order: %d\n", "root", info.order);
	printf("tree_info(%s).height: %d\n", "root", info.height);
	printf("\n");
}

void test_preorder() {
	printf("------------------\n");
	printf("Test: preorder\n\n");
	printf("preorder(%s): ", "root");
	preorder(root);
	printf("\n");
}

void test_inorder() {
	printf("------------------\n");
	printf("Test: inorder\n\n");
	printf("inorder(%s): ", "root");
	inorder(root);
	printf("\n");
}

void test_postorder() {
	printf("------------------\n");
	printf("Test: postorder\n\n");
	printf("postorder(%s): ", "root");
	postorder(root);
	printf("\n");
}

void test_bforder() {
	printf("------------------\n");
	printf("Test: bforder\n\n");
	printf("bforder(root): ");
	bforder(root);
	printf("\n");
}

void test_display_infix() {
	printf("------------------\n");
	printf("Test: display_infix\n\n");
	printf("display_infix(root): ");
	display_infix(root);
	printf("\n");
}

void test_evaluate_tree() {
	printf("------------------\n");
	printf("Test: evaluate_tree\n\n");
	printf("evaluate_tree(root): %d\n", evaluate_tree(root));
}

void test_bfs() {
	printf("------------------\n");
	printf("Test: bfs\n\n");
	TNODE *tp = NULL;
	int n = sizeof bfs_tests / sizeof *bfs_tests;
	for (int i = 0; i < n; i++) {
		tp = bfs(root, bfs_tests[i]);
		search_info("bfs", bfs_tests[i], tp);
	}
	printf("\n");
}

void test_dfs() {
	printf("------------------\n");
	printf("Test: dfs\n\n");
	TNODE *tp = NULL;
	int n = sizeof dfs_tests / sizeof *dfs_tests;
	for (int i = 0; i < n; i++) {
		tp = dfs(root, dfs_tests[i]);
		search_info("dfs", dfs_tests[i], tp);
	}
	printf("\n");
}


int main() {
	test_before();
	test_tree_info();
	test_preorder();
	test_inorder();
	test_postorder();
	test_bforder();
	test_display_infix();
	test_evaluate_tree();
	test_bfs();
	test_dfs();
	test_end();

	return 0;
}


