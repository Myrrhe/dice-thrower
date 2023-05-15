#include "text/ChainText.hpp"
#include "func.hpp"
#include <iostream>

ChainText::ChainText() :
    nodes( {}),
       leafs({}),
       blocks({}),
       blocksClosing({})
{
    //ctor
}

ChainText::~ChainText()
{
    //dtor
}

ChainText::ChainText(const ChainText& other) :
    nodes(other.nodes),
    leafs(other.leafs),
    blocks(other.blocks),
    blocksClosing(other.blocksClosing)
{
    //copy ctor
}

ChainText::ChainText(const std::u32string& str) :
    nodes( {}),
leafs({}),
blocks({}),
blocksClosing({})
{
    if (str.empty())
    {
        return;
    }
    if (parseString(str, false))
    {
        parseString(str, true);
    }
    else
    {
        std::string str8 = "";
        utf32ToUtf8(str.begin(), str.end(), std::back_inserter(str8));
        std::cout << "Error during the parsing of the string : " << str8 << " to make a ChainText." << std::endl;
        nodes = {};
        leafs = {};
        blocks = {};
        blocksClosing = {};
    }
}

ChainText::ChainText(const std::string& str) :
    nodes( {}),
leafs({}),
blocks({}),
blocksClosing({})
{
    if (str.empty())
    {
        return;
    }
    std::u32string u32str = U"";
    //sf::Utf8::toUtf32(str.begin(), str.end(), std::back_inserter(u32str));
    utf8ToUtf32(str.begin(), str.end(), std::back_inserter(u32str));
    if (parseString(u32str, false))
    {
        parseString(u32str, true);
    }
    else
    {
        std::cout << "Error during the parsing of the string : " << str << " to make a ChainText." << std::endl;
        nodes = {};
        leafs = {};
        blocks = {};
        blocksClosing = {};
    }
}
/*
ChainText::ChainText(const sf::String& str) : ChainText(str.toUtf32())
{

}
*/
ChainText& ChainText::operator=(const ChainText& rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    //assignment operator
    nodes = rhs.nodes;
    leafs = rhs.leafs;
    blocks = rhs.blocks;
    blocksClosing = rhs.blocksClosing;
    return *this;
}

void ChainText::addChar(char32_t char32, long unsigned int posAdd)
{
    if (hasNoLeaf())
    {
        leafs.emplace_back(char32);
        nodes.emplace_back(&leafs.front());
    }
    else
    {
        std::tuple<long unsigned int, long unsigned int, long unsigned int> pos = getIndexLeaf(posAdd);
        leafs[std::get<1>(pos)].addChar(char32, std::get<2>(pos));
    }
    /*
    if (nodes.empty() || nodes.back()->getType() != NodeText::Type::LEAF)
    {
        std::vector<long unsigned int> indexLeafs = {};
        for (long unsigned int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i]->getType() == NodeText::Type::LEAF)
            {
                indexLeafs.emplace_back(i);
            }
        }
        leafs.emplace_back(std::u32string(1, char32));
        for (long unsigned int i = 0; i < indexLeafs.size(); i++)
        {
            nodes[indexLeafs[i]] = &leafs[i];
        }
        nodes.emplace_back(&leafs.back());
    }
    else
    {
        dynamic_cast<LeafText*>(nodes.back())->addChar(char32);
    }
    */
}

void ChainText::addChar(char32_t char32)
{
    addChar(char32, getNbChar());
}

void ChainText::popChar(long unsigned int posPop)
{
    if (isEmpty())
    {
        return;
    }
    std::tuple<long unsigned int, long unsigned int, long unsigned int> pos = getIndexLeaf(posPop);
    leafs[std::get<1>(pos)].popChar(std::get<2>(pos));
    removeEmptyLeafs();
    removeEmptyBlockInfo();
    mergeLeafs();
    /*
    for (long unsigned int i = 0; i < nodes.size(); i++)
    {
        if (nodes[nodes.size() - i - 1]->getType() == NodeText::Type::LEAF)
        {
            dynamic_cast<LeafText*>(nodes[nodes.size() - i - 1])->popChar();
            removeEmptyLeafs();
            removeEmptyBlockInfo();
            mergeLeafs();
            return;
        }
    }
    */
}

