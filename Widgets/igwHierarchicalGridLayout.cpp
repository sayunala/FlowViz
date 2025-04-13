// SPDX-FileCopyrightText: Copyright (c) Kitware Inc.
// SPDX-FileCopyrightText: Copyright (c) Sandia Corporation
// SPDX-License-Identifier: BSD-3-Clause
#include "igwHierarchicalGridLayout.h"

#include "igwHierarchicalGridWidget.h"

#include <QDebug>
#include <QLayoutItem>
#include <QScopedValueRollback>
#include <QVector>
#include <QWidget>

#include <cassert>
#include <cmath>
#include <functional>
#include <vector>
#include <iostream>
#include <queue>
namespace
{
struct BTNode
{
  BTNode()
    : Invalid(true)
  {
  }
  BTNode(QLayoutItem* item)
    : Item(item)
    , Invalid(false)
  {
  }
  BTNode(Qt::Orientation direction, double fraction)
    : Direction(direction)
    , Fraction(fraction)
    , IsSplitter(true)
    , Invalid(false)
  {
  }
  void print()
  {
      std::cout << "Direction : " << Direction;
      std::cout << "Invalid : " << Invalid;
      std::cout << "Fraction : " << Fraction;
      std::cout << "IsSplitter : " << IsSplitter;
      std::cout << "Item : " << Item;
      std::cout << std::endl;
  }

  QWidget* widget() const { return this->Item ? this->Item->widget() : nullptr; }

  QLayoutItem* Item = nullptr;
  Qt::Orientation Direction = Qt::Horizontal;
  double Fraction = 0.5;
  bool IsSplitter = false;
  bool Invalid = true;
};

template <typename T>
T get_child0(T location)
{
  return 2 * location + 1;
}

template <typename T>
T get_child1(T location)
{
  return 2 * location + 2;
}

template <typename T>
T get_parent(T location)
{
  return (location > 0 ? ((location - 1) / 2) : -1);
}
}

//-----------------------------------------------------------------------------
class igwHierarchicalGridLayout::pqInternals
{
  int MaximizedLocation = 0;

public:
  // Sequential binary tree representation where each node is represented by a
  // BTNode.
  std::vector<BTNode> SBTree;

  // Keeps track of the QLayoutItem's added to this layout.
  QVector<QLayoutItem*> Items;

  // Keeps track of split regions of igwHierarchicalGridWidget to support
  // interactive resizing.
  QVector<igwHierarchicalGridWidget::SplitterInfo> Splitters;

  // Set to true in `igwHierarchicalGridLayout::rearrange`
  bool Rearranging = false;

  void setGeometry(const QRect& rect, int spacing)
  {
    int root = 0;
    if (this->MaximizedLocation >= 0 &&
      this->MaximizedLocation < static_cast<int>(this->SBTree.size()))
    {
      root = this->MaximizedLocation;
    }

    // reset all splitters
    this->Splitters.clear();
    this->hide(0, root);
    this->setGeometry(rect, root, spacing);
  }

  void maximize(int location)
  {
    if (location < 0 || location >= static_cast<int>(this->SBTree.size()) ||
      this->SBTree[location].Invalid)
    {
      qWarning() << "unknown cell specified : " << location;
    }
    else
    {
      this->MaximizedLocation = location;
    }
  }

private:
  void hide(int start, int end)
  {
    if (start == end || start >= static_cast<int>(this->SBTree.size()) ||
      this->SBTree[start].Invalid)
    {
      return;
    }
    const auto& node = this->SBTree[start];
    if (node.IsSplitter)
    {
      this->hide(get_child0(start), end);
      this->hide(get_child1(start), end);
    }
    else if (auto wdg = node.widget())
    {
      wdg->hide();
    }
    else if (node.Item && !node.Item->isEmpty())
    {
      qWarning("currently unsupported; please contact the developers.");
    }
  }

