#pragma once

#include <cstdint>
#include <vector>
#include "CodeTree.hpp"


/* 
 * A canonical Huffman code, which only describes the code length of each symbol.
 * Code length 0 means no code for the symbol.
*/
class CanonicalCode final {
		
	private:
		std::vector<std::uint32_t> codeLengths;
		
	// Constructs a canonical Huffman code from the given array of symbol code lengths.
	public:
		explicit CanonicalCode(const std::vector<std::uint32_t> &codeLens);
	
	
		// Builds a canonical Huffman code from the given code tree.
		explicit CanonicalCode(const CodeTree &tree, std::uint32_t symbolLimit);
	
	
		// Recursive helper method for the above constructor.
	private:
		void buildCodeLengths(const Node *node, std::uint32_t depth);
		
	// Returns the symbol limit for this canonical Huffman code.
	// Thus this code covers symbol values from 0 to symbolLimit&minus;1.
	public: std::uint32_t getSymbolLimit() const;
	
	
	// Returns the code length of the given symbol value. The result is 0
	// if the symbol has node code; otherwise the result is a positive number.
	public: std::uint32_t getCodeLength(std::uint32_t symbol) const;
	
	
	// Returns the canonical code tree for this canonical Huffman code.
	public: CodeTree toCodeTree() const;
	
};
