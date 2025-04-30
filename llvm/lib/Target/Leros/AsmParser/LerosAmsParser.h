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

class LerosAsmParser : public llvm::MCAsmParserExtension {
public:
  bool MatchAndEmitInstruction(llvm::SMLoc IDLoc, unsigned &Opcode,
                               OperandVector &Operands,
                               llvm::MCStreamer &Out,
                               uint64_t &ErrorInfo,
                               bool MatchingInlineAsm);

  bool MatchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                             OperandVector &Operands,
                             MCStreamer &Out,
                             uint64_t &ErrorInfo,
                             bool MatchingInlineAsm);

};