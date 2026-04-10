#include "SearchEngineMaxMin.hpp"
#include <iostream>
GridType_T CSearchEngineMaxMin::GetMove(const TicTacToeBoard_T& board,const ChessTypes_T side)
{
	m_moveSide = side;
	m_root = nullptr;
	GridType_T result;
	
	auto newNode = std::make_shared<SearchTreeNode_T>();
	newNode->m_board = board;
	newNode->m_parent.reset();
	newNode->m_depth = 0;
	newNode->m_playSide = side;
	newNode->m_bValueCalculated = false;
	m_root = newNode;
	CreateSearchTree(newNode, side,side,1);
	CalculateValueOfSearchTree();
	int nValue = MIN_VALUE;
	for (auto item : m_root->m_sons)
	{
		if (item->m_value > nValue)
		{
			nValue = item->m_value;
			result = item->m_moveGrid;
		}
	}
	return result;
}
bool CSearchEngineMaxMin::IsBoardStateCheckMate(const Shared_TreeNode node)const
{
	CTicTacToeBoard board;
	board.SetBoard(node->m_board);
	ChessTypes_T otherSide = ChessTypes_T::None_Type;
	if (node->m_playSide == ChessTypes_T::X_Type)
	{
		otherSide = ChessTypes_T::O_Type;
	}
	if (node->m_playSide == ChessTypes_T::O_Type)
	{
		otherSide = ChessTypes_T::X_Type;
	}
	if (board.IsSideWin(node->m_playSide))
	{
		return true;
	}
	if (board.IsSideWin(otherSide))
	{
		return true;
	}
	auto allPos = board.GetAllPosibleGrids();
	if(allPos.empty())
	{
		return true;
	}
	return false;
}
bool CSearchEngineMaxMin::CheckSaveLevelNodes(const std::vector<Shared_TreeNode>& nodes)const
{
	for (const auto& item : nodes)
	{
		if (!item->m_bValueCalculated)
		{
			std::cout << "----------------------------------------------" << std::endl;
			PrintNodeSons(item);
			std::cout << "----------------------------------------------" << std::endl;
			PrintSingleNode(item);
			CTicTacToeBoard board;
			board.SetBoard(item->m_board);
			auto allPos = board.GetAllPosibleGrids();
			for (auto itemPos : allPos)
			{
				std::cout << itemPos._xPos << " " << itemPos._yPos << std::endl;
			}
			std::cout << "----------------------------------------------" << std::endl;
		}
	}
	return true;
}

