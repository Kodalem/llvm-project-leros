//===--- Leros.h - Declare Leros target feature support ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares Leros TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_Leros_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_Leros_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/TargetParser/Triple.h"
#include "llvm/Support/Compiler.h"
#include "llvm/ADT/SmallVector.h" // Add this include

namespace clang {
namespace targets {

// RISC-V Target
class LerosTargetInfo : public TargetInfo {
protected:
  std::string ABI;

public:
  LerosTargetInfo(const llvm::Triple &Triple, const TargetOptions &)
      : TargetInfo(Triple) {
    TLSSupported = false;
    LongDoubleWidth = 128;
    LongDoubleAlign = 128;
    LongDoubleFormat = &llvm::APFloat::IEEEquad();
    SuitableAlign = 128;
    WCharType = SignedInt;
    WIntType = UnsignedInt;
  }

  StringRef getABI() const override { return ABI; }
  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  llvm::SmallVector<Builtin::InfosShard>
  getTargetBuiltins() const override {
    return {};
  }

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }

  std::string_view getClobbers() const override { return {}; }

  ArrayRef<const char *> getGCCRegNames() const override;

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override;

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &Info) const override {
    return false;
  }

  bool hasFeature(StringRef Feature) const override;
};
class LLVM_LIBRARY_VISIBILITY Leros32TargetInfo : public LerosTargetInfo {
public:
  Leros32TargetInfo(const llvm::Triple &Triple, const TargetOptions &Opts)
      : LerosTargetInfo(Triple, Opts) {
    IntPtrType = SignedInt;
    PtrDiffType = SignedInt;
    SizeType = UnsignedInt;
    resetDataLayout("e-m:e-p:32:32-i64:64-n32-S128");
  }

  bool setABI(const std::string &Name) override {
    // TODO: support ilp32f and ilp32d ABIs.
    if (Name == "ilp32") {
      ABI = Name;
      return true;
    }
    return false;
  }
};
class LLVM_LIBRARY_VISIBILITY Leros64TargetInfo : public LerosTargetInfo {
public:
  Leros64TargetInfo(const llvm::Triple &Triple, const TargetOptions &Opts)
      : LerosTargetInfo(Triple, Opts) {
    LongWidth = LongAlign = PointerWidth = PointerAlign = 64;
    IntMaxType = Int64Type = SignedLong;
    resetDataLayout("e-m:e-p:64:64-i64:64-i128:128-n64-S128");
  }

  bool setABI(const std::string &Name) override {
    // TODO: support lp64f and lp64d ABIs.
    if (Name == "lp64") {
      ABI = Name;
      return true;
    }
    return false;
  }
};
} // namespace targets
} // namespace clang

#endif // LLVM_CLANG_LIB_BASIC_TARGETS_Leros_H
