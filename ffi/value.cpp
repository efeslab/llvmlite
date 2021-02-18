#include <string>
#include "llvm-c/Core.h"
#include "core.h"

#include <iostream>

// the following is needed for WriteGraph()
#include "llvm/Analysis/CFGPrinter.h"
// iangneal: for debug info
#include "llvm/IR/DebugInfoMetadata.h"

/* An iterator around a attribute list, including the stop condition */
struct AttributeListIterator {
    typedef llvm::AttributeList::iterator const_iterator;
    const_iterator cur;
    const_iterator end;

    AttributeListIterator(const_iterator cur, const_iterator end)
        :cur(cur), end(end)
    { }
};

struct OpaqueAttributeListIterator;
typedef OpaqueAttributeListIterator* LLVMAttributeListIteratorRef;

/* An iterator around a attribute set, including the stop condition */
struct AttributeSetIterator {
    typedef llvm::AttributeSet::iterator const_iterator;
    const_iterator cur;
    const_iterator end;

    AttributeSetIterator(const_iterator cur, const_iterator end)
        :cur(cur), end(end)
    { }
};

struct OpaqueAttributeSetIterator;
typedef OpaqueAttributeSetIterator* LLVMAttributeSetIteratorRef;

/* An iterator around a function's blocks, including the stop condition */
struct BlocksIterator {
    typedef llvm::Function::const_iterator const_iterator;
    const_iterator cur;
    const_iterator end;

    BlocksIterator(const_iterator cur, const_iterator end)
        :cur(cur), end(end)
    { }
};

struct OpaqueBlocksIterator;
typedef OpaqueBlocksIterator* LLVMBlocksIteratorRef;

/* An iterator around a function's arguments, including the stop condition */
struct ArgumentsIterator {
    typedef llvm::Function::const_arg_iterator const_iterator;
    const_iterator cur;
    const_iterator end;

    ArgumentsIterator(const_iterator cur, const_iterator end)
        :cur(cur), end(end)
    { }
};

struct OpaqueArgumentsIterator;
typedef OpaqueArgumentsIterator* LLVMArgumentsIteratorRef;


/* An iterator around a basic block's instructions, including the stop condition */
struct InstructionsIterator {
    typedef llvm::BasicBlock::const_iterator const_iterator;
    const_iterator cur;
    const_iterator end;

    InstructionsIterator(const_iterator cur, const_iterator end)
        :cur(cur), end(end)
    { }
};

struct OpaqueInstructionsIterator;
typedef OpaqueInstructionsIterator* LLVMInstructionsIteratorRef;

/* An iterator around a instruction's operands, including the stop condition */
struct OperandsIterator {
    typedef llvm::Instruction::const_op_iterator const_iterator;
    const_iterator cur;
    const_iterator end;

    OperandsIterator(const_iterator cur, const_iterator end)
        :cur(cur), end(end)
    { }
};

struct OpaqueOperandsIterator;
typedef OpaqueOperandsIterator* LLVMOperandsIteratorRef;

/* iangneal: An iterator around a value's users, including the stop condition */
struct UseIterator {
    typedef llvm::Value::const_use_iterator const_iterator;
    const_iterator cur;
    const_iterator end;

    UseIterator(const_iterator cur, const_iterator end) : cur(cur), end(end) {}
};

struct OpaqueUseIterator;
typedef OpaqueUseIterator* LLVMUseIteratorRef;

/* iangneal: An iterator around a struct's elements, including the stop condition */
struct ElementsIterator {
    typedef llvm::StructType::element_iterator const_iterator;
    const_iterator cur;
    const_iterator end;

    ElementsIterator(const_iterator cur, const_iterator end)
        :cur(cur), end(end)
    { }
};

struct OpaqueElementsIterator;
typedef OpaqueElementsIterator* LLVMElementsIteratorRef;

