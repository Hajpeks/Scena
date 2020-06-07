#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>


class Scene
{
private:
   sf::RenderWindow window_;
   std::vector<sf::Sprite> _cactus;
   std::vector<sf::Sprite> _fences;
   std::vector<sf::Sprite> _background_screens;

public:

    Scene(sf::Texture &texture,sf::Texture &Block_Texture,sf::Texture &wooden,sf::Texture &blue,sf::Texture &red)
        : window_(sf::VideoMode(1920,1080), "SCENE", sf::Style::Close | sf::Style::Titlebar)
    {
      window_.setVerticalSyncEnabled(true);

      this->genereteCactus(texture);
      this->generateBlocks(Block_Texture);
      this->generate_bacground(wooden,blue,red);
    }
    ~Scene()
    {

    };

    std::vector<sf::Sprite>genereteCactus(sf::Texture &texture)
    {
      sf::Sprite cactus1;
      cactus1.setTexture(texture);
      cactus1.setPosition(400,200);
      cactus1.setScale(0.5,0.5);
      _cactus.emplace_back(cactus1);

      sf::Sprite cactus2;
      cactus2.setTexture(texture);
      cactus2.setPosition(1472,200);
      cactus2.setScale(0.5,0.5);
      _cactus.emplace_back(cactus2);

      sf::Sprite cactus3;
      cactus3.setTexture(texture);
      cactus3.setPosition(400,500);
      cactus3.setScale(0.5,0.5);
      _cactus.emplace_back(cactus3);

      sf::Sprite cactus4;
      cactus4.setTexture(texture);
      cactus4.setPosition(1472,500);
      cactus4.setScale(0.5,0.5);
      _cactus.emplace_back(cactus4);

      sf::Sprite cactus5;
      cactus5.setTexture(texture);
      cactus5.setPosition(400,800);
      cactus5.setScale(0.5,0.5);
      _cactus.emplace_back(cactus5);

      sf::Sprite cactus6;
      cactus6.setTexture(texture);
      cactus6.setPosition(1472,800);
      cactus6.setScale(0.5,0.5);
      _cactus.emplace_back(cactus6);

      return _cactus;
    }
      std::vector<sf::Sprite>generateBlocks(sf::Texture &block_Texture)
     {
         sf::Sprite block1;
         block1.setTexture(block_Texture);
         block1.setPosition(930,350);
         block1.setScale(0.7,0.7);
         _fences.emplace_back(block1);

         sf::Sprite block2;
         block2.setTexture(block_Texture);
         block2.setPosition(930,650);
         block2.setScale(0.7,0.7);
         _fences.emplace_back(block2);

         sf::Sprite block3;
         block3.setTexture(block_Texture);
         block3.setPosition(930,50);
         block3.setScale(0.7,0.7);
         _fences.emplace_back(block3);

         sf::Sprite block4;
         block4.setTexture(block_Texture);
         block4.setPosition(930,950);
         block4.setScale(0.7,0.7);
         _fences.emplace_back(block4);

         return _fences;
     }

     std::vector<sf::Sprite>generate_bacground(sf::Texture &Wooden,sf::Texture &Blue,sf::Texture &Red)
     {


         sf::Sprite Red_Background;
         Red_Background.setTexture(Red);
         Red_Background.setPosition(0,0);
         Red_Background.setTextureRect(sf::IntRect(0,0,1920,1080));
         _background_screens.emplace_back(Red_Background);

         sf::Sprite Blue_Background;
         Blue_Background.setTexture(Blue);
         Blue_Background.setPosition(0,0);
         Blue_Background.setTextureRect(sf::IntRect(0,0,1920,1080));
         _background_screens.emplace_back(Blue_Background);

         sf::Sprite wooden_background;
         wooden_background.setTexture(Wooden);
         wooden_background.setPosition(0,0);
         wooden_background.setTextureRect(sf::IntRect(0,0,1920,1080));
         _background_screens.emplace_back(wooden_background);


         return _background_screens;

     }


    void draw()
    {
        window_.clear();

        for(auto &el3:_background_screens)
        {
            window_.draw(el3);
        }
        for(auto &el: _cactus)
        {
            window_.draw(el);
        }
        for(auto &el2: _fences)
        {
            window_.draw(el2);
        }

        window_.display();
    }

    void loop()
    {
        sf::Event sfEvent;
        while (window_.isOpen()) {

            while (window_.pollEvent(sfEvent)) {
                if (sfEvent.type == sf::Event::Closed) {
                    window_.close();
                }
            }

        this->draw();
        }
    }
};
//         void loadtexture()
//         {
//             sf::Texture Cactus;
//             if (!Cactus.loadFromFile("cactus1.png")) { throw("couldn't retudn"); }

//             sf::Texture Blocks;
//             if (!Blocks.loadFromFile("fence.png")) { throw("shit happens"); }
//         }

int main()
{

    sf::Texture Wooden_Backround;
    Wooden_Backround.setRepeated(true);
    if (!Wooden_Backround.loadFromFile("drewniane_tlo.png")) { return -1; }

    sf::Texture Blue_Background;
    Blue_Background.setRepeated(true);
    if (!Blue_Background.loadFromFile("niebieskie_tlo.png")) { return -1; }

    sf::Texture Red_Background;
    Red_Background.setRepeated(true);
    if (!Red_Background.loadFromFile("czerwone_tlo.png")) { return -1; }


    sf::Texture Cactus;
    Cactus.setSrgb(true);
    if (!Cactus.loadFromFile("cactus1.png")) { return -1; }

    sf::Texture Blocks;
    Blocks.setSrgb(true);
    if (!Blocks.loadFromFile("fence.png")) { return -1; }


    Scene ob(Cactus,Blocks,Wooden_Backround,Blue_Background,Red_Background);
    //ob.generate_bacground(Wooden_Backround,Blue_Background,Red_Background);
    ob.loop();




    return 0;

}
