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
   std::vector<sf::Sprite> _blocks;

public:

    Scene(sf::Texture &texture,sf::Texture &Block_Texture): window_(sf::VideoMode(1920,1080), "SCENE")
    {
      this->genereteCactus(texture);
      this->generateBlocks(Block_Texture);
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
         _blocks.emplace_back(block1);

         sf::Sprite block2;
         block2.setTexture(block_Texture);
         block2.setPosition(930,650);
         block2.setScale(0.7,0.7);
         _blocks.emplace_back(block2);

         sf::Sprite block3;
         block3.setTexture(block_Texture);
         block3.setPosition(930,50);
         block3.setScale(0.7,0.7);
         _blocks.emplace_back(block3);

         sf::Sprite block4;
         block4.setTexture(block_Texture);
         block4.setPosition(930,950);
         block4.setScale(0.7,0.7);
         _blocks.emplace_back(block4);

         return _blocks;
     }
         void loadtexture()
         {
             sf::Texture Cactus;
             if (!Cactus.loadFromFile("cactus1.png")) { throw("couldn't retudn"); }

             sf::Texture Blocks;
             if (!Blocks.loadFromFile("fence.png")) { throw("shit happens"); }
         }


    void draw()
    {
        window_.clear();

        for(auto &el: _cactus)
        {
            window_.draw(el);
        }
        for(auto &el2: _blocks)
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

int main()
{

    sf::Texture Cactus;
    if (!Cactus.loadFromFile("cactus1.png")) { return -1; }

    sf::Texture Blocks;
    if (!Blocks.loadFromFile("fence.png")) { return -1; }

    Scene ob(Cactus,Blocks);
    ob.loop();



    return 0;

}
