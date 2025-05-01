//===-- LerosAsmParser.cpp - Parse Leros assembly to MCInst instructions --===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Leros.h"
#include "MCTargetDesc/LerosMCExpr.h"
#include "MCTargetDesc/LerosMCTargetDesc.h"
#include "MCTargetDesc/LerosTargetStreamer.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstBuilder.h"
#include "llvm/MC/MCParser/MCAsmLexer.h"
#include "llvm/MC/MCParser/MCAsmParser.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/MC/MCParser/MCTargetAsmParser.h"
#include "llvm/MC/MCParser/MCAsmParserExtension.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h" // Ensure MCStreamer header is included
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/SMLoc.h"
#include "llvm/MC/TargetRegistry.h"
#include "LerosAmsParser.h"
#include <memory>

using namespace llvm;

namespace {
class LerosAsmParser : public MCTargetAsmParser {
  SMLoc getLoc() const { return getParser().getTok().getLoc(); }

  LerosTargetStreamer &getTargetStreamer() {
    MCTargetStreamer &TS = *getParser().getStreamer().getTargetStreamer();
    return static_cast<LerosTargetStreamer &>(TS);
  }

  unsigned validateTargetOperandClass(MCParsedAsmOperand &Op,
                                      unsigned Kind) override;

  bool matchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                               OperandVector &Operands, MCStreamer &Out,
                               uint64_t &ErrorInfo,
                               bool MatchingInlineAsm) override;

  bool parseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) override {
    ParseStatus Status = tryParseRegister(Reg, StartLoc, EndLoc);
    return !Status.isSuccess();
  }
  ParseStatus tryParseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) override;
  void convertToMapAndConstraints(unsigned Kind, unsigned &OpInfo,
                                  const MCExpr *&Expr);

  bool parseInstruction(ParseInstructionInfo &Info, StringRef Name,
                        SMLoc NameLoc, OperandVector &Operands) override;

  bool ParseDirective(AsmToken DirectiveID) override { return true; }

// Auto-generated instruction matching functions
#define GET_ASSEMBLER_HEADER
#include "LerosGenAsmMatcher.inc"

  bool parseOperand(OperandVector &Operands, StringRef Mnemonic);
  ParseStatus parseImmediate(OperandVector &Operands);
  bool ParseRegister(unsigned &RegNo, SMLoc &StartLoc, SMLoc &EndLoc);
  ParseStatus parseRegister(OperandVector &Operands);
  ParseStatus parseBareSymbol(OperandVector &Operands);

public:
  enum LerosMatchResultTy {
    Match_Dummy = FIRST_TARGET_MATCH_RESULT_TY,
#define GET_OPERAND_DIAGNOSTIC_TYPES
#include "LerosGenAsmMatcher.inc"
#undef GET_OPERAND_DIAGNOSTIC_TYPES
  };

  static bool classifySymbolRef(const MCExpr *Expr,
                                LerosMCExpr::VariantKind &Kind,
                                int64_t &Addend);

  LerosAsmParser(const MCSubtargetInfo &STI, MCAsmParser &Parser,
                 const MCInstrInfo &MII, const MCTargetOptions &Options)
      : MCTargetAsmParser(Options, STI, MII) {}
};

/// LerosOperand - Instances of this class represent a parsed machine
/// instruction
struct LerosOperand : public MCParsedAsmOperand {

  enum KindTy { Token, Register, Immediate, Memory } Kind;

  struct RegOp {
    unsigned RegNum;
  };

  struct ImmOp {
    const MCExpr *Val;
  };


  struct SysRegOp {
    const char *Data;
    unsigned Length;
    unsigned Encoding;
    // FIXME: Add the Encoding parsed fields as needed for checks,
    // e.g.: read/write or user/supervisor/machine privileges.
  };

  SMLoc StartLoc, EndLoc;
  union {
    StringRef Tok;
    RegOp Reg;
    ImmOp Imm;
    SysRegOp SysReg;
  };

  LerosOperand(KindTy K) : MCParsedAsmOperand(), Kind(K) {}

public:
  LerosOperand(const LerosOperand &o) : MCParsedAsmOperand() {
    Kind = o.Kind;
    StartLoc = o.StartLoc;
    EndLoc = o.EndLoc;
    switch (Kind) {
    case Register:
      Reg = o.Reg;
      break;
    case Immediate:
      Imm = o.Imm;
      break;
    case Token:
      Tok = o.Tok;
      break;
    case Memory:
      break;
    }
  }

  bool isToken() const override { return Kind == Token; }
  bool isReg() const override { return Kind == Register; }
  bool isImm() const override { return Kind == Immediate; }
  bool isMem() const override { return Kind == Memory; }

