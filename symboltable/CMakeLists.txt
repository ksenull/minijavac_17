project(SymbolTable)

set(INFO Table.cpp Table.h Symbol.cpp Symbol.h VariableInfo.cpp VariableInfo.h MethodInfo.h ClassInfo.cpp ClassInfo.h MethodInfo.cpp)
set(ERRORS ../common/Exception.h SymbolException.h)
set(HEADER_FILES ../ast/nodes/Identifier.h ../ast/nodes/Nodes.h ../ast/nodes/INode.h)
set(SOURCE_FILES main.cpp)
set(PARSE ../grammar/Scanner.cpp ../grammar/Parser.cpp ../grammar/parse.cpp)
set(TYPECHECK TypeCheckVisitor.cpp TypeCheckVisitor.h)

add_executable(SymbolTable ${SOURCE_FILES} ${INFO} ${HEADER_FILES} ${PARSE} ${ERRORS} ${TYPECHECK})

target_link_libraries(SymbolTable)
set_property(TARGET SymbolTable PROPERTY CXX_STANDARD 14)
