#include "grid.h"

#include <stack>
#include <cassert>

// Constants ---------------------------------------------------------
Grid::weight_t const Grid::NOEDGE = -1;
Grid::weight_t const Grid::PATH = 1;
std::string const P3_NODE = "255 255 255\n";
std::string const P3_EDGE = "255 255 255\n";
std::string const P3_WALL = "0 0 0\n";
std::string const P3_PATH = "255 0 0\n";

// Definitions -------------------------------------------------------
std::ostream& operator<<(std::ostream &out, Point const &p) {
    return out << '(' << p.x << ',' << p.y << ')';
}

Grid::Node::Node() {
	for(unsigned i = 0; i < Node::NUM_DIRECTIONS; i++) {
		weights[i] = Grid::NOEDGE;
		visited = false;
		ismaze = false;
	}
}

Grid::Grid(unsigned height, unsigned width) {
	for(unsigned i = 0; i < height; i++) {
                std::vector<Node> nodeRow;
                for(unsigned j = 0; j < width; j++) {
                        Node n;
                        nodeRow.push_back(n);
                }
                nodes_.push_back(nodeRow);
        }
}

/*Grid Grid::makeMaze() {
	Grid blankGrid(getHeight(), getWidth());
	std::vector<Wall> walls;
	//unsigned startx = (random() % getWidth())-1;
	//unsigned starty = (random() % getHeight())-1;
	unsigned startx = 0;
	unsigned starty = 0;
	Node cell = nodes_[starty][startx];
	cell.ismaze = true;
	nodes_[starty][startx] = cell;
	if(cell.weights[Node::RIGHT] != Grid::NOEDGE) {
		Point a;
		a.x = startx;
		a.y = starty;
		Point b;
		b.x = startx+1;
		b.y = starty;
		Wall w;
		w.a = a;
		w.b = b;
		walls.push_back(w);
	}
	else if (cell.weights[Node::DOWN] != Grid::NOEDGE) {
		Point a;
                a.x = startx;
                a.y = starty;
                Point b;
                b.x = startx;
                b.y = starty+1;
                Wall w;
                w.a = a;
                w.b = b;
                walls.push_back(w);
	}
	while(walls.empty() != true) {
		unsigned ind = (random() % walls.size());
		Wall RWall = walls[ind];
		Node oppositeNode;
		Point oppositePoint;
		Point currentPoint;
		if((RWall.a.x+1< getWidth()) && RWall.a.x+1 == RWall.b.x) { 
			if(((int)(RWall.a.x-1)) >= 0) {
				oppositeNode = nodes_[RWall.a.y][RWall.a.x-1];
				oppositePoint.x = RWall.a.x-1;
				oppositePoint.y = RWall.a.y;
				currentPoint = RWall.a;
			}
			else {
				oppositeNode = nodes_[RWall.a.y][RWall.a.x];
				currentPoint = RWall.b;
				oppositePoint = RWall.a;
			}
		}
		else {
			if((int)(RWall.a.y-1) >= 0) {
				oppositeNode = nodes_[RWall.a.y-1][RWall.a.x];
				oppositePoint.x = RWall.a.x;
				oppositePoint.y = RWall.a.y-1;
				currentPoint = RWall.a;
			}
			else {
				oppositeNode = nodes_[RWall.a.y][RWall.a.x];
				currentPoint = RWall.b;
				oppositePoint = RWall.a;
			}
		}
		if(oppositeNode.ismaze) {
			for(unsigned i = 0; i < walls.size(); i++) {
				if(walls[i].a == RWall.a && walls[i].b == RWall.b) {
					walls.erase(walls.begin() + i);
					break;
				}
			}
		}
		else {
			if(oppositePoint != currentPoint) {
				if((oppositePoint.x+1 < getWidth()) && oppositePoint.x+1 == currentPoint.x) {
					blankGrid.nodes_[oppositePoint.y][oppositePoint.x].ismaze = true;
					blankGrid.nodes_[currentPoint.y][currentPoint.x].ismaze = false;
				}
				else {
					blankGrid.nodes_[oppositePoint.y][oppositePoint.x].ismaze = true;
					blankGrid.nodes_[currentPoint.y][currentPoint.x].ismaze = false;
				}
			}
			if(oppositeNode.weights[Node::RIGHT] != Grid::NOEDGE) {
                		Point a;
                		a.x = startx;
                		a.y = starty;
                		Point b;
                		b.x = startx + 1;
                		b.y = starty;
                		Wall w;
                		w.a = a;
               			w.b = b;
                		walls.push_back(w);
        		}
        		else if (oppositeNode.weights[Node::DOWN] != Grid::NOEDGE) {
                		Point a;
                		a.x = startx;
                		a.y = starty;
                		Point b;
                		b.x = startx;
                		b.y = starty+1;
                		Wall w;
              			w.a = a;
               			w.b = b;
                		walls.push_back(w);
        		}		
		}
	}
	for(unsigned y = 0; y < getHeight(); y++) {
		for(unsigned x = 0; x < getWidth(); x++) {
			if(nodes_[y][x].ismaze) {
				if((x+1 < getWidth()) && nodes_[y][x+1].ismaze) {
					blankGrid.nodes_[y][x].weights[Node::RIGHT] = nodes_[y][x].weights[Node::RIGHT];
				}
				else {
					blankGrid.nodes_[y][x].weights[Node::RIGHT] = Grid::NOEDGE;
				}
				if((y+1 < getHeight()) && nodes_[y+1][x].ismaze) {
					blankGrid.nodes_[y][x].weights[Node::DOWN] = nodes_[y][x].weights[Node::DOWN];
				}
				else {
					blankGrid.nodes_[y][x].weights[Node::DOWN] = Grid::NOEDGE;
				}
			}
		}
	}
	return blankGrid;

}*/
Grid Grid::makeMaze()  {
	Grid blankGrid(getHeight(),getWidth());
	unsigned currentsmalledge = 0;
	if(nodes_[0][0].weights[Node::RIGHT] < nodes_[0][0].weights[Node::DOWN]) {
		currentsmalledge = nodes_[0][0].weights[Node::RIGHT];
	}
	else {
		currentsmalledge = nodes_[0][0].weights[Node::DOWN];
	}
	for(unsigned y = 0; y < getHeight(); y++) {
		for(unsigned x = 0; x < getWidth(); x++) {
			if (nodes_[y][x].weights[Node::RIGHT] == Grid::NOEDGE && nodes_[y][x].weights[Node::DOWN] == Grid::NOEDGE) {
                                continue;
                        }
			if(y+1 == getHeight()) {
				Point b;
				Point c;
				b.x = x;
				b.y = y;
				c.x = x+1;
				c.y = y;
				if ((int(y-1)) >= 0 && x == 0 && nodes_[y-1][x].weights[Node::DOWN] != Grid::NOEDGE) {
					blankGrid.setEdge(b,c, nodes_[y][x].weights[Node::RIGHT]);
				}
				else {
					if(x < getWidth()) {
						if((((int)x-1) >= 0) && (blankGrid.nodes_[y][x-1].weights[Node::RIGHT] != Grid::NOEDGE)) {
							blankGrid.setEdge(b,c, Grid::NOEDGE);
						}
						else {
							blankGrid.setEdge(b,c, nodes_[y][x].weights[Node::RIGHT]);
						}
					}
				}
			}
			else if(nodes_[y][x].weights[Node::RIGHT] < nodes_[y][x].weights[Node::DOWN]) {
				Point a;
				a.x = x;
				a.y = y;
				Point b;
				b.x = x+1;
				b.y = y;
				if(x+1 < getWidth()) {
					blankGrid.setEdge(a,b,nodes_[y][x].weights[Node::RIGHT]);
				}
				else {
					blankGrid.setEdge(a,b,Grid::NOEDGE);
				}
				Point c;
				c.x = x;
				c.y = y+1;
				if(y+1 < getHeight()){
					if(nodes_[y][x].weights[Node::DOWN] < currentsmalledge) {
						blankGrid.setEdge(a,c,nodes_[y][x].weights[Node::DOWN]);
					}
					else {
						blankGrid.setEdge(a,c,Grid::NOEDGE);
					}
				}
			}
			else if (nodes_[y][x].weights[Node::DOWN] < nodes_[y][x].weights[Node::RIGHT]) {
				Point a;
                                a.x = x;
                                a.y = y;
				Point b;
				b.x = x;
				b.y = y+1;
				if(y+1 < getHeight()) {
					blankGrid.setEdge(a,b,nodes_[y][x].weights[Node::DOWN]);	
				}
				else {
					blankGrid.setEdge(a,b, Grid::NOEDGE);
				}
				Point c;
                                c.x = x+1;
                                c.y = y;
				if(x+1 < getWidth()) {
					if(nodes_[y][x].weights[Node::RIGHT] < currentsmalledge) {
						blankGrid.setEdge(a,c,nodes_[y][x].weights[Node::RIGHT]);
						currentsmalledge = nodes_[y][x].weights[Node::RIGHT];
					}
					else{
						blankGrid.setEdge(a,c,Grid::NOEDGE);
					}
				}
			}
		}
	}	
	return blankGrid;
}