  /// getStartLoc - Gets location of the first token of this operand
  SMLoc getStartLoc() const override { return StartLoc; }
  /// getEndLoc - Gets location of the last token of this operand
  SMLoc getEndLoc() const override { return EndLoc; }

  MCRegister getReg() const override {
    assert(Kind == Register && "Invalid type access!");
    return Reg.RegNum;
  }

  void print(raw_ostream &OS) const override {
    switch (Kind) {
    case Immediate:
      OS << *getImm();
      break;
    case Register:
      OS << "<register r";
      OS << getReg().id() << ">";
      break;
    case Token:
      OS << "'" << getToken() << "'";
      break;
    case Memory:
      OS << "<memory>";
      break;
    }
  }

  static bool evaluateConstantImm(const MCExpr *Expr, int64_t &Imm,
                                  LerosMCExpr::VariantKind &VK) {
    if (auto *RE = dyn_cast<LerosMCExpr>(Expr)) {
      VK = RE->getKind();
      return RE->evaluateAsConstant(Imm);
    }

    if (auto CE = dyn_cast<MCConstantExpr>(Expr)) {
      VK = LerosMCExpr::VK_Leros_None;
      Imm = CE->getValue();
      return true;
    }

    return false;
  }

  bool isBareSymbol() const {
    int64_t Imm;
    LerosMCExpr::VariantKind VK;
    // Must be of 'immediate' type but not a constant.
    if (!isImm() || evaluateConstantImm(getImm(), Imm, VK))
      return false;
    return LerosAsmParser::classifySymbolRef(getImm(), VK, Imm) &&
           VK == LerosMCExpr::VK_Leros_None;
  }

  void addExpr(MCInst &Inst, const MCExpr *Expr) const {
    assert(Expr && "Expr shouldn't be null!");
    int64_t Imm = 0;
    LerosMCExpr::VariantKind VK;
    bool IsConstant = evaluateConstantImm(Expr, Imm, VK);

    if (IsConstant)
      Inst.addOperand(MCOperand::createImm(Imm));
    else
      Inst.addOperand(MCOperand::createExpr(Expr));
  }

  bool isUImm8() const {
    int64_t Imm;
    LerosMCExpr::VariantKind VK;
    if (!isImm())
      return false;
    bool IsConstantImm = evaluateConstantImm(getImm(), Imm, VK);
    return IsConstantImm && isUInt<8>(Imm) && VK == LerosMCExpr::VK_Leros_None;
  }

  bool isUImm7() const {
    int64_t Imm;
    LerosMCExpr::VariantKind VK;
    if (!isImm())
      return false;
    bool IsConstantImm = evaluateConstantImm(getImm(), Imm, VK);
    return IsConstantImm && isUInt<7>(Imm) && VK == LerosMCExpr::VK_Leros_None;
  }

  bool isSImm8() const {
    int64_t Imm;
    LerosMCExpr::VariantKind VK;
    if (!isImm())
      return false;
    bool IsConstantImm = evaluateConstantImm(getImm(), Imm, VK);
    return IsConstantImm && isInt<8>(Imm) && VK == LerosMCExpr::VK_Leros_None;
  }

  // True if operand is a symbol with no modifiers, or a constant with no
  // modifiers and isShiftedInt<N-S, S>(Op).
  template <int N, int S> bool isBareSimmNLsb0() const {
    int64_t Imm;
    LerosMCExpr::VariantKind VK;
    if (!isImm())
      return false;
    bool IsConstantImm = evaluateConstantImm(getImm(), Imm, VK);
    bool IsValid;
    if (!IsConstantImm)
      IsValid = LerosAsmParser::classifySymbolRef(getImm(), VK, Imm);
    else
      IsValid = isShiftedInt<N - S, S>(Imm);
    return IsValid && VK == LerosMCExpr::VK_Leros_None;
  }

  // True if operand is a symbol with no modifiers, or a constant with no
  // modifiers
  template <int N> bool isBareSimm() const {
    int64_t Imm;
    LerosMCExpr::VariantKind VK;
    if (!isImm())
      return false;
    bool IsConstantImm = evaluateConstantImm(getImm(), Imm, VK);
    bool IsValid = true;
    if (!IsConstantImm)
      IsValid = LerosAsmParser::classifySymbolRef(getImm(), VK, Imm);
    return IsValid && VK == LerosMCExpr::VK_Leros_None;
  }

