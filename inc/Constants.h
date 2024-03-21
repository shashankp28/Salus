#ifndef CONSTANTS_H
#define CONSTANTS_H

enum CompareType
{
    EQUAL,
    NOT_EQUAL,
    GREATER,
    LESS,
    GREATER_EQUAL,
    LESS_EQUAL
};

enum LogLevel
{
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
};

enum HierarchyState
{
    CYCLE,
    LOW_ROOT,
    DISJOINT,
    CONSISTANT,
};

#endif