  void setGeometry(const QRect& rect, int location, int spacing)
  {
    if (location < 0 || location >= static_cast<int>(this->SBTree.size()))
    {
      return;
    }
    const auto& node = this->SBTree[location];
    if (node.Invalid)
    {
      return;
    }

    if (node.IsSplitter)
    {
      igwHierarchicalGridWidget::SplitterInfo sinfo;
      sinfo.Direction = node.Direction;
      sinfo.Bounds = rect;
      sinfo.Location = location;

      // split rect and pass to children.
      if (node.Direction == Qt::Horizontal)
      {
        const int width0 = static_cast<int>(std::ceil((rect.width() - spacing) * node.Fraction));
        const QRect lRect = QRect(rect.x(), rect.y(), width0, rect.height());
        const QRect rRect = QRect(
          rect.x() + width0 + spacing, rect.y(), rect.width() - width0 - spacing, rect.height());
        this->setGeometry(lRect, get_child0(location), spacing);
        this->setGeometry(rRect, get_child1(location), spacing);

        sinfo.Position = width0 + spacing / 2;
      }
      else
      {
        const int height0 = static_cast<int>(std::ceil((rect.height() - spacing) * node.Fraction));
        const QRect tRect = QRect(rect.x(), rect.y(), rect.width(), height0);
        const QRect bRect = QRect(
          rect.x(), rect.y() + height0 + spacing, rect.width(), rect.height() - height0 - spacing);
        this->setGeometry(tRect, get_child0(location), spacing);
        this->setGeometry(bRect, get_child1(location), spacing);

        sinfo.Position = height0 + spacing / 2;
      }

      this->Splitters.push_back(sinfo);
    }
    else if (node.Item != nullptr)
    {
      if (auto wdg = node.widget())
      {
        wdg->show();
      }
      node.Item->setGeometry(rect);
    }
  }
};

//-----------------------------------------------------------------------------
igwHierarchicalGridLayout::igwHierarchicalGridLayout(QWidget* parentObject)
  : Superclass(parentObject)
  , Internals(new igwHierarchicalGridLayout::pqInternals())
{
}

//-----------------------------------------------------------------------------
igwHierarchicalGridLayout::~igwHierarchicalGridLayout()
{
  auto& internals = *this->Internals;
  for (auto item : internals.Items)
  {
    delete item;
  }
}

//-----------------------------------------------------------------------------
void igwHierarchicalGridLayout::addItem(QLayoutItem* item)
{
  auto& internals = *this->Internals;

  // current implementation doesn't support adding non-QWidget items to the
  // layout. In future, we may support it, if needed.
  assert(item->widget() != nullptr);

  internals.Items.push_back(item);

  // skip adding to binary tree if we're in middle of rearrangement.
  if (internals.Rearranging)
  {
    return;
  }

  // now add the item to the binary tree.

  // 1. If tree is empty, simply add the item as the root node.
  if (internals.SBTree.empty())
  {
    item->widget()->setProperty("FRAME_INDEX", QVariant(0));
    internals.SBTree.emplace_back(BTNode(item));

    return;
  }

  // 2. Find an empty leaf node and place the item in it.
  int index = 0;
  for (auto& node : internals.SBTree)
  {
    if (node.Invalid == false && node.IsSplitter == false && node.Item == nullptr)
    {
      item->widget()->setProperty("FRAME_INDEX", QVariant(index));
      node.Item = item;

      return;
    }
    ++index;
  }

  // 3. Find an invalid node, that is node that is not yet reachable from the root
  //    and split its parent. That's an easy way to keep the tree balanced.
  for (size_t cc = 1, max = internals.SBTree.size(); cc < max; ++cc)
  {
    auto& node = internals.SBTree[cc];
    if (node.Invalid)
    {
      const auto parentIdx = get_parent(cc);
      assert(internals.SBTree[parentIdx].Invalid == false &&
        internals.SBTree[parentIdx].IsSplitter == false);

      this->splitAny(static_cast<int>(parentIdx), 0.5);
      const auto child1 = get_child1(parentIdx);
      assert(internals.SBTree[child1].Invalid == false && internals.SBTree[child1].Item == nullptr);
      item->widget()->setProperty("FRAME_INDEX", QVariant(index));
      internals.SBTree[child1].Item = item;
      return;
    }
  }

  // we have a fully-balanced tree, just split the last cell and try again.
  const int last_cell = static_cast<int>(internals.SBTree.size() - 1);
  this->splitAny(last_cell, 0.5);

  const auto child1 = get_child1(last_cell);
  assert(internals.SBTree[child1].Invalid == false && internals.SBTree[child1].Item == nullptr);
//  item->widget()->setProperty("FRAME_INDEX", QVariant(child1));
  internals.SBTree[child1].Item = item;
  for (size_t cc = 1, max = internals.SBTree.size(); cc < max; ++cc)
  {
    auto& node = internals.SBTree[cc];
    std::cout << cc << std::endl;
    node.print();
  }
}