  bool isSImm9Lsb0() const { return isBareSimmNLsb0<9, 1>(); }
  bool isSImm10Lsb00() const { return isBareSimmNLsb0<10, 2>(); }
  bool isSImm13Lsb0() const { return isBareSimmNLsb0<13, 1>(); }

  // Operand parser for signed 8-bit immediates which are either constants
  // or symbol references (used for load operations)
  bool isSImm8SymbolRef() const { return isBareSimm<8>(); }

  bool isImmXLen() const {
    int64_t Imm;
    LerosMCExpr::VariantKind VK;
    if (!isImm())
      return false;
    bool IsConstantImm = evaluateConstantImm(getImm(), Imm, VK);
    // Given only Imm, ensuring that the actually specified constant is either
    // a signed or unsigned 64-bit number is unfortunately impossible.
    bool IsInRange = isInt<32>(Imm);
    return IsConstantImm && IsInRange && VK == LerosMCExpr::VK_Leros_None;
  }

  const MCExpr *getImm() const {
    assert(Kind == Immediate && "Invalid type access!");
    return Imm.Val;
  }

  StringRef getToken() const {
    assert(Kind == Token && "Invalid type access!");
    return Tok;
  }

  void addRegOperands(MCInst &Inst, unsigned N) const {
    assert(N == 1 && "Invalid number of operands!");
    Inst.addOperand(MCOperand::createReg(getReg()));
  }

  void addImmOperands(MCInst &Inst, unsigned N) const {
    assert(N == 1 && "Invalid number of operands!");
    addExpr(Inst, getImm());
  }

  static std::unique_ptr<LerosOperand> createToken(StringRef Str, SMLoc S) {
    auto Op = std::make_unique<LerosOperand>(Token);
    Op->Tok = Str;
    Op->StartLoc = S;
    Op->EndLoc = S;
    return Op;
  }

  static std::unique_ptr<LerosOperand> createReg(unsigned RegNo, SMLoc S,
                                                 SMLoc E) {
    auto Op = std::make_unique<LerosOperand>(Register);
    Op->Reg.RegNum = RegNo;
    Op->StartLoc = S;
    Op->EndLoc = E;
    return Op;
  }

  static std::unique_ptr<LerosOperand> createImm(const MCExpr *Val, SMLoc S,
                                                 SMLoc E) {
    auto Op = std::make_unique<LerosOperand>(Immediate);
    Op->Imm.Val = Val;
    Op->StartLoc = S;
    Op->EndLoc = E;
    return Op;
  }
};

#define GET_REGISTER_MATCHER
#define GET_MATCHER_IMPLEMENTATION
#include "LerosGenAsmMatcher.inc"

ParseStatus tryParseRegister(MCRegister &Reg, SMLoc &StartLoc,
                            SMLoc &EndLoc);

ParseStatus LerosAsmParser::tryParseRegister(MCRegister &Reg, SMLoc &StartLoc,
                                            SMLoc &EndLoc) {
  const AsmToken &Tok = getParser().getTok();
  StartLoc = Tok.getLoc();
  EndLoc = Tok.getEndLoc();

  // Check if this is an identifier
  if (Tok.isNot(AsmToken::Identifier))
    return ParseStatus::NoMatch;

  StringRef Name = Tok.getString();

  // Try to match the register name
  Reg = MatchRegisterName(Name);
  if (Reg == 0)
    return ParseStatus::NoMatch;

  getParser().Lex(); // Consume the register token only on success
  return ParseStatus::Success;
}

void convertToMapAndConstraints(unsigned Kind,
                               const OperandVector &Operands,
                               MCRegister &RegFirst, MCRegister &RegLast,
                               SMLoc &StartLoc, SMLoc &EndLoc,
                               SmallVectorImpl<std::unique_ptr<MCParsedAsmOperand>> &Rewritten,
                               uint64_t &ErrorInfo,
                               bool &HasMatchingFeature) {
  // This is usually empty for simple architectures
  return;
}

ParseStatus LerosAsmParser::parseRegister(OperandVector &Operands) {
  switch (getLexer().getKind()) {
  default:
    return ParseStatus::NoMatch;
  case AsmToken::Identifier:
    StringRef Name = getLexer().getTok().getIdentifier();
    unsigned RegNo = MatchRegisterName(Name);
    if (RegNo == 0) {
      RegNo = MatchRegisterAltName(Name);
      if (RegNo == 0) {
        return ParseStatus::NoMatch;
      }
    }
    getLexer().Lex(); // Eat register token.
    SMLoc S = getLoc();
    SMLoc E = SMLoc::getFromPointer(S.getPointer() - 1);
    Operands.push_back(LerosOperand::createReg(RegNo, S, E));
  }
  return ParseStatus::Success;
}

