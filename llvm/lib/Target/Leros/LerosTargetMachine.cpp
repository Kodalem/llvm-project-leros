//===-- LerosTargetMachine.cpp - Define TargetMachine for Leros -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Leros target spec.
//
//===----------------------------------------------------------------------===//

#include "LerosTargetMachine.h"
#include "Leros.h"
#include "LerosTargetObjectFile.h"
#include "MCTargetDesc/LerosMCTargetDesc.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Target/TargetOptions.h"

namespace llvm {
extern "C" void LLVMInitializeLerosTarget() {
  RegisterTargetMachine<LerosTargetMachine> X(getTheLeros32Target());
  RegisterTargetMachine<LerosTargetMachine> Y(getTheLeros64Target());
}

static std::string computeDataLayout(const Triple &TT) {
  if (TT.isArch64Bit()) {
    return "e-m:e-p:64:64-i64:64-i128:128-n64-S128";
  } else {
    return "e-m:e-p:32:32-i64:64-n32-S128";
  }
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           std::optional<Reloc::Model> RM) {
  if (!RM)
    return Reloc::Static;
  return *RM;
}

static CodeModel::Model getEffectiveCodeModel(std::optional<CodeModel::Model> CM) {
  if (CM)
    return *CM;
  return CodeModel::Small;
}

LerosTargetMachine::LerosTargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     std::optional<Reloc::Model> RM,
                                     std::optional<CodeModel::Model> CM,
                                     CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, computeDataLayout(TT), TT, CPU, FS, Options,
                             getEffectiveRelocModel(TT, RM),
                             getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, CPU, FS, *this) {
  initAsmInfo();
}

namespace {
class LerosPassConfig : public TargetPassConfig {
public:
  LerosPassConfig(LerosTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  LerosTargetMachine &getLerosTargetMachine() const {
    return getTM<LerosTargetMachine>();
  }

  bool addInstSelector() override;
  void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *LerosTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new LerosPassConfig(*this, PM);
}

void LerosPassConfig::addPreEmitPass() {
  addPass(createLerosUseAccumulatorPass());
}

bool LerosPassConfig::addInstSelector() {
  addPass(createLerosISelDag(getLerosTargetMachine()));

  return false;
}
} // namespace llvm
