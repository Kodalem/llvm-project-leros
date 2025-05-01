//===- LerosSubtarget.cpp - Leros Subtarget Information ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the Leros specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#include "LerosSubtarget.h"

#define DEBUG_TYPE "leros-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "LerosGenSubtargetInfo.inc"

#include "llvm/CodeGen/MachineFrameInfo.h"

namespace llvm {

void LerosSubtarget::initializeSubtargetDependencies(StringRef CPU,
                                                     StringRef FS,
                                                     const Triple &TT) {
  std::string CPUName = CPU.str();
  if (CPUName.empty()) {
    if (TT.isArch64Bit()) {
      CPUName = "generic-leros64";
      XLen = 64;
      XLenVT = MVT::i64;
    } else {
      CPUName = "generic-leros32";
    }
  }
  // Pass CPUName as both CPU and TuneCPU parameters
  ParseSubtargetFeatures(CPUName, CPUName, FS);
}

bool LerosFrameLowering::hasFPImpl(const MachineFunction &MF) const {
  const MachineFrameInfo &MFI = MF.getFrameInfo();
  return MF.getTarget().Options.DisableFramePointerElim(MF) ||
         MFI.hasVarSizedObjects() ||
         MFI.isFrameAddressTaken();
}

LerosSubtarget::LerosSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                               const TargetMachine &TM)
    : LerosGenSubtargetInfo(TT, CPU, CPU, FS), FrameLowering(*this), InstrInfo(),
      RegInfo(LerosGenSubtargetInfo::getHwMode()), TLInfo(TM, *this) {

  initializeSubtargetDependencies(CPU, FS, TT);
}
}
