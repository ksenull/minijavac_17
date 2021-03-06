#pragma once

#include <iostream>
#include "../common/Located.h"

namespace symboltable {

    class Symbol {
    public:
        Symbol() = default;
        virtual ~Symbol() = default;

        Symbol(const std::string& name) : name(name) {}

        Symbol(std::string&& name) : name(std::move(name)) {}

//        Symbol(const Symbol&) = delete;

//        Symbol operator=(const Symbol&) = delete;

        std::string name; // TODO make it private and add getter
    };

    Symbol* getIntern(const std::string& symbolName);

    class IInfo : public common::Located {
    public:
        IInfo() = default;

        explicit IInfo(const common::Location& loc) : common::Located(loc) {}
        virtual ~IInfo() = default;

    private:
        Symbol symbol;
    };
}