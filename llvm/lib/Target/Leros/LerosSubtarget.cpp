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

namespace llvm {

void LerosSubtarget::initializeSubtargetDependencies(StringRef CPU,
                                                     StringRef FS,
                                                     const Triple &TT) {
  std::string CPUName = CPU;
  if (CPUName.empty()) {
    if (TT.isArch64Bit()) {
      CPUName = "generic-leros64";
      XLen = 64;
      XLenVT = MVT::i64;
    } else {
      CPUName = "generic-leros32";
    }
  }
  ParseSubtargetFeatures(CPUName, FS);
}

LerosSubtarget::LerosSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                               const TargetMachine &TM)
    : LerosGenSubtargetInfo(TT, CPU, FS), FrameLowering(*this), InstrInfo(),
      RegInfo(getHwMode()), TLInfo(TM, *this) {

  initializeSubtargetDependencies(CPU, FS, TT);
}
}
