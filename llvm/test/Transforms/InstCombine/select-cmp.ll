; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -passes=instcombine -S | FileCheck %s

define i1 @f(i1 %cond, i32 %x, i32 %x2) {
; CHECK-LABEL: @f(
; CHECK-NEXT:    [[C:%.*]] = icmp eq i32 [[X:%.*]], [[X2:%.*]]
; CHECK-NEXT:    ret i1 [[C]]
;
  %y = select i1 %cond, i32 poison, i32 %x
  %c = icmp eq i32 %y, %x2
  ret i1 %c
}

define i1 @icmp_ne_common_op00(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_ne_common_op00(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp ne i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp ne i6 %x, %y
  %cmp2 = icmp ne i6 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_ne_samesign_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_ne_samesign_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp ne i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp samesign ne i6 %x, %y
  %cmp2 = icmp ne i6 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_ne_common_op01(i1 %c, i3 %x, i3 %y, i3 %z) {
; CHECK-LABEL: @icmp_ne_common_op01(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i3 [[Y:%.*]], i3 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp ne i3 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp ne i3 %x, %y
  %cmp2 = icmp ne i3 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_ne_common_op10(i1 %c, i4 %x, i4 %y, i4 %z) {
; CHECK-LABEL: @icmp_ne_common_op10(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i4 [[Y:%.*]], i4 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp ne i4 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp ne i4 %y, %x
  %cmp2 = icmp ne i4 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define <3 x i1> @icmp_ne_common_op11(<3 x i1> %c, <3 x i17> %x, <3 x i17> %y, <3 x i17> %z) {
; CHECK-LABEL: @icmp_ne_common_op11(
; CHECK-NEXT:    [[R_V:%.*]] = select <3 x i1> [[C:%.*]], <3 x i17> [[Y:%.*]], <3 x i17> [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp ne <3 x i17> [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret <3 x i1> [[R]]
;
  %cmp1 = icmp ne <3 x i17> %y, %x
  %cmp2 = icmp ne <3 x i17> %z, %x
  %r = select <3 x i1> %c, <3 x i1> %cmp1, <3 x i1> %cmp2
  ret <3 x i1> %r
}

define i1 @icmp_eq_common_op00(i1 %c, i5 %x, i5 %y, i5 %z) {
; CHECK-LABEL: @icmp_eq_common_op00(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i5 [[Y:%.*]], i5 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp eq i5 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp eq i5 %x, %y
  %cmp2 = icmp eq i5 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_eq_samesign_common(i1 %c, i5 %x, i5 %y, i5 %z) {
; CHECK-LABEL: @icmp_eq_samesign_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i5 [[Y:%.*]], i5 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp eq i5 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp eq i5 %x, %y
  %cmp2 = icmp samesign eq i5 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define <5 x i1> @icmp_eq_common_op01(<5 x i1> %c, <5 x i7> %x, <5 x i7> %y, <5 x i7> %z) {
; CHECK-LABEL: @icmp_eq_common_op01(
; CHECK-NEXT:    [[R_V:%.*]] = select <5 x i1> [[C:%.*]], <5 x i7> [[Y:%.*]], <5 x i7> [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp eq <5 x i7> [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret <5 x i1> [[R]]
;
  %cmp1 = icmp eq <5 x i7> %x, %y
  %cmp2 = icmp eq <5 x i7> %z, %x
  %r = select <5 x i1> %c, <5 x i1> %cmp1, <5 x i1> %cmp2
  ret <5 x i1> %r
}

define i1 @icmp_eq_common_op10(i1 %c, i32 %x, i32 %y, i32 %z) {
; CHECK-LABEL: @icmp_eq_common_op10(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i32 [[Y:%.*]], i32 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp eq i32 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp eq i32 %y, %x
  %cmp2 = icmp eq i32 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_eq_common_op11(i1 %c, i64 %x, i64 %y, i64 %z) {
; CHECK-LABEL: @icmp_eq_common_op11(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i64 [[Y:%.*]], i64 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp eq i64 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp eq i64 %y, %x
  %cmp2 = icmp eq i64 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_common_one_use_1(i1 %c, i8 %x, i8 %y, i8 %z) {
; CHECK-LABEL: @icmp_common_one_use_1(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp eq i8 [[Y:%.*]], [[X:%.*]]
; CHECK-NEXT:    call void @use(i1 [[CMP1]])
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i8 [[Y]], i8 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp eq i8 [[X]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp eq i8 %y, %x
  call void @use(i1 %cmp1)
  %cmp2 = icmp eq i8 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_slt_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_slt_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp slt i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp slt i6 %x, %y
  %cmp2 = icmp slt i6 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_slt_samesign_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_slt_samesign_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp slt i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp samesign ult i6 %x, %y
  %cmp2 = icmp slt i6 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_sgt_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_sgt_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp sgt i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp sgt i6 %x, %y
  %cmp2 = icmp sgt i6 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_sgt_samesign_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_sgt_samesign_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp sgt i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp samesign ugt i6 %x, %y
  %cmp2 = icmp sgt i6 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_sle_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_sle_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp sge i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp sle i6 %y, %x
  %cmp2 = icmp sle i6 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_sle_samesign_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_sle_samesign_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp sge i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp sle i6 %y, %x
  %cmp2 = icmp samesign ule i6 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_sge_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_sge_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp sle i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp sge i6 %y, %x
  %cmp2 = icmp sge i6 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_sge_samesign_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_sge_samesign_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp sle i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp sge i6 %y, %x
  %cmp2 = icmp samesign uge i6 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_slt_sgt_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_slt_sgt_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp slt i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp slt i6 %x, %y
  %cmp2 = icmp sgt i6 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_slt_sgt_samesign_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_slt_sgt_samesign_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp slt i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp samesign ult i6 %x, %y
  %cmp2 = icmp sgt i6 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_sle_sge_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_sle_sge_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp sge i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp sle i6 %y, %x
  %cmp2 = icmp sge i6 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_sle_sge_samesign_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_sle_sge_samesign_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp sge i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp sle i6 %y, %x
  %cmp2 = icmp samesign uge i6 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_ult_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_ult_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp ult i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp ult i6 %x, %y
  %cmp2 = icmp ult i6 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_ule_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_ule_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp uge i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp ule i6 %y, %x
  %cmp2 = icmp ule i6 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_ugt_common(i1 %c, i8 %x, i8 %y, i8 %z) {
; CHECK-LABEL: @icmp_ugt_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i8 [[Y:%.*]], i8 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp ult i8 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp ugt i8 %y, %x
  %cmp2 = icmp ugt i8 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_uge_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_uge_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp ule i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp uge i6 %y, %x
  %cmp2 = icmp uge i6 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_ult_ugt_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_ult_ugt_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp ult i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp ult i6 %x, %y
  %cmp2 = icmp ugt i6 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @icmp_ule_uge_common(i1 %c, i6 %x, i6 %y, i6 %z) {
; CHECK-LABEL: @icmp_ule_uge_common(
; CHECK-NEXT:    [[R_V:%.*]] = select i1 [[C:%.*]], i6 [[Y:%.*]], i6 [[Z:%.*]]
; CHECK-NEXT:    [[R:%.*]] = icmp uge i6 [[X:%.*]], [[R_V]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp ule i6 %y, %x
  %cmp2 = icmp uge i6 %x, %z
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

; negative test: pred is not the same

define i1 @icmp_common_pred_different(i1 %c, i8 %x, i8 %y, i8 %z) {
; CHECK-LABEL: @icmp_common_pred_different(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp eq i8 [[Y:%.*]], [[X:%.*]]
; CHECK-NEXT:    [[CMP2:%.*]] = icmp ne i8 [[Z:%.*]], [[X]]
; CHECK-NEXT:    [[R:%.*]] = select i1 [[C:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp eq i8 %y, %x
  %cmp2 = icmp ne i8 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

; negative test for non-equality: two pred is not swap

define i1 @icmp_common_pred_not_swap(i1 %c, i8 %x, i8 %y, i8 %z) {
; CHECK-LABEL: @icmp_common_pred_not_swap(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp slt i8 [[Y:%.*]], [[X:%.*]]
; CHECK-NEXT:    [[CMP2:%.*]] = icmp sle i8 [[Z:%.*]], [[X]]
; CHECK-NEXT:    [[R:%.*]] = select i1 [[C:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp slt i8 %y, %x
  %cmp2 = icmp sle i8 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

; negative test for non-equality: not commute pred

define i1 @icmp_common_pred_not_commute_pred(i1 %c, i8 %x, i8 %y, i8 %z) {
; CHECK-LABEL: @icmp_common_pred_not_commute_pred(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp slt i8 [[Y:%.*]], [[X:%.*]]
; CHECK-NEXT:    [[CMP2:%.*]] = icmp sgt i8 [[Z:%.*]], [[X]]
; CHECK-NEXT:    [[R:%.*]] = select i1 [[C:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp slt i8 %y, %x
  %cmp2 = icmp sgt i8 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

; negative test: both icmp is not one-use

define i1 @icmp_common_one_use_0(i1 %c, i8 %x, i8 %y, i8 %z) {
; CHECK-LABEL: @icmp_common_one_use_0(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp eq i8 [[Y:%.*]], [[X:%.*]]
; CHECK-NEXT:    call void @use(i1 [[CMP1]])
; CHECK-NEXT:    [[CMP2:%.*]] = icmp eq i8 [[Z:%.*]], [[X]]
; CHECK-NEXT:    call void @use(i1 [[CMP2]])
; CHECK-NEXT:    [[R:%.*]] = select i1 [[C:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp eq i8 %y, %x
  call void @use(i1 %cmp1)
  %cmp2 = icmp eq i8 %z, %x
  call void @use(i1 %cmp2)
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

; negative test: no common op

define i1 @icmp_no_common(i1 %c, i8 %x, i8 %y, i8 %z) {
; CHECK-LABEL: @icmp_no_common(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp eq i8 [[Y:%.*]], 0
; CHECK-NEXT:    [[CMP2:%.*]] = icmp eq i8 [[Z:%.*]], [[X:%.*]]
; CHECK-NEXT:    [[R:%.*]] = select i1 [[C:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[R]]
;
  %cmp1 = icmp eq i8 %y, 0
  %cmp2 = icmp eq i8 %z, %x
  %r = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %r
}

define i1 @test_select_inverse_eq(i64 %x, i1 %y) {
; CHECK-LABEL: @test_select_inverse_eq(
; CHECK-NEXT:    [[CMP2:%.*]] = icmp eq i64 [[X:%.*]], 0
; CHECK-NEXT:    [[SEL:%.*]] = xor i1 [[Y:%.*]], [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp ne i64 %x, 0
  %cmp2 = icmp eq i64 %x, 0
  %sel = select i1 %y, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_signed(i64 %x, i1 %y) {
; CHECK-LABEL: @test_select_inverse_signed(
; CHECK-NEXT:    [[CMP2:%.*]] = icmp slt i64 [[X:%.*]], 0
; CHECK-NEXT:    [[SEL:%.*]] = xor i1 [[Y:%.*]], [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp sgt i64 %x, -1
  %cmp2 = icmp slt i64 %x, 0
  %sel = select i1 %y, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_unsigned(i64 %x, i1 %y) {
; CHECK-LABEL: @test_select_inverse_unsigned(
; CHECK-NEXT:    [[CMP2:%.*]] = icmp ugt i64 [[X:%.*]], 10
; CHECK-NEXT:    [[SEL:%.*]] = xor i1 [[Y:%.*]], [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp ult i64 %x, 11
  %cmp2 = icmp ugt i64 %x, 10
  %sel = select i1 %y, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_eq_ptr(ptr %x, i1 %y) {
; CHECK-LABEL: @test_select_inverse_eq_ptr(
; CHECK-NEXT:    [[CMP2:%.*]] = icmp ne ptr [[X:%.*]], null
; CHECK-NEXT:    [[SEL:%.*]] = xor i1 [[Y:%.*]], [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp eq ptr %x, null
  %cmp2 = icmp ne ptr %x, null
  %sel = select i1 %y, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_fail(i64 %x, i1 %y) {
; CHECK-LABEL: @test_select_inverse_fail(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp sgt i64 [[X:%.*]], 0
; CHECK-NEXT:    [[CMP2:%.*]] = icmp slt i64 [[X]], 0
; CHECK-NEXT:    [[SEL:%.*]] = select i1 [[Y:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp sgt i64 %x, 0
  %cmp2 = icmp slt i64 %x, 0
  %sel = select i1 %y, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define <2 x i1> @test_select_inverse_vec(<2 x i64> %x, <2 x i1> %y) {
; CHECK-LABEL: @test_select_inverse_vec(
; CHECK-NEXT:    [[CMP2:%.*]] = icmp eq <2 x i64> [[X:%.*]], zeroinitializer
; CHECK-NEXT:    [[SEL:%.*]] = xor <2 x i1> [[Y:%.*]], [[CMP2]]
; CHECK-NEXT:    ret <2 x i1> [[SEL]]
;
  %cmp1 = icmp ne <2 x i64> %x, zeroinitializer
  %cmp2 = icmp eq <2 x i64> %x, zeroinitializer
  %sel = select <2 x i1> %y, <2 x i1> %cmp1, <2 x i1> %cmp2
  ret <2 x i1> %sel
}

define <2 x i1> @test_select_inverse_vec_fail(<2 x i64> %x, i1 %y) {
; CHECK-LABEL: @test_select_inverse_vec_fail(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp ne <2 x i64> [[X:%.*]], zeroinitializer
; CHECK-NEXT:    [[CMP2:%.*]] = icmp eq <2 x i64> [[X]], zeroinitializer
; CHECK-NEXT:    [[SEL:%.*]] = select i1 [[Y:%.*]], <2 x i1> [[CMP1]], <2 x i1> [[CMP2]]
; CHECK-NEXT:    ret <2 x i1> [[SEL]]
;
  %cmp1 = icmp ne <2 x i64> %x, zeroinitializer
  %cmp2 = icmp eq <2 x i64> %x, zeroinitializer
  %sel = select i1 %y, <2 x i1> %cmp1, <2 x i1> %cmp2
  ret <2 x i1> %sel
}

define i1 @test_select_inverse_nonconst1(i64 %x, i64 %y, i1 %cond) {
; CHECK-LABEL: @test_select_inverse_nonconst1(
; CHECK-NEXT:    [[CMP2:%.*]] = icmp eq i64 [[X:%.*]], [[Y:%.*]]
; CHECK-NEXT:    [[SEL:%.*]] = xor i1 [[COND:%.*]], [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp ne i64 %x, %y
  %cmp2 = icmp eq i64 %x, %y
  %sel = select i1 %cond, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_nonconst2(i64 %x, i64 %y, i1 %cond) {
; CHECK-LABEL: @test_select_inverse_nonconst2(
; CHECK-NEXT:    [[CMP2:%.*]] = icmp eq i64 [[Y:%.*]], [[X:%.*]]
; CHECK-NEXT:    [[SEL:%.*]] = xor i1 [[COND:%.*]], [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp ne i64 %x, %y
  %cmp2 = icmp eq i64 %y, %x
  %sel = select i1 %cond, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_nonconst3(i64 %x, i64 %y, i1 %cond) {
; CHECK-LABEL: @test_select_inverse_nonconst3(
; CHECK-NEXT:    [[CMP2:%.*]] = icmp uge i64 [[X:%.*]], [[Y:%.*]]
; CHECK-NEXT:    [[SEL:%.*]] = xor i1 [[COND:%.*]], [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp ult i64 %x, %y
  %cmp2 = icmp uge i64 %x, %y
  %sel = select i1 %cond, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_nonconst4(i64 %x, i64 %y, i64 %z, i1 %cond) {
; CHECK-LABEL: @test_select_inverse_nonconst4(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp ult i64 [[X:%.*]], [[Y:%.*]]
; CHECK-NEXT:    [[CMP2:%.*]] = icmp uge i64 [[Z:%.*]], [[Y]]
; CHECK-NEXT:    [[SEL:%.*]] = select i1 [[COND:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp ult i64 %x, %y
  %cmp2 = icmp uge i64 %z, %y
  %sel = select i1 %cond, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_samesign_true_arm(i64 %x, i64 %y, i1 %cond) {
; CHECK-LABEL: @test_select_inverse_samesign_true_arm(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp samesign ult i64 [[X:%.*]], [[Y:%.*]]
; CHECK-NEXT:    [[CMP2:%.*]] = icmp uge i64 [[X]], [[Y]]
; CHECK-NEXT:    [[SEL:%.*]] = select i1 [[COND:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp samesign ult i64 %x, %y
  %cmp2 = icmp uge i64 %x, %y
  %sel = select i1 %cond, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_samesign_false_arm(i64 %x, i64 %y, i1 %cond) {
; CHECK-LABEL: @test_select_inverse_samesign_false_arm(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp ult i64 [[X:%.*]], [[Y:%.*]]
; CHECK-NEXT:    [[CMP2:%.*]] = icmp samesign uge i64 [[X]], [[Y]]
; CHECK-NEXT:    [[SEL:%.*]] = select i1 [[COND:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp ult i64 %x, %y
  %cmp2 = icmp samesign uge i64 %x, %y
  %sel = select i1 %cond, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_samesign_both(i64 %x, i64 %y, i1 %cond) {
; CHECK-LABEL: @test_select_inverse_samesign_both(
; CHECK-NEXT:    [[CMP2:%.*]] = icmp samesign uge i64 [[X:%.*]], [[Y:%.*]]
; CHECK-NEXT:    [[SEL:%.*]] = xor i1 [[COND:%.*]], [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp samesign ult i64 %x, %y
  %cmp2 = icmp samesign uge i64 %x, %y
  %sel = select i1 %cond, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_samesign_false_arm_rhsc_same_sign(i64 %x, i64 %y, i1 %cond) {
; CHECK-LABEL: @test_select_inverse_samesign_false_arm_rhsc_same_sign(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp ult i64 [[X:%.*]], 11
; CHECK-NEXT:    [[CMP2:%.*]] = icmp samesign ugt i64 [[X]], 10
; CHECK-NEXT:    [[SEL:%.*]] = select i1 [[COND:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp ult i64 %x, 11
  %cmp2 = icmp samesign ugt i64 %x, 10
  %sel = select i1 %cond, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_samesign_true_arm_rhsc_same_sign(i64 %x, i64 %y, i1 %cond) {
; CHECK-LABEL: @test_select_inverse_samesign_true_arm_rhsc_same_sign(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp samesign ult i64 [[X:%.*]], 11
; CHECK-NEXT:    [[CMP2:%.*]] = icmp ugt i64 [[X]], 10
; CHECK-NEXT:    [[SEL:%.*]] = select i1 [[COND:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp samesign ult i64 %x, 11
  %cmp2 = icmp ugt i64 %x, 10
  %sel = select i1 %cond, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_samesign_both_rhsc_same_sign(i64 %x, i64 %y, i1 %cond) {
; CHECK-LABEL: @test_select_inverse_samesign_both_rhsc_same_sign(
; CHECK-NEXT:    [[CMP2:%.*]] = icmp samesign ugt i64 [[X:%.*]], 10
; CHECK-NEXT:    [[SEL:%.*]] = xor i1 [[COND:%.*]], [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp samesign ult i64 %x, 11
  %cmp2 = icmp samesign ugt i64 %x, 10
  %sel = select i1 %cond, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @test_select_inverse_samesign_both_rhsc_diff_sign(i64 %x, i64 %y, i1 %cond) {
; CHECK-LABEL: @test_select_inverse_samesign_both_rhsc_diff_sign(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp samesign slt i64 [[X:%.*]], 0
; CHECK-NEXT:    [[CMP2:%.*]] = icmp samesign sgt i64 [[X]], -1
; CHECK-NEXT:    [[SEL:%.*]] = select i1 [[COND:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[SEL]]
;
  %cmp1 = icmp samesign slt i64 %x, 0
  %cmp2 = icmp samesign sgt i64 %x, -1
  %sel = select i1 %cond, i1 %cmp1, i1 %cmp2
  ret i1 %sel
}

define i1 @sel_icmp_two_cmp(i1 %c, i32 %a1, i32 %a2, i32 %a3, i32 %a4) {
; CHECK-LABEL: @sel_icmp_two_cmp(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp ule i32 [[A1:%.*]], [[A2:%.*]]
; CHECK-NEXT:    [[CMP2:%.*]] = icmp sle i32 [[A3:%.*]], [[A4:%.*]]
; CHECK-NEXT:    [[CMP:%.*]] = select i1 [[C:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[CMP]]
;
  %v1 = call i8 @llvm.ucmp(i32 %a1, i32 %a2)
  %v2 = call i8 @llvm.scmp(i32 %a3, i32 %a4)
  %sel = select i1 %c, i8 %v1, i8 %v2
  %cmp = icmp sle i8 %sel, 0
  ret i1 %cmp
}

define i1 @sel_icmp_two_cmp_extra_use1(i1 %c, i32 %a1, i32 %a2, i32 %a3, i32 %a4) {
; CHECK-LABEL: @sel_icmp_two_cmp_extra_use1(
; CHECK-NEXT:    [[V1:%.*]] = call i8 @llvm.ucmp.i8.i32(i32 [[A1:%.*]], i32 [[A2:%.*]])
; CHECK-NEXT:    call void @use.i8(i8 [[V1]])
; CHECK-NEXT:    [[CMP1:%.*]] = icmp ule i32 [[A1]], [[A2]]
; CHECK-NEXT:    [[CMP2:%.*]] = icmp sle i32 [[A3:%.*]], [[A4:%.*]]
; CHECK-NEXT:    [[CMP:%.*]] = select i1 [[C:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[CMP]]
;
  %v1 = call i8 @llvm.ucmp(i32 %a1, i32 %a2)
  %v2 = call i8 @llvm.scmp(i32 %a3, i32 %a4)
  call void @use.i8(i8 %v1)
  %sel = select i1 %c, i8 %v1, i8 %v2
  %cmp = icmp sle i8 %sel, 0
  ret i1 %cmp
}

define i1 @sel_icmp_two_cmp_extra_use2(i1 %c, i32 %a1, i32 %a2, i32 %a3, i32 %a4) {
; CHECK-LABEL: @sel_icmp_two_cmp_extra_use2(
; CHECK-NEXT:    [[V1:%.*]] = call i8 @llvm.ucmp.i8.i32(i32 [[A1:%.*]], i32 [[A2:%.*]])
; CHECK-NEXT:    [[V2:%.*]] = call i8 @llvm.scmp.i8.i32(i32 [[A3:%.*]], i32 [[A4:%.*]])
; CHECK-NEXT:    [[SEL:%.*]] = select i1 [[C:%.*]], i8 [[V1]], i8 [[V2]]
; CHECK-NEXT:    call void @use.i8(i8 [[SEL]])
; CHECK-NEXT:    [[CMP:%.*]] = icmp slt i8 [[SEL]], 1
; CHECK-NEXT:    ret i1 [[CMP]]
;
  %v1 = call i8 @llvm.ucmp(i32 %a1, i32 %a2)
  %v2 = call i8 @llvm.scmp(i32 %a3, i32 %a4)
  %sel = select i1 %c, i8 %v1, i8 %v2
  call void @use.i8(i8 %sel)
  %cmp = icmp sle i8 %sel, 0
  ret i1 %cmp
}

define i1 @sel_icmp_two_cmp_not_const(i1 %c, i32 %a1, i32 %a2, i32 %a3, i32 %a4, i8 %b) {
; CHECK-LABEL: @sel_icmp_two_cmp_not_const(
; CHECK-NEXT:    [[V1:%.*]] = call i8 @llvm.ucmp.i8.i32(i32 [[A1:%.*]], i32 [[A2:%.*]])
; CHECK-NEXT:    [[V2:%.*]] = call i8 @llvm.scmp.i8.i32(i32 [[A3:%.*]], i32 [[A4:%.*]])
; CHECK-NEXT:    [[SEL:%.*]] = select i1 [[C:%.*]], i8 [[V1]], i8 [[V2]]
; CHECK-NEXT:    [[CMP:%.*]] = icmp sle i8 [[SEL]], [[B:%.*]]
; CHECK-NEXT:    ret i1 [[CMP]]
;
  %v1 = call i8 @llvm.ucmp(i32 %a1, i32 %a2)
  %v2 = call i8 @llvm.scmp(i32 %a3, i32 %a4)
  %sel = select i1 %c, i8 %v1, i8 %v2
  %cmp = icmp sle i8 %sel, %b
  ret i1 %cmp
}

define <2 x i1> @sel_icmp_two_cmp_vec(i1 %c, <2 x i32> %a1, <2 x i32> %a2, <2 x i32> %a3, <2 x i32> %a4) {
; CHECK-LABEL: @sel_icmp_two_cmp_vec(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp ule <2 x i32> [[A1:%.*]], [[A2:%.*]]
; CHECK-NEXT:    [[CMP2:%.*]] = icmp sle <2 x i32> [[A3:%.*]], [[A4:%.*]]
; CHECK-NEXT:    [[CMP:%.*]] = select i1 [[C:%.*]], <2 x i1> [[CMP1]], <2 x i1> [[CMP2]]
; CHECK-NEXT:    ret <2 x i1> [[CMP]]
;
  %v1 = call <2 x i8> @llvm.ucmp(<2 x i32> %a1, <2 x i32> %a2)
  %v2 = call <2 x i8> @llvm.scmp(<2 x i32> %a3, <2 x i32> %a4)
  %sel = select i1 %c, <2 x i8> %v1, <2 x i8> %v2
  %cmp = icmp sle <2 x i8> %sel, zeroinitializer
  ret <2 x i1> %cmp
}

define <2 x i1> @sel_icmp_two_cmp_vec_nonsplat(i1 %c, <2 x i32> %a1, <2 x i32> %a2, <2 x i32> %a3, <2 x i32> %a4) {
; CHECK-LABEL: @sel_icmp_two_cmp_vec_nonsplat(
; CHECK-NEXT:    [[V1:%.*]] = call <2 x i8> @llvm.ucmp.v2i8.v2i32(<2 x i32> [[A1:%.*]], <2 x i32> [[A2:%.*]])
; CHECK-NEXT:    [[V2:%.*]] = call <2 x i8> @llvm.scmp.v2i8.v2i32(<2 x i32> [[A3:%.*]], <2 x i32> [[A4:%.*]])
; CHECK-NEXT:    [[SEL:%.*]] = select i1 [[C:%.*]], <2 x i8> [[V1]], <2 x i8> [[V2]]
; CHECK-NEXT:    [[CMP:%.*]] = icmp slt <2 x i8> [[SEL]], <i8 1, i8 2>
; CHECK-NEXT:    ret <2 x i1> [[CMP]]
;
  %v1 = call <2 x i8> @llvm.ucmp(<2 x i32> %a1, <2 x i32> %a2)
  %v2 = call <2 x i8> @llvm.scmp(<2 x i32> %a3, <2 x i32> %a4)
  %sel = select i1 %c, <2 x i8> %v1, <2 x i8> %v2
  %cmp = icmp sle <2 x i8> %sel, <i8 0, i8 1>
  ret <2 x i1> %cmp
}

define i1 @sel_icmp_cmp_and_simplify(i1 %c, i32 %a1, i32 %a2) {
; CHECK-LABEL: @sel_icmp_cmp_and_simplify(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp ule i32 [[A1:%.*]], [[A2:%.*]]
; CHECK-NEXT:    [[NOT_C:%.*]] = xor i1 [[C:%.*]], true
; CHECK-NEXT:    [[CMP:%.*]] = select i1 [[NOT_C]], i1 true, i1 [[CMP1]]
; CHECK-NEXT:    ret i1 [[CMP]]
;
  %v = call i8 @llvm.ucmp(i32 %a1, i32 %a2)
  %sel = select i1 %c, i8 %v, i8 0
  %cmp = icmp sle i8 %sel, 0
  ret i1 %cmp
}

define i1 @sel_icmp_cmp_and_no_simplify(i1 %c, i32 %a1, i32 %a2, i8 %b) {
; CHECK-LABEL: @sel_icmp_cmp_and_no_simplify(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp ule i32 [[A1:%.*]], [[A2:%.*]]
; CHECK-NEXT:    [[CMP2:%.*]] = icmp slt i8 [[B:%.*]], 1
; CHECK-NEXT:    [[CMP:%.*]] = select i1 [[C:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[CMP]]
;
  %v = call i8 @llvm.ucmp(i32 %a1, i32 %a2)
  %sel = select i1 %c, i8 %v, i8 %b
  %cmp = icmp sle i8 %sel, 0
  ret i1 %cmp
}

define i1 @sel_icmp_cmp_and_no_simplify_comm(i1 %c, i32 %a1, i32 %a2, i8 %b) {
; CHECK-LABEL: @sel_icmp_cmp_and_no_simplify_comm(
; CHECK-NEXT:    [[CMP1:%.*]] = icmp slt i8 [[B:%.*]], 1
; CHECK-NEXT:    [[CMP2:%.*]] = icmp ule i32 [[A1:%.*]], [[A2:%.*]]
; CHECK-NEXT:    [[CMP:%.*]] = select i1 [[C:%.*]], i1 [[CMP1]], i1 [[CMP2]]
; CHECK-NEXT:    ret i1 [[CMP]]
;
  %v = call i8 @llvm.ucmp(i32 %a1, i32 %a2)
  %sel = select i1 %c, i8 %b, i8 %v
  %cmp = icmp sle i8 %sel, 0
  ret i1 %cmp
}

define i1 @icmp_lt_slt(i1 %c, i32 %arg) {
; CHECK-LABEL: @icmp_lt_slt(
; CHECK-NEXT:    [[SELECT_V:%.*]] = select i1 [[C:%.*]], i32 131072, i32 0
; CHECK-NEXT:    [[SELECT:%.*]] = icmp slt i32 [[ARG:%.*]], [[SELECT_V]]
; CHECK-NEXT:    ret i1 [[SELECT]]
;
  %cmp1 = icmp samesign ult i32 %arg, 131072
  %cmp2 = icmp slt i32 %arg, 0
  %select = select i1 %c, i1 %cmp1, i1 %cmp2
  ret i1 %select
}

declare void @use(i1)
declare void @use.i8(i8)
