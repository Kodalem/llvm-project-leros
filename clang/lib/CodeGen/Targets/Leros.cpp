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
      : TargetCodeGenInfo(new DefaultABIInfo(CGT)) {}
};
}