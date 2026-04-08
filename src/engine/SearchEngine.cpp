#include "SearchEngine.hpp"
#include <iostream>
GridType_T CSearchEngine::GetMove(const TicTacToeBoard_T& board,const ChessTypes_T side)
{
	m_root = nullptr;
	
	auto newNode = std::make_shared<SearchTreeNode_T>();
	newNode->m_board = board;
	newNode->m_parent.reset();
	newNode->m_depth = 0;
	FillNode(newNode, side,side,0);

	m_root = newNode;
	CalculateAllNodes();
	PrintAllMoveWays();
	GridType_T result;
	result._xPos = 0;
	result._yPos = 0;
	return result;
}
bool CSearchEngine::IsFillEnd(Shared_TreeNode node, const ChessTypes_T playSide, const int depth)const
{
	CTicTacToeBoard board;
	board.SetBoard(node->m_board);
	ChessTypes_T otherSide = ChessTypes_T::None_Type;
	if (playSide == ChessTypes_T::X_Type)
	{
		otherSide = ChessTypes_T::O_Type;
	}
	if (playSide == ChessTypes_T::O_Type)
	{
		otherSide = ChessTypes_T::X_Type;
	}
	if (board.IsSideWin(playSide))
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
void CSearchEngine::PrintFillNode(Shared_TreeNode node)
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
		std::cout << " Value: " << item->get()->m_value << std::endl;
		board.PrintBoard();
	}
	std::cout << "---------------Print Fill Node------------------" << std::endl;
}

bool CSearchEngine::CalculateValue(Shared_TreeNode node)
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
	if (board.IsSideWin(node->m_playSide))
	{
		node->m_value = MAX_VALUE;
	}
	else if (board.IsSideWin(otherSide))
	{
		node->m_value = MIN_VALUE;
	}
	else
	{
		node->m_value = DRAW_VALUE;
	}
	return false;
}
void CSearchEngine::PrintAllMoveWays()
{
	for (auto item : m_allLeaves)
	{
		std::cout << "---------------------PrintAllMoveWays-------------------------------" << std::endl;
		PrintFillNode(item);
		std::cout << "---------------------PrintAllMoveWays-------------------------------" << std::endl;
	}
}
bool CSearchEngine::CalculateAllNodes()
{
	for (auto& item : m_allLeaves)
	{
		CalculateValue(item);
	}

	std::vector<Shared_TreeNode> oldNodes;
	std::vector<Shared_TreeNode> newNodes;
	oldNodes = m_allLeaves;
	while(!oldNodes.empty())
	{
		for (auto& item : oldNodes)
		{
			Shared_TreeNode pParent = item->m_parent.lock();
			if (pParent)
			{
				int maxValue = MIN_VALUE;
				int nCount = 0;
				for (auto& sonItem : pParent->m_sons)
				{
					if (sonItem->m_value != DEFAULT_VALUE)
					{
						maxValue = std::max(maxValue, sonItem->m_value);
						nCount++;
					}
					else
					{
						break;
					}
				}
				if (nCount == pParent->m_sons.size())
				{
					pParent->m_value = maxValue;
					newNodes.push_back(pParent);
				}
				else
				{
					newNodes.push_back(pParent);
				}
			}
		}
		oldNodes = newNodes;
		newNodes.clear();
	}

	return false;
}
bool CSearchEngine::FillNode(Shared_TreeNode node,const ChessTypes_T playSide, const ChessTypes_T side,const int depth)
{
	if (IsFillEnd(node, playSide, depth))
	{
		CalculateValue(node);
		PrintFillNode(node);
		bool bFind = false;
		for (auto& item : m_allLeaves)
		{
			if (item.get()->m_board == node->m_board)
			{
				bFind = true;
				break;
			}
		}
		if (!bFind)
		{
			m_allLeaves.push_back(node);
		}
		return true;
	}
	else
	{
		//std::cout << "----------------Depth: " << depth << std::endl;
		CTicTacToeBoard board;
		board.SetBoard(node->m_board);
		auto allPos = board.GetAllPosibleGrids();
		CTicTacToeBoard oldBoard;
		bool bHaveSon = false;
		for (const auto& item : allPos)
		{
			oldBoard = board;
			if (board.CanSidePlay(side, item))
			{
				board.SidePlay(side, item);
				bHaveSon = true;
				auto boardData = board.GetBoard();
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
					auto newNode = std::make_shared<SearchTreeNode_T>();
					newNode->m_board = boardData;
					newNode->m_parent = node;
					newNode->m_depth = depth;
					newNode->m_playSide = playSide;
					node->m_sons.push_back(newNode);
				}
				
			}
			board = oldBoard;
		}
		if (bHaveSon)
		{
			int depthNew = depth + 1;
			for (auto& item : node->m_sons)
			{
				if (side == ChessTypes_T::X_Type)
				{
					FillNode(item, playSide, ChessTypes_T::O_Type, depthNew);
				}
				else if (side == ChessTypes_T::O_Type)
				{
					FillNode(item, playSide, ChessTypes_T::X_Type, depthNew);
				}
			}
		}
	}
	return false;
}