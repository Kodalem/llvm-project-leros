//===- LerosMCAsmInfo.cpp - Leros asm properties --------------------*- C++
//-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "LerosMCAsmInfo.h"
#include "llvm/ADT/Triple.h"

namespace llvm {
void LerosMCAsmInfo::anchor() {}

LerosMCAsmInfo::LerosMCAsmInfo(const Triple &TT) {
  CodePointerSize = CalleeSaveStackSlotSize = TT.isArch64Bit() ? 8 : 4;
  CommentString = "#";
  AlignmentIsInBytes = false;
  SupportsDebugInformation = true;
}
}
