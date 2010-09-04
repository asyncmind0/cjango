/**
 * Copyright (C) 2010  Jakub Wieczorek <fawek@fawek.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.

 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include "CommentNode.h"
#include "Node.h"
#include "Parser.h"
#include "TagNode.h"
#include "TemplateNode.h"
#include "TextNode.h"
#include "VariableExpression.h"
#include "VariableNode.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const char* nodeTypeName(Node::Type type)
{
    switch (type) {
        case Node::Template:
            return "Template";
        case Node::Text:
            return "Text";
        case Node::Tag:
            return "Tag";
        case Node::Variable:
            return "Variable";
        case Node::Comment:
            return "Comment";
        default:
            assert(0);
    }
}

int depth(Node* node)
{
    int depth = 0;
    while (node->parent()) {
        node = node->parent();
        ++depth;
    }
    return depth;
}

Node* nextNodeInPreOrder(Node* node)
{
    if (node->firstChild())
        return node->firstChild();
    Node* next = node;
    while (next && !next->nextSibling())
        next = next->parent();
    return next ? next->nextSibling() : 0;
}

std::string removeNewLines(const std::string& string)
{
    std::string ret;
    for (int i = 0; i < string.size(); ++i) {
        if (string[i] == '\n')
            ret.append("\\n");
        else
            ret.push_back(string[i]);
    }
    return ret;
}

#define INDENT 2

void printNode(std::string& output, Node* node)
{
    int indent = depth(node) * INDENT;
    output.append(indent, ' ');
    
    Node::Type type = node->type();
    output.append(nodeTypeName(type));
    switch (type) {
        case Node::Template:
            break;
        case Node::Text: {
            TextNode* textNode = static_cast<TextNode*>(node);
            output.push_back(' ');
            output.push_back('"');
            output.append(removeNewLines(textNode->text()));
            output.push_back('"');
            break;
        }   
        case Node::Tag: {
            TagNode* tagNode = static_cast<TagNode*>(node);
            output.push_back(' ');
            output.push_back('"');
            output.append(tagNode->name());
            output.push_back('"');
            
            const std::vector<std::string>& parameters = tagNode->parameters();
            std::vector<std::string>::const_iterator it = parameters.begin();
            std::vector<std::string>::const_iterator end = parameters.end();
            for (it; it != end; ++it) {
                output.push_back(' ');
                output.push_back('"');
                output.append(removeNewLines(*it));
                output.push_back('"');
            }
            break;
        }
        case Node::Variable: {
            VariableNode* variableNode = static_cast<VariableNode*>(node);
            output.push_back(' ');
            output.append(variableNode->expression()->name());
            break;
        }
        case Node::Comment: {
            CommentNode* commentNode = static_cast<CommentNode*>(node);
            output.push_back(' ');
            output.push_back('"');
            output.append(removeNewLines(commentNode->text()));
            output.push_back('"');
            break;
        }
        default:
            assert(0);
    }
    
    output.push_back('\n');
}

class ParserTest : public ::testing::TestWithParam<const char*> { };

#define DATA_PATH "./testParserData/"

TEST_P(ParserTest, Parse) {
    const char* testName = GetParam();
    
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
    Node* node = root;
    while (node) {
        printNode(output, node);
        node = nextNodeInPreOrder(node);
    }
    
    std::istringstream outputStream(output);
    int line = 1;
    while (resultStream.good() || outputStream.good()) {
        std::string outputLine, resultLine;
        getline(outputStream, outputLine);
        getline(resultStream, resultLine);
        
        ASSERT_EQ(resultLine, outputLine) << "Line " << line;
        ++line;
    }
}

INSTANTIATE_TEST_CASE_P(Basic, ParserTest, ::testing::Values(
    "almostLikeClauses", "emptyFile", "filterWithLiteralParameter", "simpleComment", "simpleTag", "simpleTemplate", "simpleVariable", "tagWithLiteralParameter", "withTag"
    ));

