//===--- Leros.cpp - Implement Leros target feature support ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements Leros TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#include "Leros.h"
#include "clang/Basic/MacroBuilder.h"
#include "llvm/ADT/StringSwitch.h"

using namespace clang;
using namespace clang::targets;

ArrayRef<const char *> LerosTargetInfo::getGCCRegNames() const {
  static const char *const GCCRegNames[] = {
      "x0",  "x1",  "x2",  "x3",  "x4",  "x5",  "x6",  "x7",
      "x8",  "x9",  "x10", "x11", "x12", "x13", "x14", "x15",
      "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23",
      "x24", "x25", "x26", "x27", "x28", "x29", "x30", "x31"};
  return llvm::makeArrayRef(GCCRegNames);
}

ArrayRef<TargetInfo::GCCRegAlias> LerosTargetInfo::getGCCRegAliases() const {
  static const TargetInfo::GCCRegAlias GCCRegAliases[] = {
      {{"zero"}, "x0"}, {{"ra"}, "x1"},  {{"sp"}, "x2"},   {{"gp"}, "x3"},
      {{"tp"}, "x4"},   {{"t0"}, "x5"},  {{"t1"}, "x6"},   {{"t2"}, "x7"},
      {{"s0"}, "x8"},   {{"s1"}, "x9"},  {{"a0"}, "x10"},  {{"a1"}, "x11"},
      {{"a2"}, "x12"},  {{"a3"}, "x13"}, {{"a4"}, "x15"},  {{"a5"}, "x15"},
      {{"a6"}, "x16"},  {{"a7"}, "x17"}, {{"s2"}, "x18"},  {{"s3"}, "x19"},
      {{"s4"}, "x20"},  {{"s5"}, "x21"}, {{"s6"}, "x22"},  {{"s7"}, "x23"},
      {{"s8"}, "x24"},  {{"s9"}, "x25"}, {{"s10"}, "x26"}, {{"s11"}, "x27"},
      {{"t3"}, "x28"},  {{"t4"}, "x29"}, {{"t5"}, "x30"},  {{"t6"}, "x31"}};
  return llvm::makeArrayRef(GCCRegAliases);
}

void LerosTargetInfo::getTargetDefines(const LangOptions &,
                                       MacroBuilder &Builder) const {
  Builder.defineMacro("__ELF__");
  Builder.defineMacro("__leros__");
  bool Is64Bit = getTriple().getArch() == llvm::Triple::leros64;
  Builder.defineMacro("__leros_xlen__", Is64Bit ? "64" : "32");
  // TODO: modify when more code models and ABIs are supported.
  Builder.defineMacro("__leros_cmodel_medlow__");
  Builder.defineMacro("__leros_float_abi_soft__");
}

/// Return true if has this feature, need to sync with handleTargetFeatures.
bool LerosTargetInfo::hasFeature(StringRef Feature) const {
  bool Is64Bit = getTriple().getArch() == llvm::Triple::leros64;
  return llvm::StringSwitch<bool>(Feature)
      .Case("Leros", true)
      .Case("Leros32", !Is64Bit)
      .Case("Leros64", Is64Bit)
      .Default(false);
}
