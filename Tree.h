#pragma once
#include <vector>
#include "Base_item.h";
#include "Node.h";


class Tree 
{
public:
	
	void MakeTreeFromItemsVector(vector<Base_item> &base_items);
	void PrintAllNodesToConsole();
	void RecalculateCompletedProperty();
	void CreateAndWriteToCsvFile();
private:
	void PrintBitemToConsole(Base_item& base_item, int p);
	void GoThroughNodesAndPrintToConsole(Node* node, int p);
	int CalculateNewCompletedProperty(Node* node);
	void WriteToCsvFile(Node* node, int level, ofstream& file);

	vector<Node> root_nodes;
	vector<Node> sub_nodes;

};
