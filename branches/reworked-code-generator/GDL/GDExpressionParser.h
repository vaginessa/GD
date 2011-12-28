/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */
#if defined(GD_IDE_ONLY)

#ifndef GDEXPRESSIONPARSER_H
#define GDEXPRESSIONPARSER_H

#include <string>
#include <vector>
class GDExpression;
class ParserCallbacks;
class Game;
class Scene;
class ParameterInfo;
class ExpressionInstruction;
class StrExpressionInstruction;
class ExpressionInfos;
class StrExpressionInfos;

/** \brief Internal class. Parse a plainExpression by calling functors at each token
 *
 * Parse the expression, and call functors when a token is reached
 * ( like a function call )
 */
class GD_API GDExpressionParser
{
    public:
        GDExpressionParser(const std::string & expressionPlainString_);
        virtual ~GDExpressionParser() {};

        /**
         * Parse the expression, calling each functor when necessary
         * \return True if expression was correctly parsed.
         */
        bool ParseMathExpression(const Game & game, const Scene & scene, ParserCallbacks & callbacks);

        /**
         * Parse the expression, calling each functor when necessary
         * \return True if expression was correctly parsed.
         */
        bool ParseTextExpression(const Game & game, const Scene & scene, ParserCallbacks & callbacks);

        #if defined(GD_IDE_ONLY)
        std::string firstErrorStr;
        size_t firstErrorPos;
        #endif

    private:

        /**
         * Tool function to add a parameter
         */
        bool AddParameterToList(const Game & game, const Scene & scene, ParserCallbacks &, std::vector < GDExpression > & parameters, std::string parameterStr, std::vector < ParameterInfo > parametersInfos, const size_t positionInExpression);

        /**
         * Tool function to prepare a parameter
         */
        bool PrepareParameter(const Game & game, const Scene & scene, ParserCallbacks &, GDExpression & parameter, const ParameterInfo & parametersInfo, const size_t positionInExpression);

        bool ValidSyntax(const std::string & str);

        std::string expressionPlainString;
        static std::string parserSeparators;
};

/** \brief Callbacks called by parser during parsing
 *
 * Parser will call the appropriate functions during parsing, allowing to do special works.
 */
class ParserCallbacks
{
    public:

    ParserCallbacks() {};
    virtual ~ParserCallbacks() {};

    virtual void OnConstantToken(std::string text) = 0;
    virtual void OnNumber(std::string text) = 0;
    virtual void OnOperator(std::string text) = 0;

    virtual void OnStaticFunction(std::string functionName, const ExpressionInstruction & instruction, const ExpressionInfos & expressionInfo) = 0;
    virtual void OnStaticFunction(std::string functionName, const StrExpressionInstruction & instruction, const StrExpressionInfos & expressionInfos) = 0;

    virtual void OnObjectFunction(std::string functionName, const ExpressionInstruction & instruction, const ExpressionInfos & expressionInfo) = 0;
    virtual void OnObjectFunction(std::string functionName, const StrExpressionInstruction & instruction, const StrExpressionInfos & expressionInfos) = 0;

    virtual void OnObjectAutomatismFunction(std::string functionName, const ExpressionInstruction & instruction, const ExpressionInfos & expressionInfo) = 0;
    virtual void OnObjectAutomatismFunction(std::string functionName, const StrExpressionInstruction & instruction, const StrExpressionInfos & expressionInfos) = 0;

    virtual bool OnSubMathExpression(const Game & game, const Scene & scene, GDExpression & expression) = 0;
    virtual bool OnSubTextExpression(const Game & game, const Scene & scene, GDExpression & expression) = 0;

    #if defined(GD_IDE_ONLY)
    std::string firstErrorStr;
    size_t firstErrorPos;
    #endif
};

#endif // GDEXPRESSIONPARSER_H

#endif