bool Grid::nextMovePossible(Point &curr){
	if((curr.x+1 < getWidth()) && (nodes_[curr.y][curr.x].weights[Node::RIGHT] != Grid::NOEDGE) && (nodes_[curr.y][curr.x+1].visited != true)) {
		curr.x+=1;
		return true;
	}
	else if((curr.y+1 < getHeight()) && (nodes_[curr.y][curr.x].weights[Node::DOWN] != Grid::NOEDGE) && (nodes_[curr.y+1][curr.x].visited != true)) {
		curr.y+=1;
		return true;
	}
	else if(((int(curr.y-1) >= 0)) && (nodes_[curr.y-1][curr.x].weights[Node::DOWN] != Grid::NOEDGE) && (nodes_[curr.y-1][curr.x].visited != true)) {
		curr.y-=1;
		return true;
	}
	else if(((int(curr.x-1) >= 0)) && (nodes_[curr.y][curr.x-1].weights[Node::RIGHT] != Grid::NOEDGE) && (nodes_[curr.y][curr.x-1].visited != true)) {
		curr.x-=1;
		return true;
	}
	else {
		return false;
	}
}

void Grid::findPath(Point start, Point end) {
	// pseudo
	// create current point variable
	// create stack w std::stack
	// push first point onto stack
	// set first point visited to true
	// while loop ?
	// if the next move is possible with the current point (helper function or check in here
	// then set the current point to the next point that is possible
	// set that point's visited to true
	// push onto stack
	// else
	// pop the item from the stack and set curr to top of stack after pop
	Point firstNode;
	firstNode.x = start.x;
	firstNode.y = start.y;
	std::stack<Point> path;
	if(firstNode.x != end.x && firstNode.y != end.y) {
		path.push(firstNode);
		nodes_[firstNode.y][firstNode.x].visited = true;
	}
	else {
		return;
	}
	Point curr = start;
	while(curr != end) {	
		if(curr.x == end.x && curr.y == end.y) {
			nodes_[curr.y][curr.x].visited = true;
			path.push(curr);
			break;
		}
		else if(nextMovePossible(curr)) { 
			nodes_[curr.y][curr.x].visited = true;
			path.push(curr);
		}
		else {
			if(path.size() > 0) {
				path.pop();
				curr = path.top();
			}
			else {
				return;
			}
		}
	}
	while(path.size() != 1) {	
		Point a = path.top();
		path.pop();
		Point b = path.top();
		setEdge(a, b, Grid::PATH);
	
	}
	path.pop();
}