bool LerosAsmParser::parseOperand(OperandVector &Operands, StringRef Mnemonic) {
  // Check if the current operand has a custom associated parser, if so, try to
  // custom parse the operand, or fallback to the general approach.
  ParseStatus Result = MatchOperandParserImpl(Operands, Mnemonic, /*ParseForAllFeatures=*/true);

  if (Result.isSuccess())
    return true;
  if (Result.isFailure())
    return true;

  // Attempt to parse as a register operand.
  if (parseRegister(Operands).isSuccess())
    return false;

  // Attempt to parse as an immediate operand.
  if (parseImmediate(Operands).isSuccess())
    return false;

  // Finally, try to parse bare symbol.
  Error(getLoc(), "unknown operand");
  return true;
}

ParseStatus LerosAsmParser::parseBareSymbol(OperandVector &Operands) {
  SMLoc S = getLoc();
  SMLoc E = SMLoc::getFromPointer(S.getPointer() - 1);
  const MCExpr *Res;

  if (getLexer().getKind() != AsmToken::Identifier)
    return ParseStatus::NoMatch;

  StringRef Identifier;
  if (getParser().parseIdentifier(Identifier))
    return ParseStatus::Failure;

  MCSymbol *Sym = getContext().getOrCreateSymbol(Identifier);
  Res = MCSymbolRefExpr::create(Sym, MCSymbolRefExpr::VK_None, getContext());
  Operands.push_back(LerosOperand::createImm(Res, S, E));
  return ParseStatus::Success;
}

ParseStatus LerosAsmParser::parseImmediate(OperandVector &Operands) {
  SMLoc S = getLoc();
  SMLoc E = SMLoc::getFromPointer(S.getPointer() - 1);
  const MCExpr *Res;

  switch (getLexer().getKind()) {
  default:
    return ParseStatus::NoMatch;
  case AsmToken::LParen:
  case AsmToken::Minus:
  case AsmToken::Plus:
  case AsmToken::Integer:
  case AsmToken::String:
    if (getParser().parseExpression(Res))
      return ParseStatus::Failure;
    break;
  case AsmToken::Identifier: {
    StringRef Identifier;
    // This calls parseIdentifier twice, maybe check MCAsmParser::parsePrimaryExpr?
    if (getParser().parseIdentifier(Identifier))
      return ParseStatus::Failure;
    MCSymbol *Sym = getContext().getOrCreateSymbol(Identifier);
    Res = MCSymbolRefExpr::create(Sym, MCSymbolRefExpr::VK_None, getContext());
    break;
  }
  }
  E = SMLoc::getFromPointer(getLoc().getPointer() - 1);

  Operands.push_back(LerosOperand::createImm(Res, S, E));
  return ParseStatus::Success;
}

bool LerosAsmParser::parseInstruction(ParseInstructionInfo &Info, StringRef Name,
                                     SMLoc NameLoc, OperandVector &Operands) {
  // First operand is token for instruction
  Operands.push_back(LerosOperand::createToken(Name, NameLoc));

  // If there are no more operands, then finish
  if (getLexer().is(AsmToken::EndOfStatement))
    return false;

  // Parse operands
  while (getLexer().isNot(AsmToken::EndOfStatement)) {
    if (parseOperand(Operands, Name))
      return true;

    // Check if the token is a comma, if so, eat it and continue
    if (getLexer().is(AsmToken::Comma))
      getLexer().Lex();
    else if (getLexer().isNot(AsmToken::EndOfStatement)) {
      SMLoc Loc = getLexer().getLoc();
      return Error(Loc, "unexpected token in operand list");
    }
  }

  Lex(); // Consume the EndOfStatement.
  return false;
}

unsigned LerosAsmParser::validateTargetOperandClass(MCParsedAsmOperand &AsmOp,
                                                    unsigned) {
  LerosOperand &Op = static_cast<LerosOperand &>(AsmOp);
  if (!Op.isReg())
    return Match_InvalidOperand;
  return Match_Success;
}