//-----------------------------------------------------------------------------
QLayoutItem* igwHierarchicalGridLayout::itemAt(int index) const
{
  auto& internals = *this->Internals;
  if (index >= 0 && index < internals.Items.size())
  {
    return internals.Items[index];
  }
  return nullptr;
}

//-----------------------------------------------------------------------------
QLayoutItem* igwHierarchicalGridLayout::takeAt(int index)
{
  auto& internals = *this->Internals;
  if (index >= 0 && index < internals.Items.size())
  {
    auto item = internals.Items.takeAt(index);

    // remove item from the SBTree.
    for (auto& node : internals.SBTree)
    {
      if (node.Item == item)
      {
        node.Item = nullptr;
        break;
      }
    }
    return item;
  }

//  this->invalidate();
  return nullptr;
}

//-----------------------------------------------------------------------------
int igwHierarchicalGridLayout::count() const
{
  auto& internals = *this->Internals;
  return internals.Items.size();
}

//-----------------------------------------------------------------------------
QSize igwHierarchicalGridLayout::minimumSize() const
{
  // todo: maybe scan the views, not sure what's a good min size.
  return QSize(200, 200);
}

//-----------------------------------------------------------------------------
void igwHierarchicalGridLayout::setGeometry(const QRect& rect)
{
  this->Superclass::setGeometry(rect);
  auto& internals = *this->Internals;
  internals.setGeometry(rect, this->spacing());

  // since layout may have changed, let the igwHierarchicalGridWidget know about
  // the splitter locations to support interactive resizing of the layout.
  if (auto p = qobject_cast<igwHierarchicalGridWidget*>(this->parentWidget()))
  {
    p->setSplitters(internals.Splitters);
  }
}

//-----------------------------------------------------------------------------
QSize igwHierarchicalGridLayout::sizeHint() const
{
  return QSize();
}

//-----------------------------------------------------------------------------
bool igwHierarchicalGridLayout::isLocationValid(int location) const
{
  const auto& internals = *this->Internals;
  if (location >= 0 && location < static_cast<int>(internals.SBTree.size()))
  {
    return (internals.SBTree[location].Invalid == false);
  }

  return false;
}

//-----------------------------------------------------------------------------
void igwHierarchicalGridLayout::splitAny(int location, double splitFraction)
{
  if (!this->isLocationValid(location))
  {
    qCritical() << "invalid location specified `" << location << "`.";
  }
  else if (location == 0)
  {
    this->splitHorizontal(location, splitFraction);
  }
  else
  {
    auto& internals = *this->Internals;
    const auto parentIdx = get_parent(location);
    assert(internals.SBTree[parentIdx].Invalid == false && internals.SBTree[parentIdx].IsSplitter);

    this->split(location,
      (internals.SBTree[parentIdx].Direction == Qt::Horizontal) ? Qt::Vertical : Qt::Horizontal,
      splitFraction);
  }
}

//-----------------------------------------------------------------------------
void igwHierarchicalGridLayout::setSplitFraction(int location, double splitFraction)
{
  if (!this->isLocationValid(location))
  {
    qCritical() << "invalid location specified `" << location << "`.";
  }
  else
  {
    auto& internals = *this->Internals;
    auto& node = internals.SBTree[location];
    if (node.IsSplitter)
    {
      node.Fraction = splitFraction;
      this->invalidate();
    }
  }
}

