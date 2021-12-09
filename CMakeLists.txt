cmake_minimum_required(VERSION 3.16)
project(Project_5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project_5
        AddAutomaton.cpp
        AddAutomaton.h
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        CommaAutomaton.cpp
        CommaAutomaton.h
        CommentAutomaton.cpp
        CommentAutomaton.h
        EOF_Automaton.cpp
        EOF_Automaton.h
        FactsAutomaton.cpp
        FactsAutomaton.h
        ID_Automaton.cpp
        ID_Automaton.h
        LeftParenAutomaton.cpp
        LeftParenAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        MultiplyAutomaton.cpp
        MultiplyAutomaton.h
        PeriodAutomaton.cpp
        PeriodAutomaton.h
        QMarkAutomaton.cpp
        QMarkAutomaton.h
        QueriesAutomaton.cpp
        QueriesAutomaton.h
        RightParenAutomaton.cpp
        RightParenAutomaton.h
        RulesAutomaton.cpp
        RulesAutomaton.h
        SchemesAutomaton.cpp
        SchemesAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        Token.cpp
        Token.h Parser.cpp Parser.h DatalogProgram.cpp DatalogProgram.h Predicate.cpp Predicate.h Parameter.cpp Parameter.h Rule.cpp Rule.h Database.cpp Database.h Header.cpp Header.h Relation.cpp Relation.h Tuple.cpp Tuple.h Interpreter.cpp Interpreter.h Graph.cpp Graph.h)
