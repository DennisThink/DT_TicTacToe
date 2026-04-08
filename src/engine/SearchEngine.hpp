#ifndef _SEARCH_ENGINE_H_
#define _SEARCH_ENGINE_H_
#include "TicTacToeBoard.h"
#include <memory>
struct SearchTreeNode_T;
using Shared_TreeNode = std::shared_ptr<SearchTreeNode_T>;
using Weaked_TreeNode = std::weak_ptr<SearchTreeNode_T>;
struct SearchTreeNode_T
{
	Weaked_TreeNode m_parent;
	int m_depth;
	TicTacToeBoard_T m_board;
	std::vector<Shared_TreeNode> m_sons;
};

class CSearchEngine
{
public:
	GridType_T GetMove(const TicTacToeBoard_T& board,const ChessTypes_T side);
private:
	bool CreatNote(const TicTacToeBoard_T& board);
	bool FillNode(Shared_TreeNode node,const ChessTypes_T playSide,const ChessTypes_T side,const int depth);
	bool IsFillEnd(Shared_TreeNode node, const ChessTypes_T playSide, const int depth)const;
	void PrintFillNode(Shared_TreeNode node);
	std::shared_ptr<SearchTreeNode_T> m_root;
	std::vector<TicTacToeBoard_T> m_allBoards;
};
#endif