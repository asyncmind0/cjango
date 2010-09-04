#include <gtest/gtest.h>

#include "ASCIIUtils.h"
#include "Context.h"
#include "Parser.h"
#include "TemplateNode.h"
#include "VariantUtils.h"

#include <iostream>
#include <fstream>
#include <string>

class TemplateTest : public ::testing::TestWithParam<const char*> { };

#define DATA_PATH "./testTemplateData/"

TEST_P(TemplateTest, Tokenize) {
    const char* testName = GetParam();
    
    char* variableFile = (char*) malloc(sizeof(char) * (strlen(DATA_PATH) + strlen(testName) + strlen(".var") + 1));
    strcpy(variableFile, DATA_PATH);
    strcat(variableFile, testName);
    strcat(variableFile, ".var");
    std::fstream variableStream(variableFile, std::fstream::in);

    Context context;
    while (variableStream.good()) {
        std::string variableLine;
        getline(variableStream, variableLine);
        int pos = variableLine.find_first_of(' ');
        if (pos == std::string::npos)
            break;
        
        std::string variable = variableLine.substr(0, pos);
        while (pos < variableLine.size() && isWhitespace(variableLine[pos]))
            ++pos;
        std::string value = variableLine.substr(pos);
        
        context.set(variable, variantFromString(value));
    }
    
    char* inputFile = (char*) malloc(sizeof(char) * (strlen(DATA_PATH) + strlen(testName) + strlen(".in") + 1));
    strcpy(inputFile, DATA_PATH);
    strcat(inputFile, testName);
    strcat(inputFile, ".in");
    std::fstream inputStream(inputFile, std::fstream::in);
    ASSERT_TRUE(inputStream.good());
    
    char* resultFile = (char*) malloc(sizeof(char) * (strlen(DATA_PATH) + strlen(testName) + strlen(".out") + 1));
    strcpy(resultFile, DATA_PATH);
    strcat(resultFile, testName);
    strcat(resultFile, ".out");
    std::fstream resultStream(resultFile, std::fstream::in);
    ASSERT_TRUE(resultStream.good());
    
    Parser parser(&inputStream);
    TemplateNode* root = parser.parse();
    
    std::string output;
    std::stringstream outputStream(output);
    root->render(&context, &outputStream);
    
    int line = 1;
    while (resultStream.good() || outputStream.good()) {
        std::string outputLine, resultLine;
        getline(outputStream, outputLine);
        getline(resultStream, resultLine);
        
        ASSERT_EQ(resultLine, outputLine) << "Line " << line;
        ++line;
    }
}

INSTANTIATE_TEST_CASE_P(Basic, TemplateTest, ::testing::Values(
    ));

