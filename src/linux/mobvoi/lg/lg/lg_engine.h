// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_ENGINE_H_
#define LG_LG_ENGINE_H_

#include <vector>
#include <memory>

#include "lg/lg_appproxy.h"
#include "lg/lg_context.h"
#include "lg/lg_filled_response.h"
#include "lg/lg_resource.h"
#include "lg_interface/lg_result.h"

namespace mobvoi {
namespace lg {

class LgEngine {
 public:
  LgResult Generate(const LgContext &context,
                    std::weak_ptr<const LgAppProxy> app) const;

 private:
  const LgRule* MatchRules(const LgContext &context,
                           std::shared_ptr<const LgAppProxy> lgapp,
                           size_t* index) const;

  bool MatchRules(const LgContext &context,
                  std::shared_ptr<const LgAppProxy> lgapp,
                  const LgRule* rule) const;

  bool CheckConditions(const LgContext &context,
                       std::shared_ptr<const LgAppProxy> lgapp,
                       const LgConditions* conditions) const;

  bool CheckCondition(const LgContext &context,
                      std::shared_ptr<const LgAppProxy> lgapp,
                      const LgCondition* condition) const;

  bool FillResponses(const LgContext &context,
                     std::shared_ptr<const LgAppProxy> lgapp,
                     const LgResponses* responses,
                     std::vector<LgFilledResponse*>* out) const;

  bool FillChunks(const LgContext &context,
                  std::shared_ptr<const LgAppProxy> lgapp,
                  const LgChunks* chunks,
                  std::vector<LgFilledChunk*>* out) const;

  LgFilledChunk* FillChunk(const LgContext &context,
                           std::shared_ptr<const LgAppProxy> lgapp,
                           const LgChunk* chunk) const;

  LgFilledPhrase* FillVariable(const LgContext &context,
                               std::shared_ptr<const LgAppProxy> lgapp,
                               const LgVariable* variable) const;

  LgFilledPhrase* FillChunkPhrase(const LgContext &context,
                                  std::shared_ptr<const LgAppProxy> lgapp,
                                  std::shared_ptr<const LgRsChunk> rs_chunk,
                                  const LgChunk* chunk) const;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_ENGINE_H_
