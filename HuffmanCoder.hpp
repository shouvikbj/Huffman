#pragma once

#include "BitIoStream.hpp"
#include "CodeTree.hpp"


/* 
 * Reads from a Huffman-coded bit stream and decodes symbols.
 */
class HuffmanDecoder final {	
	// The underlying bit input stream.
	private: BitInputStream &input;
	
	// The code tree to use in the next read() operation. Must be given a non-null value
	// before calling read(). The tree can be changed after each symbol decoded, as long
	// as the encoder and decoder have the same tree at the same point in the code stream.
	public:
		const CodeTree *codeTree;
		// Constructs a Huffman decoder based on the given bit input stream.
		explicit HuffmanDecoder(BitInputStream &in);
		// Reads from the input stream to decode the next Huffman-coded symbol.
		int read();
	
};


/* 
 * Encodes symbols and writes to a Huffman-coded bit stream.
 */
class HuffmanEncoder final {
		
	// The underlying bit output stream.
	private:
		BitOutputStream &output;
	
	// The code tree to use in the next write(uint32_t) operation. Must be given a non-null
	// value before calling write(). The tree can be changed after each symbol encoded, as long
	// as the encoder and decoder have the same tree at the same point in the code stream.
	public:
		const CodeTree *codeTree;
		
		// Constructs a Huffman encoder based on the given bit output stream.
		explicit HuffmanEncoder(BitOutputStream &out);
		
		// Encodes the given symbol and writes to the Huffman-coded output stream.
		void write(std::uint32_t symbol);
	
};