bool CSearchEngineMaxMin::CalculateLevelNodes(std::vector<Shared_TreeNode>& nodes)
{
	for (auto& item : nodes)
	{
		if (!item->m_bValueCalculated)
		{
			CalculateNodeValue(item);
		}
	}
	return true;
}
void CSearchEngineMaxMin::PrintSingleNode(Shared_TreeNode node)const
{
	
	CTicTacToeBoard board;
	board.SetBoard(node->m_board);
	Shared_TreeNode parNode = node->m_parent.lock();
	int parId = -1;
	if (parNode)
	{
		parId = parNode->m_id;
	}
	std::cout << "ID: "<<node->m_id<<"  Parent ID: "<< parId << " Value: " << node->m_value << " Depth : " << node->m_depth << " Side : " << ToString(node->m_playSide) << " BCalue : " << node->m_bValueCalculated <<" BLeaf : "<<node->m_bIsLeaf <<" SonCount : "<<node->m_sons.size() << std::endl;
	board.PrintBoard();

}
void CSearchEngineMaxMin::PrintNodeSons(Shared_TreeNode node)const
{
	if (node)
	{
		if (!node->m_sons.empty())
		{
			for (auto item = node->m_sons.begin(); item != node->m_sons.end();item++)
			{
				PrintSingleNode(*item);
				PrintNodeSons(*item);
			}
		}
	}
	
}
void CSearchEngineMaxMin::PrintFillNode(Shared_TreeNode node)const
{
	std::cout << "---------------Print Fill Node------------------" << std::endl;
	std::vector<Shared_TreeNode> nodeVec;
	Shared_TreeNode curNode = node;
	while (curNode != nullptr)
	{
		nodeVec.push_back(curNode);
		curNode = curNode->m_parent.lock();
	}

	for (auto item = nodeVec.rbegin(); item != nodeVec.rend();item++)
	{
		CTicTacToeBoard board;
		board.SetBoard(item->get()->m_board);
		std::cout << " Value: " << item->get()->m_value <<" Depth: "<<item->get()->m_depth <<" Side: "<<ToString(item->get()->m_playSide) << std::endl;
		board.PrintBoard();
	}
	std::cout << "---------------Print Fill Node------------------" << std::endl;
}
bool CSearchEngineMaxMin::CalculateTreeNodeValue(Shared_TreeNode& node) const
{
	int nMinValue = MAX_VALUE;
	int nMaxValue = MIN_VALUE;
	bool bCanCalculated = true;
	if (node->m_playSide == m_moveSide)
	{
		for (auto sonItem : node->m_sons)
		{
			if (sonItem->m_bValueCalculated)
			{
				nMaxValue = std::max(nMaxValue, sonItem->m_value);
			}
			else
			{
				bCanCalculated = false;
				break;
			}
		}
		if (bCanCalculated)
		{
			node->m_value = nMaxValue;
			node->m_bValueCalculated = true;
		}
	}
	else
	{
		for (auto sonItem : node->m_sons)
		{
			if (sonItem->m_bValueCalculated)
			{
				nMinValue = std::min(nMinValue, sonItem->m_value);
			}
			else
			{
				bCanCalculated = false;
				break;
			}
		}
		if (bCanCalculated)
		{
			node->m_value = nMinValue;
			node->m_bValueCalculated = true;
		}
	}
	return bCanCalculated;
}

bool CSearchEngineMaxMin::CalculateNodeValue(Shared_TreeNode& node)const
{
	if (node->m_sons.empty())
	{
		bool bResult =  CalculateLeafNodeValue(node);
		if (node->m_value == DEFAULT_VALUE)
		{
			bResult = CalculateLeafNodeValue(node);
		}
	}
	else
	{
		bool bResult = CalculateTreeNodeValue(node);
		if (node->m_value == DEFAULT_VALUE)
		{
			bResult = CalculateTreeNodeValue(node);
		}
	}
	return true;
}

