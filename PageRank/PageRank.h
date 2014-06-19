#ifndef PAGERANK_H
#define PAGERANK_H

#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

// use graph store webpage, weight representlink times
class Node 
{
public:
    explicit Node(int name, double priority = 0, double pr = 1 ):name_(name), priority_(priority), page_rank_(pr) {}

    ~Node()
    {
        linkin_nodes_.clear();
    }

    void InsertLinkdInNode(Node* node) 
    {
        //如果没有链接
        if (linkin_nodes_.find(node) == linkin_nodes_.end()) 
        {
            linkin_nodes_.insert(node);
        }
        node->InsertLinkOutNode(this);
    }

    void InsertLinkOutNode(Node* node) 
    {
        //如果没有链接
        if (linkout_nodes_.find(node) == linkout_nodes_.end()) 
        {
            linkout_nodes_.insert(node);
        }
    }

	void removeLinkdInNode(Node* node) {
		linkin_nodes_.erase( node );
	}

	void removeLinkdOutNode(Node* node) {
		linkout_nodes_.erase( node );
	}

	void refreshEdge( set< Node* > curNodeSet ) {
		set< Node* > res;
		set< Node* > lost;
		set_intersection( linkin_nodes_.begin(), linkin_nodes_.end(),
			curNodeSet.begin(), curNodeSet.end(), inserter( res, res.begin() ) );
		set_difference( curNodeSet.begin(), curNodeSet.end(),
			linkin_nodes_.begin(), linkin_nodes_.end(), inserter( res, res.begin() ) );
		set_difference( linkin_nodes_.begin(), linkin_nodes_.end(),
			curNodeSet.begin(), curNodeSet.end(), inserter( lost, lost.begin() ) );

		linkin_nodes_ = res;
		linkout_nodes_ = res;

		for ( set< Node* >::iterator iter = lost.begin(); iter != lost.end(); ++iter ) {
			( *iter )->removeLinkdInNode( this );
			( *iter )->removeLinkdOutNode( this );
		}
	}

	int GetName() {
		return name_;
	}

	double GetPriority() {
		return priority_;
	}

	void ResetPriority() {
		priority_ = 0.0;
	}

	void IncrementPriority() {
		priority_ += page_rank_;
	}

    double GetPageRank()
    {
        return page_rank_;
    }

    void SetPageRank(double pr)
    {
        page_rank_ = pr;
    }

    double CalcRank()
    {
        double pr = 0;
		linkin_nodes_.begin();
        set<Node*>::const_iterator citr = linkin_nodes_.begin();
        for (; citr != linkin_nodes_.end(); ++citr)
        {
            Node * node = *citr;
            pr += node->GetPageRank()/node->GetOutBoundNum();
        }
        return pr;
    }

    size_t GetOutBoundNum() 
    {
        return linkout_nodes_.size();
    }

    size_t GetInBoundNum() 
    {
        return linkin_nodes_.size();
    }
    
    void PrintNode()
    {
        cout << "Node:" << name_ << " 's pagerank is: " << page_rank_ << endl; 
    }
private:
    int name_;
	double priority_;
    set<Node*> linkin_nodes_;
    set<Node*> linkout_nodes_;
    double page_rank_;
};

class PageRank
{
public:
    PageRank(double q=0.85);
    ~PageRank(void);
    void Calc(vector<Node*> & nodes, int n);
    double Calc(Node* node);
    void PrintPageRank(vector<Node*> & nodes);
private:
    double q_; //阻尼系数
};

#endif