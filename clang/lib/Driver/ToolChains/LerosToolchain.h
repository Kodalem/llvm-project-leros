//===--- Leros.h - Leros Tool and ToolChain Implementations ---------*- C++
//-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_Leros_H
#define LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_Leros_H

#include "llvm/Option/ArgList.h"
#include "llvm/Support/Compiler.h"
#include "clang/Driver/InputInfo.h"
#include "clang/Driver/ToolChain.h"
#include "clang/Driver/Tool.h"
#include "ToolChains/Gnu.h" // Add this include

namespace clang {
namespace driver {
namespace toolchains {

class LLVM_LIBRARY_VISIBILITY LerosToolChain : public Generic_ELF {
protected:
  Tool *buildLinker() const override;

public:
  LerosToolChain(const Driver &D, const llvm::Triple &Triple,
                 const llvm::opt::ArgList &Args);

  RuntimeLibType GetDefaultRuntimeLibType() const override;

  bool IsIntegratedAssemblerDefault() const override { return true; }
};

} // end namespace toolchains

namespace tools {
namespace Leros {
class LLVM_LIBRARY_VISIBILITY Linker : public Tool {
public:
  Linker(const ToolChain &TC) : Tool("Leros::Linker", "ld.lld", TC) {}
  bool hasIntegratedCPP() const override { return false; }
  bool isLinkJob() const override { return true; }
  void ConstructJob(Compilation &C, const JobAction &JA,
                    const InputInfo &Output, const InputInfoList &Inputs,
                    const llvm::opt::ArgList &TCArgs,
                    const char *LinkingOutput) const override;
};
} // end namespace Leros
} // end namespace tools
} // end namespace driver
} // end namespace clang

#endif // LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_Leros_H