namespace llvm {

static LLVMAttributeListIteratorRef
wrap(AttributeListIterator* GI){
    return reinterpret_cast<LLVMAttributeListIteratorRef>(GI);
}

static AttributeListIterator*
unwrap(LLVMAttributeListIteratorRef GI){
    return reinterpret_cast<AttributeListIterator *>(GI);
}

static LLVMAttributeSetIteratorRef
wrap(AttributeSetIterator* GI){
    return reinterpret_cast<LLVMAttributeSetIteratorRef>(GI);
}

static AttributeSetIterator*
unwrap(LLVMAttributeSetIteratorRef GI){
    return reinterpret_cast<AttributeSetIterator *>(GI);
}

static LLVMBlocksIteratorRef
wrap(BlocksIterator* GI){
    return reinterpret_cast<LLVMBlocksIteratorRef>(GI);
}

static BlocksIterator*
unwrap(LLVMBlocksIteratorRef GI){
    return reinterpret_cast<BlocksIterator *>(GI);
}

static LLVMArgumentsIteratorRef
wrap(ArgumentsIterator* GI){
    return reinterpret_cast<LLVMArgumentsIteratorRef>(GI);
}

static ArgumentsIterator*
unwrap(LLVMArgumentsIteratorRef GI){
    return reinterpret_cast<ArgumentsIterator *>(GI);
}

static LLVMInstructionsIteratorRef
wrap(InstructionsIterator* GI){
    return reinterpret_cast<LLVMInstructionsIteratorRef>(GI);
}

static InstructionsIterator*
unwrap(LLVMInstructionsIteratorRef GI){
    return reinterpret_cast<InstructionsIterator *>(GI);
}

static LLVMOperandsIteratorRef
wrap(OperandsIterator* GI){
    return reinterpret_cast<LLVMOperandsIteratorRef>(GI);
}

static OperandsIterator*
unwrap(LLVMOperandsIteratorRef GI){
    return reinterpret_cast<OperandsIterator *>(GI);
}

static LLVMUseIteratorRef
wrap(UseIterator* GI){
    return reinterpret_cast<LLVMUseIteratorRef>(GI);
}

static UseIterator*
unwrap(LLVMUseIteratorRef GI){
    return reinterpret_cast<UseIterator *>(GI);
}

static LLVMElementsIteratorRef
wrap(ElementsIterator* GI){
    return reinterpret_cast<LLVMElementsIteratorRef>(GI);
}

static ElementsIterator*
unwrap(LLVMElementsIteratorRef GI){
    return reinterpret_cast<ElementsIterator *>(GI);
}

}