bool LerosAsmParser::matchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                                          OperandVector &Operands,
                                          MCStreamer &Out,
                                          uint64_t &ErrorInfo,
                                          bool MatchingInlineAsm) {
  MCInst Inst;

  auto Result =
      MatchInstructionImpl(Operands, Inst, ErrorInfo, MatchingInlineAsm);
  switch (Result) {
  default:
    break;
  case Match_Success: {
    Out.emitInstruction(Inst, getSTI());
    return false;
  }
  case Match_MissingFeature:
    return Error(IDLoc, "instruction use requires an option to be enabled");
  case Match_MnemonicFail:
    return Error(IDLoc, "unrecognized instruction mnemonic");
  case Match_InvalidOperand: {
    SMLoc ErrorLoc = Operands.empty() ? IDLoc : Operands[0]->getStartLoc(); // Default to operand 0 if ErrorInfo is invalid
    if (ErrorInfo != ~0U && ErrorInfo < Operands.size()) {
      ErrorLoc = ((LerosOperand &)*Operands[ErrorInfo]).getStartLoc();
      if (ErrorLoc == SMLoc())
        ErrorLoc = IDLoc;
    } else if (ErrorInfo >= Operands.size()) {
        // ErrorInfo points past the last operand.
        return Error(IDLoc, "too few operands for instruction");
    }
    return Error(ErrorLoc, "invalid operand for instruction");
  }
  }

  // Handle the case when the error message is of specific type
  // other than the generic Match_InvalidOperand, and the
  // corresponding operand is missing.
  if (Result > FIRST_TARGET_MATCH_RESULT_TY) {
    SMLoc ErrorLoc = IDLoc;
    if (ErrorInfo != ~0U && ErrorInfo >= Operands.size()) {
      return Error(ErrorLoc, "too few operands for instruction");
    } else if (ErrorInfo != ~0U) {
      ErrorLoc = ((LerosOperand &)*Operands[ErrorInfo]).getStartLoc();
    }
  }

  llvm_unreachable("Unknown match type detected!");
}

bool LerosAsmParser::classifySymbolRef(const MCExpr *Expr,
                                       LerosMCExpr::VariantKind &Kind,
                                       int64_t &Addend) {
  Kind = LerosMCExpr::VK_Leros_None;
  Addend = 0;

  if (const LerosMCExpr *RE = dyn_cast<LerosMCExpr>(Expr)) {
    Kind = RE->getKind();
    Expr = RE->getSubExpr();
  }

  // It's a simple symbol reference or constant with no addend.
  if (isa<MCConstantExpr>(Expr) || isa<MCSymbolRefExpr>(Expr))
    return true;

  const MCBinaryExpr *BE = dyn_cast<MCBinaryExpr>(Expr);
  if (!BE)
    return false;

  if (!isa<MCSymbolRefExpr>(BE->getLHS()))
    return false;

  if (BE->getOpcode() != MCBinaryExpr::Add &&
      BE->getOpcode() != MCBinaryExpr::Sub)
    return false;

  // We are able to support the subtraction of two symbol references
  if (BE->getOpcode() == MCBinaryExpr::Sub &&
      isa<MCSymbolRefExpr>(BE->getRHS()))
    return true;

  // See if the addend is a constant, otherwise there's more going
  // on here than we can deal with.
  auto AddendExpr = dyn_cast<MCConstantExpr>(BE->getRHS());
  if (!AddendExpr)
    return false;

  Addend = AddendExpr->getValue();
  if (BE->getOpcode() == MCBinaryExpr::Sub)
    Addend = -Addend;

  // It's some symbol reference + a constant addend
  return Kind != LerosMCExpr::VK_Leros_Invalid;
}

} // namespace

namespace llvm {

LerosAsmParser::LerosAsmParser(const MCSubtargetInfo &STI, MCAsmParser &Parser,
                               const MCInstrInfo &MII, const MCTargetOptions &Options)
    : MCTargetAsmParser(Options, STI, MII), LerosParser(Parser) {}

bool LerosAsmParser::parseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) {
  ParseStatus Status = tryParseRegister(Reg, StartLoc, EndLoc);
  return !Status.isSuccess();
}

ParseStatus LerosAsmParser::tryParseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) {
  const AsmToken &Tok = getParser().getTok();
  StartLoc = Tok.getLoc();
  EndLoc = Tok.getEndLoc();

  if (Tok.isNot(AsmToken::Identifier))
    return ParseStatus::NoMatch;

  StringRef Name = Tok.getString();
  Reg = MatchRegisterName(Name);
  if (Reg == 0)
    return ParseStatus::NoMatch;

  getParser().Lex(); // Consume the register token
  return ParseStatus::Success;
}

void LerosAsmParser::convertToMapAndConstraints(unsigned Kind, const OperandVector &Operands) {
  // Simple implementation for now
}

} // end namespace llvm

extern "C" void LLVMInitializeLerosAsmParser() {
  RegisterMCAsmParser<llvm::LerosAsmParser> X(getTheLeros32Target());
  RegisterMCAsmParser<llvm::LerosAsmParser> Y(getTheLeros64Target());
}

