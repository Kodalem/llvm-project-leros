//===- Leros.cpp ----------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Symbols.h"
#include "SyntheticSections.h"
#include "Target.h"
#include "lld/Common/ErrorHandler.h"
#include "llvm/Object/ELFObjectFile.h"
#include "llvm/Support/Endian.h"

using namespace llvm;
using namespace llvm::support::endian;
using namespace llvm::ELF;
using namespace lld;
using namespace lld::elf;
using namespace llvm::object;

namespace {
class Leros final : public TargetInfo {
public:
  Leros(Ctx &);
  uint32_t calcEFlags() const override;
  RelExpr getRelExpr(RelType type, const Symbol &s,
                     const uint8_t *loc) const override;
  void relocate(uint8_t *loc, const Relocation &rel,
                uint64_t val) const override;
};
} // namespace

Leros::Leros(Ctx &ctx) : TargetInfo(ctx) {
  //noneRel = R_LEROS_NONE;
  defaultCommonPageSize = 1024; // 1KB page size
  defaultMaxPageSize = 8192;    // 8KB max page size
  defaultImageBase = 0;
}

uint32_t Leros::calcEFlags() const {
  if (ctx.objectFiles.empty())
    return 0;

  // Use the e_flags from the first object file
  const InputFile *f = ctx.objectFiles[0];
  if (f->ekind == ELF64LEKind)
    return cast<ObjFile<ELF64LE>>(f)->getObj().getHeader().e_flags;
return cast<ObjFile<ELF32LE>>(f)->getObj().getHeader().e_flags;
}

RelExpr Leros::getRelExpr(RelType type, const Symbol &s,
                          const uint8_t *loc) const {
  switch (type) {
  case R_LEROS_BYTE0:
  case R_LEROS_BYTE1:
  case R_LEROS_BYTE2:
  case R_LEROS_BYTE3:
  case R_LEROS_32:
  case R_LEROS_64:
    return R_ABS;
  case R_LEROS_BRANCH:
    return R_PC;
  case R_LEROS_NONE:
    return R_NONE;
  default:
    Err(ctx) << getErrorLoc(ctx, loc) << "unknown relocation (" << type.v
             << ") against symbol " << &s;
    return R_NONE;
  }
}

void Leros::relocate(uint8_t *loc, const Relocation &rel, uint64_t val) const {
  uint16_t insn = read16le(loc) & 0xFF00;

  switch (rel.type) {
  case R_LEROS_32:
    write32le(loc, val);
    return;
  case R_LEROS_64:
    write64le(loc, val);
    return;
  case R_LEROS_BYTE0:
    checkInt(ctx, loc, static_cast<int64_t>(val), 32, rel);
    insn |= val & 0xFF;
    break;
  case R_LEROS_BYTE1:
    checkInt(ctx, loc, static_cast<int64_t>(val), 32, rel);
    insn |= (val >> 8) & 0xFF;
    break;
  case R_LEROS_BYTE2:
    checkInt(ctx, loc, static_cast<int64_t>(val), 32, rel);
    insn |= (val >> 16) & 0xFF;
    break;
  case R_LEROS_BYTE3:
    checkInt(ctx, loc, static_cast<int64_t>(val), 32, rel);
    insn |= (val >> 24) & 0xFF;
    break;
  case R_LEROS_BRANCH:
    // Verify that it is representable as a 13-bit immediate,
    // with lsb = 0
    checkInt(ctx, loc, static_cast<int64_t>(val), 13, rel);
    checkAlignment(ctx, loc, val, 2, rel);
    insn |= (val >> 1) & 0xFFF;
    break;
  default:
    llvm_unreachable("unknown relocation");
  }
  write16le(loc, insn);
}

void elf::setLerosTargetInfo(Ctx &ctx) { ctx.target.reset(new Leros(ctx)); }