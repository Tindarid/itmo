#include <vector>
#include <ostream>

class tree {
  std::vector<tree> children;
  std::string name;

  void printTreeHelper(std::ostream &out, int deep, std::string prefix) {
    if (deep != 0) {
      out << prefix.substr(0, prefix.size() - 11);
      out << "|--------->";
    }
    out << name << std::endl;
    for (int i = 0; i < children.size(); ++i) {
      if (i == children.size() - 1) {
        children[i].printTreeHelper(out, deep + 1, prefix + "           ");
      } else {
        children[i].printTreeHelper(out, deep + 1, prefix + "|          ");
      }
    }
  }

public:
  tree(const std::string &n, const std::vector<tree> &t) :
    name(n), children(t) { }
  tree(const std::string &n) : 
    name(n) { }
  tree() : 
    name("") { }

  void printTree(std::ostream &out) {
    printTreeHelper(out, 0, "");
  }

  bool operator==(const tree &rhs) {
    if (name != rhs.name || children.size() != rhs.children.size()) {
      return false;
    }
    for (int i = 0; i < children.size(); ++i) {
      if (!(children[i] == rhs.children[i])) {
        return false;
      }
    }
    return true;
  }
};