//-----------------------------------------------------------------------------
void igwHierarchicalGridLayout::split(int location, Qt::Orientation direction, double splitFraction)
{
  if (!this->isLocationValid(location))
  {
    qCritical() << "invalid location specified `" << location << "`.";
    return;
  }

  auto& internals = *this->Internals;
  assert(location >= 0 && location < static_cast<int>(internals.SBTree.size()));

  auto& node = internals.SBTree[location];

  // if node.Invalid, we're splitting an unreachable location.
  assert(node.Invalid == false);
  if (node.IsSplitter)
  {
    node.Direction = direction;
    node.Fraction = splitFraction;
  }
  else
  {
    const int child0 = get_child0(location);
    const int child1 = get_child1(location);
    if (static_cast<int>(internals.SBTree.size()) <= child1)
    {
      internals.SBTree.resize(child1 + 1);
    }
    assert(internals.SBTree[child0].Invalid && internals.SBTree[child1].Invalid);

    internals.SBTree[child0] = std::move(internals.SBTree[location]);
    if(internals.SBTree[child0].Item != nullptr)
    {
        internals.SBTree[child0].Item->widget()->setProperty("FRAME_INDEX", QVariant(child0));
    }
    internals.SBTree[child1] = BTNode(nullptr);
    internals.SBTree[location] = BTNode(direction, splitFraction);
  }

  this->invalidate();
}

//-----------------------------------------------------------------------------
void igwHierarchicalGridLayout::maximize(int location)
{
  auto& internals = *this->Internals;
  internals.maximize(location);
  this->invalidate();
}

//-----------------------------------------------------------------------------
QVector<QWidget*> igwHierarchicalGridLayout::rearrange(
  const QVector<igwHierarchicalGridLayout::Item>& litems)
{
  auto& internals = *this->Internals;
  QScopedValueRollback<bool> rollback(internals.Rearranging, true);

  // build a map of all QWidget instances and their QLayoutItem's we know
  // currently.
  std::map<QWidget*, QLayoutItem*> w2l;

  auto updateMap = [&internals, &w2l](QWidget* current) {
    for (auto litem : internals.Items)
    {
      if (auto wdg = litem->widget())
      {
        if (current == nullptr || wdg == current)
        {
          w2l[wdg] = litem;
        }
      }
    }
  };
  updateMap(nullptr);

  std::vector<BTNode> bstree(litems.size());
  std::function<void(int)> build = [&build, &litems, &bstree, &w2l, this, &updateMap](int index) {
    if (index < 0 || index >= litems.count())
    {
      return;
    }

    const auto& litem = litems[index];
    if (litem.Fraction >= 0.0)
    {
      bstree[index] = BTNode(litem.Direction, litem.Fraction);
      build(get_child0(index));
      build(get_child1(index));
    }
    else if (litem.Widget != nullptr)
    {
//      litem.Widget->setProperty("FRAME_INDEX", index);
      auto iter = w2l.find(litem.Widget);
      if (iter == w2l.end())
      {
        this->addWidget(litem.Widget);
        updateMap(litem.Widget);
        iter = w2l.find(litem.Widget);
      }
      if (iter != w2l.end())
      {
        assert(iter->second != nullptr); // same widget cannot be added twice to the tree.
        bstree[index] = BTNode(iter->second);
        iter->second = nullptr;
      }
    }
  };
  build(0);

  internals.SBTree.clear();
  internals.SBTree = std::move(bstree);


  for(int i = 0; i < internals.SBTree.size(); ++i)
  {
      if(internals.SBTree[i].Item != nullptr)
          internals.SBTree[i].Item->widget()->setProperty("FRAME_INDEX", QVariant(i));
  }
  QVector<QWidget*> removed;

  // delete QLayoutItem's for all QWidget's that are no longer placed in
  // the layout and return the QWidget instances back to the caller.
  for (auto& pair : w2l)
  {
    if (pair.second != nullptr)
    {
      removed.push_back(pair.first);

      // delete the QLayoutItem associated with the widget
      // we're passing back to the caller as unclaimed.
      this->removeItem(pair.second);
      delete pair.second;

      pair.second = nullptr;
    }
  }

  // iterate of QWidget's provided in the input argument that were potentially
  // unreachable to bad binary tree specification and return those in the
  // removed list as well.
  for (auto& litem : litems)
  {
    if (litem.Widget && w2l.find(litem.Widget) == w2l.end())
    {
      removed.push_back(litem.Widget);
    }
  }

  this->invalidate();
  return removed;
}

