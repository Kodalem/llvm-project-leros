//===--- Leros.cpp - Leros ToolChain Implementations ----------------*- C++
//-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "LerosToolchain.h"
#include "CommonArgs.h"
#include "clang/Driver/Compilation.h"
#include "clang/Driver/Driver.h"
#include "clang/Driver/InputInfo.h"
#include "clang/Driver/Options.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Support/FileSystem.h"
#include <memory>

using namespace clang::driver;
using namespace clang::driver::toolchains;
using namespace clang;
using namespace llvm::opt;

/// Leros Toolchain
LerosToolChain::LerosToolChain(const Driver &D, const llvm::Triple &Triple,
                               const ArgList &Args)
    : Generic_ELF(D, Triple, Args) {}
Tool *LerosToolChain::buildLinker() const {
  return new tools::Leros::Linker(*this);
}

ToolChain::RuntimeLibType LerosToolChain::GetDefaultRuntimeLibType() const {
  return ToolChain::RLT_CompilerRT;
}

void clang::driver::tools::Leros::Linker::ConstructJob(Compilation &C, const JobAction &JA,
                                                      const InputInfo &Output,
                                                      const InputInfoList &Inputs,
                                                      const ArgList &Args,
                                                      const char *LinkingOutput) const {
  const ToolChain &ToolChain = getToolChain();
  std::string Linker = ToolChain.GetProgramPath(getShortName());
  ArgStringList CmdArgs;

  if (!Args.hasArg(options::OPT_nostdlib, options::OPT_nostartfiles)) {
    CmdArgs.push_back(
        Args.MakeArgString(ToolChain.GetFilePath("crt0.leros.o")));
  }

  AddLinkerInputs(getToolChain(), Inputs, Args, CmdArgs, JA);

  if (!Args.hasArg(options::OPT_nostdlib, options::OPT_nodefaultlibs)) {

    // Grab builints library from compiler-rt
    // CmdArgs.push_back("-lc");
    AddRunTimeLibs(ToolChain, ToolChain.getDriver(), CmdArgs, Args);
  }

  CmdArgs.push_back("-o");
  CmdArgs.push_back(Output.getFilename());
  C.addCommand(std::make_unique<Command>( // Use std::make_unique
      JA, *this, ResponseFileSupport::None(), // Add ResponseFileSupport::None()
      Args.MakeArgString(Linker), CmdArgs, Inputs));
}
// Leros tools end.
