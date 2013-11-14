#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>

class IUnionFind {
public:
  virtual void addunion(int, int) = 0;
  virtual bool isconnected(int, int) = 0;
};

class ArrayUnionFind : public IUnionFind {
protected:
  std::vector<int> id;
public:
  ArrayUnionFind(int n) {
    id.resize(n);
    for(int i = 0; i < id.size(); ++i) id[i] = i;
  }
};


class QuickUnionFind : public ArrayUnionFind {
public:
  QuickUnionFind(int n):ArrayUnionFind(n) {}
  
  void addunion(int p, int q) {
    int pset = id[p];
    int qset = id[q];
    for(int i = 0; i < id.size(); ++i)
      if(id[i] == pset) id[i] = qset;
  }
  
  bool isconnected(int p, int q) {
    return (id[p] == id[q]);
  }
};

class TreeUnionFind : public ArrayUnionFind {
protected:
  std::vector<int> sz;

private:
  virtual int root(int p) {
    while(id[p] != p) p = id[p];
    return p;
  }

public:
  TreeUnionFind(int n) : ArrayUnionFind(n) {
    sz.resize(n);
    for(int i = 0; i < sz.size(); ++i) sz[i] = 1;
  }
  
  void addunion(int p, int q) {

    int proot = root(p);
    int qroot = root(q);

    /* If size of root of p is greater than size of root of q
       then make root of p as parent of root of q, also update
       the size of root */
    if (sz[proot] > sz[qroot]) {
      id[qroot] = proot;
      sz[proot] += sz[qroot];
    } else {
      id[proot] = qroot;
      sz[qroot] += sz[proot];
    }
  }

  bool isconnected(int p, int q) {
    return (root(p) == root(q));
  }
};

class UnionFind : public TreeUnionFind {
private:
  /* flattern the tree while traversing */
  virtual int root(int p) {
    while(id[p] != p) {
      id[p] = id[id[p]];
      p = id[p];
    }
    return p;
  }

public:
  UnionFind(int n):TreeUnionFind(n) { }
};

#endif
