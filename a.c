// #include "gtest/gtest.h"

// #include "tree.h"
// #include "tree_printer.h"
// #include "binary_tree.h"


// template<typename N>


// auto to_string (const N& node) {
//     std::stringstream ss;
//     ss << std::endl;
//     ss << node;
//     return ss.str();
// }

// TEST(Tree_printer_test, arbitrary_tree)
// {
//     using node = Array_tree_node<int>;
//     using nodes = Array<node>;

//     node n(1);
//     ASSERT_EQ(to_string(n), "\n1");

//     n = {1, nodes::build_array(11)};
//     ASSERT_EQ(to_string(n), R"(\n 1\n │\n11)");

//     std::stringstream ss;
//     ss << std::endl;
//     for (auto& s : Tree_printer<node>::default_instance().compose_text_lines(n))
//         ss << s << std::endl;

//     ASSERT_EQ(ss.str(), R"(\n 1\n │\n11\n)");

//     n = {1, nodes::build_array(1, 2)};
//     ASSERT_EQ(to_string(n), R"(\n  1\n┌─┴┐\n1  2)");

//     n = {1, nodes::build_array(node(1, nodes::build_array(4)), 2, 3)};
//     ASSERT_EQ(to_string(n), R"(\n   1\n┌──┼──┐\n1  2  3\n│\n4)");

//     n = {1, nodes::build_array(
//             node(11, nodes::build_array(111, 112, 113)),
//             node(12, nodes::build_array(121, 122)),
//             node(13, nodes::build_array(
//                     node(131, nodes::build_array(1311, 1312, 1313)),
//                     132, 133))
//             )};

//     ASSERT_EQ(to_string(n), R"(\n                   1\n      ┌────────────┼───────────┐\n     11           12          13\n ┌────┼────┐    ┌──┴─┐    ┌────┼────┐\n111  112  113  121  122  131  132  133\n                    ┌─────┼─────┐\n                  1311  1312  1313)");

//     n = {1, nodes::build_array(
//             node(11, nodes::build_array(111, 112, 113)),
//             node(12, nodes::build_array(
//                     121, 
//                     node(122, nodes::build_array(1221, 1222, 1223)))),
//             node(13, nodes::build_array(
//                     node(131, nodes::build_array(1311, 1312, 1313)),
//                     node(132, nodes::build_array(1321, 1322)),
//                     133))
//             )};
//     ASSERT_EQ(to_string(n), R"(\n                            1\n      ┌────────────┬────────┴────────────────────┐\n     11           12                            13\n ┌────┼────┐    ┌──┴─┐                 ┌─────────┴────┬────┐\n111  112  113  121  122               131            132  133\n               ┌─────┼─────┐     ┌─────┼─────┐     ┌──┴──┐\n             1221  1222  1223  1311  1312  1313  1321  1322)");

//     n = {7, nodes::build_array(
//             node(5, nodes::build_array(
//                     node(2, nodes::build_array(
//                             node(3, nodes::build_array(4, 9)))),
//                     6)), 
//             node(8, nodes::build_array(0)))
//     };

//     ASSERT_EQ(to_string(n), R"(\n      7\n    ┌─┴─┐\n    5   8\n  ┌─┴┐  │\n  2  6  0\n  │\n  3\n┌─┴┐\n4  9)");
// }

// TEST(Tree_printer_test, binary_tree) {
//     using node = Binary_tree_node<int>;
//     node n = {1, 
//         new node(
//             11, nullptr, 
//             new node(112, nullptr, new node(1122))), 
//         new node(
//             12, nullptr, 
//             new node(122, nullptr, new node(1222))), 
//     };
//     ASSERT_EQ(to_string(n), R"(\n       1\n  ┌────┴───┐\n 11       12\n┌─┴─┐   ┌──┴─┐\n   112      122\n ┌──┴─┐   ┌──┴─┐\n    1122     1222)");
//     n = {1, 
//         new node(
//             11, nullptr, 
//             new node(112, new node(1121), new node(1122))), 
//         new node(
//             12, nullptr, 
//             new node(122, new node(1221), new node(1222))), 
//     };
//     ASSERT_EQ(to_string(n), R"(\n        1\n   ┌────┴────┐\n  11        12\n┌──┴─┐   ┌───┴───┐\n    112         122\n  ┌──┴──┐     ┌──┴──┐\n1121  1122  1221  1222)");
// }



































































#include <stdio.h>
#include <stdlib.h>

// Define a basic tree node
typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new tree node
TreeNode* createTreeNode(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to print the tree recursively
void printTree(const char* prefix, TreeNode* parent, int isLeft, int isRoot) {
    if (parent == NULL)
        return;

    if (isRoot) {
        printf("─────>");
    } else {
        printf("%s%s", prefix, (isLeft ? "L├────>" : "R└────>"));
    }

    printf("(%d)\n", parent->value);

    char newPrefix[255];
    sprintf(newPrefix, "%s%s", prefix, (isLeft ? " │   " : "    "));

    printTree(newPrefix, parent->left, 1, 0);
    printTree(newPrefix, parent->right, 0, 0);
}

// Function to print the tree (entry point)
void print(TreeNode* root) {
    printTree("", root, 0, 1);
}

// Example usage
int main() {
    // Create a sample tree
    TreeNode* root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
	root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);

	root->right->left->left = createTreeNode(6);
	root->right->left->right = createTreeNode(6);
	root->right->right->left = createTreeNode(7);
	root->right->right->right = createTreeNode(7);
    // Print the tree
    print(root);

    // Free allocated memory
    // Note: In a real application, you should free the entire tree.
    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
