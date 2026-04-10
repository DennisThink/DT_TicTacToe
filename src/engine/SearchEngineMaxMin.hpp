#ifndef _SEARCH_ENGINE_H_
#define _SEARCH_ENGINE_H_
#include "TicTacToeBoard.h"
#include "SearchEngineBase.hpp"
class CSearchEngineMaxMin
{
public:
	GridType_T GetMove(const TicTacToeBoard_T& board,const ChessTypes_T side);
	bool Clean();
private:
	bool CreatNote(const TicTacToeBoard_T& board);
	bool FillNode(Shared_TreeNode node,const ChessTypes_T playSide,const ChessTypes_T side,const int depth);
	bool IsFillEnd(Shared_TreeNode node)const;
	bool CalculateAllNodes();
	void PrintAllMoveWays();
	bool CalculateLeafValue(Shared_TreeNode& node);
	ChessTypes_T GetOtherSide(const ChessTypes_T& side);
	bool CalculateNodeValue(Shared_TreeNode& node);
	bool CalculateTreeNodeValue(Shared_TreeNode& node);
	void PrintFillNode(Shared_TreeNode node)const;
	void PrintNodeSons(Shared_TreeNode node)const;
	void PrintSingleNode(Shared_TreeNode node)const;
	bool CheckSaveLevelNodes(const std::vector<Shared_TreeNode>& nodes)const;
	bool CalculateLevelNodes(std::vector<Shared_TreeNode>& nodes);
	std::shared_ptr<SearchTreeNode_T> m_root;
	std::vector<Shared_TreeNode> m_allLeaves;
	ChessTypes_T m_moveSide;
	std::vector<TicTacToeBoard_T> m_allBoards;
};
#endif