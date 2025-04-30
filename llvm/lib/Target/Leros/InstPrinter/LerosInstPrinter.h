//== LerosInstPrinter.h - Convert Leros MCInst to assembly syntax -*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints a Leros MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_LEROS_INSTPRINTER_RISCVINSTPRINTER_H
#define LLVM_LIB_TARGET_LEROS_INSTPRINTER_RISCVINSTPRINTER_H

#include "MCTargetDesc/LerosMCTargetDesc.h"
#include "llvm/MC/MCInstPrinter.h"

namespace llvm {

class TargetMachine;

class LerosInstPrinter : public MCInstPrinter {
public:
  LerosInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                   const MCRegisterInfo &MRI)
      : MCInstPrinter(MAI, MII, MRI) {}

  // Add this line to declare the printInst method
  void printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
                 const MCSubtargetInfo &STI, raw_ostream &O) override;

  void printRegName(raw_ostream &O, MCRegister Reg) override;
  std::pair<const char *, uint64_t> getMnemonic(const MCInst &MI) const override;
  bool printAliasInstr(const MCInst *MI, raw_ostream &O);

private:
  void printCondCode(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printAddrModeMemSrc(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O);
};
} // end namespace llvm

#endif
