#ifndef CHAINTEXT_HPP
#define CHAINTEXT_HPP
#include "LeafText.hpp"
#include "BlockInfoText.hpp"
#include "BlockClosingText.hpp"

class ChainText
{
public:
    ChainText();
    ~ChainText();
    ChainText(const ChainText& other);
    ChainText(const std::u32string& str);
    ChainText(const std::string& str);
    //ChainText(const sf::String& str);
    ChainText& operator=(const ChainText& rhs);

    void addChar(char32_t char32, long unsigned int posAdd);
    void addChar(char32_t char32);
    void popChar(long unsigned int posPop);
    void popChar();
    void delChar(long unsigned int posInit, long unsigned int posFina);

    void removeEmptyLeafs();
    void removeEmptyBlockInfo();
    void removeUselessBlockInfo();
    void mergeLeafs();

    std::size_t getSize() const;
    bool isEmpty() const;
    bool hasNoLeaf() const;
    const NodeText* operator[](std::size_t i) const;

    bool operator==(const ChainText& right) const;
    bool operator!=(const ChainText& right) const;

    long unsigned int getNbChar() const;
    long unsigned int getNbChar(long unsigned int i) const;

    std::tuple<long unsigned int, long unsigned int, long unsigned int> getIndexLeaf(long unsigned int posChar) const;

    std::u32string getStr() const;

    std::u32string toStr() const;

protected:

private:

    bool parseString(const std::u32string& str, bool setNodes);

    std::vector<NodeText*> nodes;
    std::vector<LeafText> leafs;
    std::vector<BlockInfoText> blocks;
    std::vector<BlockClosingText> blocksClosing;
};

#endif // CHAINTEXT_HPP
