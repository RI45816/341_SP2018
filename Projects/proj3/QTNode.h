#ifndef QTNODE_H
#define QTNODE_H

#include <vector>
#include "Point.h"
#include "BBox.h"

#define QT_NUM_KIDS 4
enum {BL,BR,TL,TR}; // Enumerator with the values of the directions

class QTNode {
public:
    class iterator {
    public:
	iterator();
	bool operator==(const QTNode::iterator &other);
	bool operator!=(const QTNode::iterator &other);
	iterator &operator++();          // Prefix: e.g. "++it"
	iterator operator++(int dummy);  // Postfix: "it++"
	QTNode *&operator*();

    private:
//	 Add data members here to record state of current iterator position
//        vector<QTNode*>::iterator it;
        int m_position;
        QTNode * m_node;
        friend class QTNode;
    };

    QTNode();
    ~QTNode();
    bool add(const Point &pt, int data);  // actually, add/replace
    bool remove(const Point &pt, bool &empty);
    bool find(const Point &pt, int &data);
    int findPoints(const BBox &region, std::vector<Point> &found);
    void dump();

    iterator begin();
    iterator end();

    BBox m_bounds;  // The bounding box for this node
    Point m_point;  // If leaf node (i.e., no kids), m_point, m_data hold the
    int m_data;     // actual point and data value the user inserted.
    // YOu must add data member(s) to store pointers to child QTNode's
    
    //
    // YOU CAN ADD ANY OTHER CONSTRUCTORS, MEMBER FUNCTIONS, MEMBER DATA, ETC.
    // AS NEEDED.
    //
    QTNode * m_nodes[QT_NUM_KIDS];   // Store the QTNodes for top left, top right, bottom left, and bottom right
    bool isEmpty(); // Return true if there are no sub-nodes
    bool m_isLeaf; // True if current node is a leaf
    int sortPoint(Point &pt); // Return the index of the sub-node to sort the point into
    QTNode(Point &pt,int data, int dim); // Create a new leaf node and set the data accordingly
    QTNode(QTNode * nodes[], BBox bounds,int dim); // Create a new subnode
        
    static int debug_count;
    };
#endif
