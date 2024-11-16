#include <SFML/Graphics.hpp>
#include <vector>


void updateLayer(sf::Sprite& spriteA, sf::Sprite& spriteB, float speed, float deltaTime, const sf::Texture& texture) {
    
    spriteA.move(-speed * deltaTime, 0);
    spriteB.move(-speed * deltaTime, 0);

   
    int textureWidth = static_cast<int>(texture.getSize().x);


    if (spriteA.getPosition().x <= -textureWidth) {
        spriteA.setPosition(spriteB.getPosition().x + textureWidth, 0);
    }
    if (spriteB.getPosition().x <= -textureWidth) {
        spriteB.setPosition(spriteA.getPosition().x + textureWidth, 0);
    }
}

int main() {
  
    sf::RenderWindow window(sf::VideoMode(592 , 272), "Parallax Effect");

  
    sf::Texture layer1Texture, layer2Texture, layer3Texture, layer4Texture;
    if (!layer1Texture.loadFromFile("background_1.png") ||
        !layer2Texture.loadFromFile("background_2.png") ||
        !layer3Texture.loadFromFile("background_3.png") ||
        !layer4Texture.loadFromFile("background_4.png")) {
        return -1;
    }

    sf::Sprite layer1A(layer1Texture), layer1B(layer1Texture);
    sf::Sprite layer2A(layer2Texture), layer2B(layer2Texture);
    sf::Sprite layer3A(layer3Texture), layer3B(layer3Texture);
    sf::Sprite layer4A(layer4Texture), layer4B(layer4Texture);


    layer1B.setPosition(layer1Texture.getSize().x, 0);
    layer2B.setPosition(layer2Texture.getSize().x, 0);
    layer3B.setPosition(layer3Texture.getSize().x, 0);
    layer4B.setPosition(layer4Texture.getSize().x, 0);


    const float speedLayer1 = 10.f; 
    const float speedLayer2 = 30.f;
    const float speedLayer3 = 50.f;
    const float speedLayer4 = 80.f; 


    sf::Clock clock;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();


        updateLayer(layer1A, layer1B, speedLayer1, deltaTime, layer1Texture);
        updateLayer(layer2A, layer2B, speedLayer2, deltaTime, layer2Texture);
        updateLayer(layer3A, layer3B, speedLayer3, deltaTime, layer3Texture);
        updateLayer(layer4A, layer4B, speedLayer4, deltaTime, layer4Texture);

        window.clear();


        window.draw(layer1A);
        window.draw(layer1B);
        window.draw(layer2A);
        window.draw(layer2B);
        window.draw(layer3A);
        window.draw(layer3B);
        window.draw(layer4A);
        window.draw(layer4B);


        window.display();
    }

    return 0;
}