void ChainText::popChar()
{
    popChar(getNbChar());
}

void ChainText::delChar(long unsigned int posInit, long unsigned int posFina)
{
    std::tuple<long unsigned int, long unsigned int, long unsigned int> posI = getIndexLeaf(posInit);
    std::tuple<long unsigned int, long unsigned int, long unsigned int> posF = getIndexLeaf(posFina);
    leafs[std::get<1>(posI)].trimRight(std::get<2>(posI));
    leafs[std::get<1>(posF)].trimLeft(std::get<2>(posF));
    removeEmptyLeafs();
    removeEmptyBlockInfo();
    mergeLeafs();
}

void ChainText::removeEmptyLeafs()
{
    long unsigned int indexLeaf = 0;
    long unsigned int nbLeafDeleted = 0;
    for (long unsigned int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getType() == NodeText::Type::LEAF)
        {
            //nodes[i] -= nbLeafDeleted;
            nodes[i] = &leafs[indexLeaf];
            if (dynamic_cast<LeafText*>(nodes[i])->isEmpty())
            {
                leafs.erase(leafs.begin() + static_cast<long int>(indexLeaf));
                nodes.erase(nodes.begin() + static_cast<long int>(i));
                nbLeafDeleted++;
                i--;
                indexLeaf--;
            }
            indexLeaf++;
        }
    }
}

void ChainText::removeEmptyBlockInfo()
{

}

void ChainText::removeUselessBlockInfo()
{

}

void ChainText::mergeLeafs()
{
    long unsigned int indexLeaf = 0;
    long unsigned int nbLeafDeleted = 0;
    bool prevIsLeaf = false;
    for (long unsigned int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getType() == NodeText::Type::LEAF)
        {
            nodes[i] -= nbLeafDeleted;
            if (prevIsLeaf)
            {
                leafs[indexLeaf - 1].mergeLeaf(leafs[indexLeaf]);
                leafs.erase(leafs.begin() + static_cast<long int>(indexLeaf));
                nodes.erase(nodes.begin() + static_cast<long int>(i));
                nbLeafDeleted++;
                i--;
            }
            indexLeaf++;
            prevIsLeaf = true;
        }
        else
        {
            prevIsLeaf = false;
        }
    }
}

std::size_t ChainText::getSize() const
{
    return nodes.size();
}

bool ChainText::isEmpty() const
{
    bool noText = true;
    for (long unsigned int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getType() == NodeText::Type::LEAF)
        {
            noText = noText && dynamic_cast<LeafText*>(nodes[i])->isEmpty();
        }
    }
    return noText;
}

bool ChainText::hasNoLeaf() const
{
    for (long unsigned int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getType() == NodeText::Type::LEAF)
        {
            return false;
        }
    }
    return true;
}

const NodeText* ChainText::operator[](std::size_t i) const
{
    return nodes[i];
}

bool ChainText::operator==(const ChainText& right) const
{
    if (nodes.size() != right.nodes.size())
    {
        return false;
    }
    for (long unsigned int i = 0; i < nodes.size(); i++)
    {
        if (*nodes[i] != *right.nodes[i])
        {
            return false;
        }
    }
    return true;
}

bool ChainText::operator!=(const ChainText& right) const
{
    return !(*this == right);
}

long unsigned int ChainText::getNbChar() const
{
    long unsigned int res = 0;
    for (long unsigned int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getType() == NodeText::Type::LEAF)
        {
            res += dynamic_cast<LeafText*>(nodes[i])->getSize();
        }
    }
    return res;
}

long unsigned int ChainText::getNbChar(long unsigned int i) const
{
    if (nodes[i]->getType() != NodeText::Type::LEAF)
    {
        return 0;
    }
    else
    {
        return dynamic_cast<LeafText*>(nodes[i])->getSize();
    }
}

