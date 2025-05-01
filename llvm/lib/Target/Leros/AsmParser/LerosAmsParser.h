// LerosAsmParser.h
#pragma once

#include "llvm/MC/MCParser/MCAsmParser.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/MC/MCParser/MCTargetAsmParser.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstBuilder.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCStreamer.h"   // for llvm::MCStreamer
#include "llvm/Support/SMLoc.h"   // for llvm::SMLoc
#include "llvm/MC/MCParser/MCParsedAsmOperand.h" // for OperandVector
#include <memory>

namespace llvm {

class LerosAsmParser : public MCTargetAsmParser { // Inherit from MCTargetAsmParser

public:
  MCAsmParser &LerosParser;

  MCAsmParser &getParser() const { return LerosParser; }
  MCAsmLexer &getLexer() const { return getParser().getLexer(); }

  // Declare the parseOperand method
  bool parseOperand(OperandVector &Operands, StringRef Mnemonic);

  // Constructor needs to match MCTargetAsmParser requirements or initialize members appropriately
  LerosAsmParser(const MCSubtargetInfo &STI, MCAsmParser &Parser,
                 const MCInstrInfo &MII, const MCTargetOptions &Options);
  bool parseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) override;
  ParseStatus tryParseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) override;
  void convertToMapAndConstraints(unsigned Kind, const OperandVector &Operands) override;

  // Declare ParseInstruction as an override if it matches the base class
  // signature
  bool parseInstruction(ParseInstructionInfo &Info, StringRef Name,
                        SMLoc NameLoc, OperandVector &Operands) override;

  // Declare MatchAndEmitInstruction as an override
  bool matchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                               OperandVector &Operands, MCStreamer &Out,
                               uint64_t &ErrorInfo,
                               bool MatchingInlineAsm) override;

  // Declare ParseRegister if it's part of the public interface or used internally
  bool ParseRegister(unsigned &RegNo, SMLoc &StartLoc, SMLoc &EndLoc);

  // isMem might need adjustment based on its purpose
  bool isMem() const;

  // Required by MCTargetAsmParser
  unsigned validateTargetOperandClass(MCParsedAsmOperand &Op,
                                      unsigned Required) override;
  bool generateImmOutOfRangeError(OperandVector &Operands, uint64_t ErrorInfo,
                                  int64_t Lower, int64_t Upper, Twine Msg);
};

} // end namespace llvm
