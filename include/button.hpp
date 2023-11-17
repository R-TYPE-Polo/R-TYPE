#include <SFML/Graphics.hpp>

class Button
{
public:
    Button(sf::RenderWindow&   window,
           const sf::Vector2f& size,
           const sf::Vector2f& position,
           const sf::Color&    fillColor,
           const sf::Color&    outlineColor,
           float               outlineThickness,
           const std::string&  textString,
           const sf::Font&     font,
           unsigned int        characterSize) :
    m_window(window),
    m_text(textString, font, characterSize)
    {
        m_button.setSize(size);
        m_button.setPosition(position);
        m_button.setFillColor(fillColor);

        m_button.setOutlineColor(outlineColor);
        m_button.setOutlineThickness(outlineThickness);

        sf::FloatRect textBounds = m_text.getLocalBounds();
        m_text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        m_text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
    }

    bool checkClick()
    {
        sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
        bool clicked = m_button.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if (clicked && !m_isClicked)
        {
            m_isClicked = true;
            return true;
        }
        else if (!clicked)
        {
            m_isClicked = false;
        }

        return false;
    }

    void draw()
    {
        m_window.draw(m_button);
        m_window.draw(m_text);
    }

private:
    sf::RectangleShape m_button;
    sf::RenderWindow&  m_window;
    sf::Text           m_text;
    bool               m_isClicked{false};
};