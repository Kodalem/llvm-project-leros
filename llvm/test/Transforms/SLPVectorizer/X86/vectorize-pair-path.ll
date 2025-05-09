; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -passes=slp-vectorizer -mattr=+avx2 -S | FileCheck %s

target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; In this test case we start trying to vectorize reduction but end up
; in tryToVectorize() method which then can make several attempts to
; find a pair (roots) for a tree that can be vectorized.
; The order (path) it makes probes for various pairs is predefined by
; the method implementation and it is not guaranteed that the best option
; encountered first (like here).

define double @root_selection(double %a, double %b, double %c, double %d) local_unnamed_addr #0 {
; CHECK-LABEL: @root_selection(
; CHECK-NEXT:    [[TMP1:%.*]] = insertelement <2 x double> poison, double [[B:%.*]], i32 0
; CHECK-NEXT:    [[TMP2:%.*]] = insertelement <2 x double> [[TMP1]], double [[A:%.*]], i32 1
; CHECK-NEXT:    [[TMP3:%.*]] = fdiv fast <2 x double> [[TMP2]], <double 5.000000e+00, double 7.000000e+00>
; CHECK-NEXT:    [[TMP4:%.*]] = extractelement <2 x double> [[TMP3]], i32 0
; CHECK-NEXT:    [[I09:%.*]] = fmul fast double [[TMP4]], undef
; CHECK-NEXT:    [[I10:%.*]] = fsub fast double undef, [[I09]]
; CHECK-NEXT:    [[TMP5:%.*]] = fmul fast <2 x double> [[TMP3]], <double undef, double 3.000000e+00>
; CHECK-NEXT:    [[TMP6:%.*]] = insertelement <2 x double> <double poison, double undef>, double [[I10]], i32 0
; CHECK-NEXT:    [[TMP7:%.*]] = fmul fast <2 x double> [[TMP6]], [[TMP5]]
; CHECK-NEXT:    [[TMP8:%.*]] = fsub fast <2 x double> [[TMP7]], <double 1.100000e+01, double undef>
; CHECK-NEXT:    [[TMP9:%.*]] = fmul fast <2 x double> [[TMP8]], <double 1.200000e+01, double 4.000000e+00>
; CHECK-NEXT:    [[TMP10:%.*]] = fdiv fast <2 x double> [[TMP9]], splat (double 1.400000e+00)
; CHECK-NEXT:    [[TMP11:%.*]] = extractelement <2 x double> [[TMP10]], i32 1
; CHECK-NEXT:    [[I07:%.*]] = fadd fast double undef, [[TMP11]]
; CHECK-NEXT:    [[TMP12:%.*]] = extractelement <2 x double> [[TMP10]], i32 0
; CHECK-NEXT:    [[I16:%.*]] = fadd fast double [[I07]], [[TMP12]]
; CHECK-NEXT:    [[I17:%.*]] = fadd fast double [[I16]], [[C:%.*]]
; CHECK-NEXT:    [[I18:%.*]] = fadd fast double [[I17]], [[D:%.*]]
; CHECK-NEXT:    ret double [[I18]]
;
  %i01 = fdiv fast double %a, 7.0
  %i02 = fmul fast double %i01, 3.0
  %i03 = fmul fast double undef, %i02
  %i04 = fsub fast double %i03, undef
  %i05 = fmul fast double %i04, 4.0
  %i06 = fdiv fast double %i05, 1.4
  %i07 = fadd fast double undef, %i06
  %i08 = fdiv fast double %b, 5.0
  %i09 = fmul fast double %i08, undef
  %i10 = fsub fast double undef, %i09
  %i11 = fmul fast double %i08, undef
  %i12 = fmul fast double %i10, %i11
  %i13 = fsub fast double %i12, 11.0
  %i14 = fmul fast double %i13, 12.0
  %i15 = fdiv fast double %i14, 1.4
  %i16 = fadd fast double %i07, %i15
  %i17 = fadd fast double %i16, %c
  %i18 = fadd fast double %i17, %d
  ret double %i18
}

attributes #0 = { "unsafe-fp-math"="true" }
