#pragma once

#include <vector>

#include "../Temp.h"
#include "IVisitor.h"

namespace ir {
namespace tree {

    enum BinaryOperation {
        BO_Plus, BO_Minus, BO_Mul, BO_Div, BO_And, BO_Or, BO_Lshift, BO_Rshift, BO_Arshift, BO_Xor
    };

    enum RelationalOperation {
        RO_Eq, RO_Ne, RO_Lt, RO_Gt, RO_Le, RO_Ge, RO_Ult, RO_Ugt, RO_Ule, RO_Uge
    };

    struct IStatement;

    struct INode {
        virtual ~INode() = default;
        virtual void accept(const IVisitor<void>* visitor) const = 0;
    };

#define DEFINE_PRINT_ACCEPT \
        void accept(const IVisitor<void>* visitor) const override { \
            visitor->visit(this); \
        }

    struct INodeList : public INode {
        INodeList() = default;
        explicit INodeList(const std::vector<INode*>& _nodes) : nodes(_nodes) {}

        std::vector<INode*> nodes;
    };

    struct IExpression : public INode {
        virtual ~IExpression() = default;
        virtual void accept(const IVisitor<void>* visitor) const = 0;
    };

    struct CExpressionList : INodeList {
        CExpressionList() = default;
        ~CExpressionList() = default;
        /* implicit */ CExpressionList(const std::vector<INode*>& _nodes) : INodeList(_nodes) {};

        DEFINE_PRINT_ACCEPT
    };

    struct CConstExpression : IExpression {
        explicit CConstExpression(int i) : i(i) {}
        DEFINE_PRINT_ACCEPT

        int i;
    };

    struct CNameExpression : IExpression {
        explicit CNameExpression(const Label& label) : label(label) {}
        explicit CNameExpression(const std::string& str) : label(str) {}
        DEFINE_PRINT_ACCEPT

        Label label;
    };

    struct CTempExpression : IExpression {
        explicit CTempExpression(IReg* reg) : reg(reg) {}
        DEFINE_PRINT_ACCEPT

        IReg* reg;
    };

    struct CBinopExpression : IExpression {
        CBinopExpression(IExpression* left, BinaryOperation op, IExpression* right) :
        left(left), op(op), right(right) {}
        DEFINE_PRINT_ACCEPT

        IExpression* left;
        BinaryOperation op;
        IExpression* right;
    };

    struct CMemExpression : IExpression { // content of wordSize bytes from addr
        explicit CMemExpression(IExpression* addr) : addr(addr) {}
        DEFINE_PRINT_ACCEPT

        IExpression* addr;
    };

    struct CCallExpression : IExpression {
        CCallExpression(Label* _func) : func(_func) {
            args = new CExpressionList();
        }
        CCallExpression(Label* _func, CExpressionList* _args) : func(_func), args(_args) {}
        
        DEFINE_PRINT_ACCEPT

        Label* func;
        CExpressionList* args;
//        IStatement* args;
    };

    struct CEseqExpression : IExpression { //stm evaluated for side effects, then e evalutes for a result
        CEseqExpression(IStatement* stm, IExpression* exp) : stm(stm), exp(exp) {}
        DEFINE_PRINT_ACCEPT

        IStatement* stm;
        IExpression* exp;
    };

#undef DEFINE_PRINT_ACCEPT
}
}