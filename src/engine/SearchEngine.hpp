#ifndef _SEARCH_ENGINE_H_
#define _SEARCH_ENGINE_H_
#include "TicTacToeBoard.h"
#include <memory>
struct SearchTreeNode_T;
using Shared_TreeNode = std::shared_ptr<SearchTreeNode_T>;
using Weaked_TreeNode = std::weak_ptr<SearchTreeNode_T>;
const static int DEFAULT_VALUE = -114514;
const static int MIN_VALUE = -100;
const static int DRAW_VALUE = 0;
const static int MAX_VALUE = 100;

struct SearchTreeNode_T
{
	SearchTreeNode_T() {
		m_parent.reset();
		m_depth = 0;
		m_value = DEFAULT_VALUE;
		m_playSide = ChessTypes_T::None_Type;
		m_sons.clear();
	}
	Weaked_TreeNode m_parent;
	int m_depth;
	TicTacToeBoard_T m_board;
	int m_value;
	ChessTypes_T m_playSide;
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
	bool CalculateAllNodes();
	void PrintAllMoveWays();
	bool CalculateValue(Shared_TreeNode node);
	void PrintFillNode(Shared_TreeNode node);
	std::shared_ptr<SearchTreeNode_T> m_root;
	std::vector<Shared_TreeNode> m_allLeaves;
	std::vector<TicTacToeBoard_T> m_allBoards;
};
#endif