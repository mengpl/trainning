#ifndef __GAME_OF_LIFE_HPP__
#define __GAME_OF_LIFE_HPP__ 

#include <vector>
#include <utility>
#include <iostream>

#define GAME_OVER  -1
#define GAME_OK 0

typedef std::pair<int,int> IntPair;
typedef std::vector<char> charVector;
typedef std::vector<charVector> charMatrix;

void printf_matrix(const charMatrix & cMatrix);

bool is_matrixCorrect(const charMatrix & cMatrix);

int get_liveNeighboursNum(const charMatrix & cMatrix,int i,int j);

void change_life(charMatrix & cMatrix,
	const std::vector<IntPair> & deadToliveVector,
	const std::vector<IntPair> & liveToDeadVector);	

int calculate_next_generation(charMatrix & cMatrix);


#endif