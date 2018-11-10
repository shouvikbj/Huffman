#pragma once

#include <cstdint>
#include <memory>
#include <queue>
#include <vector>
#include "CodeTree.hpp"


class FrequencyTable final {
	
	/*---- Field and constructor ----*/
	
	// Length at least 2.
	private: std::vector<std::uint32_t> frequencies;
	
	
	// Constructs a frequency table from the given array of frequencies.
	// The array length must be at least 2, and each value must be non-negative.
	public: explicit FrequencyTable(const std::vector<std::uint32_t> &freqs);
	
	
	
	/*---- Basic methods ----*/
	
	// Returns the number of symbols in this frequency table. The result is always at least 2.
	public: std::uint32_t getSymbolLimit() const;
	
	
	// Returns the frequency of the given symbol in this frequency table.
	public: std::uint32_t get(std::uint32_t symbol) const;
	
	
	// Sets the frequency of the given symbol in this frequency table to the given value.
	public: void set(std::uint32_t symbol, std::uint32_t freq);
	
	
	// Increments the frequency of the given symbol in this frequency table.
	public: void increment(std::uint32_t symbol);
	
	
	
	/*---- Advanced methods ----*/
	
	// Returns a code tree that is optimal for the symbol frequencies in this table.

	public: CodeTree buildCodeTree() const;
	
	
	// Helper structure for buildCodeTree()
	private: class NodeWithFrequency {
		
		public: std::unique_ptr<Node> node;
		public: std::uint32_t lowestSymbol;
		public: std::uint64_t frequency;  // Using wider type prevents overflow
		
		
		public: explicit NodeWithFrequency(Node *nd, std::uint32_t lowSym, std::uint64_t freq);
		
		
		// Sort by ascending frequency, breaking ties by ascending symbol value.
		public: bool operator<(const NodeWithFrequency &other) const;
		
	};
	
	
	private: static NodeWithFrequency popQueue(std::priority_queue<NodeWithFrequency> &pqueue);
	
};
