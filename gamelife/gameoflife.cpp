
#include "gameoflife.hpp"

void printf_matrix(const charMatrix & cMatrix)
{
	for(int i = 0; i < cMatrix.size() ; ++i)
	{
		for(int j = 0; j < cMatrix[i].size(); ++j)
		{
			std::cout << cMatrix[i][j] ;
		}

		std::cout << "\n" << std::endl;
	}
}

bool is_matrixCorrect(const charMatrix & cMatrix)
{
	if(!cMatrix.empty())
	{
		charMatrix::const_iterator it = cMatrix.begin();
		int iWith = it->size();
		int iWithTmp = 0;
		for(;it != cMatrix.end(); ++it)
		{
			iWithTmp = it->size();
			if(iWith != iWithTmp && iWith != 0 && iWithTmp != 0)
			{
				return false;
			}
		}
		return true;
	}

	return true;
}

int get_liveNeighboursNum(const charMatrix & cMatrix,int i,int j)
{
	using namespace std;
	int iLiveNeighboursNum = 0;
	vector<IntPair> offset;
	offset.push_back(make_pair(i-1,j-1)); // up left
	offset.push_back(make_pair(i-1,j));   // up
	offset.push_back(make_pair(i-1,j+1)); // up right
	offset.push_back(make_pair(i,j-1));   // left
	offset.push_back(make_pair(i,j+1));   // right
	offset.push_back(make_pair(i+1,j-1)); // down left
	offset.push_back(make_pair(i+1,j));   // down
	offset.push_back(make_pair(i+1,j+1)); // down right

	int iWith;
	int iLength;

	for(int i = 0; i < offset.size(); ++i)
	{
		iWith = offset.at(i).first;
		iLength = offset.at(i).second;
		if('*' == cMatrix[iWith][iLength])
		{
			iLiveNeighboursNum++;
		}
	}

	return iLiveNeighboursNum;
}

void change_life(charMatrix & cMatrix,
	const std::vector<IntPair> & deadToliveVector,
	const std::vector<IntPair> & liveToDeadVector)
{
	int iWidth ;
	int iLength ;
	// std::cout << deadToliveVector.size() << std::endl;
	// std::cout << liveToDeadVector.size() << std::endl;
	// change life in the matrix dead to live
	for(int i = 0; i < deadToliveVector.size(); ++i)
	{
		iWidth = deadToliveVector[i].first;
		iLength = deadToliveVector[i].second;

		cMatrix[iWidth][iLength] = '*';
	}

	// change life in the matrix live to dead
	for(int i = 0; i < liveToDeadVector.size(); ++i)
	{
		iWidth = liveToDeadVector[i].first;
		iLength = liveToDeadVector[i].second;

		cMatrix[iWidth][iLength] = '.';		
	}
}

int calculate_next_generation(charMatrix & cMatrix)
{
	//1 check charMatrix
	if(!is_matrixCorrect(cMatrix))
	{
		printf_matrix(cMatrix);
		std::cout << "Matrix is not correct ,please check the input params " << std::endl;
		return GAME_OVER;
	}

	int iLiveNeighboursNum = 0;

	// when loop the matrix ,do not modify life ,just put into this vector
	std::vector<IntPair> deadToliveVector; // some dead position need becomes live
	std::vector<IntPair> liveToDeadVector;     // some live position need becomes dead

	// loop the Matrix
	// case no life can exist off the edges,so we do not loop the edges,
	// loop from the position (1,1) to (cMatrix.size() -1,cMatrix[i].size() -1)
	for(int i = 1; i < cMatrix.size() -1 ; ++i)
	{
		for(int j = 1; j < cMatrix[i].size() -1; ++j)
		{
			if('*' == cMatrix[i][j])
			{
				iLiveNeighboursNum = get_liveNeighboursNum(cMatrix,i,j);
				
				if(iLiveNeighboursNum < 2)
				{
					// cMatrix[i][j] = '.';
					// std::cout << "iLiveNeighboursNum "<< std::endl;
					// std::cout << iLiveNeighboursNum << std::endl;
					// std::cout << "i = " << i << "j =	 " << j << std::endl;
 					liveToDeadVector.push_back(std::make_pair(i,j));
				}

				if(iLiveNeighboursNum > 3)
				{
					// cMatrix[i][j] = '.';
					std::cout << iLiveNeighboursNum << std::endl;	
					liveToDeadVector.push_back(std::make_pair(i,j));
				}
			}
			else if('.' == cMatrix[i][j])
			{
				iLiveNeighboursNum = get_liveNeighboursNum(cMatrix,i,j);

				if(iLiveNeighboursNum == 3)
				{
					// cMatrix[i][j] = '*';
					deadToliveVector.push_back(std::make_pair(i,j));
				}
			}
		}
	}

	change_life(cMatrix,deadToliveVector,liveToDeadVector);

	return GAME_OK;
}

// int main()
// {
// 	charMatrix cMatrix;
// 	charVector listChar;
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');

// 	cMatrix.push_back(listChar);

// 	listChar.clear();
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('*');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');

// 	cMatrix.push_back(listChar);

// 	listChar.clear();
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('*');
// 	listChar.push_back('*');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	cMatrix.push_back(listChar);

// 	listChar.clear();
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');
// 	listChar.push_back('.');

// 	cMatrix.push_back(listChar);

// 	std::cout << "input :" << std::endl;
// 	printf_matrix(cMatrix);

// 	calculate_next_generation(cMatrix);

// 	std::cout << "after :" << std::endl;

// 	printf_matrix(cMatrix);

	
// } 