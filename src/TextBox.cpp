#include "InputManager.hpp"
#include "TextBox.hpp"
#include "Window.hpp"
#include "func.hpp"
#include <iostream>
#include <istream>

TextBox::TextBox() : ClickableWidget(),
    textureRect(),
    ninePatch(),
    textureCursor(nullptr),
    textureRectCursor(),
    verticesCursor(),
    positionCursor(),
    positionCursorOffset(),
    posMaxCursor(),
    positionText(),
    positionTextOffset(),
    chainText(),
    text(),
    indexCursor(0),
    lastAction(Action::ADD_CHAR),
    selIni(0),
    selEnd(0),
    selMin(0),
    selMax(0),
    sizeBorderSlide(1.0f),
    frameCount(0)
{
    text.setChainText({&chainText});
}

TextBox::TextBox(float newWidth, float newHeight, const sf::Texture* newTexture, const sf::Window* newWindow) : ClickableWidget(),
    textureRect(sf::Rect<int>()),
    ninePatch(),
    textureCursor(nullptr),
    textureRectCursor(),
    verticesCursor(),
    positionCursor(),
    positionCursorOffset(),
    posMaxCursor(),
    positionText(),
    positionTextOffset(),
    chainText(),
    text(),
    indexCursor(0),
    lastAction(Action::ADD_CHAR),
    selIni(0),
    selEnd(0),
    selMin(0),
    selMax(0),
    sizeBorderSlide(1.0f),
    frameCount(0)
{
    setSize(newWidth, newHeight);
    setTexture(*newTexture);
    setWindow(newWindow);
    text.setChainText({&chainText});
}

TextBox::~TextBox()
{

}

TextBox::TextBox(const TextBox& right) : ClickableWidget(right),
    textureRect(right.textureRect),
    ninePatch(right.ninePatch),
    textureCursor(right.textureCursor),
    textureRectCursor(right.textureRectCursor),
    verticesCursor(right.verticesCursor),
    positionCursor(right.positionCursor),
    positionCursorOffset(right.positionCursorOffset),
    posMaxCursor(right.posMaxCursor),
    positionText(right.positionText),
    positionTextOffset(right.positionTextOffset),
    chainText(right.chainText),
    text(right.text),
    indexCursor(right.indexCursor),
    lastAction(right.lastAction),
    selIni(right.selIni),
    selEnd(right.selEnd),
    selMin(right.selMin),
    selMax(right.selMax),
    sizeBorderSlide(right.sizeBorderSlide),
    frameCount(right.frameCount)
{

}

TextBox& TextBox::operator=(const TextBox& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    ClickableWidget::operator=(rhs);
    textureRect = rhs.textureRect;
    ninePatch = rhs.ninePatch;
    textureCursor = rhs.textureCursor;
    textureRectCursor = rhs.textureRectCursor;
    verticesCursor = rhs.verticesCursor;
    positionCursor = rhs.positionCursor;
    positionCursorOffset = rhs.positionCursorOffset;
    posMaxCursor = rhs.posMaxCursor;
    positionText = rhs.positionText;
    positionTextOffset = rhs.positionTextOffset;
    chainText = rhs.chainText;
    text = rhs.text;
    indexCursor = rhs.indexCursor;
    lastAction = rhs.lastAction;
    selIni = rhs.selIni;
    selEnd = rhs.selEnd;
    selMin = rhs.selMin;
    selMax = rhs.selMax;
    sizeBorderSlide = rhs.sizeBorderSlide;
    frameCount = rhs.frameCount;
    return *this;
}

