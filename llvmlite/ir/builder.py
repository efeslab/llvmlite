from __future__ import print_function, absolute_import
import functools
from . import types, values

_CMP_MAP = {
    '>': 'gt',
    '<': 'lt',
    '==': 'eq',
    '!=': 'ne',
    '>=': 'ge',
    '<=': 'le',
}


def _binop(opname, cls=values.Instruction):
    def wrap(fn):
        @functools.wraps(fn)
        def wrapped(self, lhs, rhs, name=''):
            assert lhs.type == rhs.type, "Operands must be the same type"
            instr = cls(self.block, lhs.type, opname, (lhs, rhs), name)
            self._insert(instr)
            return instr

        return wrapped

    return wrap


def _uniop(opname, cls=values.Instruction):
    def wrap(fn):
        @functools.wraps(fn)
        def wrapped(self, operand, name=''):
            instr = cls(self.block, operand.type, opname, [operand], name)
            self._insert(instr)
            return instr

        return wrapped

    return wrap


def _castop(opname, cls=values.CastInstr):
    def wrap(fn):
        @functools.wraps(fn)
        def wrapped(self, val, typ, name=''):
            if val.type == typ:
                return val
            instr = cls(self.block, opname, val, typ, name)
            self._insert(instr)
            return instr

        return wrapped

    return wrap