unsigned Grid::getHeight() const {
       return nodes_.size();	
}

unsigned Grid::getWidth() const {
	return nodes_[0].size();
}

Grid::weight_t Grid::getEdge(Point const &a, Point const &b) const {	
	if((a.x == b.x) && (a.y == b.y)) {
		return 0;
	}
		if((a.x+1 < getWidth()) && a.x+1 == b.x && a.y == b.y) {
			return nodes_[a.y][a.x].weights[Node::RIGHT];
		}
		else if(((int)(b.x-1) >= 0) && b.x-1 == a.x && a.y == b.y) {
			return nodes_[a.y][b.x-1].weights[Node::RIGHT];
		}
		else if((a.y+1 < getHeight()) && a.y+1 == b.y && a.x == b.x) {
			return nodes_[a.y][a.x].weights[Node::DOWN];
		}
		else if (((int)(b.y-1) >= 0) && b.y-1 == a.y && a.x == b.x) {
			return nodes_[b.y-1][a.x].weights[Node::DOWN];
		}
	return Grid::NOEDGE;
}

bool Grid::setEdge(Point const &a, Point const &b, weight_t weight) {
                if(((a.x+1) < getWidth()) && a.x+1 == b.x && a.y == b.y) {
                        nodes_[a.y][a.x].weights[Node::RIGHT] = weight;
                	return true;
		}
		else if((int(a.x-1)) >= 0 && a.x-1 == b.x && a.y == b.y) {
			nodes_[a.y][a.x-1].weights[Node::RIGHT] = weight;
		}
		else if(b.x+1 < getWidth() && a.x == b.x+1 && a.y == b.y) {
			nodes_[b.y][b.x+1].weights[Node::RIGHT] = weight;
		}
                else if(((int)(b.x-1) >= 0) && a.x == b.x-1 && a.y == b.y) {
                        nodes_[a.y][b.x-1].weights[Node::RIGHT] = weight;
                	return true;
		}
                else if((a.y+1 < getHeight()) && a.y+1 == b.y && a.x == b.x) {
                        nodes_[a.y][a.x].weights[Node::DOWN] = weight;
                	return true;
		}
		else if ((int(a.y-1) >= 0) && a.y-1 == b.y && a.x == b.x) {
			nodes_[a.y-1][a.x].weights[Node::DOWN] = weight;
			return true;
		}
		else if (b.y+1 < getHeight() && b.y+1 == a.y && a.x == b.x) {
			nodes_[b.y+1][b.x].weights[Node::DOWN] = weight;
		}
                else if (((int)(b.y-1) >= 0) && b.y-1 == a.y && a.x == b.x) {
                        nodes_[b.y-1][a.x].weights[Node::DOWN] = weight;
			return true;
                }
        return false;
}