ChessTypes_T CSearchEngineMaxMin::GetOtherSide(const ChessTypes_T& side)
{
	ChessTypes_T otherSide = ChessTypes_T::None_Type;
	if (side == ChessTypes_T::X_Type)
	{
		otherSide = ChessTypes_T::O_Type;
	}
	if (side == ChessTypes_T::O_Type)
	{
		otherSide = ChessTypes_T::X_Type;
	}
	return otherSide;
}
bool CSearchEngineMaxMin::CalculateLeafNodeValue(Shared_TreeNode& node) const
{
	ChessTypes_T otherSide = ChessTypes_T::None_Type;
	if (node->m_playSide == ChessTypes_T::X_Type)
	{
		otherSide = ChessTypes_T::O_Type;
	}
	if (node->m_playSide == ChessTypes_T::O_Type)
	{
		otherSide = ChessTypes_T::X_Type;
	}
	CTicTacToeBoard board;
	board.SetBoard(node->m_board);
	if (node->m_playSide == m_moveSide)
	{
		if (board.IsSideWin(node->m_playSide))
		{
			node->m_value = MAX_VALUE;
			node->m_bValueCalculated = true;
		}
		else if (board.IsSideWin(otherSide))
		{
			node->m_value = MIN_VALUE;
			node->m_bValueCalculated = true;
		}
		else
		{
			node->m_value = DRAW_VALUE;
			node->m_bValueCalculated = true;
		}
	}
	else if (otherSide == m_moveSide)
	{
		if (board.IsSideWin(node->m_playSide))
		{
			node->m_value = MIN_VALUE;
			node->m_bValueCalculated = true;
		}
		else if (board.IsSideWin(otherSide))
		{
			node->m_value = MAX_VALUE;
			node->m_bValueCalculated = true;
		}
		else
		{
			node->m_value = DRAW_VALUE;
			node->m_bValueCalculated = true;
		}
	}
	return true;
}
void CSearchEngineMaxMin::PrintAllMoveWays()
{
	std::vector<Shared_TreeNode> uniqueNodes;
	bool bFind = false;
	for (auto item : m_allLeaves)
	{
		bFind = false;
		for (auto uniqItem : uniqueNodes)
		{
			if (item->m_board == uniqItem->m_board)
			{
				bFind = true;
				break;
			}
		}
		if (!bFind)
		{
			uniqueNodes.push_back(item);
		}
	}

	int roadIndex = 0;
	for (auto roadItem : uniqueNodes)
	{
		std::cout << "------------------------------------------------------------------" << std::endl;
		std::cout << "--Road Index: " << roadIndex << std::endl;
		roadIndex++;
		PrintFillNode(roadItem);
		std::cout << "------------------------------------------------------------------" << std::endl;
	}
}
bool CSearchEngineMaxMin::CalculateValueOfSearchTree()
{
	CalculateLevelNodes(m_allLeaves);
	CheckSaveLevelNodes(m_allLeaves);
	int nMaxDepth = 0;
	for (auto& item : m_allLeaves)
	{
		nMaxDepth = std::max(item->m_depth, nMaxDepth);
	}

	nMaxDepth = nMaxDepth + 2;
	int nDepth = nMaxDepth;
	std::vector<Shared_TreeNode> upLevelNodes;
	std::vector<Shared_TreeNode> downLevelNodes;
	while (nDepth > 0)
	{
		downLevelNodes = upLevelNodes;
		{
			for (const auto& leaveItem : m_allLeaves)
			{
				if (leaveItem->m_depth == nDepth)
				{
					downLevelNodes.push_back(leaveItem);
				}
			}
		}

		CalculateLevelNodes(downLevelNodes);
		CheckSaveLevelNodes(downLevelNodes);
		{
			int curDepth = nDepth - 1;
			upLevelNodes.clear();
			for (const auto& downItem : downLevelNodes)
			{
				Shared_TreeNode parentNode = downItem->m_parent.lock();
				if (parentNode)
				{
					//CalculateNodeValue(parentNode);
					upLevelNodes.push_back(parentNode);
				}
			}
		}
		nDepth--;
	}
	return false;
}
bool CSearchEngineMaxMin::CreateSearchTree(Shared_TreeNode node,const ChessTypes_T playSide, const ChessTypes_T side,const int depth)
{
	if (IsBoardStateCheckMate(node))
	{
		node->m_bIsLeaf = true;
		m_allLeaves.push_back(node);
		return true;
	}
	else
	{
		CTicTacToeBoard board;
		board.SetBoard(node->m_board);
		auto allPos = board.GetAllPosibleGrids();
		CTicTacToeBoard oldBoard;
		bool bHaveSon = false;
		for (const auto& item : allPos)
		{
			oldBoard.SetBoard(board.GetBoard());
			if (board.CanSidePlay(side, item))
			{
				board.SidePlay(side, item);
				bHaveSon = true;
				auto boardData = board.GetBoard();
				/* {
					bool bAlreadySave = false;
					for (auto item : m_allBoards)
					{
						if (item == boardData)
						{
							bAlreadySave = true;
							break;
						}
					}
					if (!bAlreadySave)
					{
						m_allBoards.push_back(boardData);
					}
				}*/

				auto newNode = std::make_shared<SearchTreeNode_T>();
				newNode->m_board = boardData;
				newNode->m_parent = node;
				newNode->m_depth = depth;
				newNode->m_playSide = GetOtherSide(node->m_playSide);
				newNode->m_moveGrid = item;
				node->m_sons.push_back(newNode);
				board.SetBoard(oldBoard.GetBoard());
			}
		}
		if (bHaveSon)
		{
			int depthNew = depth + 1;
			for (auto& item : node->m_sons)
			{
				if (side == ChessTypes_T::X_Type)
				{
					CreateSearchTree(item, playSide, ChessTypes_T::O_Type, depthNew);
				}
				else if (side == ChessTypes_T::O_Type)
				{
					CreateSearchTree(item, playSide, ChessTypes_T::X_Type, depthNew);
				}
			}
		}
	}
	return true;
}