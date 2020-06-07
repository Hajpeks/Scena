#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<cmath>
#include <vector>
#include<ctime>

std::vector<sf::Sprite> generateWalls(sf::Texture& texture) {
    std::vector<sf::Sprite> walls;
    int position_x=0;
    int position_y=-130;
    int x=0;
    int y=0;

for(int a=0;a<4;a++)
{
     position_y+=220;
    for(int i=0;i<6;i++)
    {
      position_x+=200;
        sf::Sprite w1;
            w1.setTexture(texture);
            w1.setPosition(position_x, position_y);
            w1.setScale(0.5,0.7);
            w1.setTextureRect(sf::IntRect(0, 0, w1.getGlobalBounds().width , w1.getGlobalBounds().height));
            walls.emplace_back(w1);
    }
    position_x=0;
}
    return walls;
}

class Player
    : public sf::Sprite
{
public:



      float framerate = 0.f;
      int width = 0;


      sf::IntRect startRect;
      sf::IntRect currentRect;
      sf::IntRect endRect;

      float timer = 0.f;
      sf::Vector2f before;

      //movement variables
      sf::Vector2f direction;
      sf::Vector2f velocity;
      float angel;
      float rotation;
      float rotationSpeed = 180.f;

      float maxVelocity = 200.f;
      float acceleration = 4800.f;
      float deceleration = 100;

      bool grounded = false;

      bool prime=false;


      sf::RectangleShape hitbox;

    Player(sf::Texture& animationSheet) {
        this->setTexture(animationSheet);
        this->direction = sf::Vector2f(0, 1);
        this->rotation = 0;

        this->hitbox.setOutlineColor(sf::Color::Red);
        this->hitbox.setOutlineThickness(3.f);
       this->hitbox.setFillColor(sf::Color::Transparent);
    }

    void addAnimation(const float framerate,
        const int start_frame_x, const int start_frame_y,
        const int length, const int frame_width, const int frame_height) {

        //start_frame_x - on which column animation starts
        //start_frame_y - on which row animation stars
        //length - how many frames there are in animation
        //frame_width/height - dimesns of single frame

        this->framerate = framerate;
        this->width = frame_width;

        this->startRect = sf::IntRect(start_frame_x * frame_width, start_frame_y * frame_height,frame_width, frame_height);
        this->currentRect = this->startRect;

        this->endRect = sf::IntRect(
            start_frame_x * frame_width + frame_width * (length - 1),
            (start_frame_y)*frame_height,
            frame_width, frame_height);

        this->setTextureRect(this->startRect);

    }

    void playAnimation(const float& dt) {
        this->timer += dt;

        if (this->timer > 1 / this->framerate) {
            this->timer = 0.f;

            if (this->currentRect != this->endRect) {
                this->currentRect.left += this->width;
            }
            else {
                this->currentRect = this->startRect;
            }
            this->setTextureRect(this->currentRect);
        }
    }




    void moveSprite(const int dir, const float& dt) {
        //incrasing speed in the inputed dirction
        //this->velocity += dir * (dt * this->acceleration);
        this->move(this->direction * (this->maxVelocity *dir * dt));

    }

    void rotateSprite(const int dir, const float& dt) {
        float rot = this->rotationSpeed * dir * dt;
        this->rotation += rot;
        this->rotate(rot);
        this->direction = rotateVector(this->direction, rot);
         this->angel=rot;
    }

    void updateCollisions(std::vector<sf::Sprite>& platforms, const float& dt) {

        sf::FloatRect playerBounds = this->getGlobalBounds();

        for (auto& platform : platforms) {

            sf::FloatRect wallBounds = platform.getGlobalBounds();
            if (wallBounds.intersects(playerBounds)) {

                //Bottom collision
                if (playerBounds.top < wallBounds.top
                    && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                    && playerBounds.left < wallBounds.left + wallBounds.width
                    && playerBounds.left + playerBounds.width > wallBounds.left
                    )
                {

                    this->move(0, wallBounds.top - (playerBounds.top + playerBounds.height));
                }

                //Top Collision
                else if (playerBounds.top > wallBounds.top
                    && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                    && playerBounds.left < wallBounds.left + wallBounds.width
                    && playerBounds.left + playerBounds.width > wallBounds.left
                    )
                {

                    this->move(0,  wallBounds.top + wallBounds.height - playerBounds.top  );
                }

                //Right collisin
                if (playerBounds.left < wallBounds.left
                    && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                    && playerBounds.top < wallBounds.top + wallBounds.height
                    && playerBounds.top + playerBounds.height > wallBounds.top
                    )
                {

                    this->move(wallBounds.left - (playerBounds.left + playerBounds.width), 0);
                }

                //Left Collision
                else if (playerBounds.left > wallBounds.left
                    && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                    && playerBounds.top < wallBounds.top + wallBounds.height
                    && playerBounds.top + playerBounds.height > wallBounds.top
                    )
                {

                    this->move(wallBounds.left + wallBounds.width - (playerBounds.left ), 0);
                }
            }


        }
            }

    void update(const float& dt) {

//        this->hitbox.setPosition(this->getPosition());
//        this->hitbox.setOrigin(this->getOrigin());
        this->hitbox.setPosition(this->getGlobalBounds().left,this->getGlobalBounds().top);
        this->hitbox.setSize(sf::Vector2f(this->getGlobalBounds().width,this->getGlobalBounds().height));


        if (this->velocity.x > 0.f) { //if going in right diraction

            //deceleration
            this->velocity.x -= this->deceleration * dt;
            if (this->velocity.x < 0.f)
                this->velocity.x = 0.f;

            //max velocity check
            if (this->velocity.x > this->maxVelocity)
                this->velocity.x = maxVelocity;
        }
        else if (this->velocity.x < 0.f) { //if going left

            //decelaretion
            this->velocity.x += deceleration * dt;
            if (this->velocity.x > 0.f)
                this->velocity.x = 0.f;

            //max velocity check
            if (this->velocity.x < -this->maxVelocity)
                this->velocity.x = -this->maxVelocity;
        }

        if (this->velocity.y > 0.f) { //if going down
        //deceleration y positive
            this->velocity.y -= this->deceleration * dt;
            if (this->velocity.y < 0.f)
                this->velocity.y = 0.f;

            //max velocity check
            if (this->velocity.y > this->maxVelocity)
                this->velocity.y = maxVelocity;
        }
        else if (this->velocity.y < 0.f) { //id going up
            //decelaretion y negative
            this->velocity.y += deceleration * dt;
            if (this->velocity.y > 0.f)
                this->velocity.y = 0.f;

            //max velocity chechk y negative
            if (this->velocity.y < -this->maxVelocity)
                this->velocity.y = -this->maxVelocity;
        }

        //std::cout << this->velocity.x << " | " << this->velocity.y << "\n";
        this->move(this->velocity * dt);
    }



    //////////////////////////////////////////////////////////////////////////////////////////
    sf::Vector2f rotateVector(const sf::Vector2f& org, const float rotation)
    {
        sf::Vector2f rotated;
        double deg = (M_PI / 180) * rotation;

        rotated.x = cos(deg) * org.x - sin(deg) * org.y;
        rotated.y = sin(deg) * org.x + cos(deg) * org.y;
        return normalize(rotated);

    }


    sf::Vector2f normalize(sf::Vector2f& vector)
    {
        return vector / (float)sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////
};
std::vector<Player> bomba;
std::vector<Player>bomba1;






void check_bomb_collision(Player &hero1,sf::Texture &heroAnimationSheet1,std::vector<sf::Sprite> walls){
    for(auto enemy=bomba.begin();enemy!=bomba.end();)
    {
        bool add=false;
        //auto b=*enemy;
        if((*enemy).getGlobalBounds().intersects(hero1.getGlobalBounds()))
        {
           enemy= bomba.erase(enemy);
         heroAnimationSheet1.loadFromFile("KV-2_previewdestroyed.png");
         add=true;
        }
         if(add==false){
        for(auto wall:walls){

            if((*enemy).getGlobalBounds().intersects(wall.getGlobalBounds())&&add==false){

                enemy= bomba.erase(enemy);
                add=true;
            }}};

if(add==false){
            enemy++;}}}










void check_bomb_collision1(Player &hero,sf::Texture &heroAnimationSheet1,std::vector<sf::Sprite> walls){
    for(auto enemy=bomba1.begin();enemy!=bomba1.end();)
    {
        bool add=false;
        //auto b=*enemy;
        if((*enemy).getGlobalBounds().intersects(hero.getGlobalBounds()))
        {
           enemy= bomba1.erase(enemy);
         heroAnimationSheet1.loadFromFile("KV-2_previewdestroyed.png");
         add=true;
        }
         if(add==false){
        for(auto wall:walls){

            if((*enemy).getGlobalBounds().intersects(wall.getGlobalBounds())&&add==false){

                enemy= bomba1.erase(enemy);
                add=true;
            }}};

if(add==false){
            enemy++;}}}











int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1500, 900), "Window");
    window.setVerticalSyncEnabled(true);
    sf::Event sfEvent;
    sf::Clock clock;
    float dt;

    //Making walls
    sf::Texture wallTexture;
    if (!wallTexture.loadFromFile("wall111.png")) { return -1; }

    wallTexture.setRepeated(true);


    std::vector<sf::Sprite> walls = generateWalls(wallTexture);

    //Background
    sf::Texture grassTexture;
    if (!grassTexture.loadFromFile("grass.jpg")) { return -1; }
    grassTexture.setRepeated(true);
    sf::Sprite wall;
    wall.setTexture(grassTexture);
    wall.setPosition(0, 0);
    wall.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    //Player character
    sf::Texture heroAnimationSheet;

    if (!heroAnimationSheet.loadFromFile("M-6_preview.png")) { return -1; };

    sf::Texture heroAnimationSheet1;
    if (!heroAnimationSheet1.loadFromFile("M-6_preview.png")) { return -1; };



    Player hero(heroAnimationSheet);
 Player hero1(heroAnimationSheet1);
    hero.setPosition(30, 30);
    hero1.setPosition(300, 300);



    hero.setScale(0.4, 0.4);
     hero1.setScale(0.4, 0.4);

    hero.setOrigin(138, 138);
    hero1.setOrigin(60, 127);


    sf::Texture pocisk;
    if (!pocisk.loadFromFile("pocisk.png")) { return -1; };
    Player ogien(pocisk);
    Player ogien1(pocisk);

    int left = 0;
    int right = 0;
    int down = 0;
    int up = 0;
    float a = 0;
    //float x = 0; float y = 0;
    bool laduj=false;
    //Main gameplay loop
    while (window.isOpen()) {

        while (window.pollEvent(sfEvent)) {
            if (sfEvent.type == sf::Event::Closed) {
                window.close();
            }
        }
        dt = clock.restart().asSeconds();





        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

                 hero1.rotateSprite(-1, dt);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
              hero1.rotateSprite(1, dt);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
         hero1.moveSprite(1, dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        hero1.moveSprite(-1, dt);
        }



        //Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            hero.moveSprite(-1, dt);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            hero.moveSprite(1, dt);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            hero.rotateSprite(1, dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            hero.rotateSprite(-1, dt);
        }

        //        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        //          float  power=10;
        //                   float pices=power-power/sqrt(2);
        //                   int b=a;
        //                   float aa=(b)%90;
        //                   float mod=(aa<=45)?aa/45*pices:(aa/45-1)*pices;
        //                   int qrt=b/90;
        //                   float proportion=aa/90;

        //                   power+=mod;

        //                   if(qrt==0){x=power*proportion;y=-power*(1-proportion);}
        //                   if(qrt==1){x=power*(1-proportion);y=power*proportion;}
        //                   if(qrt==2){x=-power*proportion;y=power*(1-proportion);}
        //                   if(qrt==3){x=-power*(1-proportion);y=-power*proportion;}
        //              sf::Vector2f velocity1;
        //              velocity1.x=x;
        //              velocity1.y=y;
        //                 hero.moveSprite(velocity1,dt);
        //                }



                //Updating player
        hero.playAnimation(dt);
        hero.updateCollisions(walls, dt);
        hero.update(dt);

        hero1.playAnimation(dt);
        hero1.updateCollisions(walls, dt);
        hero1.update(dt);

        //Rendering
        window.clear();

        window.draw(wall);

        window.draw(hero);
        window.draw(hero1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        hero.prime=true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {

        if(hero.prime==true){
            ogien.setPosition(hero.getPosition());
            ogien.setScale(0.06,0.06);
            ogien.direction=hero.direction;
            ogien.velocity.x=hero.velocity.x+10;
             ogien.velocity.y=hero.velocity.y+10;
             ogien.setOrigin(24,25);


           bomba.emplace_back(ogien);
           hero.prime=false;
        }}




        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        hero1.prime=true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

        if(hero1.prime==true){
            ogien1.setPosition(hero1.getPosition());
            ogien1.setScale(0.06,0.06);
            ogien1.direction=hero1.direction;
            ogien1.velocity.x=hero1.velocity.x+10;
             ogien1.velocity.y=hero1.velocity.y+10;
             ogien1.setOrigin(24,25);


           bomba1.emplace_back(ogien1);
           hero1.prime=false;
        }








        }
        for (auto &b : bomba) {
            b.moveSprite(3,dt);
            window.draw(b);
            window.draw(b.hitbox);

}
        for (auto &b : bomba1) {
            b.moveSprite(3,dt);
            window.draw(b);
            window.draw(b.hitbox);

}

        if(!bomba.empty()||!bomba1.empty())
        { check_bomb_collision(hero1,heroAnimationSheet1,walls);
            check_bomb_collision1(hero,heroAnimationSheet,walls);
        }
        window.draw(hero.hitbox);
window.draw(hero1.hitbox);
for (auto wall : walls) {
    window.draw(wall);
}

        window.display();
    }

    return 0;

}