void Grid::draw(std::ostream &out) const {
	out << "P3\n";
	out << (getWidth()*2)+1 << " " << (getHeight()*2)+1 << "\n";
	out << "255\n";
	for(unsigned x = 0; x < (getWidth()*2)+1; x++) {
		out << P3_WALL;
	}
	for(unsigned i = 0; i < getHeight(); i++) {
		if(i+1 == getHeight()) { // last row
			out << P3_WALL; // start wall
			for(unsigned n = 0; n < getWidth(); n++) {
                        if(n+1 == getWidth()) {
				if(((int)(n-1) >= 0) && (nodes_[i][n-1].weights[Node::RIGHT] == Grid::PATH)) {
					out << P3_PATH;
				}
				else if (((int)(i-1) >= 0) && (nodes_[i-1][n].weights[Node::DOWN] == Grid::PATH)) {
					out << P3_PATH;
				}
				else {
					out << P3_NODE;
				}
                                break;
                        }
			if(nodes_[i][n].weights[Node::RIGHT] != Grid::NOEDGE) {
                                if (nodes_[i][n].weights[Node::RIGHT] == Grid::PATH) {
                                        out << P3_PATH;
                                        out << P3_PATH;
                                }
                                else {
                                                out << P3_NODE;
                                                out << P3_EDGE;
                                }
                        }
                        else {
                                if (nodes_[i][n].weights[Node::RIGHT] == Grid::PATH) {
                                        out << P3_PATH;
                                        out << P3_WALL;
                                }
                                else {
                                        if ((((int)n-1 >= 0)) && (nodes_[i][n-1].weights[Node::RIGHT] == Grid::PATH)) {
                                                out << P3_PATH;
                                                out << P3_WALL;
                                        }
                                        else if ((((int)i-1 >= 0) && (nodes_[i-1][n].weights[Node::DOWN] == Grid::PATH))) {
                                                out << P3_PATH;
                                                out << P3_WALL;
                                        }
                                        else {
                                                out << P3_NODE;
                                                out << P3_WALL;
                                        }
                                }
                        }
                }
		out << P3_WALL;
			for(unsigned x = 0; x < (getWidth()*2)+1; x++) {
                		out << P3_WALL;
        		}
			break;
		}
		out << P3_WALL; // starting row
		for(unsigned n = 0; n < getWidth(); n++) {
			if(n+1 == getWidth()) {	
				if(nodes_[i][n].weights[Node::DOWN] != Grid::NOEDGE) {
					if(nodes_[i][n].weights[Node::DOWN] == Grid::PATH) {
						out << P3_PATH;
					}
					else if ((int(n-1) >= 0) && nodes_[i][n-1].weights[Node::RIGHT] == Grid::PATH) {
                                        	out << P3_PATH;
                                	}
					else {
						out << P3_NODE;
					}
				}
				else if((((int)(i-1)) >= 0) && (nodes_[i-1][n].weights[Node::DOWN]!= Grid::NOEDGE)) {
					if(nodes_[i-1][n].weights[Node::DOWN] == Grid::PATH) {
							out << P3_PATH;
					}
					else {
						out << P3_NODE;
					}
				}
				else if(nodes_[i][n].weights[Node::RIGHT] == Grid::NOEDGE) {
					out << P3_NODE;
				}
				else {
					out << P3_WALL;
				}
				break;
			}
			if(nodes_[i][n].weights[Node::RIGHT] != Grid::NOEDGE) {
                                if (nodes_[i][n].weights[Node::RIGHT] == Grid::PATH) {
                                        out << P3_PATH;
                                        out << P3_PATH;
                                }
				else if(nodes_[i][n].weights[Node::DOWN] == Grid::PATH) {
					out << P3_PATH;
					out << P3_EDGE;
				}
				else if ((int(n-1) >= 0) && nodes_[i][n-1].weights[Node::RIGHT] == Grid::PATH) {
					out << P3_PATH;
					out << P3_EDGE;
				}
                                else {
                                        	out << P3_NODE;
                                        	out << P3_EDGE;
                                }
                        }
                        else {
                                if (nodes_[i][n].weights[Node::RIGHT] == Grid::PATH || nodes_[i][n].weights[Node::DOWN] == Grid::PATH) {
                                        out << P3_PATH;
                                        out << P3_WALL;
                                }
                                else {
                                        if (((int)n-1 >= 0) && (nodes_[i][n-1].weights[Node::RIGHT] == Grid::PATH)) {
						out << P3_PATH;
                                        	out << P3_WALL;
					}
					else if (((int)i-1 >= 0) && (nodes_[i-1][n].weights[Node::DOWN] == Grid::PATH)) {
						out << P3_PATH;
                                                out << P3_WALL;
					}
					else {
						out << P3_NODE;
                                        	out << P3_WALL;
					}
                                }
                        }
		}
		out << P3_WALL; // end row
		out << P3_WALL; // start row
		for(unsigned j = 0, n = 0; j < (getWidth()*2)-1; j++) {
			if(j % 2 == 0) {
				if(nodes_[i][n].weights[Node::DOWN] != Grid::NOEDGE) {
					if(nodes_[i][n].weights[Node::DOWN] == Grid::PATH) {
						out << P3_PATH;
					}
					else {
						out << P3_EDGE;
					}
				}
				else {
					out << P3_WALL;
				}
			}
			else {
				out << P3_WALL;
				n++;
			}
		}
		out << P3_WALL; // end row	
	}
}

