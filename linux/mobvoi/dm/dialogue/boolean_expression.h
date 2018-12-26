// Copyright 2018 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_BOOLEAN_EXPRESSION_H_
#define DIALOGUE_BOOLEAN_EXPRESSION_H_

#include <map>
#include <memory>
#include <set>
#include <string>

#include "third_party/jsoncpp/json.h"

namespace mobvoi {

class Slot;

namespace dialogue {

class TcpTaskInstance;
class Variable;

class BooleanExpression {
 public:
  enum class Operator : char {
    kNone = 0,
    kEqual,         // =, ==
    kNotEqual,      // !=
    kLessThan,      // <
    kGreatThan,     // >
    kLessEqual,     // <=
    kGreatEqual,    // >=
  };

  enum class Relation : char {
    kNone = 0,
    kAnd,           // &&
    kOr,            // ||
  };

 public:
  static Operator ToOperator(const std::string& str);
  static Relation ToRelation(const std::string& str);

  static std::string ToString(const Operator op);
  static std::string ToString(const Relation relation);

  static BooleanExpression* Parse(const std::string& exp,
                                  std::set<std::string>* deps);

 public:
  virtual ~BooleanExpression();
  virtual bool Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                        const std::map<std::string, const Slot*>& slots,
                        bool def) const = 0;

 protected:
  static BooleanExpression* Parse(const std::string& exp, size_t* cur,
                                  std::set<std::string>* deps);
};

class RelationalBooleanExpression : public BooleanExpression {
 protected:
  /* static RelationalBooleanExpression* Parse(const std::string& exp,
                                            size_t* cur); */

 public:
  ~RelationalBooleanExpression();
  bool Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                const std::map<std::string, const Slot*>& slots,
                bool def) const override;

 protected:
  RelationalBooleanExpression();

  BooleanExpression::Relation relation_;
  BooleanExpression*          left_;
  BooleanExpression*          right_;

  friend class BooleanExpression;
};

class ConstBooleanExpression : public BooleanExpression {
 protected:
  static ConstBooleanExpression* Parse(const std::string& exp, size_t* cur);

 public:
  ~ConstBooleanExpression();
  bool Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                const std::map<std::string, const Slot*>& slots,
                bool def) const override;

 protected:
  explicit ConstBooleanExpression(bool value);
  bool  value_;

  friend class BooleanExpression;
};

class OperatorBooleanExpression : public BooleanExpression {
 protected:
  static OperatorBooleanExpression* Parse(const std::string& exp, size_t* cur,
                                          std::set<std::string>* deps);

 public:
  ~OperatorBooleanExpression();
  bool Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                const std::map<std::string, const Slot*>& slots,
                bool def) const override;

 protected:
  OperatorBooleanExpression();

  Variable*                   left_;
  BooleanExpression::Operator operator_;
  Variable*                   right_;

  friend class BooleanExpression;
};

class Variable {
 public:
  virtual ~Variable();
  static Variable* Parse(const std::string& exp, size_t* cur,
                         std::set<std::string>* deps);
  virtual std::string Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                               const std::map<std::string, const Slot*>& slots,
                               const std::string& def) const = 0;
  virtual double Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                          const std::map<std::string, const Slot*>& slots,
                          const double def) const = 0;
};

// $contact_name$
class SlotVar : public Variable {
 public:
  SlotVar();
  ~SlotVar();
  static SlotVar* Parse(const std::string& exp, size_t begin, size_t end);
  std::string Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                       const std::map<std::string, const Slot*>& slots,
                       const std::string& def) const override;
  double Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                  const std::map<std::string, const Slot*>& slots,
                  const double def) const override;

 protected:
  std::string slot_name_;

  friend class Variable;
  friend class CountVar;
  friend class BooleanExpression;
  friend class RelationalBooleanExpression;
  friend class ConstBooleanExpression;
  friend class OperatorBooleanExpression;
};