extern "C" {

API_EXPORT(LLVMAttributeListIteratorRef)
LLVMPY_FunctionAttributesIter(LLVMValueRef F)
{
    using namespace llvm;
    Function* func = unwrap<Function>(F);
    AttributeList attrs = func->getAttributes();
    return wrap(new AttributeListIterator(attrs.begin(),
                                          attrs.end()));
}

API_EXPORT(LLVMAttributeSetIteratorRef)
LLVMPY_ArgumentAttributesIter(LLVMValueRef A)
{
    using namespace llvm;
    Argument* arg = unwrap<Argument>(A);
    unsigned argno = arg->getArgNo();
    AttributeSet attrs = arg->getParent()
      ->getAttributes().getParamAttributes(argno);
    return wrap(new AttributeSetIterator(attrs.begin(),
                                         attrs.end()));
}

API_EXPORT(LLVMAttributeListIteratorRef)
LLVMPY_CallInstAttributesIter(LLVMValueRef C)
{
    using namespace llvm;
    CallInst* inst = unwrap<CallInst>(C);
    AttributeList attrs = inst->getAttributes();
    return wrap(new AttributeListIterator(attrs.begin(),
                                          attrs.end()));
}

API_EXPORT(LLVMAttributeListIteratorRef)
LLVMPY_InvokeInstAttributesIter(LLVMValueRef C)
{
    using namespace llvm;
    InvokeInst* inst = unwrap<InvokeInst>(C);
    AttributeList attrs = inst->getAttributes();
    return wrap(new AttributeListIterator(attrs.begin(),
                                          attrs.end()));
}

API_EXPORT(LLVMAttributeSetIteratorRef)
LLVMPY_GlobalAttributesIter(LLVMValueRef G)
{
    using namespace llvm;
    GlobalVariable* g = unwrap<GlobalVariable>(G);
    AttributeSet attrs = g->getAttributes();
    return wrap(new AttributeSetIterator(attrs.begin(),
                                         attrs.end()));
}

API_EXPORT(LLVMBlocksIteratorRef)
LLVMPY_FunctionBlocksIter(LLVMValueRef F)
{
    using namespace llvm;
    Function* func = unwrap<Function>(F);
    return wrap(new BlocksIterator(func->begin(),
                                   func->end()));
}

API_EXPORT(LLVMArgumentsIteratorRef)
LLVMPY_FunctionArgumentsIter(LLVMValueRef F)
{
    using namespace llvm;
    Function* func = unwrap<Function>(F);
    return wrap(new ArgumentsIterator(func->arg_begin(),
                                      func->arg_end()));
}

API_EXPORT(LLVMInstructionsIteratorRef)
LLVMPY_BlockInstructionsIter(LLVMValueRef B)
{
    using namespace llvm;
    BasicBlock* block = unwrap<BasicBlock>(B);
    return wrap(new InstructionsIterator(block->begin(),
                                         block->end()));
}

API_EXPORT(LLVMOperandsIteratorRef)
LLVMPY_InstructionOperandsIter(LLVMValueRef I)
{
    using namespace llvm;
    Instruction* inst = unwrap<Instruction>(I);
    return wrap(new OperandsIterator(inst->op_begin(),
                                inst->op_end()));
}

API_EXPORT(LLVMUseIteratorRef)
LLVMPY_UseIter(LLVMValueRef V)
{
    using namespace llvm;
    Value* val = unwrap<Value>(V);
    return wrap(new UseIterator(val->use_begin(),
                                val->use_end()));
}

API_EXPORT(LLVMElementsIteratorRef)
LLVMPY_ElementsIter(LLVMTypeRef T)
{
    using namespace llvm;
    Type* ty = unwrap<Type>(T);
    StructType *st = dyn_cast<StructType>(ty);
    if (st) {
        return wrap(new ElementsIterator(st->element_begin(),
                                         st->element_end()));
    }
    return nullptr;
}

API_EXPORT(const char *)
LLVMPY_AttributeListIterNext(LLVMAttributeListIteratorRef GI)
{
    using namespace llvm;
    AttributeListIterator* iter = unwrap(GI);
    if (iter->cur != iter->end) {
        return LLVMPY_CreateString((&*iter->cur++)->getAsString().c_str());
    } else {
      return NULL;
    }
}

API_EXPORT(const char *)
LLVMPY_AttributeSetIterNext(LLVMAttributeSetIteratorRef GI)
{
    using namespace llvm;
    AttributeSetIterator* iter = unwrap(GI);
    if (iter->cur != iter->end) {
        return LLVMPY_CreateString((&*iter->cur++)->getAsString().c_str());
    } else {
      return NULL;
    }
}

API_EXPORT(LLVMValueRef)
LLVMPY_BlocksIterNext(LLVMBlocksIteratorRef GI)
{
    using namespace llvm;
    BlocksIterator* iter = unwrap(GI);
    if (iter->cur != iter->end) {
      return wrap(static_cast<const Value*>(&*iter->cur++));
    } else {
      return NULL;
    }
}

API_EXPORT(LLVMValueRef)
LLVMPY_ArgumentsIterNext(LLVMArgumentsIteratorRef GI)
{
    using namespace llvm;
    ArgumentsIterator* iter = unwrap(GI);
    if (iter->cur != iter->end) {
      return wrap(&*iter->cur++);
    } else {
      return NULL;
    }
}

API_EXPORT(LLVMValueRef)
LLVMPY_InstructionsIterNext(LLVMInstructionsIteratorRef GI)
{
    using namespace llvm;
    InstructionsIterator* iter = unwrap(GI);
    if (iter->cur != iter->end) {
      return wrap(&*iter->cur++);
    } else {
      return NULL;
    }
}

API_EXPORT(LLVMValueRef)
LLVMPY_OperandsIterNext(LLVMOperandsIteratorRef GI)
{
    using namespace llvm;
    OperandsIterator* iter = unwrap(GI);
    if (iter->cur != iter->end) {
      return wrap((&*iter->cur++)->get());
    } else {
      return NULL;
    }
}

API_EXPORT(LLVMValueRef)
LLVMPY_UseIterNext(LLVMUseIteratorRef GI)
{
    using namespace llvm;
    UseIterator* iter = unwrap(GI);
    if (iter->cur != iter->end) {
      return wrap((&*iter->cur++)->getUser());
    } else {
      return NULL;
    }
}

API_EXPORT(LLVMTypeRef)
LLVMPY_ElementsIterNext(LLVMElementsIteratorRef STI)
{
    using namespace llvm;
    ElementsIterator* iter = unwrap(STI);
    if (iter->cur != iter->end) {
      return wrap(const_cast<Type*>(*(&*iter->cur++)));
    } else {
      return NULL;
    }
}

API_EXPORT(void)
LLVMPY_DisposeAttributeListIter(LLVMAttributeListIteratorRef GI)
{
    delete llvm::unwrap(GI);
}

API_EXPORT(void)
LLVMPY_DisposeAttributeSetIter(LLVMAttributeSetIteratorRef GI)
{
    delete llvm::unwrap(GI);
}

API_EXPORT(void)
LLVMPY_DisposeBlocksIter(LLVMBlocksIteratorRef GI)
{
    delete llvm::unwrap(GI);
}

API_EXPORT(void)
LLVMPY_DisposeArgumentsIter(LLVMArgumentsIteratorRef GI)
{
    delete llvm::unwrap(GI);
}

API_EXPORT(void)
LLVMPY_DisposeInstructionsIter(LLVMInstructionsIteratorRef GI)
{
    delete llvm::unwrap(GI);
}

API_EXPORT(void)
LLVMPY_DisposeOperandsIter(LLVMOperandsIteratorRef GI)
{
    delete llvm::unwrap(GI);
}

API_EXPORT(void)
LLVMPY_DisposeUseIter(LLVMUseIteratorRef GI)
{
    delete llvm::unwrap(GI);
}

API_EXPORT(void)
LLVMPY_DisposeElementsIter(LLVMElementsIteratorRef GI)
{
    delete llvm::unwrap(GI);
}

API_EXPORT(void)
LLVMPY_PrintValueToString(LLVMValueRef Val,
                          const char** outstr)
{
    *outstr = LLVMPrintValueToString(Val);
}

API_EXPORT(const char *)
LLVMPY_GetValueName(LLVMValueRef Val)
{
    return LLVMGetValueName(Val);
}

API_EXPORT(void)
LLVMPY_SetValueName(LLVMValueRef Val, const char *Name)
{
    LLVMSetValueName(Val, Name);
}

API_EXPORT(LLVMModuleRef)
LLVMPY_GetGlobalParent(LLVMValueRef Val)
{
    return LLVMGetGlobalParent(Val);
}

API_EXPORT(LLVMTypeRef)
LLVMPY_TypeOf(LLVMValueRef Val)
{
    return LLVMTypeOf(Val);
}

API_EXPORT(const char *)
LLVMPY_PrintType(LLVMTypeRef type)
{
    char *str = LLVMPrintTypeToString(type);
    const char *out = LLVMPY_CreateString(str);
    LLVMDisposeMessage(str);
    return out;
}

API_EXPORT(const char *)
LLVMPY_GetTypeName(LLVMTypeRef type)
{
    // try to convert to a struct type, works for other derived
    // types too
    llvm::Type* unwrapped = llvm::unwrap(type);
    llvm::StructType* ty = llvm::dyn_cast<llvm::StructType>(unwrapped);
    if (ty && !ty->isLiteral()) {
        return LLVMPY_CreateString(ty->getStructName().str().c_str());
    }
    return LLVMPY_CreateString("");
}

API_EXPORT(bool)
LLVMPY_TypeIsPointer(LLVMTypeRef type)
{
    return llvm::unwrap(type)->isPointerTy();
}

API_EXPORT(LLVMTypeRef)
LLVMPY_GetElementType(LLVMTypeRef type)
{
    llvm::Type* unwrapped = llvm::unwrap(type);
    llvm::PointerType* ty = llvm::dyn_cast<llvm::PointerType>(unwrapped);
    if (ty != nullptr) {
        return llvm::wrap(ty->getElementType());
    }
    return nullptr;
}

// iangneal: struct type stuff

API_EXPORT(bool)
LLVMPY_TypeIsStruct(LLVMTypeRef type)
{
    return llvm::unwrap(type)->isStructTy();
}

API_EXPORT(unsigned)
LLVMPY_GetNumElements(LLVMTypeRef type)
{
    llvm::Type* unwrapped = llvm::unwrap(type);
    llvm::StructType* ty = llvm::dyn_cast<llvm::StructType>(unwrapped);
    if (ty != nullptr) {
        return ty->getNumElements();
    }
    return 0;
}

API_EXPORT(LLVMTypeRef)
LLVMPY_GetTypeAtIndex(LLVMTypeRef type, unsigned idx)
{
    llvm::Type* unwrapped = llvm::unwrap(type);
    llvm::StructType* ty = llvm::dyn_cast<llvm::StructType>(unwrapped);
    if (ty != nullptr) {
        return wrap(ty->getTypeAtIndex(idx));
    }

    return nullptr;
}

// -- end struct additions

// iangneal: vector type stuff

API_EXPORT(bool)
LLVMPY_TypeIsVector(LLVMTypeRef type)
{
    llvm::Type* ty = llvm::unwrap(type);
    return ty->isVectorTy() || ty->isArrayTy();
}

API_EXPORT(LLVMTypeRef)
LLVMPY_GetScalarType(LLVMTypeRef type, unsigned idx)
{
    using namespace llvm;
    llvm::Type* ty = llvm::unwrap(type);
    if (auto *at = dyn_cast<ArrayType>(ty)) {
        return wrap(at->getElementType());
    }
    return wrap(ty->getScalarType());
}

// -- end struct additions

API_EXPORT(void)
LLVMPY_SetLinkage(LLVMValueRef Val, int Linkage)
{
    LLVMSetLinkage(Val, (LLVMLinkage)Linkage);
}

API_EXPORT(int)
LLVMPY_GetLinkage(LLVMValueRef Val)
{
    return (int)LLVMGetLinkage(Val);
}

API_EXPORT(void)
LLVMPY_SetVisibility(LLVMValueRef Val, int Visibility)
{
    LLVMSetVisibility(Val, (LLVMVisibility)Visibility);
}

API_EXPORT(int)
LLVMPY_GetVisibility(LLVMValueRef Val)
{
    return (int)LLVMGetVisibility(Val);
}

API_EXPORT(void)
LLVMPY_SetDLLStorageClass(LLVMValueRef Val, int DLLStorageClass)
{
    LLVMSetDLLStorageClass(Val, (LLVMDLLStorageClass)DLLStorageClass);
}

API_EXPORT(int)
LLVMPY_GetDLLStorageClass(LLVMValueRef Val)
{
    return (int)LLVMGetDLLStorageClass(Val);
}

API_EXPORT(unsigned)
LLVMPY_GetEnumAttributeKindForName(const char *name, size_t len)
{
    /* zero is returned if no match */
    return LLVMGetEnumAttributeKindForName(name, len);
}

API_EXPORT(void)
LLVMPY_AddFunctionAttr(LLVMValueRef Fn, unsigned AttrKind)
{
    LLVMContextRef ctx = LLVMGetModuleContext(LLVMGetGlobalParent(Fn));
    LLVMAttributeRef attr_ref = LLVMCreateEnumAttribute(ctx, AttrKind, 0);
    LLVMAddAttributeAtIndex(Fn, LLVMAttributeReturnIndex, attr_ref);
}

API_EXPORT(int)
LLVMPY_IsDeclaration(LLVMValueRef GV)
{
    return LLVMIsDeclaration(GV);
}


API_EXPORT(void)
LLVMPY_WriteCFG(LLVMValueRef Fval, const char **OutStr, int ShowInst) {
    using namespace llvm;
    Function *F  = unwrap<Function>(Fval);
    std::string buffer;
    raw_string_ostream stream(buffer);
    // Note: The (const Function*)F is necessary to trigger the right behavior.
    //       A non constant Function* will result in the instruction not
    //       printed regardless of the value in the 3rd argument.
    WriteGraph(stream, (const Function*)F, !ShowInst);
    *OutStr = LLVMPY_CreateString(stream.str().c_str());
}

API_EXPORT(const char *)
LLVMPY_GetOpcodeName(LLVMValueRef Val)
{
    // try to convert to an instruction value, works for other derived
    // types too
    llvm::Value* unwrapped = llvm::unwrap(Val);
    llvm::Instruction* inst = llvm::dyn_cast<llvm::Instruction>(unwrapped);
    if (inst) {
        return LLVMPY_CreateString(inst->getOpcodeName());
    }
    return LLVMPY_CreateString("");
}

/**
 * Inspired by similar code in Hippocrates: 
 * https://github.com/efeslab/hippocrates/blob/e4b1322781eef3dcdb4843401af92ebdcfa8f0bc/src/BugReports.cpp#L189-L224
 * 
 * We need file name, function name, and line number. Function name is easy.
 */

API_EXPORT(const char *)
LLVMPY_DebugInfoGetFilename(LLVMValueRef Val)
{   
    using namespace llvm;
    // try to convert to an instruction value, works for other derived
    // types too
    llvm::Value* unwrapped = llvm::unwrap(Val);
    llvm::Instruction* inst = llvm::dyn_cast<llvm::Instruction>(unwrapped);

    // Essentially, need to get the line number and file name from the 
    // instruction debug information.
    if (!inst->hasMetadata()) return LLVMPY_CreateString("");
    if (!inst->getMetadata("dbg")) return LLVMPY_CreateString("");

    if (DILocation *di = dyn_cast<DILocation>(inst->getMetadata("dbg"))) {
        llvm::DILocalScope *ls = di->getScope();
        llvm::DIFile *df = ls->getFile();
        return LLVMPY_CreateString(df->getFilename().str().c_str());
    }

    return LLVMPY_CreateString("");
}

API_EXPORT(int64_t)
LLVMPY_DebugInfoGetLineNumber(LLVMValueRef Val)
{
    using namespace llvm;
    // try to convert to an instruction value, works for other derived
    // types too
    llvm::Value* unwrapped = llvm::unwrap(Val);
    llvm::Instruction* inst = llvm::dyn_cast<llvm::Instruction>(unwrapped);

    // Essentially, need to get the line number and file name from the 
    // instruction debug information.
    if (!inst->hasMetadata()) return -1;
    if (!inst->getMetadata("dbg")) return -1;

    if (DILocation *di = dyn_cast<DILocation>(inst->getMetadata("dbg"))) {
        return di->getLine();
    }

    return -1;
}

// iangneal: for def-use chain stuff

API_EXPORT(LLVMValueRef)
LLVMPY_OperandToInstruction(LLVMValueRef Val)
{
    using namespace llvm;
    
    llvm::Value* unwrapped = llvm::unwrap(Val);
    return wrap(llvm::dyn_cast<llvm::Instruction>(unwrapped));
}

// iangneal: for index offsets

API_EXPORT(bool)
LLVMPY_IsConstant(LLVMValueRef Val)
{
    using namespace llvm;

    Value *unwrapped = unwrap(Val);
    return dyn_cast<Constant>(unwrapped) != nullptr;
}

API_EXPORT(int64_t)
LLVMPY_GetConstant(LLVMValueRef Val)
{
    using namespace llvm;
    
    Value *unwrapped = unwrap(Val);
    const APInt &C = dyn_cast<Constant>(unwrapped)->getUniqueInteger();
    return C.getLimitedValue();
}

} // end extern "C"
