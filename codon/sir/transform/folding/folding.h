#pragma once

#include "codon/sir/transform/cleanup/canonical.h"
#include "codon/sir/transform/cleanup/dead_code.h"
#include "codon/sir/transform/cleanup/global_demote.h"
#include "codon/sir/transform/pass.h"

namespace codon {
namespace ir {
namespace transform {
namespace folding {

class FoldingPass;

/// Group of constant folding passes.
class FoldingPassGroup : public PassGroup {
private:
  cleanup::GlobalDemotionPass *gd;
  cleanup::CanonicalizationPass *canon;
  FoldingPass *fp;
  cleanup::DeadCodeCleanupPass *dce;

public:
  static const std::string KEY;
  std::string getKey() const override { return KEY; }

  /// @param sideEffectsPass the key of the side effects pass
  /// @param reachingDefPass the key of the reaching definitions pass
  /// @param globalVarPass the key of the global variables pass
  FoldingPassGroup(const std::string &sideEffectsPass,
                   const std::string &reachingDefPass, const std::string &globalVarPass,
                   bool runGlobalDemotion = true);

  bool shouldRepeat() const override;
};

} // namespace folding
} // namespace transform
} // namespace ir
} // namespace codon