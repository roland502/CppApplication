#include "Tree.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <filesystem>
#include <fstream>

void Tree::PrintBitemToConsole(Base_item& base_item, int p) 
{
	cout.width(p);
	cout << right << base_item.id << " | " << base_item.parent_id << " | " << base_item.name << " | "
		<< base_item.planned_start << " | " << base_item.planned_end << endl;
}

void Tree::MakeTreeFromItemsVector(vector<Base_item>& base_items)
{
	for (Base_item& b_item : base_items)
	{
		if (b_item.name.empty())
			continue;

		if (b_item.name.find("Root") != string::npos)
		{
			root_nodes.push_back(Node(b_item));
		}
		else
		{
			sub_nodes.push_back(Node(b_item));
		}
	}
	map<int, Node*> node_map;
		
	for (Node& node : sub_nodes) 
	{
		node_map[node.base_item.id] = &node;
		
		if (node.base_item.parent_id != -1)
		{
			int key = node.base_item.parent_id;
			map<int, Node*>::iterator it = node_map.find(key);
			if (it != node_map.end())
			{
				Node* parent = node_map[key];
				parent->nodes_vector.push_back(&node);
			}

			for (Node& root : root_nodes)
			{
				if (key == root.base_item.id)
				{
					root.nodes_vector.push_back(&node);
				}
			}
		}
	}
}

void Tree::GoThroughNodesAndPrintToConsole(Node* node, int p)
{
	if (node->nodes_vector.size() > 0)
	{
		p += 10;

		sort(node->nodes_vector.begin(), node->nodes_vector.end(), [](Node* node1, Node* node2)
			{
				if (node1->base_item.planned_start != node2->base_item.planned_start)
					return node1->base_item.planned_start < node2->base_item.planned_start;
				else if (node1->base_item.planned_end != node2->base_item.planned_end)
					return node1->base_item.planned_end < node2->base_item.planned_end;
				else
					return node1->base_item.name < node2->base_item.name;
			});

		for (Node* node : node->nodes_vector)
		{
			PrintBitemToConsole(node->base_item,p);
			GoThroughNodesAndPrintToConsole(node, p);
		}
	}
}

void Tree::PrintAllNodesToConsole()
{

	for (Node& root : root_nodes)
	{	
		cout << root.base_item.name << endl;
		GoThroughNodesAndPrintToConsole(&root, 0);
	}
}

int Tree::CalculateNewCompletedProperty(Node *node)
{
	int new_val = node->base_item.completed;

	if (node->nodes_vector.size() > 0)
	{
		new_val = 0;
		
		for (Node* n : node->nodes_vector)
		{
			new_val = (new_val + CalculateNewCompletedProperty(n));
		}

		float val = static_cast<float>(new_val) / static_cast<float>(node->nodes_vector.size() * 100);
		val *= 100;
		new_val = static_cast<int>(val);
		node->completed = true;
	}

	node->base_item.completed = new_val;

	return new_val;
}

void Tree::RecalculateCompletedProperty()
{
	if (root_nodes.size() == 0)
		return;
	for (Node& root : root_nodes)
	{
		CalculateNewCompletedProperty(&root);
	}
}

void Tree::CreateAndWriteToCsvFile()
{
	filesystem::create_directory("C:\\dev");
	ofstream file("C:\\dev\\hiararchical-roland.csv");
	int level = 1;
	for (Node& root : root_nodes)
	{
		WriteToCsvFile(&root,level,file);
	}

	file.close();
}

void Tree::WriteToCsvFile(Node* node, int level, ofstream& file)
{
	if (node->nodes_vector.size() > 0)
	{
		level += 1;
		for(Node* n : node->nodes_vector)
		{
			file << level << "," << n->base_item.name << "," << n->base_item.planned_start << "," 
				<< n->base_item.planned_end << "," << n->base_item.completed << "," 
				<< (n->completed ? "true" : "false") << endl;
			
			WriteToCsvFile(n, level, file); 
		}
	}
}