// {destination[0].type} {destination[0].type}
class KnowledgeVar : public Variable {
 public:
  KnowledgeVar();
  ~KnowledgeVar();
  static KnowledgeVar* Parse(const std::string& exp, size_t begin, size_t end,
                             std::set<std::string>* deps);
  std::string Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                       const std::map<std::string, const Slot*>& slots,
                       const std::string& def) const override;
  double Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                  const std::map<std::string, const Slot*>& slots,
                  const double def) const override;

 protected:
  std::string param_name_;
  int         index_;
  std::string jpath_;

  friend class Variable;
  friend class CountVar;
  friend class BooleanExpression;
  friend class RelationalBooleanExpression;
  friend class ConstBooleanExpression;
  friend class OperatorBooleanExpression;
};

// #destination#
class ResolverVar : public Variable {
 public:
  ResolverVar();
  ~ResolverVar();
  static ResolverVar* Parse(const std::string& exp, size_t begin, size_t end,
                            std::set<std::string>* deps);
  std::string Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                       const std::map<std::string, const Slot*>& slots,
                       const std::string& def) const override;
  double Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                  const std::map<std::string, const Slot*>& slots,
                  const double def) const override;

 protected:
  std::string param_name_;

  friend class Variable;
  friend class BooleanExpression;
  friend class RelationalBooleanExpression;
  friend class ConstBooleanExpression;
  friend class OperatorBooleanExpression;
};

// @{destination} @$contact_name$
class CountVar : public Variable {
 public:
  CountVar();
  ~CountVar();
  // static CountVar* Parse(const std::string& exp, size_t begin, size_t end);
  std::string Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                       const std::map<std::string, const Slot*>& slots,
                       const std::string& def) const override;
  double Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                  const std::map<std::string, const Slot*>& slots,
                  const double def) const override;

 protected:
  Variable* variable_;

  friend class Variable;
  friend class BooleanExpression;
  friend class RelationalBooleanExpression;
  friend class ConstBooleanExpression;
  friend class OperatorBooleanExpression;
};

// ::function(param)
class FunctionVar : public Variable {
 public:
  FunctionVar();
  ~FunctionVar();
  static FunctionVar* Parse(const std::string& exp, size_t begin, size_t end,
                            std::set<std::string>* deps);
  std::string Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                       const std::map<std::string, const Slot*>& slots,
                       const std::string& def) const override;
  double Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                  const std::map<std::string, const Slot*>& slots,
                  const double def) const override;

 protected:
  std::string function_name_;
  std::string param_value_;

  friend class Variable;
  friend class BooleanExpression;
  friend class RelationalBooleanExpression;
  friend class ConstBooleanExpression;
  friend class OperatorBooleanExpression;
};

// 'string' "string"
class StringConstants : public Variable {
 public:
  StringConstants();
  ~StringConstants();
  static StringConstants* Parse(const std::string& exp, size_t* cur);
  std::string Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                       const std::map<std::string, const Slot*>& slots,
                       const std::string& def) const override;
  double Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                  const std::map<std::string, const Slot*>& slots,
                  const double def) const override;

 protected:
  std::string value_;

  friend class Variable;
  friend class BooleanExpression;
  friend class RelationalBooleanExpression;
  friend class ConstBooleanExpression;
  friend class OperatorBooleanExpression;
};

// 1 1.0
class DoubleConstants : public Variable {
 public:
  DoubleConstants();
  ~DoubleConstants();
  static DoubleConstants* Parse(const std::string& exp, size_t* cur);
  std::string Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                       const std::map<std::string, const Slot*>& slots,
                       const std::string& def) const override;
  double Evaluate(std::shared_ptr<TcpTaskInstance> instance,
                  const std::map<std::string, const Slot*>& slots,
                  const double def) const override;

 protected:
  double      value_;

  friend class Variable;
  friend class BooleanExpression;
  friend class RelationalBooleanExpression;
  friend class ConstBooleanExpression;
  friend class OperatorBooleanExpression;
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_BOOLEAN_EXPRESSION_H_
