// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: shtxie@mobvoi.com (Shoutao Xie)

#ifndef DIALOGUE_LANGUAGE_TEMPLATE_LEXER_H_
#define DIALOGUE_LANGUAGE_TEMPLATE_LEXER_H_

#include "dialogue/language_template.h"

#include <string>
#include <vector>

#include "mobvoi/base/log.h"

namespace mobvoi {
namespace dialogue {

enum TemplateErrorCode {
  kNoError = 0,

  // the start marker char is wrong.
  kBadStartMarker,

  // miss the symbol after '\'
  kEscapeMissSymbol,

  // "No valid identifier can be found after
  kMissIdentifer,

  // lack of a '$' at slot end.
  kMissSlotEnd,

  // expect '[' for parameter node index
  kMissIndexStart,

  // expect a valid number after '['
  kInvalidIndex,

  // lack of a ']' at parameter node index end.
  kMissIndexEnd,

  // lack of a '}' at parameter node end.
  kMissParamEnd,

  // unrecognized char after parameter id
  kBadAfterParamId,

  // expect a variable after '@' but no found.
  kMissVariable,

  // unrecognized variable after '@'.
  kUnknownVar,

  // bad format variable after '@'.
  kBadVar,

  // lack of a '}' at counter end.
  kMissCounterEnd,

  // Bad format sub node
  kBadSubNode,

  // lack of a ']' at optional node end.
  kMissOptionalEnd
};

// Error builder when lexer parsing on language template.
// Error location and reason will be tracked.
class TemplateErrorBuilder {
 public:
  struct Err {
    size_t curr_pos;
    TemplateNodeType curr_node;
    TemplateErrorCode error_code;

    Err(size_t pos, TemplateNodeType node, TemplateErrorCode code)
        : curr_pos(pos), curr_node(node), error_code(code) {}
  };

  TemplateErrorBuilder() {}

  std::string ToString();

  void AppendError(size_t curr_pos, TemplateNodeType curr_node,
                   TemplateErrorCode error_code) {
    err_stack_.push_back(Err(curr_pos, curr_node, error_code));
  }

  bool has_error() { return err_stack_.size() > 0; }

 private:
  std::vector<Err> err_stack_;
};

// Scanner for language template. The `lexer` naming may not appropriate but I
// can't find another better name..
class TemplateLexer {
 public:
  TemplateLexer(const Slice& src, TemplateErrorBuilder* eb)
      : src_(src), curr_pos_(0), eb_(eb) {}

  // Consume a template node (defined in language_template.h)
  // If meet end or error, this method will return NULL.
  // The error will be stored in TemplateErrorBuilder passed on constructor.
  TemplateNode* ConsumeNode();

 private:
  static inline bool IsIdentifierContinuingChar(char c) {
    return IsIdentifierFirstChar(c) || IsNumber(c);
  }

  static inline bool IsIdentifierFirstChar(char c) {
    return c == '_' || IsAlpha(c);
  }

  static inline bool IsNumber(char c) { return c >= '0' && c <= '9'; }

  static inline bool IsAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
  }

  static inline bool IsKeyChar(char c) {
    return c == '$' || c == '{' || c == '}' || c == '[' || c == ']' ||
           c == '@' || c == '\\';
  }

  inline char current() { return src_[curr_pos_]; }

  inline bool at_end() { return curr_pos_ == src_.size(); }

  inline void Advance() { curr_pos_++; }

  inline void Advance(char c) {
    DCHECK(src_[curr_pos_] == c);
    curr_pos_++;
  }

  inline bool has_error() { return eb_->has_error(); }

  Slice ConsumeIdentifer();

  Slice ConsumeInteger();

  Slice ConsumeIndex();

  PlainText* ConsumePlainText();

  SlotVariable* ConsumeSlot();

  ParameterVariable* ConsumeParameter();

  VariableCounter* ConsumeCounter();

  TemplateNode* ConsumeOptional();

 private:
  Slice src_;
  size_t curr_pos_;
  TemplateErrorBuilder* eb_;
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_LANGUAGE_TEMPLATE_LEXER_H_
