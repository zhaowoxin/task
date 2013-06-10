target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32"
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
define i32 @main(i32 %argc, i8** nocapture %argv) nounwind uwtable {
		%Y1 = alloca <4 x i32>, align 4
		store <4 x i32> <i32 1, i32 2, i32 3, i32 4>, <4 x i32>* %Y1
    %y1 = load <4 x i32>* %Y1
    ;%y4 = zext <4 x i32> %y1 to <8 x i32>
    ;%y2 = shufflevector <8 x i32> %y1, <8 x i32> undef, <2 x i32> <i32 1, i32 5>
    %y2 = shufflevector <4 x i32> %y1, <4 x i32> undef, <2 x i32> <i32 1, i32 3>
    %y3 = extractelement <2 x i32> %y2, i32 1
    call i32 (i8*, ...)* @printf(i8* getelementptr ([4 x i8]* @.str, i32 0, i32 0), i32 %y3)
ret i32 0
}
declare i32 @printf(i8* nocapture, ...) nounwind
declare {i32, i1} @llvm.sadd.with.overflow.i32(i32, i32) nounwind readnone
declare {i32, i1} @llvm.uadd.with.overflow.i32(i32, i32) nounwind readnone
declare {i32, i1} @llvm.ssub.with.overflow.i32(i32, i32) nounwind readnone
declare {i32, i1} @llvm.usub.with.overflow.i32(i32, i32) nounwind readnone
