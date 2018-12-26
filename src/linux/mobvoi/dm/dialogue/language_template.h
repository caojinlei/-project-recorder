// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: shtxie@mobvoi.com (Shoutao Xie)

#ifndef DIALOGUE_LANGUAGE_TEMPLATE_H_
#define DIALOGUE_LANGUAGE_TEMPLATE_H_

#include <sstream>
#include <string>
#include <vector>

#include "mobvoi/base/string_piece.h"

namespace mobvoi {
namespace dialogue {

typedef StringPiece Slice;

enum TemplateNodeType {
  kUnknownNode = 0,
  kPlainTextNode,
  kSlotNode,
  kParameterNode,
  kCounterNode,
  kOptionalNode,
};

extern std::string TemplateNodeTypeToString(int type);

class LgBase;

class TemplateNode {
 public:
  virtual ~TemplateNode() {}
  virtual TemplateNodeType type() const = 0;

  virtual std::string Accept(LgBase* lg) = 0;

  void set_origin(const char* data, size_t length) {
    origin_ = Slice(data, length);
  }

  Slice origin() const { return origin_; }

 private:
  Slice origin_;
};

class PlainText : public TemplateNode {
 public:
  // PlainText don't own the |char* data|
  PlainText(const char* data, size_t length) : data_(data), length_(length) {}
  virtual TemplateNodeType type() const { return kPlainTextNode; }
  virtual std::string Accept(LgBase* lg);

 private:
  const char* data_;
  size_t length_;
};

class VariableNode : public TemplateNode {
 public:
  explicit VariableNode(const Slice& name) : name_(name) {}
  Slice name() const { return name_; }

 protected:
  Slice name_;
};

class SlotVariable : public VariableNode {
 public:
  explicit SlotVariable(const Slice& name) : VariableNode(name) {}

  virtual TemplateNodeType type() const { return kSlotNode; }
  virtual std::string Accept(LgBase* lg);
};

class ParameterVariable : public VariableNode {
 public:
  explicit ParameterVariable(const Slice& name)
      : VariableNode(name), index_(-1), json_path_() {}

  ParameterVariable(const Slice& name, int index)
      : VariableNode(name), index_(index), json_path_() {}

  ParameterVariable(const Slice& name, int index, const Slice& json_path)
      : VariableNode(name), index_(index), json_path_(json_path) {}

  virtual TemplateNodeType type() const { return kParameterNode; }
  virtual std::string Accept(LgBase* lg);
  int index() const { return index_; }
  Slice jpath() const { return json_path_; }

 private:
  int index_;
  Slice json_path_;
};

class VariableCounter : public TemplateNode {
 public:
  // VariableCounter will own |VariableNode* var|
  explicit VariableCounter(VariableNode* var) : var_(var) {}
  ~VariableCounter() { delete var_; }

  virtual TemplateNodeType type() const { return kCounterNode; }
  virtual std::string Accept(LgBase* lg);
  VariableNode* variable() const { return var_; }

 private:
  VariableNode* var_;
};

class OptionalNode : public TemplateNode {
 public:
  void Add(TemplateNode* node) { nodes_.push_back(node); }

  size_t size() const { return nodes_.size(); }

  const TemplateNode* operator[](size_t i) const { return nodes_[i]; }

  ~OptionalNode() {
    for (int i = 0; i < nodes_.size(); i++) {
      delete nodes_[i];
    }
  }

  virtual TemplateNodeType type() const { return kOptionalNode; }
  virtual std::string Accept(LgBase* lg);

 private:
  std::vector<TemplateNode*> nodes_;
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_LANGUAGE_TEMPLATE_H_
