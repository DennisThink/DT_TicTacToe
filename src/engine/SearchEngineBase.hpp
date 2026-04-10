#ifndef _SEARCH_ENGINE_BASE_H_
#define _SEARCH_ENGINE_BASE_H_
#include <memory>
#include <vector>
#include "types_tictactoe.hpp"
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
	virtual ~SearchTreeNode_T() {
		//std::cout << "ID destroy: " << m_id << std::endl;
	}
	Weaked_TreeNode m_parent;
	GridType_T m_moveGrid;
	int m_depth;
	TicTacToeBoard_T m_board;
	bool m_bValueCalculated;
	bool m_bIsLeaf;
	int m_id;
	int m_value;
	ChessTypes_T m_playSide;
	std::vector<Shared_TreeNode> m_sons;
};

class SearchEngineBase
{
public:
	SearchEngineBase();
	virtual GridType_T GetMove(const TicTacToeBoard_T& board, const ChessTypes_T side);
};
#endif