void igwHierarchicalGridLayout::removeLocation(int location)
{
//    this->removeItem(Internals->SBTree[location].Item);
//    this->invalidate();
//    this->update();
//    Internals->SBTree[location].Item = nullptr;


    int parentIndex = get_parent(location);
    int sibling = ((location % 2) == 0) ? (2 * parentIndex + 1) : (2 * parentIndex + 2);
    this->moveSubtree(parentIndex, sibling);
    this->shrink();
//    int child0 = get_child0(parentIndex);
//    int child1 = get_child1(parentIndex);
//    BTNode& currenNode = Internals->SBTree[location];
//    BTNode& leftNode = Internals->SBTree[child0];
//    BTNode& rightNode = Internals->SBTree[child1];
//    Internals->SBTree[parentIndex] =  (location == child0) ? rightNode : leftNode;
//    if(Internals->SBTree[parentIndex] == nullptr)
//    {
//        Internals->SBTree[parentIndex] = BTNode
//    }
//    Internals->SBTree[parentIndex].Item->widget()->setProperty("FRAME_INDEX", QVariant(parentIndex));
    QVector<Item> litems;
    int nodeSize = Internals->SBTree.size();
    litems.resize(nodeSize);
    for(int i = 0; i < nodeSize; ++i)
    {
        BTNode& node = Internals->SBTree[i];
        if(node.IsSplitter)
        {
            litems[i] = Item(node.Direction,node.Fraction);
        }
        else
        {

            litems[i] = Item(node.widget());
        }
    }
    QVector<QWidget*>ws  = rearrange(litems);
    for(auto& w : ws)
    {
        delete w;
    }
}

unsigned int igwHierarchicalGridLayout::getMaxChildIndex(unsigned int parent)
{
    if (Internals->SBTree[parent].Item != nullptr)
    {
        return parent;
    }

   size_t child1 = this->getMaxChildIndex(2 * parent + 1);
   size_t child2 = this->getMaxChildIndex(2 * parent + 2);
   return std::max(child1, child2);
}

void igwHierarchicalGridLayout::moveSubtree(int destination, int source)
{
    assert(destination >= 0 && source >= 0);

    assert(destination < source);

    if (source >= static_cast<int>(Internals->SBTree.size()) ||
     destination >= static_cast<int>(Internals->SBTree.size()))
    {
     return;
    }
    std::queue<int> sourceQueue;
    std::queue<int> destQueue;

    sourceQueue.push(source);
    destQueue.push(destination);

    int kdtreeSize = static_cast<int>(Internals->SBTree.size());

    while (!sourceQueue.empty())
    {
      int currentSource = sourceQueue.front();
      sourceQueue.pop();
      int currentDest = destQueue.front();
      destQueue.pop();

      // Copy source to destination.
      if (currentSource < kdtreeSize && currentDest < kdtreeSize)
      {
        Internals->SBTree[currentDest] = Internals->SBTree[currentSource];
        Internals->SBTree[currentSource] = BTNode();

        // Push children onto queue
        sourceQueue.push(get_child0(currentSource));
        sourceQueue.push(get_child1(currentSource));
        destQueue.push(get_child0(currentDest));
        destQueue.push(get_child1(currentDest));
      }
    }
}

void igwHierarchicalGridLayout::shrink()
{

    unsigned int max_index = this->getMaxChildIndex(0);
    assert(max_index < Internals->SBTree.size());
    Internals->SBTree.resize(max_index + 1);
}
