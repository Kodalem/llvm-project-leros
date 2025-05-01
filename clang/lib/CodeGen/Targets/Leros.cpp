#include "ABIInfoImpl.h"
#include "TargetInfo.h"

using namespace clang;
using namespace clang::CodeGen;


//===----------------------------------------------------------------------===//
// Leros ABI Implementation.
//===----------------------------------------------------------------------===//

namespace {
class LerosTargetCodeGenInfo : public TargetCodeGenInfo {
public:
  LerosTargetCodeGenInfo(CodeGenTypes &CGT)
      : TargetCodeGenInfo(std::make_unique<DefaultABIInfo>(CGT)) {}
};
} // end anonymous namespace

std::unique_ptr<TargetCodeGenInfo>
CodeGen::createLerosTargetCodeGenInfo(CodeGenModule &CGM) {
  return std::make_unique<LerosTargetCodeGenInfo>(CGM.getTypes());
}