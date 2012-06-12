#pragma once

#include "structs.h"
#include "math.h"
#include "MemoryUtils.h"

#define WRONG_FILE		1

class GraphNode;		// forward declaration
class Connection;		// forward declaration
struct BestGraphRecurrency; // forward declaration

class Graph
{
public:
	Graph();

	void ClearGraph();
	bool LoadReferenceGraph(char *workpath, char *graphName);
	void ClearReferenceGraph();
	void CreateReferenceTables();
	void FillReferenceTablesFromFile(FILE *f);
	void DrawGraphOnImage(unsigned char *image, int w, int h, bool drawConnections, bool drawNodes);
	void DrawGraphOnColorImage(unsigned char *rgbimage, int w, int h, bool drawConnections, bool drawNodes);

//	void FindBestRepresentation(int label);
	bool FindBestRepresentation(int label, int minimumNodesForGraph);

//	void FindBestFittingGraphs(GraphNode *_nodes, int _nNodes);
	void FindBestFittingGraphs(GraphNode *_nodes, int _nNodes, int minimumNodesForGraph, float maxGraphDifference);

	~Graph();

	GraphNode *resultsContainer;
	int nGraphs;

	bool referenceGraphLoaded;
	float *graphScores;

private:
	GraphNode *graphNodes;
	int nGraphNodes;

	//  getting connectionTypes[node1][node2] will give you the connection type
	int **connectionTypes;

	int nNodeTypes;

	float **connectionsTable;
	int connectionsTableSize;

	int nLabels;

	// reference graph
	int nReferenceDistances;
	float *referenceDistances;
	int *referencePairs[2];
	simpleRECT *referenceRectangles;
	float *minReferenceValues, *maxReferenceValues;
	float **shiftBetweenPointsX, **shiftBetweenPointsY;		// for the missing points estimation
	float **referenceDegrees;
	
	float ***triplets_mean_angles;   // access to the specified element mean angle by [node1][node2][node3] 

	void DisconnectNotFittingNodes(float max_scale_differenc);
	int GetType(int node1, int node2);

	void LabelSeparateGraphs();
	void RemoveNodesWithoutAConnectionFromConnectionsTable();
	void GetResultsAndCalculateMissingComponents();
	float CalculateFaceRotation(GraphNode *actualGraph);
	float CalculatePointsRotation(float dx, float dy);


	int SetNewNodes(GraphNode *_nodes, int _nNodes);
//	void FindBestGraphFit(GraphNode **allNodes, 
//		int totalGraphNodes, float **connectionsTable);
	bool FindBestGraphFit(GraphNode **allNodes, 
		int totalGraphNodes, float **connectionsTable, int minimumNodesForGraph,
		float *score);


	float inline CalculateGraphCost(float *graphCosts);

	void ChooseBestFaceRepresentations();
	int FindNumberOfNodesWithLabels(int label);

	void CopyBestGraph(GraphNode **newNodes, GraphNode **oldNodes);

	void BestGraphFitRecurrency(BestGraphRecurrency *bg, int nSelectedNodes, int previousNode);
	float CalculateGraphCostFromNodes(int *selectedNodes, float **connectionsTable, BestGraphRecurrency *bg);
	void RepairGraphs();


};

class GraphNode
{
public:
	GraphNode() { label = -1; fNodeVisited = false; additionalPointer = NULL;};
	void SetNode(feature _f, int _type, int _index);
	~GraphNode();

	int type;					// for example LEFT_EYE, RIGHT_EYE, NOSE, MOUTH
	feature f;					// point coordinated and scale

	bool fNodeVisited;
	bool fNodeMarked;

	int label;
	int index;

	void *additionalPointer;					// may be used if needed


private:
};

struct BestGraphRecurrency
{
	GraphNode **allNodes; 
	float **connectionsTable;
	int minumumNodes;

	int *selectedNodes;

	int *bestNodes;
	float bestGraphCost;

	float *connectionsCosts;

	int *nodeTypes;
	
	int totalGraphNodes;

};