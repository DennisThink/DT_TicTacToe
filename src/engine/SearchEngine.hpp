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
static int M_ID = 0;
struct SearchTreeNode_T
{
	SearchTreeNode_T() {
		m_id = M_ID;
		M_ID++;
		m_parent.reset();
		m_depth = 0;
		m_bValueCalculated = false;
		m_value = DEFAULT_VALUE;
		m_bIsLeaf = false;
		m_playSide = ChessTypes_T::None_Type;
		m_sons.clear();
	}
	Weaked_TreeNode m_parent;
	int m_depth;
	TicTacToeBoard_T m_board;
	bool m_bValueCalculated;
	bool m_bIsLeaf;
	int m_id;
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