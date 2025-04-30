//===-- LerosTargetMachine.h - Define TargetMachine for Leros ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Leros specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Leros_LerosTARGETMACHINE_H
#define LLVM_LIB_TARGET_Leros_LerosTARGETMACHINE_H

#include "LerosSubtarget.h"
#include "MCTargetDesc/LerosMCTargetDesc.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include "llvm/CodeGen/CommandFlags.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class LerosTargetMachine : public CodeGenTargetMachineImpl {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  LerosSubtarget Subtarget;

public:
  LerosTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     std::optional<Reloc::Model> RM, std::optional<CodeModel::Model> CM,
                     CodeGenOptLevel OL, bool JIT);

  const TargetSubtargetInfo *getSubtargetImpl(const Function &) const {
    return &Subtarget;
  }

  TargetPassConfig *
  createPassConfig(llvm::legacy::PassManagerBase &PM) ;

  TargetLoweringObjectFile *getObjFileLowering() const {
    return TLOF.get();
  }
};
}

#endif