class IRBuilder(object):
    def __init__(self, block=None):
        self._block = block
        self._anchor = len(block.instructions) if block else 0

    @property
    def block(self):
        return self._block

    basic_block = block

    @property
    def function(self):
        return self.block.parent

    def position_before(self, instr):
        self._block = instr.parent
        # if instr is self.block.terminator:
        #     self._anchor = len(self.block.instructions)
        # else:
        self._anchor = max(0, self._block.instructions.index(instr))

    def position_after(self, instr):
        self._block = instr.parent
        self._anchor = min(self._block.instructions.index(instr) + 1,
                           len(self._block.instructions))

    def position_at_start(self, block):
        self._block = block
        self._anchor = 0

    def position_at_end(self, block):
        self._block = block
        self._anchor = len(block.instructions)

    def constant(self, typ, val):
        return values.Constant(typ, val)

    def _insert(self, instr):
        self._block.instructions.insert(self._anchor, instr)
        self._anchor += 1

    def _set_terminator(self, term):
        assert not self.block.is_terminated
        self._insert(term)
        self.block.terminator = term
        return term

    #
    # Arithmetic APIs
    #

    @_binop('add')
    def add(self, lhs, rhs, name=''):
        pass

    @_binop('fadd')
    def fadd(self, lhs, rhs, name=''):
        pass

    @_binop('sub')
    def sub(self, lhs, rhs, name=''):
        pass

    @_binop('fsub')
    def fsub(self, lhs, rhs, name=''):
        pass

    @_binop('mul')
    def mul(self, lhs, rhs, name=''):
        pass

    @_binop('fmul')
    def fmul(self, lhs, rhs, name=''):
        pass

    @_binop('udiv')
    def udiv(self, lhs, rhs, name=''):
        pass

    @_binop('sdiv')
    def sdiv(self, lhs, rhs, name=''):
        pass

    @_binop('fdiv')
    def fdiv(self, lhs, rhs, name=''):
        pass

    @_binop('urem')
    def urem(self, lhs, rhs, name=''):
        pass

    @_binop('srem')
    def srem(self, lhs, rhs, name=''):
        pass

    @_binop('frem')
    def frem(self, lhs, rhs, name=''):
        pass

    @_binop('or')
    def or_(self, lhs, rhs, name=''):
        pass

    @_binop('and')
    def and_(self, lhs, rhs, name=''):
        pass

    @_binop('xor')
    def xor(self, lhs, rhs, name=''):
        pass

    #
    # Unary APIs
    #

    def not_(self, value, name=''):
        return self.xor(value, values.Constant(value.type, -1), name=name)

    def neg(self, value, name=''):
        return self.sub(values.Constant(value.type, 0), value, name=name)

    #
    # Comparions APIs
    #

    def icmp_signed(self, cmpop, lhs, rhs, name=''):
        op = _CMP_MAP[cmpop]
        if cmpop not in ('==', '!='):
            op = 's' + op
        instr = values.ICMPInstr(self.block, op, lhs, rhs, name=name)
        self._insert(instr)
        return instr

    def icmp_unsigned(self, cmpop, lhs, rhs, name=''):
        op = _CMP_MAP[cmpop]
        if cmpop not in ('==', '!='):
            op = 'u' + op
        instr = values.ICMPInstr(self.block, op, lhs, rhs, name=name)
        self._insert(instr)
        return instr

    def fcmp_ordered(self, cmpop, lhs, rhs, name=''):
        if cmpop in _CMP_MAP:
            op = 'o' + _CMP_MAP[cmpop]
        else:
            op = cmpop
        instr = values.FCMPInstr(self.block, op, lhs, rhs, name=name)
        self._insert(instr)
        return instr

    def fcmp_unordered(self, cmpop, lhs, rhs, name=''):
        if cmpop in _CMP_MAP:
            op = 'u' + _CMP_MAP[cmpop]
        else:
            op = cmpop
        instr = values.FCMPInstr(self.block, op, lhs, rhs, name=name)
        self._insert(instr)
        return instr

    def select(self, cond, lhs, rhs, name=''):
        instr = values.SelectInstr(self.block, cond, lhs, rhs, name=name)
        self._insert(instr)
        return instr

    #
    # Cast APIs
    #

    @_castop('trunc')
    def trunc(self, value, typ, name=''):
        pass

    @_castop('zext')
    def zext(self, value, typ, name=''):
        pass

    @_castop('sext')
    def sext(self, value, typ, name=''):
        pass

    @_castop('fptrunc')
    def fptrunc(self, value, typ, name=''):
        pass

    @_castop('fpext')
    def fpext(self, value, typ, name=''):
        pass

    @_castop('bitcast')
    def bitcast(self, value, typ, name=''):
        pass

    @_castop('fptoui')
    def fptoui(self, value, typ, name=''):
        pass

    @_castop('uitofp')
    def uitofp(self, value, typ, name=''):
        pass

    @_castop('fptosi')
    def fptosi(self, value, typ, name=''):
        pass

    @_castop('sitofp')
    def sitofp(self, value, typ, name=''):
        pass

    @_castop('ptrtoint')
    def ptrtoint(self, value, typ, name=''):
        pass

    @_castop('inttoptr')
    def inttoptr(self, value, typ, name=''):
        pass

    #
    # Memory APIs
    #

    def alloca(self, typ, size=None, name=''):
        if isinstance(size, values.Constant):
            assert isinstance(size.type, types.IntType)
            size = size.constant

        assert size is None or size > 0
        if size is None:
            pass
        elif not isinstance(size, values.Value):
            # If it is not a Value instance,
            # assume to be a python number.
            size = values.Constant(types.IntType(32), int(size))

        al = values.AllocaInstr(self.block, typ, size, name)
        self._insert(al)
        return al

    def load(self, ptr, name=''):
        ld = values.LoadInstr(self.block, ptr, name)
        self._insert(ld)
        return ld

    def store(self, val, ptr):
        st = values.StoreInstr(self.block, val, ptr)
        self._insert(st)
        return st

    #
    # Terminators APIs
    #

    def switch(self, val, elseblk):
        swt = values.Terminator(self.block, 'switch', val, elseblk)
        self._set_terminator(swt)
        return swt

    def branch(self, target):
        """Jump to target
        """
        term = values.Terminator(self.block, "br", [target])
        self._set_terminator(term)
        return term

    def cbranch(self, cond, truebr, falsebr):
        """Branch conditionally
        """
        term = values.Terminator(self.block, "br", [cond, truebr, falsebr])
        self._set_terminator(term)
        return term

    def ret_void(self):
        return self._set_terminator(values.Terminator(self.block,
                                                      "ret void", ()))

    def ret(self, value):
        return self._set_terminator(values.Terminator(self.block, "ret",
                                                      [value]))

    # Call APIs

    def call(self, fn, args, name=''):
        inst = values.CallInstr(self.block, fn, args, name=name)
        self._insert(inst)
        return inst

    # GEP APIs

    def gep(self, ptr, indices, inbounds=False, name=''):
        instr = values.GEPInstr(self.block, ptr, indices,
                                inbounds=inbounds, name=name)
        self._insert(instr)
        return instr

    # Aggregate APIs

    def extract_value(self, agg, idx, name=''):
        if not isinstance(idx, (tuple, list)):
            idx = [idx]
        instr = values.ExtractValue(self.block, agg, idx, name='')
        self._insert(instr)
        return instr

    def insert_value(self, agg, elem, idx, name=''):
        if not isinstance(idx, (tuple, list)):
            idx = [idx]
        instr = values.InsertValue(self.block, agg, elem, idx, name='')
        self._insert(instr)
        return instr

    # PHI APIs

    def phi(self, typ, name=''):
        inst = values.PhiInstr(self.block, typ, name=name)
        self._insert(inst)
        return inst

    # Special API
    def unreachable(self):
        inst = values.Unreachable(self.block)
        self._set_terminator(inst)