void Grid::serialize(std::ostream &out) const {
    out << getWidth() << " " << getHeight() << "\n";
    for(unsigned y = 0; y < getHeight()-1; y++) {
	    for(unsigned x = 0; x < getWidth()-1; x++) {
		    if(nodes_[y][x].weights[Node::RIGHT] != Grid::NOEDGE) {
		    out << "(" << x << "," << y << ")" << nodes_[y][x].weights[Node::RIGHT] << "(" << x+1 << "," << y << ")" << "\n";
		   }
		    if(nodes_[y][x].weights[Node::DOWN] != Grid::NOEDGE) {
		    out << "(" << x << "," << y << ")" << nodes_[y][x].weights[Node::DOWN] << "(" << x << "," << y+1 << ")" << "\n";
		   }
	}
	    if(nodes_[y][getWidth()-1].weights[Node::DOWN] != Grid::NOEDGE) {
	    out << "(" << getWidth()-1 << "," << y << ")" << nodes_[y][getWidth()-1].weights[Node::DOWN] << "(" << getWidth()-1 << "," << y+1 << ")" << "\n";
        }
    }
    for(unsigned x = 0; x < getWidth()-1; x++) {
	    if(nodes_[getHeight()-1][x].weights[Node::RIGHT] != Grid::NOEDGE) {
	    out << "(" << x << "," << getHeight()-1 << ")" << nodes_[getHeight()-1][x].weights[Node::RIGHT] << "(" << x+1 << "," << getHeight()-1 << ")" << "\n";
	    }	
    }
}

Grid Grid::load(std::istream &in) {
    char buf[200];
    in.getline(buf, 200);
    unsigned width;
    unsigned height;
    unsigned weight;
    Point a;
    Point b;
    sscanf(buf, "%u %u", &width, &height);
    Grid Gr(height, width);
    while(in.getline(buf,200)) {
	    sscanf(buf, "(%u,%u)%u(%u,%u)",&a.x,&a.y,&weight,&b.x,&b.y);
	    Gr.setEdge(a, b, weight);
    }
    return Gr;
}
