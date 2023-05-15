#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP
#include "ChainText.hpp"
#include "ClickaBleWidget.hpp"
#include "NinePatch.hpp"
#include "Text.hpp"

class TextBox : public ClickableWidget
{
public:

    enum class Action : long unsigned int
    {
        ADD_CHAR,
        DEL_LEFT,
        DEL_RIGHT,
        MOVE_LEFT,
        MOVE_RIGHT,
    };

    TextBox();
    TextBox(float newWidth, float newHeight, const sf::Texture* newTexture, const sf::Window* newWindow);
    ~TextBox();
    TextBox(const TextBox& right);
    TextBox& operator=(const TextBox& rhs);

    void update();

    sf::Rect<float> getLocalBounds() const override;

    sf::Rect<float> getGlobalBounds() const;

    void setTexture(const sf::Texture& newTexture);

    void setTextureRect(const sf::Rect<int>& newRect);
    void setTextureRect(int newLeft, int newTop, int newWidth, int newHeight);

    void setSize(const sf::Vector2<float>& newSize);
    void setSize(float newWidth, float newHeight);

    void setColor(const sf::Color& color);

    void setBorder(float borderLeft, float borderTop, float borderRight, float borderBottom);
    void setBorder(float border);

    //State getInput() override;

    void setFont(const sf::Font& font);
    void setCharSize(unsigned int charSize);
    void setLetterSpacingFactor(float letterSpacingFactor);
    void setFillColor(const sf::Color& fllColor);
    void setOutlineColor(const sf::Color outlineColor);
    void setSizeBack(const sf::Vector2<float>& sizeBack);
    void setThickness(float thickness);

    void setPositionText(float posX, float posY);

    void setSizeBorderSlide(float newSizeBorderSlide);

    void setTextureCursor(const sf::Texture* newTextureCursor);

    void setTextureRectCursor(const sf::Rect<int>& newRect);
    void setTextureRectCursor(int newLeft, int newTop, int newWidth, int newHeight);

    void setCursorPosition();

    void setCursorPositionOffset(float posX, float posY);

    void setCursorPositionMax(float posMaxX, float posMaxY);

    void setPointerChainText();

protected:

    void updatePositions();
    void updateTexCoords();

    void updatePositionsCursor();
    void updateTexCoordsCursor();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Rect<int> textureRect;
    NinePatch ninePatch;

    const sf::Texture* textureCursor;
    sf::Rect<int> textureRectCursor;
    std::array<sf::Vertex, 4> verticesCursor;

    sf::Vector2<float> positionCursor;
    sf::Vector2<float> positionCursorOffset;

    sf::Vector2<float> posMaxCursor;

    sf::Vector2<float> positionText;
    sf::Vector2<float> positionTextOffset;

    ChainText chainText;
    Text text;

    long unsigned int indexCursor;

    Action lastAction;

    long unsigned int selIni;
    long unsigned int selEnd;

    long unsigned int selMin;
    long unsigned int selMax;

    float sizeBorderSlide;

    long unsigned int frameCount;
};

#endif // TEXTBOX_HPP
