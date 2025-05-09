set(LLVM_TARGET_DEFINITIONS Leros.td)

tablegen(LLVM LerosGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM LerosGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM LerosGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM LerosGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM LerosGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM LerosGenCallingConv.inc -gen-callingconv)
tablegen(LLVM LerosGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM LerosGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM LerosGenDisassemblerTables.inc -gen-disassembler)

add_public_tablegen_target(LerosCommonTableGen)

add_llvm_target(LerosCodeGen
 LerosInstrInfo.cpp
 LerosTargetMachine.cpp
 LerosSubtarget.cpp
 LerosISelDAGToDAG.cpp
 LerosRegisterInfo.cpp
 LerosFrameLowering.cpp
 LerosAsmPrinter.cpp
 LerosMCInstLower.cpp
 LerosTargetObjectFile.cpp
 LerosISelLowering.cpp
 LerosUseAccumulator.cpp
 LerosMachineFunctionInfo.cpp
)

add_subdirectory(AsmParser)
add_subdirectory(InstPrinter)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
add_subdirectory(Disassembler)

# Aggregate all the components under the Leros target name.
add_llvm_component_group(Leros LINK_COMPONENTS
        LerosCodeGen
        LerosAsmParser
        LerosDisassembler
        LerosInstPrinter
        LerosMCTargetDesc
        LerosTargetInfo
        LerosAsmPrinter
        LerosISelDAGToDAG
        LerosFrameLowering
        LerosISelLowering
        LerosMachineFunctionInfo
        LerosRegisterInfo
        LerosSubtarget
        LerosTargetObjectFile
        LerosUseAccumulator
        LerosMCInstLower
        LerosGenRegisterInfo
        LerosGenInstrInfo
        LerosGenCallingConv
        LerosGenSubtargetInfo
        LerosGenMCCodeEmitter
        LerosGenDisassemblerTables
        LerosGenAsmWriter
        LerosGenAsmMatcher
        LerosGenDAGISel
        LerosGenMCCodeEmitter
        LerosGenDisassemblerTables
        LerosGenAsmWriter
)