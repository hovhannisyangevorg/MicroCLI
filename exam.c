/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:19:41 by gevorg            #+#    #+#             */
/*   Updated: 2023/09/09 15:13:05 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// typedef struct s_node t_node;
// typedef struct s_data t_data;

// struct s_node
// {
//     t_data data;
//     struct s_node* left;
//     struct s_node* right;
// };

// struct s_data
// {
//     int index;
// };


// void	ft_panic(char *mess)
// {
// 	fprintf(stderr, mess);
//     exit(0);
// }

// t_node *ft_create_node(t_data data)
// {
// 	t_node *root = (t_node *)malloc(sizeof(t_node));
// 	if(!root)
// 		return (NULL);
// 	root->data = data;
// 	root->left = NULL;
// 	root->right = NULL;
// 	return (root);
// }

// t_node	*ft_insert_node(t_node *root, t_data data)
// {
// 	if (!root)
// 		return (ft_create_node(root->data));
// 	if (root->data.index < data.index)
// 		root->left = ft_insert_node(root->left, data);
// 	else if (root->data.index > data.index)
// 		root->right = ft_insert_node(root->right, data);
// 	return (root);
// }

// t_node	*ft_traversal(t_node *root, t_data data)
// {
// 	if (root)
// 	{
// 		ft_traversal(root->left, data);
// 		ft_traversal(root->right, data);
// 	}
// }











#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* insertNode(struct TreeNode* root, int data) {
    if (root == NULL)
        return (createNode(data));

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return (root);
}

void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct TreeNode* root = NULL;

    root = insertNode(root, 1);
    root = insertNode(root, 2);
    root = insertNode(root, 3);
    root = insertNode(root, 4);
    root = insertNode(root, 5);
	root = insertNode(root, 6);
    root = insertNode(root, 7);
    root = insertNode(root, 8);
	root = insertNode(root, 9);
    root = insertNode(root, 10);
    root = insertNode(root, 11);

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Don't forget to free the allocated memory when done with the tree
    // In a real program, you should have a proper memory management strategy.
    return 0;
}