std::tuple<long unsigned int, long unsigned int, long unsigned int> ChainText::getIndexLeaf(long unsigned int posChar) const
{
    if (hasNoLeaf())
    {
        return {nodes.size(), 0, posChar};
    }
    long unsigned int qtChar = 0;
    long unsigned int indexLeaf = 0;
    long unsigned int indexNode = 0;
    for (long unsigned int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getType() == NodeText::Type::LEAF)
        {
            long unsigned int sizeLeaf = dynamic_cast<LeafText*>(nodes[i])->getSize();
            qtChar += sizeLeaf;
            if (posChar < qtChar)
            {
                return {i, indexLeaf, posChar - (qtChar - sizeLeaf)};
            }
            indexNode = i;
            indexLeaf++;
        }
    }
    return {indexNode, leafs.size() - 1, leafs.back().getSize()};
}

std::u32string ChainText::getStr() const
{
    std::u32string res = U"";
    for (long unsigned int i = 0; i < nodes.size(); i++)
    {
        bool ty = nodes[i]->getType() == NodeText::Type::LEAF;
        if (ty)
        {
            res += dynamic_cast<LeafText*>(nodes[i])->getStr();
        }
    }
    return res;
}

std::u32string ChainText::toStr() const
{
    std::u32string res = U"";
    for (long unsigned int i = 0; i < nodes.size(); i++)
    {
        res += nodes[i]->toStr();
    }
    return res;
}

bool ChainText::parseString(const std::u32string& str, bool setNodes)
{
    int countSlash = 0;
    //long unsigned int indexInit = 0;
    long unsigned int indexFina = 0;
    long unsigned int sizeLeaf = 0;
    long unsigned int sizeBlock = 0;
    long unsigned int sizeClosingBlock = 0;
    std::u32string currLeaf = U"";
    for (long unsigned int i = 0; i < str.size(); i++)
    {
        if (str[i] == U'<' && countSlash % 2 == 0)
        {
            if (/*indexInit != i*/!currLeaf.empty())
            {
                if (!setNodes)
                {
                    sizeLeaf++;
                }
                else
                {
                    //leafs.emplace_back(str.substr(indexInit, i - indexInit));
                    leafs.emplace_back(currLeaf);
                    nodes.emplace_back(&leafs.back());
                }
            }
            indexFina = str.find(U'>', i);
            if (indexFina == std::string::npos)
            {
                return false;
            }
            if (str.substr(i, indexFina - i + 1) == U"</>")
            {
                if (!setNodes)
                {
                    sizeClosingBlock++;
                }
                else
                {
                    blocksClosing.emplace_back(/*BlockClosingText()*/);
                    nodes.emplace_back(&blocksClosing.back());
                }
            }
            else
            {
                if (!setNodes)
                {
                    sizeBlock++;
                }
                else
                {
                    blocks.emplace_back(str.substr(i + 1, indexFina - (i + 1)));
                    nodes.emplace_back(&blocks.back());
                }
            }
            //indexInit = indexFina + 1;
            i = indexFina;
            countSlash = 0;
            currLeaf = U"";
        }
        else if (str[i] == U'\\')
        {
            countSlash++;
            if (countSlash % 2 == 0)
            {
                currLeaf += U'\\';
            }
        }
        else
        {
            countSlash = 0;
            currLeaf += str[i];
        }
        if (sizeClosingBlock > sizeBlock)
        {
            return false;
        }
    }
    if (/*indexInit != str.size()*/!currLeaf.empty())
    {
        if (!setNodes)
        {
            sizeLeaf++;
        }
        else
        {
            //leafs.emplace_back(str.substr(indexInit, str.size() - indexInit));
            leafs.emplace_back(currLeaf);
            nodes.emplace_back(&leafs.back());
        }
    }
    if (!setNodes)
    {
        leafs.reserve(sizeLeaf);
        blocks.reserve(sizeBlock);
        blocksClosing.reserve(sizeClosingBlock);
        nodes.reserve(sizeLeaf + sizeBlock + sizeClosingBlock);
    }
    return true;
}
