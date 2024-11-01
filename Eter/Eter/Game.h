#pragma once

#include <iostream>
#include <vector>
#include <stack>


using gameboard = std::vector<std::vector<std::stack<Card>>>;
struct pairHash
{
	std::size_t operator()(const std::pair<int, int>& p) const
	{
		std::size_t h1 = std::hash<int>{}(p.first);
		std::size_t h2 = std::hash<int>{}(p.second);
		return h1 ^ (h2 << 1);
	}

};