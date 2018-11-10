#pragma once

#include <cstdint>
#include <memory>
#include <vector>


/* 
 * A node in a code tree. This class has exactly two subclasses: InternalNode, Leaf.
 */
class Node {
	
	public: virtual ~Node() = 0;
		
};



/* 
 * A leaf node in a code tree. It has a symbol value.
 */
class Leaf final : public Node {
	
	public: std::uint32_t symbol;
	
	
	public: explicit Leaf(std::uint32_t sym);
	
};



/* 
 * An internal node in a code tree. It has two nodes as children.
 */
class InternalNode final : public Node {
	
	public: std::unique_ptr<Node> leftChild;  // Not null
	
	public: std::unique_ptr<Node> rightChild;  // Not null
	
	
	public: explicit InternalNode(std::unique_ptr<Node> &&left, std::unique_ptr<Node> &&right);
	
};



/* 
 * A binary tree that represents a mapping between symbols and binary strings.
 */
class CodeTree final {
	
	/*---- Fields ----*/
	
	public: InternalNode root;
	
	
	// Stores the code for each symbol, or null if the symbol has no code.
	// For example, if symbol 5 has code 10011, then codes.get(5) is the list [1,0,0,1,1].
	private: std::vector<std::vector<char> > codes;
	
	
	/*---- Constructor ----*/
	
	// Constructs a code tree from the given tree of nodes and given symbol limit.
	// Each symbol in the tree must have value strictly less than the symbol limit.
	public: explicit CodeTree(InternalNode &&rt, std::uint32_t symbolLimit);
	
	
	/*---- Methods ----*/
	
	// Recursive helper function for the constructor
	private: void buildCodeList(const Node *node, std::vector<char> &prefix);
	
	
	// Returns the Huffman code for the given symbol, which is a list of 0s and 1s.
	public: const std::vector<char> &getCode(std::uint32_t symbol) const;
	
};
