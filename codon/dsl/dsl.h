#pragma once

#include "codon/parser/cache.h"
#include "codon/sir/sir.h"
#include "codon/sir/transform/manager.h"
#include "codon/sir/transform/pass.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include <functional>
#include <string>
#include <vector>

namespace codon {

/// Base class for DSL plugins. Plugins will return an instance of
/// a child of this class, which defines various characteristics of
/// the DSL, like keywords and IR passes.
class DSL {
public:
  /// General information about this plugin.
  struct Info {
    /// Extension name
    std::string name;
    /// Extension description
    std::string description;
    /// Extension version
    std::string version;
    /// Extension URL
    std::string url;
    /// Supported Codon versions (semver range)
    std::string supported;
    /// Plugin stdlib path
    std::string stdlibPath;
  };

  using KeywordCallback =
      std::function<ast::StmtPtr(ast::SimplifyVisitor *, ast::CustomStmt *)>;

  struct ExprKeyword {
    std::string keyword;
    KeywordCallback callback;
  };

  struct BlockKeyword {
    std::string keyword;
    KeywordCallback callback;
    bool hasExpr;
  };

  virtual ~DSL() noexcept = default;

  /// Registers this DSL's IR passes with the given pass manager.
  /// @param pm the pass manager to add the passes to
  /// @param debug true if compiling in debug mode
  virtual void addIRPasses(ir::transform::PassManager *pm, bool debug) {}

  /// Registers this DSL's LLVM passes with the given pass manager builder.
  /// @param pmb the pass manager builder to add the passes to
  /// @param debug true if compining in debug mode
  virtual void addLLVMPasses(llvm::PassManagerBuilder *pmb, bool debug) {}

  /// Returns a vector of "expression keywords", defined as keywords of
  /// the form "keyword <expr>".
  /// @return this DSL's expression keywords
  virtual std::vector<ExprKeyword> getExprKeywords() { return {}; }

  /// Returns a vector of "block keywords", defined as keywords of the
  /// form "keyword <expr>: <block of code>".
  /// @return this DSL's block keywords
  virtual std::vector<BlockKeyword> getBlockKeywords() { return {}; }
};

} // namespace codon