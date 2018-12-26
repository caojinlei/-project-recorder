// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_LANGUAGE_GENERATOR_H_
#define DIALOGUE_LANGUAGE_GENERATOR_H_

#include <string>
#include <vector>

#include "dialogue/parameter_instance.h"
#include "interface/input.h"
#include "interface/slot.h"

namespace mobvoi {
namespace dialogue {

class TemplateNode;
class PlainText;
class SlotVariable;
class VariableCounter;
class ParameterVariable;
class OptionalNode;

//
// Base visitor class for `TemplateNode`. Any method below will try to
// convert node to std::string. If failed, the `out` won't be changed.
//
class LgBase {
 public:
  virtual bool Generate(const PlainText* node, std::string* out) = 0;
  virtual bool Generate(const SlotVariable* node, std::string* out) = 0;
  virtual bool Generate(const ParameterVariable* node, std::string* out) = 0;
  virtual bool Generate(const VariableCounter* node, std::string* out) = 0;
  virtual bool Generate(const OptionalNode* node, std::string* out) = 0;
  virtual bool Generate(const TemplateNode* node, std::string* out) = 0;

  virtual ~LgBase() {}
};

class LanguageGenerator {
 public:
  explicit LanguageGenerator(const std::string& lgTemplate)
      : parse_fail_(false) {
    template_ = lgTemplate;
    parse_fail_ = parse(template_, &nodes_) != 0;
  }

  bool valid() const { return !parse_fail_; }

  // Return empty string if the input lgTemplate is invalid.
  std::string generate(const Input& input,
      const std::vector<const Slot*>* slots,
      const std::vector<const ParameterInstance*>* parameters) const;

  ~LanguageGenerator();

 private:
  int parse(const std::string& lgTemplate, std::vector<TemplateNode*>* nodes);
  std::string generate(const std::vector<TemplateNode*>& nodes,
      const Input& input, const std::vector<const Slot*>* slots,
      const std::vector<const ParameterInstance*>* parameters) const;

 private:
  std::string                template_;
  std::vector<TemplateNode*> nodes_;
  bool parse_fail_;
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_LANGUAGE_GENERATOR_H_