void TextBox::update()
{
    if (state == State::MOUSE_CLICKED)
    {
        focused = true;
    }
    else if (state == State::MOUSE_CLICKED_NOT_ON_WIDGET || state == State::MOUSE_CLICKED_OUT_ON_WIDGET)
    {
        focused = false;
    }
    if (focused)
    {
        if (Window::isTextEntered())
        {
            std::cout << "char entered : " << static_cast<unsigned int>(Window::getCharEntered()) << std::endl;
            if (Window::getCharEntered() == '\b')
            {
                if (selMin == selMax)
                {
                    if (indexCursor > 0)
                    {
                        chainText.popChar(indexCursor - 1);
                        indexCursor--;
                        lastAction = Action::DEL_LEFT;
                    }
                }
                else
                {
                    indexCursor = selMin;
                    lastAction = Action::DEL_LEFT;
                }
            }
            else
            {
                chainText.addChar(Window::getCharEntered(), indexCursor);
                indexCursor++;
                if (InputManager::isInsertMode() && indexCursor < chainText.getNbChar())
                {
                    chainText.popChar(indexCursor);
                }
                lastAction = Action::ADD_CHAR;
            }
            std::cout << str32Tostr8(text.getChainText().back()->toStr()) << std::endl;
            text.setGeometryNeedUpdate();
            setCursorPosition();
        }
        if (Window::isKeyPressed())
        {
            if (Window::getKeyPressed() == sf::Keyboard::Key::Delete)
            {
                if (indexCursor < chainText.getNbChar())
                {
                    chainText.popChar(indexCursor);
                    text.setGeometryNeedUpdate();
                    setCursorPosition();
                    lastAction = Action::DEL_RIGHT;
                }
            }
            if (Window::getKeyPressed() == sf::Keyboard::Key::Left)
            {
                if (indexCursor)
                {
                    indexCursor--;
                    setCursorPosition();
                    lastAction = Action::MOVE_LEFT;
                }
            }
            else if (Window::getKeyPressed() == sf::Keyboard::Key::Right)
            {
                if (indexCursor < chainText.getNbChar())
                {
                    indexCursor++;
                    setCursorPosition();
                    lastAction = Action::MOVE_RIGHT;
                }
            }
            else if (Window::getKeyPressed() == sf::Keyboard::Key::End)
            {
                if (indexCursor != chainText.getNbChar())
                {
                    indexCursor = chainText.getNbChar();
                    setCursorPosition();
                    lastAction = Action::MOVE_RIGHT;
                }
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2<int> mousePos = Window::getMousePosition();

            if (InputManager::isFirstFrameMouseClicked())
            {
                //selIni = text.findIndexCharacter(static_cast<sf::Vector2<float> >(mousePos) - text.getPosition());
                selIni = text.findIndexCharacter((static_cast<sf::Vector2<float> >(mousePos) - text.getPosition() - getPosition()).x);
                //selEnd = selIni;
            }
            selEnd = text.findIndexCharacter((static_cast<sf::Vector2<float> >(mousePos) - text.getPosition() - getPosition()).x);
            indexCursor = selEnd;
            /*
            long unsigned int selNew = text.findIndexCharacter((static_cast<sf::Vector2<float> >(mousePos) - text.getPosition() - getPosition()).x);
            indexCursor = selNew;
            if (selNew <= selIni)
            {
                selIni = selNew;
            }
            else
            {
                selEnd = selNew;
            }
            */
            //selEnd = text.findIndexCharacter((static_cast<sf::Vector2<float> >(mousePos) - text.getPosition() - getPosition()).x);
            /*
            if (selIni > selEnd)
            {
                long unsigned int tmpIni = selIni;
                selIni = selEnd;
                selEnd = tmpIni;
            }
            */
            selMin = std::min(selIni, selEnd);
            selMax = std::max(selIni, selEnd);
            //std::cout << "sel = " << selMin << ", " << selMax << std::endl;
            text.setBackColor(sf::Color(0, 0, 0, 0), 0, selMin);
            text.setBackColor(sf::Color(0, 120, 215, 255), selMin, selMax);
            text.setBackColor(sf::Color(0, 0, 0, 0), selMax, chainText.getNbChar());

            /*
            if (static_cast<float>(mousePos.x) - getPosition().x < sizeBorderSlide)
            {
                if (indexCursor > 0)
                {
                    indexCursor--;
                }
            }
            else if (static_cast<float>(mousePos.x) - getPosition().x > width - sizeBorderSlide)
            {
                if (indexCursor < chainText.getNbChar())
                {
                    indexCursor++;
                }
            }
            */

            setCursorPosition();
        }
    }
    if (stateChanged())
    {
        updateTexCoords();
    }
    frameCount++;
}

sf::Rect<float> TextBox::getLocalBounds() const
{
    return ninePatch.getLocalBounds();
}

sf::Rect<float> TextBox::getGlobalBounds() const
{
    return ninePatch.getGlobalBounds();
}

void TextBox::setTexture(const sf::Texture& newTexture)
{
    ninePatch.setTexture(newTexture);
}

void TextBox::setTextureRect(const sf::Rect<int>& newRect)
{
    textureRect = newRect;
    updatePositions();
    updateTexCoords();
}

void TextBox::setTextureRect(int newLeft, int newTop, int newWidth, int newHeight)
{
    setTextureRect(sf::Rect<int>(newLeft, newTop, newWidth, newHeight));
}

void TextBox::setSize(const sf::Vector2<float>& newSize)
{
    width = newSize.x;
    height = newSize.y;
    ninePatch.setSize(newSize);
}

void TextBox::setSize(float newWidth, float newHeight)
{
    setSize(sf::Vector2<float>(newWidth, newHeight));
}

void TextBox::setColor(const sf::Color& color)
{
    ninePatch.setColor(color);
    verticesCursor[0].color = color;
    verticesCursor[1].color = color;
    verticesCursor[2].color = color;
    verticesCursor[3].color = color;
}

void TextBox::setBorder(float borderLeft, float borderTop, float borderRight, float borderBottom)
{
    ninePatch.setBorder(borderLeft, borderTop, borderRight, borderBottom);
    updatePositions();
    updateTexCoords();
}

void TextBox::setBorder(float border)
{
    ninePatch.setBorder(border);
    updatePositions();
    updateTexCoords();
}
/*
ClickableWidget::State TextBox::getInput()
{
    ClickableWidget::State curState = ClickableWidget::getInput();
    return curState;
}
*/
void TextBox::setFont(const sf::Font& font)
{
    text.setFont(font);
    setCursorPosition();
}

void TextBox::setCharSize(unsigned int charSize)
{
    text.setCharacterSize(charSize);
    setCursorPosition();
}

void TextBox::setLetterSpacingFactor(float letterSpacingFactor)
{
    text.setLetterSpacing(false, letterSpacingFactor);
    setCursorPosition();
}

void TextBox::setFillColor(const sf::Color& fillColor)
{
    text.setFillColor(fillColor);
}

void TextBox::setOutlineColor(const sf::Color outlineColor)
{
    text.setOutlineColor(outlineColor);
}

void TextBox::setSizeBack(const sf::Vector2<float>& sizeBack)
{
    text.setSizeBack(sizeBack);
}

void TextBox::setThickness(float thickness)
{
    text.setOutlineThickness(thickness);
}

void TextBox::setPositionText(float posX, float posY)
{
    positionText = sf::Vector2<float>(posX, posY);
    text.setPosition(positionText);
    setCursorPosition();
}

void TextBox::setSizeBorderSlide(float newSizeBorderSlide)
{
    sizeBorderSlide = newSizeBorderSlide;
}

void TextBox::setTextureCursor(const sf::Texture* newTextureCursor)
{
    textureCursor = newTextureCursor;
}

void TextBox::setTextureRectCursor(const sf::Rect<int>& newRect)
{
    textureRectCursor = newRect;
    updatePositionsCursor();
    updateTexCoordsCursor();
}

void TextBox::setTextureRectCursor(int newLeft, int newTop, int newWidth, int newHeight)
{
    setTextureRectCursor(sf::Rect<int>(newLeft, newTop, newWidth, newHeight));
}

void TextBox::setCursorPosition()
{
    if (text.getLocalBounds().width <= posMaxCursor.x - positionText.x)
    {
        positionTextOffset = sf::Vector2<float>(0.0f, 0.0f);
        if (chainText.getNbChar() == 0)
        {
            positionCursor = positionText;
        }
        else if (indexCursor == chainText.getNbChar())
        {
            positionCursor = sf::Vector2<float>(text.getLocalBounds().width, 0.0f) + positionCursorOffset;
        }
        else
        {
            positionCursor = sf::Vector2<float>(text.findCharacterPos(indexCursor).x, 0.0f);
        }
        text.setPosition(positionText + positionTextOffset);
    }
    else
    {
        //======================================================================
        // We position the cursor relatively to the text
        if (indexCursor == chainText.getNbChar()) // The cursor is at the end of the text
        {
            positionCursor = sf::Vector2<float>(text.getLocalBounds().width, 0.0f) + positionTextOffset + positionCursorOffset;
        }
        else
        {
            positionCursor = sf::Vector2<float>(text.findLocalCharacterPos(indexCursor).x, 0.0f) + positionTextOffset;
        }
        //======================================================================
        // If the cursor is too much to the right/left, we displace cursor AND text
        if (positionCursor.x > posMaxCursor.x) // The cursor is after the end of the box
        {
            float offset = posMaxCursor.x - positionCursor.x;
            positionTextOffset.x += offset;
            text.setPosition(positionText + positionTextOffset);
            positionCursor.x += offset;
        }
        else if (positionCursor.x < positionText.x) // The cursor is before the beginning of the box
        {
            float offset = positionText.x - positionCursor.x;
            positionTextOffset.x += offset;
            text.setPosition(positionText + positionTextOffset);
            positionCursor = positionText;
        }

        //======================================================================
        // If the there is unused space in the text box, we displace the text AND the cursor
        if (text.getLocalBounds().width + positionTextOffset.x <= posMaxCursor.x - positionText.x) // Unused space at the end
        {
            float offset = posMaxCursor.x - positionText.x - (text.getLocalBounds().width + positionTextOffset.x);
            positionTextOffset.x += offset;
            text.setPosition(positionText + positionTextOffset);
            positionCursor.x += offset;
        }
        else if (positionTextOffset.x > 0.0f) // Unused space at the beginning
        {
            float offset = -positionTextOffset.x;
            positionTextOffset.x += offset;
            text.setPosition(positionText + positionTextOffset);
            positionCursor.x += offset;
        }
    }
}

void TextBox::setCursorPositionOffset(float posX, float posY)
{
    positionCursorOffset = sf::Vector2<float>(posX, posY);
}

void TextBox::setCursorPositionMax(float posMaxX, float posMaxY)
{
    posMaxCursor = sf::Vector2<float>(posMaxX, posMaxY);
}

void TextBox::setPointerChainText()
{
    text.setChainText({&chainText});
}

void TextBox::updatePositions()
{

}

void TextBox::updateTexCoords()
{
    int posTex;
    switch (state)
    {
    case State::MOUSE_NOT_ON_WIDGET:
    {
        posTex = focused ? 2 : 0;
        break;
    }
    case State::MOUSE_CLICKED_NOT_ON_WIDGET:
    {
        posTex = focused ? 2 : 0;
        break;
    }
    case State::MOUSE_CLICKED_OUT_ON_WIDGET:
    {
        posTex = focused ? 2 : 1;
        break;
    }
    case State::MOUSE_ON_WIDGET:
    {
        posTex = focused ? 2 : 1;
        break;
    }
    case State::MOUSE_CLICKED:
    {
        posTex = 2;
        break;
    }
    case State::MOUSE_CLICKED_OUT_OF_WIDGET:
    {
        posTex = 2;
        break;
    }
    case State::CLICKED:
    {
        posTex = 2;
        break;
    }
    default:
    {
        posTex = 0;
        break;
    }
    }
    ninePatch.setTextureRect(textureRect + posTex*sf::Vector2<int>(textureRect.width, 0));
}

void TextBox::updatePositionsCursor()
{
    verticesCursor[0].position = sf::Vector2<float>(0.0f, 0.0f);
    verticesCursor[1].position = sf::Vector2<float>(0.0f, static_cast<float>(textureRectCursor.height));
    verticesCursor[2].position = sf::Vector2<float>(static_cast<float>(textureRectCursor.width), 0.0f);
    verticesCursor[3].position = sf::Vector2<float>(static_cast<float>(textureRectCursor.width), static_cast<float>(textureRectCursor.height));
}

void TextBox::updateTexCoordsCursor()
{
    float left   = static_cast<float>(textureRectCursor.left);
    float right  = left + static_cast<float>(textureRectCursor.width);
    float top    = static_cast<float>(textureRectCursor.top);
    float bottom = top + static_cast<float>(textureRectCursor.height);
    verticesCursor[0].texCoords = sf::Vector2<float>(left, top);
    verticesCursor[1].texCoords = sf::Vector2<float>(left, bottom);
    verticesCursor[2].texCoords = sf::Vector2<float>(right, top);
    verticesCursor[3].texCoords = sf::Vector2<float>(right, bottom);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(ninePatch, states);

    Window::setUiView(getPosition().x + ninePatch.getLeftBorder(),
                      getPosition().y + ninePatch.getTopBorder(),
                      ninePatch.getWidth() - ninePatch.getLeftBorder() - ninePatch.getRightBorder(),
                      ninePatch.getHeight() - ninePatch.getTopBorder() - ninePatch.getBottomBorder());
    Window::pushStateView(Window::IdView::UI);
    Window::setViewTarget(target);

    target.draw(text, states);

    Window::popStateView();
    Window::setViewTarget(target);

    states.texture = textureCursor;
    states.transform.translate(positionCursor);
    if (focused && frameCount % 60 < 30)
    {
        target.draw(verticesCursor.data(), 4, sf::PrimitiveType::TriangleStrip, states);
    }
}
