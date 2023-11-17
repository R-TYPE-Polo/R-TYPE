#include "menu/introMenu/introMenu.hpp"

#include "button.hpp"
#include "music/music.hpp"

#include <iostream>

Menu::Menu()
{
    this->m_menuLogoTexture.loadFromFile(PATH_TEXTURE_MENU_LOGO);
    this->m_menuLogoSprite.setTexture(this->m_menuLogoTexture);
    this->m_menuTitleTexture.loadFromFile(PATH_TEXTURE_MENU_TITLE);
    this->m_menuTitleSprite.setTexture(this->m_menuTitleTexture);
    this->m_burnCityFont.loadFromFile(PATH_FONT_MENU);

    //// Trouver un moyen pour rendre ça plus beau
    m_menuLogoSprite.setScale(260 / m_menuLogoSprite.getLocalBounds().width, 299 / m_menuLogoSprite.getLocalBounds().height);
    m_menuLogoSprite.setPosition(800 / 2 - 260 / 2, 50);

    m_menuTitleSprite.setScale(395 / m_menuTitleSprite.getLocalBounds().width,
                               53 / m_menuTitleSprite.getLocalBounds().height);
    m_menuTitleSprite.setPosition(800 / 2 - 395 / 2, 600 / 1.5 - 53 / 2);

    this->m_burnCityText.setString("Press ENTER to burn the city");
    this->m_burnCityText.setFont(this->m_burnCityFont);
    this->m_burnCityText.setCharacterSize(30);
    this->m_burnCityText.setFillColor(sf::Color::White);
    this->m_burnCityText.setPosition(800 / 2 - this->m_burnCityText.getGlobalBounds().width / 2,
                             600 / 1.2 - this->m_burnCityText.getGlobalBounds().height / 2);
    this->onMenu = true;
}

sf::Clock Menu::blinkingText(sf::Clock mClock, sf::Time mElapsed) {
    if (mElapsed.asMilliseconds() > 500)
    {
        this->m_burnCityText.setFillColor(
            this->m_burnCityText.getFillColor() == sf::Color::Transparent ? sf::Color::White : sf::Color::Transparent);
        mClock.restart();
    }
    return mClock;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_menuLogoTexture;
    states.texture = &m_menuTitleTexture;
    target.draw(m_menuLogoSprite, states);
    target.draw(m_menuTitleSprite, states);
    target.draw(m_burnCityText, states);
}

/// choice menu ///
ChoiceMenu::ChoiceMenu()
{
    this->m_logoSamuraiTexture.loadFromFile(PATH_TEXTURE_MENU_LOGO);
    this->m_logoSamuraiSprite.setTexture(this->m_logoSamuraiTexture);

    //// Trouver un moyen pour rendre ça plus beau
    m_logoSamuraiSprite.setScale(87 / m_logoSamuraiSprite.getLocalBounds().width, 100 / m_logoSamuraiSprite.getLocalBounds().height);
    m_logoSamuraiSprite.setPosition(20, 20);

    this->onChoice = false;
}

void ChoiceMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_logoSamuraiTexture;
    target.draw(m_logoSamuraiSprite, states);
}
